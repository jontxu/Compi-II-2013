/* infija.h (versión final ANT)
   Traductor de expresiones en notación infija a notación postfija
   (c) JosuKa Díaz Labrador 2006; see gpl.txt
*/

#include <stdio.h>

/* el tipo token: al usar lex, debe ser int */

typedef int TTOKEN;

/* el tipo atributo: hay dos posibles tipos */

typedef union {
	int  TCodigo;
	char *TCadena;
} YYSTYPE;

/* declaración para el programa lex */

extern YYSTYPE atribANT;

/* lista de nombres de tokens */

#define DOLAR	0	/* 0 porque así lo quiere lex */

#define SDOLAR	257	/* falso DOLAR: mejor el primero */
#define	PAR_ABR	258
#define	PAR_CER	259
#define	P_COMA	260
#define	NUM	261
#define	OP_ADIT	262	/* atrib 1 para el +, 2 para - */
#define	OP_MULT	263	/* 1: *, 2: /, 3: % */

extern void yyerror( char * );
