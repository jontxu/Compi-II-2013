  /* infijamain.c (versión iterativa ANT)
   Traductor de expresiones en notación infija a notación postfija
   Analizador sintáctico descendente iterativo
   (c) JosuKa Díaz Labrador 2006; see gpl.txt
*/

#include "tpila.h"

/* ya incluye infija.h */

/* Terminales de la gramática: están en infija.h */

#define TER_OFFSET 257

/* orden correlativo de códigos:
   SDOLAR PAR_ABR PAR_CER P_COMA NUM OP_ADIT OP_MULT
   recordar que DOLAR debe transformarse en SDOLAR
   con la siguiente función
*/

TTOKEN falsoyylex()
{
	TTOKEN token;

	token = yylex();
	if( token == DOLAR ) token = SDOLAR;
	return( token );
}

/* Variables de la gramática */

#define VAR_OFFSET 1000

#define VAR_S	1000
#define VAR_L	1001
#define VAR_E	1002
#define VAR_Ep	1003
#define VAR_T	1004
#define VAR_Tp	1005
#define VAR_F	1006

/* Acciones semánticas */

#define ACC_OFFSET 2000

#define ACC_A1	2000
#define ACC_A2	2001
#define ACC_A3	2002
#define ACC_A4	2003
#define ACC_A5	2004
#define ACC_A6	2005

/* Reglas de la gramática; por orden desde 0:
	0	regla de relleno (todo 0)
	1	S  -> L
	2	L  -> lambda
	3	L  -> E pto_coma A1 L
	4	E  -> T Ep
	5	Ep -> lambda
	6	Ep -> op_adit A2 T A3 Ep
	7	T  -> F Tp
	8	Tp -> lambda
	9	Tp -> op_mult A4 F A5 Tp
	10	F  -> n A6
	11	F  -> ( E )
   trucos:
   * solo hacen falta partes derechas
   * se meten ya invertidas
*/

int reglasG[12][6] = {
/*  0 */  { 0,       0,      0,       0,      0,       0 }
/*  1 */ ,{ VAR_L,   0,      0,       0,      0,       0 }
/*  2 */ ,{ 0,       0,      0,       0,      0,       0 }
/*  3 */ ,{ VAR_L,   ACC_A1, P_COMA,  VAR_E,  0,       0 }
/*  4 */ ,{ VAR_Ep,  VAR_T,  0,       0,      0,       0 }
/*  5 */ ,{ 0,       0,      0,       0,      0,       0 }
/*  6 */ ,{ VAR_Ep,  ACC_A3, VAR_T,   ACC_A2, OP_ADIT, 0 }
/*  7 */ ,{ VAR_Tp,  VAR_F,  0,       0,      0,       0 }
/*  8 */ ,{ 0,       0,      0,       0,      0,       0 }
/*  9 */ ,{ VAR_Tp,  ACC_A5, VAR_F,   ACC_A4, OP_MULT, 0 }
/* 10 */ ,{ ACC_A6,  NUM,    0,       0,      0,       0 }
/* 11 */ ,{ PAR_CER, VAR_E,  PAR_ABR, 0,      0,       0 }
};

/* Tabla LL(1) */

int tablaLL1[7][7] = {
/* cols:     SDOLAR PAR_ABR PAR_CER P_COMA NUM OP_ADIT OP_MULT */
/* S  */  {  1,     1,      0,      0,     1,  0,      0       }
/* L  */ ,{  2,     3,      0,      0,     3,  0,      0       }
/* E  */ ,{  0,     4,      0,      0,     4,  0,      0       }
/* Ep */ ,{  0,     0,      5,      5,     0,  6,      0       }
/* T  */ ,{  0,     7,      0,      0,     7,  0,      0       }
/* Tp */ ,{  0,     0,      8,      8,     0,  8,      9       }
/* F  */ ,{  0,    11,      0,      0,    10,  0,      0       }
};

/* Las variables globales */

TTOKEN  tokenACT, tokenANT;
YYSTYPE atribACT, atribANT;

void parear( TTOKEN token )
{
	if( token == tokenANT ) {
		tokenACT = tokenANT; atribACT = atribANT;
		tokenANT = falsoyylex();
			/* esta llamada actualiza lateralmente atribANT */
	} else
		yyerror( "syntactic error: token incorrecto" );
}

TPILA *pilaSint;
TPILA *pilaSem;

/* Las acciones semánticas */

void accA1()
{
	printf( "\n" );
}

void accA2()
{
    // pilaSem neutra 0
    pilaSem = pilaPUSH( pilaSem, atribACT );
    return;
    // pilaSem +1 (se añade contenido a la pila) op_adit
}

void accA3()
{
  // pilaSem +1 op_adit
   YYSTYPE op; //variable temporal para la extracción
  op = pilaTOP ( pilaSem );
  if ( op.TCodigo == 1) printf( "+ ");
  else ( op.TCodigo == 2) printf( "- ");
  else yyerror( "no debería darse" );
  pilaSem = pilaPOP( pilaSem );
  return;
  //pilaSem neutra (vacía)
}

void accA4()
{
}

void accA5()
{
}

void accA6()
{
	printf( "%s ", atribACT.TCadena );
}

/* El índice de acciones: esta sí que es buena */

void (*tablaACC[6])() = {
	accA1, accA2, accA3, accA4, accA5, accA6
};

main( int argc, char *argv[] )
{
	YYSTYPE toppila;
	int regla, var, term;
	int i;

	tokenACT = atribACT.TCodigo = 0;
	tokenANT = falsoyylex();
		/* esta llamada actualiza lateralmente atribANT */

	toppila.TCodigo = VAR_S;
	pilaSint = pilaPUSH( pilaSint, toppila );

		/* empieza el tema */
	while( pilaNOVACIA( pilaSint ) ) {
		toppila = pilaTOP( pilaSint );
		pilaSint = pilaPOP( pilaSint );
		if( toppila.TCodigo >= ACC_OFFSET ) {
				/* es una accion: ejecutar */
			tablaACC[ toppila.TCodigo - ACC_OFFSET ]();
		} else if( toppila.TCodigo >= VAR_OFFSET ) {
				/* es una variable: expandir */
			var = toppila.TCodigo - VAR_OFFSET;
			term = tokenANT - TER_OFFSET;
			regla = tablaLL1[var][term];
			if( regla == 0 )
				yyerror( "syntactic error: no hay regla" );
			else
				for( i=0; reglasG[regla][i]; i++ ) {
					toppila.TCodigo = reglasG[regla][i];
					pilaSint = pilaPUSH( pilaSint, toppila );
				}
		} else /* se supone que solo puede ser terminal: parear */
			parear( toppila.TCodigo );
	}

		/* acabó el tema */
	if( tokenANT != SDOLAR )
		yyerror( "syntactic error: programa debería haber acabado" );
}
