class stgw57_Base : RifleBoltLock_Base
{
	override RecoilBase SpawnRecoilObject()
	{
		return new M4a1Recoil(this);
	}
};

class stgw57 : stgw57_Base {};