// ----------------------------------------------------------------------------
// Remove 0s de um vetor
// Para compilar: gcc remove0_seq.c -o remove0_seq -Wall
// Para executar: ./remove0_seq arquivo_entrada arquivo_saida

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// ----------------------------------------------------------------------------
void remove0(int n, int *vIn, int *m, int *vOut)
{
	int i,
		 c = 0;

	for (i = 0; i < n; i++)
	{
		if (vIn[i] != 0)
		{
			vOut[c] = vIn[i];
			c++;
		}
	}
	*m = c;
}
// ----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	int n,		// Número de elementos do vetor de entrada (com 0s)
		 m,		// Número de elementos do vetor de saída (sem 0s)
		 *vIn,	// Vetor de entrada de n elementos
		 *vOut,	// Vetor de saída de no máximo n elementos
		 i;
	FILE *arqIn,	// Arquivo texto de entrada
		  *arqOut;	// Arquivo texto de saída

	// -------------------------------------------------------------------------
	// Inicialização

	if(argc != 3)
	{
		printf("O programa foi executado com argumentos incorretos.\n") ;
		printf("Uso: ./remove0_seq arquivo_entrada arquivo_saida\n") ;
		exit(1) ;
	}

	// Abre arquivo de entrada
	arqIn = fopen(argv[1], "rt") ;

	if (arqIn == NULL)
	{
		printf("\nArquivo texto de entrada não encontrado\n") ;
		exit(1) ;
	}

	// Lê tamanho do vetor de entrada
	fscanf(arqIn, "%d", &n) ;

	// Aloca vetores de entrada e saída
	vIn  = (int *) malloc(n * sizeof(int));
	vOut = (int *) malloc(n * sizeof(int));
	if ((vIn == NULL) || (vOut == NULL))
	{
		printf("\nErro na alocação de estruturas\n") ;
		exit(1) ;
	}

	// Lê vetor do arquivo de entrada
	for (i = 0; i < n; i++)
	{
		fscanf(arqIn, "%d", &(vIn[i]));
	}

	// Fecha arquivo de entrada
	fclose(arqIn) ;

	// -------------------------------------------------------------------------
	// Corpo principal do programa

	// Mede instante de tempo inicial
	struct timeval tIni, tFim;
	gettimeofday(&tIni, 0);

	// Remove 0s do vetor de entrada, produzindo vetor de saída
	remove0(n, vIn, &m, vOut);

	// Mede instante de tempo final
	gettimeofday(&tFim, 0);
	// Tempo de execução em milissegundos
	long segundos = tFim.tv_sec - tIni.tv_sec;
	long microsegundos = tFim.tv_usec - tIni.tv_usec;
	double tempo = (segundos * 1e3) + (microsegundos * 1e-3);
	printf("Tempo=%.2fms\n", tempo);

	// -------------------------------------------------------------------------
	// Finalização

	// Cria arquivo de saída
	arqOut = fopen(argv[2], "wt") ;

	// Escreve tamanho do vetor de saída
	fprintf(arqOut, "%d\n", m) ;

	// Escreve vetor do arquivo de saída
	for (i = 0; i < m; i++)
	{
		fprintf(arqOut, "%d ", vOut[i]);
	}
	fprintf(arqOut, "\n");

	// Fecha arquivo de saída
	fclose(arqOut) ;

	// Libera vetores de entrada e saída
	free(vIn);
	free(vOut);

	return 0;
}
