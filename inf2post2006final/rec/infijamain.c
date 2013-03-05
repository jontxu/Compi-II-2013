/* infijamain.c (versión final ANT)
   Traductor de expresiones en notación infija a notación postfija
   Analizador sintáctico descendente recursivo
   (c) JosuKa Díaz Labrador 2006; see gpl.txt
*/

#include "infija.h"

TTOKEN tokenACT, tokenANT;
YYSTYPE atribACT, atribANT;

void parear( TTOKEN token )
{
	if( token == tokenANT ) {
		tokenACT = tokenANT; atribACT = atribANT;
		tokenANT = yylex();
			/* esta llamada actualiza lateralmente atribANT */
	} else
		yyerror( "syntactic error: token incorrecto" );
}

/* Los procedimientos de los no-terminales */

extern void S();
extern void L();
extern void E();
extern void Ep();
extern void T();
extern void Tp();
extern void F();

void S()
{
	switch( tokenANT ) {
	case NUM:
	case PAR_ABR:
	case DOLAR:
		L();
		break;
	default:
		yyerror( "syntactic error: regla incorrecta" );
		break;
	}
}

void L()
{
	switch( tokenANT ) {
	case NUM:
	case PAR_ABR:
		E();
		parear(PTO_COMA);

		printf( "\n" );

		L();
		break;
	case DOLAR:
		/* regla vacía */
		break;
	default:
		yyerror( "syntactic error: regla incorrecta" );
		break;
	}
}

void E()
{
	switch( tokenANT ) {
	case NUM:
	case PAR_ABR:
		T();
		Ep();
		break;
	default:
		yyerror( "syntactic error: regla incorrecta" );
		break;
	}
}

void Ep()
{
	switch( tokenANT ) {
	case OP_ADIT:
		parear(OP_ADIT);
		T();
		Ep();
		break;
	case PTO_COMA:
	case PAR_CER:
		/* regla vacía */
		break;
	default:
		yyerror( "syntactic error: regla incorrecta" );
		break;
	}
}

void T()
{
	switch( tokenANT ) {
	case NUM:
	case PAR_ABR:
		F();
		Tp();
		break;
	default:
		yyerror( "syntactic error: regla incorrecta" );
		break;
	}
}

void Tp()
{
	switch( tokenANT ) {
	case OP_MULT:
		parear(OP_MULT);
		F();
		Tp();
		break;
	case OP_ADIT:
	case PTO_COMA:
	case PAR_CER:
		/* regla vacía */
		break;
	default:
		yyerror( "syntactic error: regla incorrecta" );
		break;
	}
}

void F()
{
	switch( tokenANT ) {
	case NUM:
		parear(NUM);

		printf( "%s ", atribACT.TCadena );

		break;
	case PAR_ABR:
		parear(PAR_ABR);
		E();
		parear(PAR_CER);
		break;
	default:
		yyerror( "syntactic error: regla incorrecta" );
		break;
	}
}

main( int argc, char *argv[] )
{
	tokenACT = atribACT.TCodigo = 0;
	tokenANT = yylex();
		/* esta llamada actualiza lateralmente atribANT */
	S();
	if( tokenANT != DOLAR )
		yyerror( "syntactic error: programa debería haber acabado" );
}
