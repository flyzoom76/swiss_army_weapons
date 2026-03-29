class CfgPatches
{
    class swiss_army_weapons_stgw57
    {
        units[] = {"StGw57_Rifle"};
        weapons[] = {};
        requiredVersion = 0.1;
        requiredAddons[] = {"DZ_Data"};
    };
};

class CfgVehicles
{
    // Base class from DayZ - static display object (no function, no interaction)
    class ItemBase;

    class StGw57_Rifle : ItemBase
    {
        scope = 2;
        displayName = "StGw 57";
        descriptionShort = "Sturmgewehr 57 - Swiss assault rifle";
        model = "\swiss_army_weapons\stgw57\data\models\stgw57_rifle.p3d";

        picture = "\swiss_army_weapons\stgw57\data\textures\stgw57_rifle.edds";
        icon = "\swiss_army_weapons\stgw57\data\textures\stgw57_rifle_icon.edds";

        // Physically simulated object, no pickup/function yet
        physLayer = "item_large";
        weight = 5100;

        class AnimationSources {};
        class Particles {};
    };
};
