class CfgPatches
{
	class stgw57_diopter
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={"DZ_Data", "DZ_Weapons_Optics"};
	};
};

class CfgVehicles
{
	class ItemOptics;
	class stgw57_diopter: ItemOptics
	{
		scope=2;
		displayName="StGw75_Diopter";
		descriptionShort="Iron sight for StGw57.";
		model="swiss_army_weapons\data\stgw57_diopter\data\stgw57_diopter.p3d";
		rotationFlags=12;
		itemSize[]={2,1};
		inventorySlot[]={"weaponOptics"};
		class DamageSystem
		{
			// Damage parameters
		};
	};
};
