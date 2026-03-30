# Swiss Army Weapons - DayZ Mod

DayZ modification adding Swiss Army weapons. Starting with the Sturmgewehr 57 (StGw57).

## Verzeichnisstruktur (P: Drive)

```
P:\swiss_army_weapons\
├── config.cpp                        <- Klassen-Konfiguration
├── meta.cpp                          <- Mod-Metadaten (Workshop)
├── mod.cpp                           <- Mod-Anzeigeinformationen
├── stgw57_rifle.p3d                  <- 3D Modell (konvertiert aus FBX)
└── data\
    ├── StGw57.rvmat                  <- Material (verknüpft Texturen)
    ├── Sturmgewehr57_BaseColor.paa   <- Farbtextur
    ├── Sturmgewehr57_Normal.paa      <- Normal Map
    ├── stgw57_rifle.edds             <- Inventarbild (512x256px)
    └── stgw57_rifle_icon.edds        <- Quickbar-Icon (64x64px)
```

## Voraussetzungen (Tools)

- **DayZ Tools** (Steam) - enthält Object Builder und Addon Builder
- **Blender** mit DayZ Tools Addon - zum Konvertieren des FBX in P3D
- **GIMP** oder **Paint.NET** mit DDS Plugin - für .edds Icons

## Workflow: FBX zu P3D konvertieren

1. Blender öffnen
2. `stgw57_rifle.fbx` importieren (`File > Import > FBX`)
3. DayZ Blender-Addon aktivieren
4. Modell exportieren als `.p3d` nach `P:\swiss_army_weapons\stgw57_rifle.p3d`

## Workflow: Mod packen und testen

1. **Addon Builder** (aus DayZ Tools) öffnen
2. Source-Pfad: `P:\swiss_army_weapons`
3. Output-Pfad: z.B. `C:\DayZ Mods\@swiss_army_weapons\addons\`
4. PBO bauen → erzeugt `swiss_army_weapons.pbo`
5. `@swiss_army_weapons` Ordner in DayZ-Verzeichnis kopieren
6. DayZ mit `-mod=@swiss_army_weapons` starten

## Dateien die noch lokal hinzugefügt werden müssen

- `stgw57_rifle.p3d` - aus FBX konvertiert
- `data/Sturmgewehr57_BaseColor.paa` - bereits vorhanden
- `data/Sturmgewehr57_Normal.paa` - bereits vorhanden
- `data/stgw57_rifle.edds` - Inventarbild (noch erstellen)
- `data/stgw57_rifle_icon.edds` - Quickbar-Icon (noch erstellen)

> Binäre Dateien (.paa, .p3d, .edds) werden per Git LFS verwaltet.
