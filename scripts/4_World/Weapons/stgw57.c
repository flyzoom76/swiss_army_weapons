class stgw57_Base : RifleBoltLock_Base
{
	override RecoilBase SpawnRecoilObject()
	{
		return new M4a1Recoil(this);
	}

	override void EEItemAttached(EntityAI item, string slotName)
	{
		super.EEItemAttached(item, slotName);
		if (item.IsKindOf("LongrangeOptic"))
			SetAnimationPhase("korn_fold", 1);
	}

	override void EEItemDetached(EntityAI item, string slotName)
	{
		super.EEItemDetached(item, slotName);
		if (item.IsKindOf("LongrangeOptic"))
			SetAnimationPhase("korn_fold", 0);
	}
};

class stgw57 : stgw57_Base {};