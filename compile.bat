cd lib\libann
call compile.bat
cd ..\..\
copy lib\libann\lib\libann.dll lib\

cd src
call compile.bat 
cd ..