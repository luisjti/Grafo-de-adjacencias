#include <stdio.h>
#include <stdlib.h>

#define MAXNUMVERTICES 100
#define MAXNUMARESTAS 4500
#define MAXR 5
#define MAXTAMPROX (MAXR * MAXNUMARESTAS)
#define INDEFINIDO −1
#define FALSE 0
#define TRUE 1

typedef int TipoValorVertice;
typedef int TipoValorAresta;
typedef int Tipor;
typedef int TipoPesoAresta;
typedef int TipoPeso;
typedef TipoValorVertice TipoArranjoVertices[MAXR] ;
typedef int TipoApontador;
typedef int TipoMaxTamProx;

typedef struct TipoItem {
TipoValorVertice Vertice ;
TipoPeso Peso;
int Chave;
} TipoItem;
typedef struct TipoAresta {
TipoArranjoVertices Vertices ;
TipoPesoAresta Peso;
} TipoAresta;
typedef TipoAresta TipoArranjoArestas[MAXNUMARESTAS + 1];
typedef struct TipoGrafo {
TipoArranjoArestas Arestas;
TipoPeso Mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
int NumVertices;
int NumArestas;
TipoValorVertice Prim[MAXNUMARESTAS + 1];
TipoMaxTamProx Prox[MAXTAMPROX + 2];
TipoMaxTamProx ProxDisponivel;
Tipor r ;
} TipoGrafo;
typedef int TipoApontador;

struct TipoCelula {
TipoItem Item;
TipoApontador Prox;
} TipoCelula;

int i , j ;
TipoAresta Aresta;
TipoGrafo Grafo;
TipoArranjoArestas L;
short GAciclico;
typedef int TipoApontador;

void FGVazio(TipoGrafo  *Grafo){
  short i , j ;
  for ( i = 0; i <= Grafo->NumVertices; i++){
    for ( j = 0; j <= Grafo->NumVertices; j ++)
      Grafo->Mat[i][j] = 0;
  }
}
void InsereAresta(TipoValorVertice *V1,TipoValorVertice*V2,TipoPeso*Peso, TipoGrafo*Grafo){
  Grafo->Mat[*V1][*V2] = *Peso;
}
short ExisteAresta(TipoValorVertice Vertice1 , TipoValorVertice Vertice2 , TipoGrafo *Grafo) {
  return (Grafo->Mat[Vertice1][Vertice2] > 0);
}

short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo){ TipoApontador Aux = 0;
  short ListaVazia = TRUE;
while (Aux < Grafo->NumVertices && ListaVazia)
  if (Grafo->Mat[*Vertice][Aux] > 0) ListaVazia = FALSE;
else Aux++;
  return(ListaVazia == TRUE);
}

TipoApontador PrimeiroListaAdj ( TipoValorVertice *Vertice , TipoGrafo
*Grafo){
  TipoValorVertice Result;
  TipoApontador Aux = 0;
  short ListaVazia = TRUE;
  while (Aux < Grafo->NumVertices && ListaVazia){
    if (Grafo->Mat[*Vertice] [Aux] > 0) { Result = Aux; ListaVazia = FALSE;
    }
  else Aux++;
  }
  if (Aux == Grafo->NumVertices)
  printf ( "Erro : Lista adjacencia vazia ( PrimeiroListaAdj )\n" );
  return Result;
}

void ProxAdj(TipoValorVertice*Vertice , TipoGrafo*Grafo,TipoValorVertice
*Adj , TipoPeso*Peso,TipoApontador*Prox, short*FimListaAdj){
  *Adj = *Prox;
  *Peso = Grafo->Mat[*Vertice][*Prox] ;
  (*Prox)++;
  while(*Prox < Grafo->NumVertices && Grafo->Mat[*Vertice][*Prox] == 0)   (*Prox)++;
  if(*Prox == Grafo->NumVertices)
    *FimListaAdj = TRUE;
}

void RetiraAresta(TipoValorVertice*V1, TipoValorVertice*V2,TipoPeso
*Peso, TipoGrafo*Grafo){ 
  if (Grafo->Mat[*V1][*V2] == 0)
    printf ( "Aresta nao existe \n" );
  else{
  *Peso = Grafo->Mat[*V1][*V2];
  Grafo->Mat[*V1][*V2] = 0;
  }
}
void LiberaGrafo(TipoGrafo*Grafo){
}
void ImprimeGrafo(TipoGrafo*Grafo){
  short i , j ; printf ( " " );
  for ( i = 0; i <= Grafo->NumVertices - 1; i ++)
    printf("%3d", i );
    printf("\n" );
  for ( i = 0; i <= Grafo->NumVertices - 1; i++){
    printf("%3d", i );
    for(j = 0; j <=Grafo->NumVertices - 1; j++)
      printf("%3d" , Grafo->Mat[i][j]);
    printf("\n" );
  }
}

short VerticeGrauUm(TipoValorVertice*V, TipoGrafo*Grafo){
  return(Grafo->Prim[*V] >= 0) && (&Grafo->Prox[Grafo->Prim[*V]] == NULL);
}

void GrafoAciclico (TipoGrafo*Grafo, TipoArranjoArestas L, short *GAciclico){
  TipoValorVertice j = 0; TipoValorAresta A1;
  TipoItem x;
  TipoFila Fila;
  TipoValorAresta NArestas;
  TipoAresta Aresta;
  NArestas = Grafo->NumArestas; 
  FGVazio(&Fila);
  while ( j < Grafo->NumVertices){
      if (VerticeGrauUm (&j , Grafo)){
        x.Chave = j;
        Enfileira(x, &Fila);
      }
    j ++;
  }
  while ( !Vazia(&Fila) && (NArestas > 0)){
    Desenfileira (&Fila , &x);
    if (Grafo->Prim[x.Chave] >= 0)
    { A1 = Grafo->Prim[x.Chave] % Grafo->NumArestas;
    Aresta = RetiraAresta(&Grafo->Arestas[A1] , Grafo);
    L[Grafo->NumArestas - NArestas] = Aresta;
    NArestas = NArestas - 1;
      if (NArestas > 0){
        for ( j = 0; j < Grafo->r ; j++){
          if (VerticeGrauUm(&Aresta. Vertices [ j ] , Grafo)){
            x.Chave = Aresta. Vertices [ j ] ; Enfileira (x, &Fila );
          }
        }
      }
    }
  }
  if (NArestas == 0)
  *GAciclico = TRUE;
  else
    *GAciclico = FALSE;
}