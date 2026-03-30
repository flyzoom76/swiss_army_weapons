"""
DayZ Icon Generator - StGw57
Erstellt aus einem PNG-Bild des Gewehrs direkt fertige .edds Dateien:
  - stgw57_rifle.edds       (512x256px) -> Inventarbild
  - stgw57_rifle_icon.edds  (64x64px)   -> Quickbar-Icon

Voraussetzungen:
  pip install Pillow
  texconv.exe im gleichen Ordner wie das Script (oder im PATH)
  Download: https://github.com/microsoft/DirectXTex/releases (texconv.exe)

Verwendung: python make_icons.py mein_gewehr.png
"""

import sys
import subprocess
import shutil
from pathlib import Path
from PIL import Image


def find_texconv() -> Path | None:
    """Sucht texconv.exe im Script-Ordner oder im PATH."""
    script_dir = Path(__file__).parent
    local = script_dir / "texconv.exe"
    if local.exists():
        return local
    found = shutil.which("texconv")
    if found:
        return Path(found)
    return None


def png_to_edds(png_path: Path, texconv: Path) -> bool:
    """Konvertiert PNG zu DXT5 DDS und benennt es zu .edds um."""
    out_dir = png_path.parent
    result = subprocess.run(
        [str(texconv), "-f", "BC3_UNORM", "-y", "-o", str(out_dir), str(png_path)],
        capture_output=True,
        text=True
    )
    if result.returncode != 0:
        print(f"  texconv Fehler: {result.stderr.strip()}")
        return False

    dds_path = out_dir / png_path.with_suffix(".dds").name
    edds_path = out_dir / png_path.with_suffix(".edds").name
    if dds_path.exists():
        dds_path.rename(edds_path)
        png_path.unlink()  # PNG loeschen, nur .edds behalten
        return True
    return False


def autocrop(img: Image.Image, padding: int = 20) -> Image.Image:
    """Schneidet leeren Rand ab (transparent oder weiss)."""
    if img.mode == "RGBA":
        bbox = img.split()[3].getbbox()
    else:
        bbox = img.convert("L").getbbox()

    if bbox is None:
        return img

    left  = max(0, bbox[0] - padding)
    upper = max(0, bbox[1] - padding)
    right = min(img.width,  bbox[2] + padding)
    lower = min(img.height, bbox[3] + padding)
    return img.crop((left, upper, right, lower))


def fit_centered(img: Image.Image, target_w: int, target_h: int) -> Image.Image:
    """Skaliert proportional und zentriert auf transparentem Hintergrund."""
    scale = min(target_w / img.width, target_h / img.height)
    new_w = int(img.width  * scale)
    new_h = int(img.height * scale)
    resized = img.resize((new_w, new_h), Image.LANCZOS)

    canvas = Image.new("RGBA", (target_w, target_h), (0, 0, 0, 0))
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

    out_dir = input_path.parent
    texconv = find_texconv()

    if texconv:
        print(f"texconv gefunden: {texconv}")
    else:
        print("WARNUNG: texconv.exe nicht gefunden - nur PNG wird erstellt.")
        print("  Download: https://github.com/microsoft/DirectXTex/releases")
        print("  texconv.exe in den gleichen Ordner wie dieses Script legen.\n")

    try:
        img = Image.open(input_path).convert("RGBA")
    except Exception as e:
        print(f"Fehler beim Oeffnen der Datei: {e}")
        sys.exit(1)

    print(f"Eingabe: {input_path} ({img.width}x{img.height}px)")

    cropped = autocrop(img)
    print(f"Nach Autocrop: {cropped.width}x{cropped.height}px")

    # Inventarbild: 512x256px
    picture = fit_centered(cropped, 512, 256)
    picture_png = out_dir / "stgw57_rifle.png"
    picture.save(picture_png)

    if texconv:
        if png_to_edds(picture_png, texconv):
            print(f"Erstellt: {out_dir / 'stgw57_rifle.edds'} (512x256px)")
        else:
            print(f"Erstellt: {picture_png} (512x256px) - manuell zu .edds konvertieren")
    else:
        print(f"Erstellt: {picture_png} (512x256px) - manuell zu .edds konvertieren")

    # Quickbar-Icon: 64x64px
    icon = fit_centered(cropped, 64, 64)
    icon_png = out_dir / "stgw57_rifle_icon.png"
    icon.save(icon_png)

    if texconv:
        if png_to_edds(icon_png, texconv):
            print(f"Erstellt: {out_dir / 'stgw57_rifle_icon.edds'} (64x64px)")
        else:
            print(f"Erstellt: {icon_png} (64x64px) - manuell zu .edds konvertieren")
    else:
        print(f"Erstellt: {icon_png} (64x64px) - manuell zu .edds konvertieren")

    if not texconv:
        print("\nNaechste Schritte (ohne texconv):")
        print("  Paint.NET + 'DDS FileType Plus' Plugin:")
        print("  PNG oeffnen -> Speichern als .dds -> BC3 (DXT5) -> umbenennen zu .edds")
    else:
        print(f"\nFertig! .edds Dateien nach P:\\swiss_army_weapons\\data\\ kopieren.")


if __name__ == "__main__":
    main()
