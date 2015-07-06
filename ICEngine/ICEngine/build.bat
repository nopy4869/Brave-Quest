windres ICEngine.rc -O coff -o ICEngine.res
gcc -Wall -o "./Brave Quest.exe" "./linux.c" "./ICEngine.res" -lncursesw
