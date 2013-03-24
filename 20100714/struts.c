//pilaSem neutra
void accA1() {
	struct TRegA rA;
	rA.eR = etiqNew();
	rA.eD = etiqNew();
	rA.id = atribACT.TCadena;
	gc1("ir_a", rA.eR);
	gc1("etiq", rA.eD);
	gc1("valori", rA.id);
	pilaSem = pilaPUSH(pilaSem, rA);
	return;
}
//pilaSem +1 rA

//pilaSem +1 rA
void accA2() {
	struct TRegA rA;
	rA = pilaTOP(pilaSem);
	gc0(":=");
	gc1("etiq", rA.eR);
	/*
	 * etiqFree(rA.eR);
	 * etiqFree(rA.eD);
	 * pilaSem = pilaPOP(pilaSem);
         * No hay que eliminar la cima de la pila porque si no se pierden la etiqueta #DATE y el id.
	*/
	return;
}
//pilaSem +1 rA
void AccA3() {
	struct TRegA rA;
	rA = pilaTOP(pilaSem);
	etiqFree(rA.eR);
       	etiqFree(rA.eD);
        pilaSem = pilaPOP(pilaSem);
}
//pilaSem neutra

//pilaSem +1 rA
void AccB0 {
	struct TRegB rB;
	rB.cte = atribACT.TCadena;
	pilaSem = pilaPush(pilaSem, rB);
	return;
}
//pilaSem +2 rA, rB

//pilaSem +2 rA, rB
void accB1() {
	struct TRegA rA;
	struct TRegB rB;
	rB = pilaTOP(pilaSem);
	pilaSem = pilaPOP(pilaSem);
	rA = pilaTOP(pilaSem);
	gc1("valord", rA.id);
	gc1("insi", rB.cte);
	gc0("==");
	gc1("si_falso_ir_a", rA.eD);
	return;
}
//pilaSem +1 rA
