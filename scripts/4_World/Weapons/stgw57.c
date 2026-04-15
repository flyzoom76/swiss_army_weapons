class stgw57_Base : RifleBoltLock_Base
{
	override RecoilBase SpawnRecoilObject()
	{
		return new M4a1Recoil(this);
	}

	// --- grenade launch tracking ---
	private bool m_GrenadeMonitorActive = false;
	private int  m_PrevAmmoCount        = -1;

	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);

		if (item.IsKindOf("LongrangeOptic"))
			SetSimpleHiddenSelectionState(1, false);

		if (!GetGame().IsServer()) return;

		// Grenade attached – start fire-detection loop
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

		if (!GetGame().IsServer()) return;

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

		vector muzzleWorld = ModelToWorld(GetSelectionPositionLS("usti hlavne"));
		vector barrelDir   = GetBarrelDir();

		Object spawnedObj = GetGame().CreateObjectEx("StGw57_Grenade_Frag", muzzleWorld, ECE_NONE);
		StGw57_Grenade_Frag grenade = StGw57_Grenade_Frag.Cast(spawnedObj);
		if (grenade)
			grenade.ActivateAsProjectile(barrelDir * 80.0);

		// Grenade consumed – triggers EEItemDetached which stops the loop
		GetGame().ObjectDelete(grenadeAtt);
	}

	// Cleanup if weapon is deleted while monitoring
	override void EEDelete(EntityAI parent)
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(PollTreibladungFire);
		super.EEDelete(parent);
	}
};

class stgw57 : stgw57_Base {};
