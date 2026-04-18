class CfgPatches
{
	class stgw57_Sound
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Weapons_Muzzles",
			"DZ_Weapons_Optics",
			"DZ_Weapons_Firearms",
			"DZ_Weapons_Firearms_Scout",
			"DZ_Sounds_Weapons",
			"DZ_Weapons_Magazines",
			"DZ_Weapons_Projectiles",
			"DZ_Sounds_Effects",
			"DZ_Data",
			"DZ_Weapons_Supports"
		};
		magazines[]={};
	};
};
class CfgSoundShaders
{
	class base_closeShot_SoundShader;
	class base_midShot_SoundShader;
	class base_distShot_SoundShader;
	class stgw57_closeShot_SoundShader: base_closeShot_SoundShader
	{
		samples[] = {{"swiss_army_weapons\data\sounds\stgw57_shot",1}};
		volume = 0.8;
	};
	class stgw57_midShot_SoundShader: base_midShot_SoundShader
	{
		samples[] = {{"swiss_army_weapons\data\sounds\stgw57_shot",1}};
		volume = 0.5;
	};
	class stgw57_distShot_SoundShader: base_distShot_SoundShader
	{
		samples[] = {{"swiss_army_weapons\data\sounds\stgw57_shot",1}};
		volume = 0.35;
	};
	class base_HomeSilenced_closeShot_SoundShader;
	class base_HomeSilenced_midShot_SoundShader;
	class base_HomeSilenced_distShot_SoundShader;
	class stgw57_silencedcloseShot_SoundShader: base_HomeSilenced_closeShot_SoundShader
	{
		samples[] = {{"swiss_army_weapons\data\sounds\stgw57_suppressed_shot",1}};
		volume = 1.0;
	};
	class stgw57_silencedmidShot_SoundShader: base_HomeSilenced_midShot_SoundShader
	{
		samples[] = {{"swiss_army_weapons\data\sounds\stgw57_suppressed_shot",1}};
		volume = 0.8;
	};
	class stgw57_silenceddistShot_SoundShader: base_HomeSilenced_distShot_SoundShader
	{
		samples[] = {{"swiss_army_weapons\data\sounds\stgw57_suppressed_shot",1}};
		volume = 0.6;
	};
	class base_closeExplosion_SoundShader;
	class base_midExplosion_SoundShader;
	class base_distExplosion_SoundShader;
	class stgw57_grenade_closeExplosion_SoundShader: base_closeExplosion_SoundShader
	{
		samples[] = {{"swiss_army_weapons\data\sounds\stgw57_grenade_frag_close_explosion_03",1}};
		volume = 1.0;
	};
	class stgw57_grenade_midExplosion_SoundShader: base_midExplosion_SoundShader
	{
		samples[] = {{"swiss_army_weapons\data\sounds\stgw57_grenade_frag_mid_explosion_03",1}};
		volume = 0.8;
	};
	class stgw57_grenade_distExplosion_SoundShader: base_distExplosion_SoundShader
	{
		samples[] = {{"swiss_army_weapons\data\sounds\stgw57_grenade_frag_dist_explosion_03",1}};
		volume = 0.6;
	};
};
class CfgSoundSets
{
	class Rifle_Shot_Base_SoundSet;
	class stgw57_shot_SoundSet: Rifle_Shot_Base_SoundSet
	{
		soundShaders[] = {"stgw57_closeShot_SoundShader","stgw57_midShot_SoundShader","stgw57_distShot_SoundShader"};
	};
	class Rifle_silencerHomemade_Base_SoundSet;
	class stgw57_SilencedShot_SoundSet: Rifle_silencerHomemade_Base_SoundSet
	{
		soundShaders[] = {"stgw57_silencedcloseShot_SoundShader","stgw57_silencedmidShot_SoundShader","stgw57_silenceddistShot_SoundShader"};
	};
	class Explosion_GrenadeHand_SoundSet;
	class stgw57_Grenade_Explosion_SoundSet: Explosion_GrenadeHand_SoundSet
	{
		soundShaders[] = {"stgw57_grenade_closeExplosion_SoundShader","stgw57_grenade_midExplosion_SoundShader","stgw57_grenade_distExplosion_SoundShader"};
	};
};
