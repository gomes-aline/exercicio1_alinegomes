//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

// insert your equations here, between the MODELBEGIN and MODELEND words

//Exemplo aula 01
/*
<<<<<<< Updated upstream
EQUATION("X")
//Variável X
RESULT(VL("X",1)+V("c"))
*/

/*
//Exercicio 01 - passeio aleatorio
EQUATION("X")
RESULT(VL("X",1)+RND)
*/


//Exercicio 01 - passeio aleatorio opcao 2
EQUATION("X")
RESULT(VL("X",1)+V("c"))
EQUATION("c")
v[0] = V("min");
v[1] = V("max");
v[2] = uniform(v[0], v[1]);
RESULT(v[2])


/*
//Exercicio 01 - passeio aleatorio opcao 3
EQUATION("X")
v[0] = CURRENT;
v[1] = V("c");
v[2] = v[0]+v[1];
RESULT(v[2])
*/


/*
// Exemplo aula 02
EQUATION("X_Sum")
//Variável do setor
RESULT(SUM("X"))

EQUATION("X_Ave")
//Variável do setor
RESULT(AVE("X"))

EQUATION("X_Max")
//Variável do setor
RESULT(MAX("X"))
*/

// EXERCICIO 02
EQUATION("X_Sum")
/*
Variável do setor
*/
v[0] = 0;
CYCLE(cur, "FIRM")
{
			v[1] = VS(cur, "X");
			v[0] = v[0] + v[1];
}
RESULT(v[0])

EQUATION("X_Ave")
/*
Variável do setor
*/
v[0] = 0;
v[2] = 0;
CYCLE(cur, "FIRM")
{
			v[1] = VS(cur, "X");
			v[0] = v[0] + v[1];
			v[2] = v[2] + 1;
			v[3] = v[0]/v[2];
}
RESULT(v[3])

EQUATION("X_Max")
/*
Variável do setor
*/
v[0] = 0;
CYCLE(cur, "FIRM")
{
			v[1] = VS(cur, "X");
					if(v[1]>v[0])
					{ 
					v[2] = v[1];
					}
					else
					{
					v[2] = v[0];
					}
		
		v[0] = v[2];			
}
RESULT(v[2])


EQUATION("X_Share")
//Variável da firma
CYCLE(cur, "FIRM")
{
			v[1] = VS(cur, "X");
			v[2] = VS(cur, "X_Sum");
			v[0] = v[1]/v[2];
}
RESULT(v[0])


EQUATION("X_Share_Sum")
//Variável da firma
v[0] = 0;
CYCLE(cur, "FIRM")
{
			v[1] = VS(cur, "X_Share");
			v[0] = v[0]+v[1];
			}
RESULT(v[0])

MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
