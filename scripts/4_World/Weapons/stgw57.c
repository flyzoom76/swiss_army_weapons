class stgw57_Base : RifleBoltLock_Base
{
	override RecoilBase SpawnRecoilObject()
	{
		return new M4a1Recoil(this);
	}

	// --- grenade launch tracking ---
	private bool       m_GrenadeMonitorActive = false;
	private int        m_PrevAmmoCount        = -1;
	private Object     m_ActiveProjectile     = null;
	private vector     m_LaunchPos;
	private PlayerBase m_Owner                = null;

	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);

		if (item.IsKindOf("LongrangeOptic"))
			SetSimpleHiddenSelectionState(1, false);

		if (slot_name == "weaponGrenadeStgw57" && item.IsKindOf("StGw57_Grenade_Frag"))
		{
			m_GrenadeMonitorActive = true;
			m_PrevAmmoCount = CountTreibladungAmmo();
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(PollTreibladungFire, 200, true);
		}

		// Treibladung magazine inserted while grenade is already on the barrel
		if (m_GrenadeMonitorActive && slot_name == "magazine")
			m_PrevAmmoCount = CountTreibladungAmmo();
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		if (item.IsKindOf("LongrangeOptic"))
			SetSimpleHiddenSelectionState(1, true);

		// Grenade removed – stop loop
		if (slot_name == "weaponGrenadeStgw57")
		{
			m_GrenadeMonitorActive = false;
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(PollTreibladungFire);
		}

		// Treibladung magazine removed – reset counter
		if (m_GrenadeMonitorActive && slot_name == "magazine")
			m_PrevAmmoCount = 0;
	}

	// Returns how many Treibladung rounds are currently in the loaded magazine
	private int CountTreibladungAmmo()
	{
		Magazine mag = Magazine.Cast(FindAttachmentBySlotName("magazine"));
		if (mag && mag.IsKindOf("Mag_stgw57_24rnd_treib"))
			return mag.GetAmmoCount();
		return 0;
	}

	// Runs every 200 ms while a grenade is attached
	private void PollTreibladungFire()
	{
		if (!m_GrenadeMonitorActive) return;

		int current = CountTreibladungAmmo();
		if (m_PrevAmmoCount > 0 && current < m_PrevAmmoCount)
			LaunchAttachedGrenade();
		m_PrevAmmoCount = current;
	}

	private void LaunchAttachedGrenade()
	{
		EntityAI grenadeAtt = FindAttachmentBySlotName("weaponGrenadeStgw57");
		if (!grenadeAtt || !grenadeAtt.IsKindOf("StGw57_Grenade_Frag")) return;

		// Store player reference while hierarchy is still intact
		m_Owner = GetHierarchyRootPlayer();

		vector muzzleWorld = ModelToWorld(GetSelectionPositionLS("usti hlavne"));
		vector barrelDir   = GetDirection();

		m_LaunchPos = muzzleWorld;
		Object spawnedObj = GetGame().CreateObject("Bullet_stgw57_grenade_frag_obj", muzzleWorld, false, true, false);
		m_ActiveProjectile = spawnedObj;

		EntityAI projectile = EntityAI.Cast(spawnedObj);
		if (projectile)
		{
			vector mat[4];
			Math3D.DirectionAndUpMatrix(barrelDir, vector.Up, mat);
			mat[3] = muzzleWorld;
			projectile.SetTransform(mat);

			dBodyApplyImpulse(projectile, barrelDir * 80.0);
		}

		// Grenade consumed – triggers EEItemDetached which stops the loop
		GetGame().ObjectDelete(grenadeAtt);

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DetonateProjectile, 6000, false);
	}

	private void DetonateProjectile()
	{
		if (!m_Owner) return;

		vector pos;
		if (m_ActiveProjectile)
		{
			pos = m_ActiveProjectile.GetPosition();
			GetGame().ObjectDelete(m_ActiveProjectile);
			m_ActiveProjectile = null;
		}
		else
			pos = m_Owner.GetPosition();

		SEffectManager.PlaySound("stgw57_Grenade_Explosion_SoundSet", pos, false, false);

		float radius = 10.0;
		float d      = vector.Distance(pos, m_Owner.GetPosition());
		if (d <= radius)
		{
			float dmg = Math.Lerp(100.0, 5.0, d / radius);
			float hp  = m_Owner.GetHealth("GlobalHealth", "Health");
			m_Owner.SetHealth("GlobalHealth", "Health", Math.Max(0, hp - dmg));
		}

		m_Owner = null;
	}

	// Cleanup if weapon is deleted while monitoring
	override void EEDelete(EntityAI parent)
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(PollTreibladungFire);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(DetonateProjectile);
		super.EEDelete(parent);
	}
};

class stgw57 : stgw57_Base {};
