/* tpila.c
   TAD (bueno, quizás no tanto) pila
   (c) JosuKa Díaz Labrador 2006; see gpl.txt
*/

#include <stdlib.h>
#include "tpila.h"

TPILA *pilaNOVACIA( TPILA *pila )
{
	return( pila );		/* pilaNOVACIA(pila) = pila */
}

TPILA *pilaPUSH( TPILA *pila, YYSTYPE data )
{
	TPILA *newtop;

	newtop = (TPILA *)calloc( 1, sizeof( TPILA ) );
	newtop->sig = pila;
	newtop->content = data;
	return( newtop );
}

YYSTYPE pilaTOP( TPILA *pila )
{
	if( ! pila ) {
		printf( "\n¡¡CHAVAL!!\n" );
		exit( 2 );
	}
	return( pila->content );
}

TPILA *pilaPOP( TPILA *pila )
{
	TPILA *newtop;

	if( ! pila ) {
		printf( "\n¡¡CHAVAL!!\n" );
		exit( 3 );
	}
	newtop = pila->sig;
	free( pila );
	return( newtop );
}
