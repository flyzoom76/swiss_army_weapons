class CfgPatches
{
	class swiss_army_weapons
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};
class CfgMods
{
	class swiss_army_weapons
	{
		dir="swiss_army_weapons";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="swiss_army_weapons";
		credits="";
		author="zoom";
		authorID="0";
		version="1.0";
		extra=0;
		type="mod";
		dependencies[] = {"World"};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"swiss_army_weapons\scripts\4_World"};
			};
		};
	};
};

