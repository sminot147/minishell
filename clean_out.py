#!/usr/bin/env python3
import sys
import re

# Regex qui match tout code d'échappement ANSI (couleurs, etc.)
ansi_escape_pattern = re.compile(r'\x1B\[[0-?]*[ -/]*[@-~]')

def remove_ansi_codes(text: str) -> str:
    """
    Supprime les séquences d'échappement ANSI (couleurs) d'une chaîne.
    """
    return ansi_escape_pattern.sub('', text)

def process_file(filename: str) -> None:
    # Lecture de tout le contenu du fichier
    with open(filename, 'r') as f:
        lines = f.readlines()

    cleaned_lines = []
    for line in lines:
        # 1) Enlever les couleurs ANSI
        line_no_ansi = remove_ansi_codes(line)

        # 2) Vérifier si la ligne nettoyée contient "STD_OUT: ✅  STD_ERR: ✅"
        if "STD_OUT: ✅  STD_ERR: ✅" in line_no_ansi:
            # On saute (ignore) cette ligne
            continue

        # 3) Conserver la ligne nettoyée des couleurs ANSI
        cleaned_lines.append(line_no_ansi)

    # On réécrit le fichier avec les lignes acceptées
    with open(filename, 'w') as f:
        f.writelines(cleaned_lines)

def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <fichier1> [<fichier2> ...]")
        sys.exit(1)

    # Applique la transformation à chaque fichier passé en argument
    for file in sys.argv[1:]:
        process_file(file)

if __name__ == "__main__":
    main()
