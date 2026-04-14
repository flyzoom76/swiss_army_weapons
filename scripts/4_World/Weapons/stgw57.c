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
			Print("[StGw57] LongrangeOptic erkannt - blende Korn aus");
			SetSimpleHiddenSelectionState(1, false);
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
		Print("[StGw57] EEItemDetached: " + item.GetType());
		if (item.IsKindOf("LongrangeOptic"))
		{
			Print("[StGw57] LongrangeOptic entfernt - zeige Korn");
			SetSimpleHiddenSelectionState(1, true);
		}
	}
};

class stgw57 : stgw57_Base {};