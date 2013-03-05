rem Genera UDMPs99.exe en Win32 con DJGPP
gpp -Wall -ggdb -I "./include" -DDEBUG -Os codinter.cpp lexyy.cpp maqpila.cpp pila.cpp tabla.cpp udmps99.cpp -o udmps99.exe
move /y udmps99.exe ..\bin\win_djgpp\