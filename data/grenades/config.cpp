class CfgPatches
{
	class stgw57_grenades
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data", "DZ_Weapons_Firearms", "stgw57"};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class StGw57_Grenade_Frag: Inventory_Base
	{
		scope = 2;
		displayName = "StGw57 Gewehrgranate (Splitter)";
		descriptionShort = "Aufsteckgranate fuer das StGw57. Wird mit einer Treibladungspatrone abgefeuert.";
		model = "swiss_army_weapons\data\grenades\data\stgw57_grenade_frag.p3d";
		rotationFlags = 17;
		inventorySlot[] = {"weaponGrenadeStgw57"};
		weight = 200;
		itemSize[] = {2,2};
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"swiss_army_weapons\data\grenades\data\stgw57_grenade_frag_co.paa"};
		hiddenSelectionsMaterials[] = {"swiss_army_weapons\data\grenades\data\stgw57_grenade_frag.rvmat"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] =
					{
						{1.0, {"swiss_army_weapons\data\grenades\data\stgw57_grenade_frag.rvmat"}},
						{0.7, {"swiss_army_weapons\data\grenades\data\stgw57_grenade_frag.rvmat"}},
						{0.5, {"swiss_army_weapons\data\grenades\data\stgw57_grenade_frag_damage.rvmat"}},
						{0.3, {"swiss_army_weapons\data\grenades\data\stgw57_grenade_frag_damage.rvmat"}},
						{0.0, {"swiss_army_weapons\data\grenades\data\stgw57_grenade_frag_destruct.rvmat"}}
					};
				};
			};
		};
	};
};
