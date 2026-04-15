
class CfgPatches
{
	class stgw57
	{
		units[] = {};
		weapons[] = {"stgw57"};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Weapons_Firearms","DZ_Weapons_Magazines","DZ_Data", "DZ_Weapons_Optics"};
		magazines[] = {"Mag_stgw57_24rnd"};
	};
};
class Mode_Safe;
class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;
class OpticsInfoRifle;
class cfgWeapons
{
	class Rifle_Base;
	class stgw57_Base: Rifle_Base
	{
		scope = 0;
		displayName = "StGw57";
		descriptionShort = "The Sturmgewehr 57 was developed by SIG to serve as the standard service rifle of the Swiss Armed Forces. Fed from 24-round detachable magazines, chambered for 7.5x55mm (GP11) Swiss";
		model = "swiss_army_weapons\data\stgw57\data\stgw57.p3d";
		attachments[] = {"weaponOptics","weaponWrap","weaponBayonet","suppressorImpro","weaponBipodStgw57"};
		itemSize[] = {8,3};
		weight = 5700;
		absorbency = 0.0;
		repairableWithKits[] = {1};
		repairCosts[] = {30.0,25.0};
		PPDOFProperties[] = {1,0.5,20,170,4,10};
		WeaponLength = 0.829067;
		chamberSize = 1;
		barrelArmor = 10.125;
		chamberedRound = "";
		chamberableFrom[] = {"Ammo_750x55"};
		magazines[] = {"Mag_stgw57_24rnd"};
		magazineSwitchTime = 0.2;
		ejectType = 1;
		initSpeedMultiplier = 0.4;
		recoilModifier[] = {1.0,0.9,1.0};
		swayModifier[] = {1.4,1.4,0.8};
                simpleHiddenSelections[] = {"hide_barrel", "korn_fold"};
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"swiss_army_weapons\data\stgw57\data\stgw57_co.paa"};
		hiddenSelectionsMaterials[] = {"swiss_army_weapons\data\stgw57\data\stgw57.rvmat"};
		modes[] = {"FullAuto","SemiAuto"};
		class Melee
		{
			range = 1;
			swingTime = 0.5;
			action = "MeleeKnifeSlash";
			ammo = "MeleeLightBlunt";
			useCursor = 0;
		};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[] = {"stgw57_shot_SoundSet","stgw57_shot_SoundSet","stgw57_shot_SoundSet"};
			soundSetShotExt[] = {"stgw57_SilencedShot_SoundSet","stgw57_SilencedShot_SoundSet","stgw57_SilencedShot_SoundSet"};
			reloadTime = 0.11;
			dispersion = 0.0007;
			magazineSlot = "magazine";
		};
		class FullAuto: Mode_FullAuto
		{
			soundSetShot[] = {"stgw57_shot_SoundSet","stgw57_shot_SoundSet","stgw57_shot_SoundSet"};
			soundSetShotExt[] = {"stgw57_SilencedShot_SoundSet","stgw57_SilencedShot_SoundSet","stgw57_SilencedShot_SoundSet"};
			reloadTime = 0.075;
			dispersion = 0.0007;
			magazineSlot = "magazine";
		};
		class OpticsInfo: OpticsInfoRifle
		{
			memoryPointCamera = "eye";
			discreteDistance[] = {100,200,300,400,500,600,700,800,900,1000};
			discreteDistanceInitIndex = 0;
			modelOptics = "-";
			distanceZoomMin = 100;
			distanceZoomMax = 1000;
		};
		class Particles
		{
			class OnFire
			{
				class SmokeCloud
				{
					overrideParticle = "weapon_shot_winded_smoke";
				};
				class MuzzleFlash
				{
					overrideParticle = "weapon_shot_akm_01";
					ignoreIfSuppressed = 1;
					illuminateWorld = 1;
					positionOffset[] = {-0.05,0,0};
				};
				class ChamberSmokeBurst
				{
					overrideParticle = "weapon_shot_chamber_smoke";
					overridePoint = "Nabojnicestart";
					overrideDirectionPoint = "Nabojniceend";
				};
			};
			class OnOverheating
			{
				maxOverheatingValue = 40;
				shotsToStartOverheating = 5;
				overheatingDecayInterval = 1;
				class SmokingBarrel1
				{
					overrideParticle = "smoking_barrel_small";
					onlyWithinOverheatLimits[] = {0.0,0.5};
					positionOffset[] = {0.1,0,0};
					onlyWithinRainLimits[] = {0,0.2};
				};
				class SmokingBarrelHot1
				{
					overrideParticle = "smoking_barrel";
					onlyWithinOverheatLimits[] = {0.5,0.8};
					positionOffset[] = {0.1,0,0};
					onlyWithinRainLimits[] = {0,0.2};
				};
				class SmokingBarrelHot3
				{
					overrideParticle = "smoking_barrel_heavy";
					onlyWithinOverheatLimits[] = {0.8,1};
					positionOffset[] = {0.1,0,0};
					onlyWithinRainLimits[] = {0,0.2};
				};
				class SmokingBarrelHotSteamSmall
				{
					overrideParticle = "smoking_barrel_steam_small";
					positionOffset[] = {0.3,0,0};
					onlyWithinRainLimits[] = {0.2,0.5};
				};
				class SmokingBarrelHotSteam
				{
					overrideParticle = "smoking_barrel_steam";
					positionOffset[] = {0.3,0,0};
					onlyWithinRainLimits[] = {0.5,1};
				};
				class OpenChamberSmoke
				{
					onlyIfBoltIsOpen = 1;
					overrideParticle = "smoking_barrel_small";
					overridePoint = "Nabojnicestart";
				};
			};
			class OnBulletCasingEject
			{
				class ChamberSmokeRaise
				{
					overrideParticle = "weapon_shot_chamber_smoke_raise";
					overridePoint = "Nabojnicestart";
				};
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 800;
					healthLevels[] = {{1.0,{"swiss_army_weapons\data\stgw57\data\stgw57.rvmat"}},{0.7,{"swiss_army_weapons\data\stgw57\data\stgw57.rvmat"}},{0.5,{"swiss_army_weapons\data\stgw57\data\stgw57_damage.rvmat"}},{0.3,{"swiss_army_weapons\data\stgw57\data\stgw57_damage.rvmat"}},{0.0,{"swiss_army_weapons\data\stgw57\data\stgw57_destruct.rvmat"}}};
				};
			};
		};
	};
	class stgw57: stgw57_Base
	{
		scope = 2;
		hiddenSelectionsTextures[] = {"swiss_army_weapons\data\stgw57\data\stgw57_co.paa"};
		hiddenSelectionsMaterials[] = {"swiss_army_weapons\data\stgw57\data\stgw57.rvmat"};
	};
};
class CfgVehicles
{
	class ItemOptics_Base;
	class Inventory_Base;
	class LongrangeOptic: ItemOptics_Base
	{
		inventorySlot[] += {"weaponOptics"};
	};
	class stgw57_bipod: Inventory_Base
	{
		scope = 2;
		displayName = "StGw57 Bipod";
		descriptionShort = "Bipod for StGw57.";
		model = "swiss_army_weapons\data\stgw57\data\stgw57_bipod.p3d";
		rotationFlags = 17;
		inventorySlot[] = {"weaponBipodStgw57"};
		weight = 300;
		itemSize[] = {2,1};
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"swiss_army_weapons\data\stgw57\data\stgw57_bipod_co.paa"};
		hiddenSelectionsMaterials[] = {"swiss_army_weapons\data\stgw57\data\stgw57_bipod.rvmat"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {
						{1.0,{"swiss_army_weapons\data\stgw57\data\stgw57_bipod.rvmat"}},
						{0.7,{"swiss_army_weapons\data\stgw57\data\stgw57_bipod.rvmat"}},
						{0.5,{"swiss_army_weapons\data\stgw57\data\stgw57_bipod_damage.rvmat"}},
						{0.3,{"swiss_army_weapons\data\stgw57\data\stgw57_bipod_damage.rvmat"}},
						{0.0,{"swiss_army_weapons\data\stgw57\data\stgw57_bipod_destruct.rvmat"}}
					};
				};
			};
		};
	};
	class stgw57_bayonet: Inventory_Base
	{
		scope = 2;
		displayName = "StGw57 Bajonett";
		descriptionShort = "Bajonett für das StGw57.";
		model = "swiss_army_weapons\data\stgw57\data\stgw57_bayonet.p3d";
		rotationFlags = 17;
		animClass = "Knife";
		suicideAnim = "onehanded";
		inventorySlot[] = {"weaponBayonet","Knife"};
		weight = 250;
		itemSize[] = {3,1};
		itemModelLength = 0.3;
		itemAttachOffset = -0.18;
		recoilModifier[] = {1,1,1};
		swayModifier[] = {1,1,1};
		itemInfo[] = {"Knife"};
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"swiss_army_weapons\data\stgw57\data\stgw57_bayonet_co.paa"};
		hiddenSelectionsMaterials[] = {"swiss_army_weapons\data\stgw57\data\stgw57_bayonet.rvmat"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {
						{1.0,{"swiss_army_weapons\data\stgw57\data\stgw57_bayonet.rvmat"}},
						{0.7,{"swiss_army_weapons\data\stgw57\data\stgw57_bayonet.rvmat"}},
						{0.5,{"swiss_army_weapons\data\stgw57\data\stgw57_bayonet_damage.rvmat"}},
						{0.3,{"swiss_army_weapons\data\stgw57\data\stgw57_bayonet_damage.rvmat"}},
						{0.0,{"swiss_army_weapons\data\stgw57\data\stgw57_bayonet_destruct.rvmat"}}
					};
				};
			};
		};
		class MeleeModes
		{
			class Default
			{
				ammo = "MeleeSharpLight_4";
				range = 1.2;
			};
			class Heavy
			{
				ammo = "MeleeSharpHeavy_4";
				range = 1.2;
			};
			class Sprint
			{
				ammo = "MeleeSharpHeavy_4";
				range = 3.3;
			};
		};
		soundImpactType = "metal";
	};
	class stgw57_diopter: ItemOptics_Base
	{
		scope=2;
		displayName="StGw75_Diopter";
		descriptionShort="Iron sight for StGw57.";
		model="swiss_army_weapons\data\stgw57\data\stgw57_diopter.p3d";
		rotationFlags=17;
		itemSize[]={1,1};
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"swiss_army_weapons\data\stgw57\data\stgw57_diopter_co.paa"};
		hiddenSelectionsMaterials[]={"swiss_army_weapons\data\stgw57\data\stgw57_diopter.rvmat"};
		memoryPointCamera="eyeScope";
		cameraDir="cameraDir";
		inventorySlot[]={"weaponOptics"};
		class OpticsInfo
		{
			memoryPointCamera="eyeScope";
			cameraDir="cameraDir";
			opticsZoomMin=1.0;
			opticsZoomMax=1.0;
			opticsZoomInit=1.0;
			modelOptics="-";
			PPBlurProperties=0;
			PPDOFProperties[]={0,0,0,0,0,0};
		};
		class DamageSystem
		{
			// Damage parameters
		};
	};
};

class cfgMagazines
{
	class Magazine_Base;
	class Mag_stgw57_24rnd: Magazine_Base
	{
		scope = 2;
		displayName = "StGw57 24Magazine";
		descriptionShort = "Detachable box magazine for the StGw57. Holds up to 24 rounds of 7.5x55";
		model = "swiss_army_weapons\data\stgw57\data\stgw57_24mag.p3d";
		weight = 100;
		itemSize[] = {1,3};
		count = 24;
		ammo = "Bullet_750x55";
		ammoItems[] = {"Ammo_750x55"};
		tracersEvery = 0;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 800;
					healthLevels[] = {{1.0,{"swiss_army_weapons\data\stgw57\data\stgw57.rvmat"}},{0.7,{"swiss_army_weapons\data\stgw57\data\stgw57.rvmat"}},{0.5,{"swiss_army_weapons\data\stgw57\data\stgw57_damage.rvmat"}},{0.3,{"swiss_army_weapons\data\stgw57\data\stgw57_damage.rvmat"}},{0.0,{"swiss_army_weapons\data\stgw57\data\stgw57_destruct.rvmat"}}};
				};
			};
		};
	};
};
class CfgNonAIVehicles
{
	class ProxyAttachment;
	class Proxystgw57_24mag: ProxyAttachment
	{
		scope = 0;
		inventorySlot = "magazine";
		model = "swiss_army_weapons\data\stgw57\data\stgw57_24mag.p3d";
	};
	class Proxystgw57_diopter: ProxyAttachment
	{
		scope = 0;
		inventorySlot = "weaponOptics";
		model = "swiss_army_weapons\data\stgw57\data\stgw57_diopter.p3d";
	};
	class Proxystgw57_bipod: ProxyAttachment
	{
		scope = 0;
		inventorySlot = "weaponBipodStgw57";
		model = "swiss_army_weapons\data\stgw57\data\stgw57_bipod.p3d";
	};
	class Proxystgw57_bayonet: ProxyAttachment
	{
		scope = 2;
		inventorySlot = "weaponBayonet";
		model = "swiss_army_weapons\data\stgw57\data\stgw57_bayonet.p3d";
	};
};

class CfgSlots
{
	class weaponBipodStgw57
	{
		name = "weaponBipodStgw57";
		displayName = "Bipod";
		description = "Bipod slot for StGw57";
		selection = "bipod";
	};
};
