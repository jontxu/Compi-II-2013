rem cll1.bat (c) JosuKa D�az Labrador 2006; see gpl.txt
flex -ojkllex.c jkl.lex
gcc jkllex.c tpila.c jklmain.c -o jklc