#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
#define BRANCO 0
#define AMARELO 1
#define VERMELHO 2
typedef int TIPOPESO;
int cycle=0;

typedef struct adjacencia {
    int vertice;
    TIPOPESO peso;
    struct adjacencia * prox;
} ADJACENCIA;

typedef struct vertice {
    ADJACENCIA * cab;
} VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE * adj;
} GRAFO;

GRAFO * criaGrafo (int v) {
    int i;
    GRAFO * g = (GRAFO*)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE * )malloc(v*sizeof(VERTICE));

    for(i=0; i<v; i++)
        g->adj[i].cab = NULL;
    return(g);
}

ADJACENCIA * criaAdj(int v, int peso) {
    ADJACENCIA * temp = (ADJACENCIA *) malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->peso= peso;
    temp->prox = NULL;
    return (temp);
}

int criaAresta(GRAFO * gr, int vi, int vf, TIPOPESO p) {
    if(!gr)
    return (false);
    if((vf<0)||(vf >= gr->vertices))
    return(false);
    if((vi<0)||(vi >= gr->vertices))
    return(false);

    ADJACENCIA * novo = criaAdj(vf,p);
    novo->prox = gr->adj[vi].cab;
    gr->adj[vi].cab = novo;
    gr->arestas++;
    return (true);
}

void buscaPr (GRAFO * g, int u, int * cor) {
    cor[u] = AMARELO;
    ADJACENCIA *v =  g->adj[u].cab;
        while (v) {
            if(cor[v->vertice]==BRANCO)
            buscaPr(g,v->vertice,cor);
            if(cor[v->vertice]==AMARELO){
                cycle++;
            }
            v=v->prox;
        }
    cor[u]= VERMELHO;
}

void checkCycle (GRAFO * g) {
    int cor[g->vertices];
    int i=0,u;
    for(i=0; i<g->vertices;i++){
        cor[i] = BRANCO;
    }
    for(u=0; u<g->vertices;u++) {
        if(cor[u] == BRANCO)
        buscaPr(g,u,cor);
    }
}

void imprimeGrafo(GRAFO *gr) {
    printf("Vertices: %d. Arestas: %d.\n", gr->vertices, gr->arestas);
    int i;
    for(i=0; i<gr->vertices; i++) {
        printf("v%d: ",i);
        ADJACENCIA *ad = gr->adj[i].cab;
        while(ad) {
            printf("v%d(%d) ", ad->vertice, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
}

int main () {
    GRAFO * G = criaGrafo(5);
    criaAresta(G,0,1,2);
    criaAresta(G,1,2,4);
    criaAresta(G,2,0,12);
    criaAresta(G,2,4,40);
    criaAresta(G,3,1,3);
    criaAresta(G,4,3,8);
    checkCycle(G);
    if(cycle!=0)
    printf("O grafo possui ciclos\n");
    else
    printf("Grafo aciclico\n");

    return 0;
}