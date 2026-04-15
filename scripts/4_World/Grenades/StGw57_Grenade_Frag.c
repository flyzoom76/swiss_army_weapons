class StGw57_Grenade_Frag extends ItemBase
{
	private bool   m_IsProjectile = false;
	private bool   m_Detonated    = false;
	private vector m_Velocity;

	// Called server-side by stgw57 when a Treibladung is fired with a grenade attached
	void ActivateAsProjectile(vector velocity)
	{
		m_IsProjectile = true;
		m_Velocity     = velocity;
		// Update flight every 50 ms
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateFlight, 50, true);
	}

	private void UpdateFlight()
	{
		if (!m_IsProjectile || m_Detonated) return;
		if (!GetGame().IsServer()) return;

		const float DT = 0.05; // 50 ms time step

		// Apply gravity
		m_Velocity[1] = m_Velocity[1] - 9.81 * DT;

		vector pos    = GetPosition();
		vector newPos = pos + m_Velocity * DT;

		// Terrain contact check
		float groundY = GetGame().SurfaceY(newPos[0], newPos[2]);
		if (newPos[1] <= groundY)
		{
			newPos[1] = groundY;
			SetPosition(newPos);
			Detonate();
			return;
		}

		SetPosition(newPos);

		// Rotate grenade to face direction of travel
		SetOrientation(m_Velocity.VectorToAngles());
	}

	void Detonate()
	{
		if (m_Detonated) return;
		m_Detonated    = true;
		m_IsProjectile = false;

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(UpdateFlight);

		vector pos    = GetPosition();
		float  radius = 10.0;

		array<Object> objects = new array<Object>();
		GetGame().GetObjectsAtPosition(pos, radius, objects, null);

		foreach (Object obj : objects)
		{
			if (!obj.IsInherited(PlayerBase)) continue;
			float d = vector.Distance(pos, obj.GetPosition());
			if (d > radius) continue;
			// Linear falloff: 100 damage at ground zero, 5 at edge
			float dmg = Math.Lerp(100.0, 5.0, d / radius);
			obj.ProcessDirectDamage(DT_CLOSE_COMBAT, null, "Torso", "Explosion_Heavy", pos, dmg);
		}

		GetGame().ObjectDelete(this);
	}

	// Cleanup timer if the object is deleted externally (e.g. admin tool)
	override void EEDelete(EntityAI parent)
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(UpdateFlight);
		super.EEDelete(parent);
	}
};
