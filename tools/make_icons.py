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

    # Schwarzer Hintergrund (DayZ Standard für Icons)
    canvas = Image.new("RGBA", (target_w, target_h), (0, 0, 0, 255))

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

    input_path = sys.argv[1]

    try:
        img = Image.open(input_path).convert("RGBA")
    except FileNotFoundError:
        print(f"Fehler: Datei '{input_path}' nicht gefunden.")
        sys.exit(1)

    print(f"Eingabe: {input_path} ({img.width}x{img.height}px)")

    # Leeren Rand abschneiden
    cropped = autocrop(img, padding=20)
    print(f"Nach Autocrop: {cropped.width}x{cropped.height}px")

    # Inventarbild: 512x256px
    picture = fit_centered(cropped, 512, 256)
    picture.save("stgw57_rifle_picture.png")
    print("Erstellt: stgw57_rifle_picture.png (512x256px) -> umbenennen zu stgw57_rifle.edds")

    # Quickbar-Icon: 64x64px
    icon = fit_centered(cropped, 64, 64)
    icon.save("stgw57_rifle_icon.png")
    print("Erstellt: stgw57_rifle_icon.png (64x64px)     -> umbenennen zu stgw57_rifle_icon.edds")

    print("\nNaechste Schritte:")
    print("1. Beide PNG in GIMP oder Paint.NET oeffnen")
    print("2. Als .dds exportieren (DXT5 fuer Transparenz)")
    print("3. .dds umbenennen zu .edds")
    print("4. In P:\\swiss_army_weapons\\data\\ kopieren")


if __name__ == "__main__":
    main()
