#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
struct Aresta
{
    int origin, destino, peso;
};
 
struct Grafo
{
    int vert, arest;
 
    struct Aresta* aresta;
};
 
struct Grafo* criarGrafo(int vert, int arest)
{
    struct Grafo* grafo = (struct Grafo*) malloc( sizeof(struct Grafo));
 
    grafo->vert = vert;  
 
    grafo->arest = arest;
 
    grafo->aresta = (struct Aresta*) malloc( grafo->arest * sizeof( struct Aresta ) );
 
    return grafo;
}
 
void final(int dist[], int n)
{
    printf("Vertice \t\t Distancia da origem\n");
    int i;
 
    for (i = 0; i < n; ++i)
    {
        printf("%d \t\t %d\n", i + 1, dist[i]);
    }
}
 
void BellmanFord(struct Grafo* grafo, int origin)
{
    int vert = grafo->vert;
 
    int arest = grafo->arest;
 
    int distancia[vert];
 
    int i,j;
 
    for (i = 0; i < vert; i++)
    {
         distancia[i] = INT_MAX;
    }
 
    distancia[origin] = 0;
 
    for (i = 1; i <= vert-1; i++)
    {
        for (j = 0; j < arest; j++)
        {
            int u = grafo->aresta[j].origin;
 
            int v = grafo->aresta[j].destino;
 
            int peso = grafo->aresta[j].peso;
 
            if (distancia[u] + peso < distancia[v])
            {
                distancia[v] = distancia[u] + peso;
            }
        }
    }
 
    for (i = 0; i < arest; i++)
    {
        int u = grafo->aresta[i].origin;
 
        int v = grafo->aresta[i].destino;
 
        int peso = grafo->aresta[i].peso;
 
        if (distancia[u] + peso < distancia[v])
        {
            printf("O grafo contem um ciclo negativo\n");
        }
    }
 
    final(distancia, vert);
 
    return;
}
 
 
int main()
{
    int vertices,arestas,i; 
    char nome[30];
    char aux;
    printf("Digite o nome do arquivo de entrada:\n");
    scanf("%s", nome);
    getchar();
    FILE *arquivo;
    arquivo = fopen(nome, "r");

    fscanf(arquivo, "%d", &vertices);
    fscanf(arquivo, "%d", &arestas);
    struct Grafo* grafo = criarGrafo(vertices, arestas);
    for(i=0;i<arestas;i++)
    {
        fscanf(arquivo, "%d", &grafo->aresta[i].origin);
        grafo->aresta[i].origin--;
        fscanf(arquivo, "%d", &grafo->aresta[i].destino);
        grafo->aresta[i].destino--;
        fscanf(arquivo, "%c", &aux);
        if (aux == ' ')
        {
            fscanf(arquivo, "%d", &grafo->aresta[i].peso);
        }
        else
        {
            grafo->aresta[i].peso = 1;
        }
    }     
    

    BellmanFord(grafo, 0);
 
    return 0;
}