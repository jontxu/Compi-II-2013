rem cll1.bat (c) JosuKa Díaz Labrador 2006; see gpl.txt
flex -oinfijalex.c infija.lex
gcc infijalex.c infijamain.c -o inf2post.exe
