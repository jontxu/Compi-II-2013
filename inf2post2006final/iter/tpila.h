/* tpila.h
   TAD (bueno, quizás no tanto) pila
   (c) JosuKa Díaz Labrador 2006; see gpl.txt
*/

#include "infija.h"

/* la pila puede tener los mismos tipos que los atributos: YYSTYPE */

struct tpila {
	YYSTYPE       content;
	struct tpila *sig;
};

typedef struct tpila TPILA;

TPILA  * pilaNOVACIA( TPILA *pila );
TPILA  * pilaPUSH( TPILA *pila, YYSTYPE data );
YYSTYPE  pilaTOP( TPILA *pila );
TPILA  * pilaPOP( TPILA *pila );
