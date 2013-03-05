rem Genera UDMPs99.exe en Win32 con vs

call "%VS100COMNTOOLS%vsvars32"
cl -I ./ -I ./include /MT /O1 /GL codinter.cpp lexyy.cpp maqpila.cpp pila.cpp tabla.cpp udmps99.cpp -o ..\bin\win_vs\udmps99.exe
del *.obj