/* jkl.h
   Compilador del lenguaje JKL
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

#define	DOLAR	0	/* 0 porque así lo quiere lex */

#define	SDOLAR	257	/* falso DOLAR: mejor el primero */
#define	PAR_ABR	258
#define	PAR_CER	259
#define	P_COMA	260
#define	OP_OR	261
#define	OP_AND	262
#define	OP_REL	263
#define	OP_ADIT	264
#define	OP_MULT	265
#define	OP_NOT	266
#define	NUM		267
#define	ID		268
#define	ASIGN	269
#define	PUNTO	270
#define	CAD		271
#define	PBEGIN	272
#define	PEND	273
#define	PPROG	274
#define	PVAR	275
#define	PREAD	276
#define	PWRITE	277
#define	PWRITC	278
#define	PWRITL	279
#define	PIF		280
#define	PTHEN	281
#define	PELSE	282
#define	PWHILE	283
#define	PDO		284
#define	PFOR	285
#define	PTODO	286

extern void yyerror( char * );
