class StGw57_Grenade_Frag extends ItemBase
{
	private bool m_IsProjectile = false;
	private bool m_Detonated    = false;
	private vector m_PrevPos;
	private int m_StillCount = 0;

	// Called server-side by stgw57.EEFired when a Treibladung is fired with a grenade attached
	void ActivateAsProjectile(vector velocity)
	{
		m_IsProjectile = true;
		m_PrevPos      = GetPosition();

		SetDynamicPhysicsLifeTime(-1);
		dBodySetVelocity(this, velocity);

		// Start impact polling (150 ms interval)
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(CheckImpact, 150, true);
	}

	private void CheckImpact()
	{
		if (!m_IsProjectile || m_Detonated) return;
		if (!GetGame().IsServer()) return;

		vector curPos = GetPosition();
		float moved   = vector.Distance(curPos, m_PrevPos);

		if (moved < 0.05)
		{
			m_StillCount++;
			if (m_StillCount >= 2)
			{
				Detonate();
				return;
			}
		}
		else
		{
			m_StillCount = 0;
		}

		m_PrevPos = curPos;
	}

	void Detonate()
	{
		if (m_Detonated) return;
		m_Detonated    = true;
		m_IsProjectile = false;

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(CheckImpact);

		vector pos    = GetPosition();
		float  radius = 10.0;

		// Damage all players within blast radius
		array<Object> objects = new array<Object>();
		GetGame().GetObjectsAtPosition(pos, radius, objects, null);

		foreach (Object obj : objects)
		{
			if (!obj.IsInherited(PlayerBase)) continue;

			float d   = vector.Distance(pos, obj.GetPosition());
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
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(CheckImpact);
		super.EEDelete(parent);
	}
};
