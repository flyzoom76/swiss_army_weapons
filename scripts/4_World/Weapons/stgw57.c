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
};

class stgw57 : stgw57_Base {};
