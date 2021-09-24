#include<stdio.h>
#include<stdlib.h>

#define infinity 9999
#define MAX 20

int grafo[MAX][MAX],geradora[MAX][MAX],vertices;

int prim()
{
	int custo[MAX][MAX];
	int u,v,menor_distancia,distancia[MAX],desde[MAX];
	int visitado[MAX],arestas,i,custo_minimo,j;
	for(i=0;i<vertices;i++)
		for(j=0;j<vertices;j++)
		{
			if(grafo[i][j]==0)
				custo[i][j]=infinity;
			else
				custo[i][j]=grafo[i][j];
			geradora[i][j]=0;
		}
		distancia[0]=0;
		visitado[0]=1;
		for(i=1;i<vertices;i++)
		{
			distancia[i]=custo[0][i];
			desde[i]=0;
			visitado[i]=0;
		}
		custo_minimo=0; 
		arestas=vertices-1; 
		while(arestas>0)
		{
			menor_distancia=infinity;
			for(i=1;i<vertices;i++)
				if(visitado[i]==0 && distancia[i]<menor_distancia)
				{
					v=i;
					menor_distancia=distancia[i];
				}
				u=desde[v];
				geradora[u][v]=distancia[v];
				geradora[v][u]=distancia[v];
				arestas--;
				visitado[v]=1;
				for(i=1;i<vertices;i++)
					if(visitado[i]==0 && custo[i][v]<distancia[i])
					{
						distancia[i]=custo[i][v];
						desde[i]=v;
					}
					custo_minimo=custo_minimo+custo[u][v];
				}
				return(custo_minimo);
			}

			int main()
			{
				int i, j, linha, coluna, peso, arestas2, custo_total;
				char aux, nome[30];
				printf("Digite o nome do arquivo de entrada:\n");
				scanf("%s", nome);
				getchar();
				FILE *arquivo;
				arquivo = fopen(nome, "r");
				fscanf(arquivo, "%d", &vertices);
				fscanf(arquivo, "%d", &arestas2);
				for(i=0;i<arestas2;i++){
					fscanf(arquivo, "%d", &linha);
					fscanf(arquivo, "%d", &coluna);
					fscanf(arquivo, "%c", &aux);
					if (aux == ' ')
					{
						fscanf(arquivo, "%d", &peso);
					}else{
						peso = 1;
					}
					grafo[linha-1][coluna-1] = peso;
					grafo[coluna-1][linha-1] = peso;
				}
				custo_total=prim();
				printf("\nMatriz da arvore geradora:\n");
				for(i=0;i<vertices;i++)
				{
					printf("\n");
					for(j=0;j<vertices;j++)
						printf("%d\t",geradora[i][j]);
				}
				printf("\n\nCusto total da arvore geradora = %d",custo_total);
				return 0;
			}