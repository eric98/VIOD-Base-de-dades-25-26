#!/bin/bash
# Propósit: Aquest script genera i comprimeix una còpia de seguretat arran els paràmetres rebuts.

# 0. Comprovem si rebem els paràmetres
if [ $# -ne 5 ]; then
	echo "[ERROR] Has escrit $# paràmetres"
	echo "Ús: $0 usuari password host base_de_dades desti"
	exit 1 # 1: Sortida amb error general
fi

usuari=$1
contrasenya=$2
host=$3
base_de_dades=$4
desti=$5

# 1. Preparem les variables rebudes per paràmetre
if [ ! -d "$desti" ]; then
	echo "[ERROR] La ruta $desti no existeix"
	exit 1
fi

# 2. Fem la còpia de seguretat amb mysqldump
copia_seguretat="$base_de_dades".sql
if ! mysqldump -u root -pAlumne.123 "$base_de_dades" > "$copia_seguretat"; then
	echo "[ERROR] Error en crear la còpia de seguretat de $base_de_dades"
	exit 1
fi

# 3. Comprimim la còpia de seguretat amb gzip
if ! gzip "$copia_seguretat"; then
	echo "[ERROR] Error en comprimir $copia_seguretat"
	exit 1
fi

# 4. Movem la còpia de seguretat comprimida
#   al directori de destí amb mv
copia_seguretat_comprimida="$copia_seguretat".gz
if ! mv "$copia_seguretat_comprimida" "$desti"; then
	echo "[ERROR] Error en moure $copia_seguretat_comprimida a $desti"
	exit 1
fi

exit 0 # 0: Sortida satisfactòria

