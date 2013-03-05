rem Genera UDMPs99.exe en Win32 con mingw
g++ -Wall -ggdb -static -I ./ -I ./include -DDEBUG -Os codinter.cpp lexyy.cpp maqpila.cpp pila.cpp tabla.cpp udmps99.cpp -o udmps99d.exe
move /y udmps99d.exe ..\bin\win_mingw\