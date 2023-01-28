cd %1
copy "%2.ppp" "%PPP%\lib\%2.ppp" 
cd %PPP%\lib
del "sketch.h"
ren "%2.ppp" "sketch.h"
%PPP%\bin\MinGW\bin\g++ -c -o %PPP%\out\test.o %PPP%\lib\*.cpp -I"%PPP%\bin\freeglut\include"
%PPP%\bin\MinGW\bin\g++ -o %PPP%\out\%2.exe %PPP%\out\test.o -L"%PPP%\bin\freeglut\lib\x64" -lfreeglut -lopengl32 -Wl,--subsystem,windows
cd %1
copy "%PPP%\out\%2.exe" "%2.exe"
%2.exe