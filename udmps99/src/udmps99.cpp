/*
udmps99.cpp - main
Copyright (C) 1997, 1998, 1999, 2007, 2008, 2009, 2011
The UDMPs99 team (Universidad de Deusto)

The UDMPs99 team: Andoni Eguíluz, JosuKa Díaz
(Departamento de Ingeniería Informática, Facultad de Ingeniería)
and Jesús Redrado, Jorge García, Ana Cabana, Sergio Argüello, David Vázquez,
Igor Ruiz, David Ausín, Endika Gutiérrez, Luis Rodríguez

v.1.0ß 19990419
v.1.1ß 20110318

This file is part of UDMPs99.

UDMPs99 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

UDMPs99 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

// $JK200910 cambio 2 lineas...
//#include <stdio.h>
//#include <string.h>
// $JK200910 ... por 2 lineas...
#include <cstdio>
#include <cstring>
// $JK200910 ... hasta aqui
// $JK200910 linea nueva
#include <iostream>
// $JK200910 cambio linea
// #include "MaqPila.h"
#include "maqpila.h"

// $JK200910 linea nueva
using namespace std;

const char *CAD_UDMP = "udmps99";   // nombre de la aplicación

int main( int argc, char **argv ) {
// SAG: ¨esta variable?
//    int token;

// 201102 EGS+LRG+JK: asuntos finales
//    cout << CAD_UDMP << " v1.0á Int‚rprete de M quina de Pila Simb¢lica\n";
//    cout << "Universidad de Deusto - ESIDE 1997-99\n";
//    cout << "Dpto. de Lenguajes y Sistemas Inform ticos\n";
    cout << CAD_UDMP << " v1.1ß Intérprete de máquina de pila simbólica\n";
    cout << "Copyright (C) 2011 The UDMPs99 team - Universidad de Deusto\n\n";

    int log = 0,
        check_only = 0;

    if ( argc == 3 )
    {
// $JK200910 cambio 2 lineas...
//      log         = !strcmpi( argv[2], "-d" );
//      check_only  = !strcmpi( argv[2], "-c" );
// $JK200910 ... por 2 lineas...
        log         = !strcmp( argv[2], "-d" );
        check_only  = !strcmp( argv[2], "-c" );
// $JK200910 ... hasta aqui
    }

    if ( argc > 1 && argc < 4 )
    {
        MaqPila *maqpila = new MaqPila( argv[1], log );
        if( maqpila->error )
			cout << "\nNo se ha encontrado el fichero " << argv[1] << ".mpv";
		else
            maqpila->Ejecutar( check_only );
        delete maqpila;
    }
    else
    {
        cout << "Uso: " << CAD_UDMP << " <archivo_origen> [-d | -c]\n";
// 201102 EGS+LRG+JK: asuntos finales
//        cout << "\t<archivo_origen>: fichero fuente (sin extension), busca .mpv\n";
        cout << "\t<archivo_origen>: fichero fuente (sin extensión), busca .mpv\n";
        cout << "\t-d: genera archivo <archivo_origen>.log con traza (peligroso)\n";
        cout << "\t-c: comprueba el archivo origen (sin ejecutarlo)\n\n";
		cout << "This is free software; see the source for copying conditions.  There is NO\n";
		cout << "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";
    }
    return 0;
}
