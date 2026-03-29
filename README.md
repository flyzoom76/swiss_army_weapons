# Swiss Army Weapons - DayZ Mod

DayZ modification adding Swiss Army weapons. Starting with the Sturmgewehr 57 (StGw57).

## Verzeichnisstruktur (P: Drive)

```
P:\swiss_army_weapons\
├── mod.cpp
├── README.md
└── addons\
    └── stgw57\
        ├── config.cpp          <- Klassen-Konfiguration
        ├── model.cfg           <- LOD/Skeleton Konfiguration
        ├── $PBOPREFIX$         <- PBO Pfad: swiss_army_weapons\stgw57
        └── data\
            ├── stgw57_rifle.p3d          <- Konvertiert aus stgw57_rifle.fbx
            ├── Sturmgewehr57_BaseColor.paa
            └── Sturmgewehr57_Normal.paa
```

## Voraussetzungen (Tools)

- **DayZ Tools** (Steam) - enthält Object Builder und Addon Builder
- **Mikero's Tools** oder **DayZ Tools PBO Manager** - zum Packen der PBOs
- **Blender** mit **DayZ Tools Addon** - zum Konvertieren des FBX in P3D

## Workflow: FBX zu P3D konvertieren

1. Blender öffnen
2. `stgw57_rifle.fbx` importieren (`File > Import > FBX`)
3. DayZ Blender-Addon aktivieren
4. Modell exportieren als `.p3d` nach `P:\swiss_army_weapons\stgw57\data\stgw57_rifle.p3d`

## Workflow: Mod packen und testen

1. **Addon Builder** (aus DayZ Tools) öffnen
2. Source-Pfad: `P:\swiss_army_weapons\addons\stgw57`
3. Output-Pfad: z.B. `C:\DayZ Mods\@swiss_army_weapons\addons\`
4. PBO bauen -> erzeugt `stgw57.pbo`
5. `@swiss_army_weapons` Ordner in DayZ-Verzeichnis kopieren
6. DayZ mit `-mod=@swiss_army_weapons` starten

## Dateien die noch hinzugefügt werden müssen (lokal, nicht in Git)

- `data/stgw57_rifle.p3d` - aus FBX konvertiert
- `data/Sturmgewehr57_BaseColor.paa` - bereits vorhanden
- `data/Sturmgewehr57_Normal.paa` - bereits vorhanden

> Binäre Dateien (.paa, .p3d, .fbx) werden separat per Git LFS oder lokal verwaltet.
