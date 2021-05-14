#!/bin/bash

mkdir -p pruebas/

# probamos primero con un fichero pequeño
./bin/prueba_encriptar_fichero_mars notas.md pruebas/notas_encriptado.dat mi_claveaseteqed apsoelfoepss1ela

./bin/prueba_desencriptar_fichero_mars pruebas/notas_encriptado.dat notas_des.md mi_claveaseteqed apsoelfoepss1ela

md5sum notas.md
md5sum notas_des.md
