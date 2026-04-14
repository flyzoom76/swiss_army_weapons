class stgw57_Base : RifleBoltLock_Base
{
	override RecoilBase SpawnRecoilObject()
	{
		return new M4a1Recoil(this);
	}

	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);
		Print("[StGw57] EEItemAttached: " + item.GetType());
		if (item.IsKindOf("LongrangeOptic"))
		{
			Print("[StGw57] LongrangeOptic erkannt - klappe Korn ein");
			SetAnimationPhase("korn_fold", 1.0);
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
		Print("[StGw57] EEItemDetached: " + item.GetType());
		if (item.IsKindOf("LongrangeOptic"))
		{
			Print("[StGw57] LongrangeOptic entfernt - klappe Korn aus");
			SetAnimationPhase("korn_fold", 0.0);
		}
	}
};

class stgw57 : stgw57_Base {};