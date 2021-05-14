#!/bin/bash

mkdir -p pruebas/

# probamos primero con un fichero pequeño
./bin/prueba_encriptar_fichero_mars notas.md pruebas/notas_encriptado.dat mi_claveaseteqed apsoelfoepss1ela

./bin/prueba_desencriptar_fichero_mars pruebas/notas_encriptado.dat pruebas/notas_des.md mi_claveaseteqed apsoelfoepss1ela

md5sum notas.md
md5sum pruebas/notas_des.md


# ahora con una imagen
./bin/prueba_encriptar_fichero_mars images/xkcd_153.png pruebas/xkcd_encryp.dat mi_claveaseteqed apsoelfoepss1ela

./bin/prueba_desencriptar_fichero_mars pruebas/xkcd_encryp.dat pruebas/xkcd_153.png mi_claveaseteqed apsoelfoepss1ela

md5sum images/xkcd_153.png
md5sum pruebas/xkcd_153.png
