class stgw57_Base : RifleBoltLock_Base
{
	override RecoilBase SpawnRecoilObject()
	{
		return new M4a1Recoil(this);
	}

	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);
		if (item.IsKindOf("LongrangeOptic"))
		{
			SetSimpleHiddenSelectionState(1, false);
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
		if (item.IsKindOf("LongrangeOptic"))
		{
			SetSimpleHiddenSelectionState(1, true);
		}
	}

	override void EEFired(string ammoType, string muzzleType, string mode)
	{
		super.EEFired(ammoType, muzzleType, mode);

		if (!GetGame().IsServer()) return;
		if (ammoType != "Bullet_750_treib") return;

		EntityAI grenadeAtt = FindAttachmentBySlotName("weaponGrenadeStgw57");
		if (!grenadeAtt || !grenadeAtt.IsKindOf("StGw57_Grenade_Frag")) return;

		// Spawn position at muzzle, direction from barrel
		vector muzzleWorld = ModelToWorld(GetSelectionPositionLS("usti hlavne"));
		vector barrelDir   = GetBarrelDir();

		StGw57_Grenade_Frag grenade = StGw57_Grenade_Frag.Cast(
			GetGame().CreateObjectEx("StGw57_Grenade_Frag", muzzleWorld, ECE_CREATEPHYSICS | ECE_DYNAMIC_PHYSICS)
		);

		if (grenade)
		{
			grenade.ActivateAsProjectile(barrelDir * 80.0);
		}

		// Grenade is consumed when fired
		GetGame().ObjectDelete(grenadeAtt);
	}
};

class stgw57 : stgw57_Base {};
