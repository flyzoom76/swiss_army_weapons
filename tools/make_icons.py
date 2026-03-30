"""
DayZ Icon Generator - StGw57
Erstellt aus einem PNG-Bild des Gewehrs:
  - stgw57_rifle_picture.png  (512x256px) -> Inventarbild
  - stgw57_rifle_icon.png     (64x64px)   -> Quickbar-Icon

Danach beide Dateien mit GIMP/Paint.NET als .dds speichern
und zu .edds umbenennen.

Voraussetzung: pip install Pillow
Verwendung:    python make_icons.py mein_gewehr.png
"""

import sys
from pathlib import Path
from PIL import Image


def autocrop(img: Image.Image, padding: int = 10) -> Image.Image:
    """Schneidet leeren Rand ab (transparent oder weiss)."""
    if img.mode == "RGBA":
        # Nutze Alpha-Kanal zum Erkennen des Inhalts
        bbox = img.split()[3].getbbox()
    else:
        img_rgba = img.convert("RGBA")
        bg = Image.new("RGBA", img.size, (255, 255, 255, 255))
        diff = Image.new("RGBA", img.size)
        for x in range(img.size[0]):
            for y in range(img.size[1]):
                px = img_rgba.getpixel((x, y))
                bg_px = bg.getpixel((x, y))
                diff.putpixel((x, y), tuple(abs(a - b) for a, b in zip(px, bg_px)))
        bbox = diff.convert("L").getbbox()

    if bbox is None:
        return img

    # Padding hinzufügen
    left   = max(0, bbox[0] - padding)
    upper  = max(0, bbox[1] - padding)
    right  = min(img.width,  bbox[2] + padding)
    lower  = min(img.height, bbox[3] + padding)

    return img.crop((left, upper, right, lower))


def fit_centered(img: Image.Image, target_w: int, target_h: int) -> Image.Image:
    """Skaliert das Bild proportional und zentriert es auf schwarzem Hintergrund."""
    # Proportional skalieren damit es in target_w x target_h passt
    scale = min(target_w / img.width, target_h / img.height)
    new_w = int(img.width  * scale)
    new_h = int(img.height * scale)

    resized = img.resize((new_w, new_h), Image.LANCZOS)

    # Transparenter Hintergrund (Alpha = 0)
    canvas = Image.new("RGBA", (target_w, target_h), (0, 0, 0, 0))

    # Zentrieren
    offset_x = (target_w - new_w) // 2
    offset_y = (target_h - new_h) // 2

    if resized.mode == "RGBA":
        canvas.paste(resized, (offset_x, offset_y), resized)
    else:
        canvas.paste(resized, (offset_x, offset_y))

    return canvas


def main():
    if len(sys.argv) < 2:
        print("Verwendung: python make_icons.py <eingabe.png>")
        sys.exit(1)

    input_arg = Path(sys.argv[1])

    # Datei suchen: erst absolut/relativ zum CWD, dann relativ zum Script-Ordner
    script_dir = Path(__file__).parent
    if input_arg.exists():
        input_path = input_arg
    elif (script_dir / input_arg).exists():
        input_path = script_dir / input_arg
    else:
        print(f"Fehler: Datei '{input_arg}' nicht gefunden.")
        print(f"  Gesucht in: {input_arg.resolve()}")
        print(f"  Gesucht in: {(script_dir / input_arg).resolve()}")
        sys.exit(1)

    # Output-Dateien im gleichen Ordner wie die Eingabedatei speichern
    out_dir = input_path.parent

    try:
        img = Image.open(input_path).convert("RGBA")
    except Exception as e:
        print(f"Fehler beim Oeffnen der Datei: {e}")
        sys.exit(1)

    print(f"Eingabe: {input_path} ({img.width}x{img.height}px)")

    # Leeren Rand abschneiden
    cropped = autocrop(img, padding=20)
    print(f"Nach Autocrop: {cropped.width}x{cropped.height}px")

    # Inventarbild: 512x256px
    picture = fit_centered(cropped, 512, 256)
    picture_out = out_dir / "stgw57_rifle_picture.png"
    picture.save(picture_out)
    print(f"Erstellt: {picture_out} (512x256px) -> umbenennen zu stgw57_rifle.edds")

    # Quickbar-Icon: 64x64px
    icon = fit_centered(cropped, 64, 64)
    icon_out = out_dir / "stgw57_rifle_icon.png"
    icon.save(icon_out)
    print(f"Erstellt: {icon_out} (64x64px)     -> umbenennen zu stgw57_rifle_icon.edds")

    print("\nNaechste Schritte:")
    print("1. Beide PNG in GIMP oder Paint.NET oeffnen")
    print("2. Als .dds exportieren (DXT5 fuer Transparenz)")
    print("3. .dds umbenennen zu .edds")
    print("4. In P:\\swiss_army_weapons\\data\\ kopieren")


if __name__ == "__main__":
    main()
