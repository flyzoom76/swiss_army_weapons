class CfgPatches
{
	class Ammo_750_treib
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Weapons_Ammunition"};
		magazines[] = {"Ammo_750_treib"};
		ammo[] = {"Bullet_750_treib"};
	};
};
class cfgMagazines
{
	class Ammunition_Base;
	class Ammo_750_treib: Ammunition_Base
	{
		scope = 2;
		displayName = "7.5x55 Treibladung";
		descriptionShort = "7.5x55 Treibladung. Platzmunition fuer ausgewaehlte Gewehre.";
		model = "swiss_army_weapons\data\ammo\750_treib\data\750_treib.p3d";
		weight = 60;
		count = 24;
		ammo = "Bullet_750_treib";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 200;
					healthLevels[] = {{1.0,{"swiss_army_weapons\data\ammo\750_treib\data\750_treib.rvmat"}},{0.7,{"swiss_army_weapons\data\ammo\750_treib\data\750_treib.rvmat"}},{0.5,{"swiss_army_weapons\data\ammo\750_treib\data\750_treib_damage.rvmat"}},{0.3,{"swiss_army_weapons\data\ammo\750_treib\data\750_treib_damage.rvmat"}},{0.0,{"swiss_army_weapons\data\ammo\750_treib\data\750_treib_destruct.rvmat"}}};
				};
			};
		};
	};
};
class CfgAmmo
{
	class Bullet_Base;
	class Bullet_750_treib: Bullet_Base
	{
		scope = 2;
		cartridge = "FxCartridge_762";
		casing = "FxCartridge_762";
		round = "FxRound_308Win";
		spawnPileType = "Ammo_750_treib";
		hit = 12;
		indirectHit = 0;
		indirectHitRange = 0;
		visibleFire = 22;
		audibleFire = 22;
		visibleFireTime = 4;
		airLock = 1;
		initSpeed = 900;
		typicalSpeed = 900;
		airFriction = -0.00066;
		caliber = 1.5;
		deflecting = 20;
		damageBarrel = 0;
		damageBarrelDestroyed = 0;
		weight = 0.0162;
		impactBehaviour = 1;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0;
			bleedThreshold = 1;
			class Health
			{
				damage = 155;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 125;
			};
		};
		class NoiseHit
		{
			strength = 40;
			type = "shot";
		};
	};
};
class cfgAmmoTypes
{
	class AType_Bullet_750_treib
	{
		name = "Bullet_750_treib";
	};
};
