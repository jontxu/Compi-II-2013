/* infija.h (versi�n final ANT)
   Traductor de expresiones en notaci�n infija a notaci�n postfija
   (c) JosuKa D�az Labrador 2006; see gpl.txt
*/

/* el tipo token: tiene que ser el mismo de los defines de m�s abajo */

typedef int TTOKEN;

/* el tipo atributo: hay dos posibles tipos */

typedef union {
	int  TCodigo;
	char *TCadena;
} YYSTYPE;

/* declaraci�n para el programa lex */

extern YYSTYPE atribANT;

/* lista de nombres de tokens */

#define DOLAR	0	/* 0 porque as� lo quiere lex */

#define	PAR_ABR	258
#define	PAR_CER	259
#define	PTO_COMA	260
#define	NUM	261
#define	OP_ADIT	262
#define	OP_MULT	263

extern void yyerror( char * );
