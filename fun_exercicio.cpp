//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN



//EXERCÍCIO 03
/* OBS: Usei os seguintes valores para os parâmetros (não estão baseados em nenhuma literatura)
	b1 = 0.8; b2 = 0.4; d= 0.9; e = 0.1
*/

EQUATION("X")
CYCLE(cur, "FIRM")
 {
		v[0] = V("b1")*VS(cur,"P")+V("b2")*VS(cur,"QUALI")+RND;
 }
RESULT(v[0])

EQUATION("QUALI")
//variável no nivel da firma
CYCLE(cur, "FIRM")
 {
    v[0] = VLS(cur, "QUALI",1);
    v[1] = V("d")*v[0]+RND;
    if(v[1]<v[0])
    		{ 
    		v[2] = v[0];
    		}
    		else
    		{
    		v[2] = v[1];
    		}
 } 
RESULT(v[2])


EQUATION("P")
//variável no nivel da firma

CYCLE(cur, "FIRM")
 {
   v[0] = VLS(cur,"P",1);
   v[1] = VLS(cur,"X_Share",1);
   v[2] = VLS(cur,"X_Share",2);
   v[3] = v[1] - v[2];
   if(v[3]>0)
     		{ 
     		v[0]=v[0]+V("e");
     		}
     		else
     		{
     		v[0]=v[0];
     		}
     		
 }
RESULT(v[0])


EQUATION("X_Sum")
//Variável do setor
RESULT(SUM("X"))

EQUATION("X_Share")
//Variável da firma
	v[1] = V("X");
	v[2] = V("X_Sum");
	v[0] = v[1]/v[2];
RESULT(v[0])



// ======= MAIS ANTIGOS =======

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

/*
//Exercicio 01 - passeio aleatorio opcao 2
EQUATION("X")
RESULT(VL("X",1)+V("c"))
EQUATION("c")
v[0] = V("min");
v[1] = V("max");
v[2] = uniform(v[0], v[1]);
RESULT(v[2])
*/

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

/*
// EXERCICIO 02
EQUATION("X_Sum")
//Variável do setor
v[0] = 0;
CYCLE(cur, "FIRM")
{
			v[1] = VS(cur, "X");
			v[0] = v[0] + v[1];
}
RESULT(v[0])
*/

/*
EQUATION("X_Ave")
//Variável do setor
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
*/

/*
EQUATION("X_Max")
//Variável do setor
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
*/

/*
EQUATION("X_Share")
//Variável da firma
CYCLE(cur, "FIRM")
			{
			v[1] = VS(cur, "X");
			v[2] = VS(cur, "X_Sum");
			v[0] = v[1]/v[2];
			}
RESULT(v[0])
*/

/*
EQUATION("X_Share")
//Variável da firma
	v[1] = V("X");
	v[2] = V("X_Sum");
	v[0] = v[1]/v[2];
RESULT(v[0])
*/

/*
EQUATION("X_Share_Sum")
//Variável da firma
v[0] = 0;
CYCLE(cur, "FIRM")
			{
			v[1] = VS(cur, "X_Share");
			v[0] = v[0]+v[1];
			}
RESULT(v[0])
*/

/*
EQUATION("X_Share_Sum")
RESULT(SUM("X_Share"))
*/

/*
//DESAFIO
EQUATION("Leader")
v[0] = 0;
v[1] = 0;
CYCLE(cur, "FIRM")
{
			v[1] = v[1] + 1;
			v[2] = VS(cur, "X");
			if(v[2]>v[0])
			{
			v[0]=v[2];
			v[3]=v[1];
			}
}
RESULT(v[3])
*/

/*
//DESAFIO USANDO SEARCH
EQUATION("Leader")
  v[0] = V("X_Max");
  cur1 = SEARCH_CND("X", v[0]);
  v[1] = SEARCH_INST(cur1);
RESULT(v[1])	
*/

/*
// EXERCÍCIO 2.1 EXTRA
EQUATION("Rank")
	SORT("FIRM","X","DOWN");
	v[0]=0;
		CYCLE(cur, "FIRM")
		{
		v[0]++;
		WRITES(cur, "firm_rank", v[0]);
		}
RESULT(0)
//Sort reorganiza as firmas pelo critério de maior valor antes de passar o Cycle
//SORT(Objeto a organizar, critério, ordem cresc ou descresc)
//v[0]++ é o mesmo que v[0]=[v0]+1
//Write S é o Write para um objeto específico (s) (nesse caso, a firma apontado em "cur")
// WRITES(objeto específico, parâmetro em que deve escrever, valor a ser escrito)
*/

//Caso desejasse que o Firm_Rank fosse uma variável, é necessario atribuir uma equação
/*
EQUATION("Firm_Rank")
RESULT(CURRENT)
//ou
EQUATION_DUMMY("Firm_Rank","Rank")
*/
/*
EQUATION("EntryExit")
	c[0]=V("switch_entry");
	if(v[0]==1)
	{
		cur=SEARCH_CND("Firm_rank",10);
		DELETE(cur);
		cur1 = SEARCH_CND("firm_rank",5);
		ADDOBJ_EX("FIRM",cur1);
	}
RESULT(0)
//SEARCH_CND é a busca condicional (cnd). SEARCH_CDN(Objeto, condição)
//_EX em ADDOBJ serve para criar um objeto atribuindo valores de um exemplo (nesse caso, cur1)
*/



MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
