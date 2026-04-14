class stgw57_Base : RifleBoltLock_Base
{
	override RecoilBase SpawnRecoilObject()
	{
		return new M4a1Recoil(this);
	}

	override void OnAttachmentAttached(EntityAI attachment, InventoryLocation loc)
	{
		super.OnAttachmentAttached(attachment, loc);
		if (attachment.IsKindOf("LongrangeOptic"))
			SetAnimationPhase("korn_fold", 1);
	}

	override void OnAttachmentDetached(EntityAI attachment, InventoryLocation loc)
	{
		super.OnAttachmentDetached(attachment, loc);
		if (attachment.IsKindOf("LongrangeOptic"))
			SetAnimationPhase("korn_fold", 0);
	}
};

class stgw57 : stgw57_Base {};