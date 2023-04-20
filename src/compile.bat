call compileobj.bat
set cflags=-lm -fPIC -std=c++17 -Wextra -O3 -fopenmp
set ldflags=-L../lib/libann/lib -lann
set iflags=-I../lib/libann/include
mkdir ..\lib
g++ %cflags% %iflags% ..\build\*.o -shared -o ..\lib\libspiced.dll %ldflags%
