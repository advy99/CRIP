#!/bin/bash

mkdir -p pruebas/

# probamos primero con un fichero pequeño
./bin/prueba_encriptar_fichero_mars notas.md pruebas/notas_encriptado.dat mi_claveaseteqed apsoelfoepss1ela

./bin/prueba_desencriptar_fichero_mars pruebas/notas_encriptado.dat pruebas/notas_des.md mi_claveaseteqed apsoelfoepss1ela

md5sum notas.md
md5sum pruebas/notas_des.md
md5sum pruebas/notas_encriptado.dat

echo ""

# ahora con una imagen
./bin/prueba_encriptar_fichero_mars images/xkcd_153.png pruebas/xkcd_encryp.dat mi_claveaseteqed apsoelfoepss1ela

./bin/prueba_desencriptar_fichero_mars pruebas/xkcd_encryp.dat pruebas/xkcd_153.png mi_claveaseteqed apsoelfoepss1ela

md5sum images/xkcd_153.png
md5sum pruebas/xkcd_153.png
md5sum pruebas/xkcd_encryp.dat

echo ""

# ahora con un un archivo de 1GB
./bin/prueba_encriptar_fichero_mars archivo_aleatorio pruebas/archivo_aleatorio_cifrado mi_claveaseteqed apsoelfoepss1ela

./bin/prueba_desencriptar_fichero_mars pruebas/archivo_aleatorio_cifrado pruebas/archivo_aleatorio_descifrado mi_claveaseteqed apsoelfoepss1ela

md5sum archivo_aleatorio
md5sum pruebas/archivo_aleatorio_descifrado
md5sum pruebas/archivo_aleatorio_cifrado

echo ""


# ahora con una AES
./bin/prueba_encriptar_fichero_AES archivo_aleatorio pruebas/archivo_aleatorio_cifrado_aes mi_claveaseteqed apsoelfoepss1ela

./bin/prueba_desencriptar_fichero_AES pruebas/archivo_aleatorio_cifrado_aes pruebas/archivo_aleatorio_descifrado_aes mi_claveaseteqed apsoelfoepss1ela

md5sum archivo_aleatorio
md5sum pruebas/archivo_aleatorio_descifrado_aes
md5sum pruebas/archivo_aleatorio_cifrado_aes
