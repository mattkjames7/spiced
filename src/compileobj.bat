mkdir ..\build

set cflags=-lm -fPIC -std=c++17 -Wextra -O3 -fopenmp
set ldflags=-L../lib/libann/lib -lann
set iflags=-I../lib/libann/include


ld -r -b binary -o ..\build\mavh.o mavh.bin
ld -r -b binary -o ..\build\mavcps.o mavcps.bin
ld -r -b binary -o ..\build\mavcpt.o mavcpt.bin
ld -r -b binary -o ..\build\ps.o ps.bin
ld -r -b binary -o ..\build\pt.o pt.bin
ld -r -b binary -o ..\build\prob.o prob.bin
ld -r -b binary -o ..\build\mavhann.o mavhann.bin 
ld -r -b binary -o ..\build\mavcpsann.o mavcpsann.bin 
ld -r -b binary -o ..\build\mavcptann.o mavcptann.bin 
ld -r -b binary -o ..\build\psann.o psann.bin 
ld -r -b binary -o ..\build\ptann.o ptann.bin 
ld -r -b binary -o ..\build\probann.o probann.bin 
ld -r -b binary -o ..\build\mavlambda.o mavlambda.bin

g++ -c %cflags% %iflags% annmodel.cc -o ..\build\annmodel.o
g++ -c %cflags% %iflags% annmavhmodel.cc -o ..\build\annmavhmodel.o
g++ -c %cflags% %iflags% annmavpsmodel.cc -o ..\build\annmavpsmodel.o
g++ -c %cflags% %iflags% annmavptmodel.cc -o ..\build\annmavptmodel.o
g++ -c %cflags% %iflags% annprobmodel.cc -o ..\build\annprobmodel.o
g++ -c %cflags% %iflags% annpsmodel.cc -o ..\build\annpsmodel.o
g++ -c %cflags% %iflags% annptmodel.cc -o ..\build\annptmodel.o
g++ -c %cflags% %iflags% avmodel.cc -o ..\build\avmodel.o
g++ -c %cflags% %iflags% avpsmodel.cc -o ..\build\avpsmodel.o
g++ -c %cflags% %iflags% avptmodel.cc -o ..\build\avptmodel.o
g++ -c %cflags% %iflags% avprobmodel.cc -o ..\build\avprobmodel.o
g++ -c %cflags% %iflags% avmavhmodel.cc -o ..\build\avmavhmodel.o
g++ -c %cflags% %iflags% avmavpsmodel.cc -o ..\build\avmavpsmodel.o
g++ -c %cflags% %iflags% avmavptmodel.cc -o ..\build\avmavptmodel.o
g++ -c %cflags% %iflags% mavtrans.cc -o ..\build\mavtrans.o
g++ -c %cflags% %iflags% polynomial.cc -o ..\build\polynomial.o
g++ -c %cflags% %iflags% rescale.cc -o ..\build\rescale.o
g++ -c %cflags% %iflags% reversearray.cc -o ..\build\reversearray.o
g++ -c %cflags% %iflags% libspiced.cc -o ..\build\libspiced.o 