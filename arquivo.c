#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

Lista* criaLista(){
	//Cria a lista
	Lista* novaLista = (Lista*) malloc(sizeof(Lista));
	//Valida que nenhum erro aconteceu
	if(novaLista == NULL){
		printf("Nao consegui alocar memoria /0\/");
	}
	//Inicia inicio e fim da lista com NULL
	novaLista->inicio = NULL;
	novaLista->fim = NULL;
	
	//Retorna Lista
	return novaLista;	
}

void criarArquivo(int qntNumeros){
	//Variáveis
	FILE *arquivo;	
	
	//Abre o aqruivo, e sobreescreve o mesmo caso já exita
	arquivo = fopen("arquivo.txt", "w");
	//Seta tempo para o sorteio
	srand(time(NULL));
	//Sorteia e grava no arquivo de acordo com a qunatidade de números desejados
	for(int i = 0; i < qntNumeros; i ++){			
		fprintf(arquivo, "%d;", rand() % 1000);
	}
	
	//Fecha o arquivo
	fclose(arquivo);
};

void popularLista(Lista** lista){	
	//Variáveis
	FILE *arquivo;	
	char* conteudo;
	//Abre o arquivo
	arquivo = fopen("arquivo.txt", "r");
	//Valida que nenhum erro aconteceu
	if(arquivo == 0) {
		printf("Erro ao abrir arquivo\n\n");
		exit(1);
	}
	
	//verifica qual é tamanho do arquivo para criar uma variável do tamanho correspondente
	fseek( arquivo, 0L, SEEK_END );
    long tam = ftell(arquivo);
	conteudo = (char *)malloc(tam * sizeof(char)); 
	//Verifica se conseguiu alocar a memória
	if(conteudo == NULL){
		printf("Nao consegui alocar memoria /0\/");
	}
	
	//Fecha o arquivo
	fclose(arquivo);
	
	//Abre o arquivo
	arquivo = fopen("arquivo.txt", "r");	
	//Verifica se conseguiu abrir o arquivo
	if(arquivo == 0) {
		printf("Erro ao abrir arquivo :/\n\n");
		exit(1);
	}
	
	//Lê o arquivo
	fscanf(arquivo, "%s", conteudo);
	//Fecha o arquivo
	fclose(arquivo);    	
	
	//Separa o conteúdo do arquivo de acordo com ';'
	if(conteudo != NULL){
		//pega o primeiro valor
		conteudo = strtok(conteudo, ";");
		
		while(conteudo != NULL){	
			//Insere na lista os valores separados				
			insereNaLista(lista, strtol(conteudo, NULL, 10));	
			//Pega o próximo valor			
			conteudo = strtok(NULL, ";");   			
		}  		   				
	} else{
		//Imprime mensagem na tela caso algum erro aconteça
		printf("Algum erro aconteceu ao tentar realizar a leitura do arquivo");
	}
	
	//Libera memória
   	free(conteudo);
   	free(conteudo);
};

void insereNaLista(Lista** lista, int valor){	
	//Cria nó alocando memória
	No* no = (No*) malloc(sizeof(No));
	//Verifica se conseguiu alocar a memória
	if(no == NULL){
		printf("Nao consegui alocar memoria \0/");
	}
	
	//Coloca o valor no novo nó
	no->valor = valor;
		
	//verifica se o sim é null
	if((*lista)->fim == NULL){
		//seta o proximo do no como null
		no->prox = NULL;
		//seta o anterior do no como null
		no->ant = NULL;
		// pega o inicio e seta nele o novo nó
		(*lista)->inicio = no;
	}
	else{
		//seta null no proximo do nó
		no->prox = NULL;
		//seta o final da lista no anterior do nó
		no->ant = (*lista)->fim;
		//seta no proximo do fim e seta o no
		(*lista)->fim->prox = no;
	}
	//pega a lista e seta o novo nó como fim
	(*lista)->fim = no;		
}

int intParaBinario(int valor){
	//Variáveis
	int i = 0, j;
	int binario[15];
	int num =0;
	
	while(valor > 0)
	{
		//Obtém o resto da divisão de num por 2
		binario[i] = valor % 2;		
		// Adiciona +1 na contagem
		i++;
		valor = valor / 2;
	}

	//Percorre o vetor para mostrar o número em binário
	for(j = i - 1; j >= 0; j--){
		num = num *10 +  binario[j];
	}
}

void insereOrdenado(Lista** lista, int valor){	
	//Cria lista, alocando certinho
	No* no = (No*) malloc(sizeof(No));
	//Verifica se conseguiu alocar memória
	if(no == NULL){
		printf("Nao consegui alocar memoria \0/");
	}
	//Coloca o valor no novo nó
	no->valor = valor;
	
	//Verifica se o incio da lista é null
	if((*lista)->inicio == NULL){
		//seta o valor do próximo como null
		no->prox = NULL;
		//seta o valor do anterior como null
		no->ant = NULL;
		//pega o final e seta com o nó
		(*lista)->fim = no;
		//pega a lista e seta o novo nó como inicio
		(*lista)->inicio = no;
	}
	else{
		//Verifica se o valor é menor que o primeiro valor da lista
		if(valor < (*lista)->inicio->valor){ 
			//seta o inicio da lista, como o próximo do nó
			no->prox = (*lista)->inicio;
			//seta como null o anterior do nó
			no->ant = NULL;
			//coloca o no como anterior do primeiro valor
			(*lista)->inicio->ant = no;
			//o inicio vira o nó
			(*lista)->inicio = no;
		}else if(valor > (*lista)->fim->valor){
			//seta null no proximo do nó
			no->prox = NULL;
			//seta o final da lista no anterior do nó
			no->ant = (*lista)->fim;
			//seta no proximo do fim e seta o no
			(*lista)->fim->prox = no;
			//pega a lista e seta o novo nó como fim
			(*lista)->fim = no;	
		}else{			
			//Cria um novo nó
			No* atual = (No*) malloc(sizeof(No));
			//Verifica se conseguiu alocar memória
			if(atual == NULL){
				printf("Nao consegui alocar memoria \0/");
			}
			
			//inicia o novo nó com o valor inicial da lista
			atual = (*lista)->inicio;	
			
			//enquanto o atual é diferente da lista, imprime o valor do atual
			while(atual != NULL){
				// percorre a lista e verifia se o valor é maior que o valor a tual e menor que o próximo
				if(valor >= atual->valor && atual->prox != NULL && valor< atual->prox->valor){
					if(atual->prox != NULL){
						//seta o próximmo no proximo do nó
						no->prox = atual->prox;
					} else{
						//seta null no proximo do nó
						no->prox = NULL;
					}
					//seta no anterior o nó atual
					no->ant = atual;
					//seta o próximo com o nó
					atual->prox = no;
					//seta o anterior com o nó
					atual->ant = no;
					//retorna
					return;
				}				
				//seta ao atual, o valor do proximo
				atual = atual->prox;
			}
		}
	}
}

void gravarArquivoInvertido(Lista* lista){	
	//Variaveis
	FILE *arquivo;	
	
	//Abre o aqruivo, e sobreescreve o mesmo caso já exita
	arquivo = fopen("arquivoInvertido.txt", "w");
	
	//verifica se o inicio da lista é diferente de null
	if(lista->inicio == NULL){
		printf("Nao tem conteudo na lista!\n");
		return 1;
	}
	//seta no nó atual o inicio da lista
	No* no = (No*) malloc(sizeof(No));
	no = lista->fim;
	//Verifica se conseguiu alocar memória
	if(no == NULL){
		printf("Nao consegui alocar memoria \0/");
	}	
	
	//Enquanto o nó é diferente de nULL grava no arquivo
	while(no != NULL){
		fprintf(arquivo, "%d;", no->valor);
		//seta no nó, o valor do anterior
		no = no->ant;
	}
	//Fecha o arquivo
	fclose(arquivo);
}

void gravarArquivoOrdenado(Lista* lista){	
	//Verifica se o inicio da lista é diferente de null
	if(lista->inicio == NULL){
		printf("Nao tem conteudo na lista!\n");
		return 1;
	}
	
	//Variáveis
	FILE *arquivo;		
	Lista* novaLista = criaLista();		
		
	//seta no nó atual o inicio da lista
	No* no = (No*) malloc(sizeof(No));
		
	//seta no nó atual o inicio da lista
	no = lista->inicio;	
	
	//Utiliza função recursiva
	criaListaOrdenada(no, novaLista);
	
	//Abre o aqruivo, e sobreescreve o mesmo caso já exita
	arquivo = fopen("arquivoOrdenado.txt", "w");
	
	//Seta no nó o o nó inicial da nova lista
	no =novaLista->inicio;	
	
	//enquanto o nó atual é diferente de NULL, grava no arquivo
	while(no != NULL){
		fprintf(arquivo, "%d;", no->valor);
		//seta ao nó atual, o valor do proximo
		no = no->prox;
	}
	
	//Fecha o arquivo
	fclose(arquivo);
}

void criaListaOrdenada(No* no, Lista* ordenada){	
	//Insere valor ordenado
	insereOrdenado(&ordenada, no->valor);
		
	//Verifica se o nó é diferente de NULL
	if(no->prox != NULL){
		//Pega o valor do próximo nó
		no = no->prox;	
		//Recursividade		
		criaListaOrdenada(no, ordenada);
	}else{
		//Retorna
		return;
	}
}

void gravarArquivoMedia(Lista* lista){	
	//Variáveis
	FILE *arquivo;
	float qnt = 0, valorTotal = 0, maior = 0, menor = 0, media =0; 	
	
	//verifica se o inicio da lista é diferente de null
	if(lista->inicio == NULL){
		printf("Nao tem conteudo na lista!\n");
		return 1;
	}
	
	//seta no nó atual o inicio da lista
	No* atual =lista->inicio;	
	
	//Inicia o valor menor com o primeiro valor da lista
	menor = atual->valor;
	//enquanto o atual é diferente da lista, imprime o valor do atual
	while(atual != NULL){
		//Adiciona +1 na quantidade
		qnt ++;
		//Soma na variável total o valor do nó atual
		valorTotal += atual->valor;
		//Verifica se o valor é menor que o que está armazenado na variável menor
		if(atual->valor < menor){
			menor = atual->valor;
		}
		//Verifica se o valor é maior que o que está armazenado na variável maior
		if(atual->valor > maior){
			maior = atual->valor;
		}								
		//seta ao atual, o valor do proximo
		atual = atual->prox;
	}
	
	//Calcula o valor médio
	media = valorTotal/qnt;
		
	//Abre o arquivo
	arquivo = fopen("arquivoValoresMedios.txt", "w");
	//Coloca o valor médio no arquivo
	fprintf(arquivo, "media: %.2f\n", media);
	//Coloca o valor maior no arquivo
	fprintf(arquivo, "o valor maior: %.0f\n", maior);
	//Coloca o valor menor no arquivo
	fprintf(arquivo, "o valor menor: %.0f\n", menor);
	//Fecha o arquivo
	fclose(arquivo);
}

void gravarArquivoBinario(Lista* lista){	
	//Variáveis
	FILE *arquivo;	
	
	//Abre o aqruivo, e sobreescreve o mesmo caso já exita	
	arquivo = fopen("arquivoBinario.txt", "w");
	
	//verifica se o inicio da lista é diferente de null
	if(lista->inicio == NULL){
		printf("Nao tem conteudo na lista!\n");
		return 1;
	}
	//seta no nó atual o inicio da lista
	No* atual =lista->inicio;	
	
	//enquanto o atual é diferente da lista, imprime o valor do atual
	while(atual != NULL){
		fprintf(arquivo, "%d;\n", intParaBinario(atual->valor));
		//seta ao atual, o valor do proximo		
		atual = atual->prox;
	}
	//Fecha o arquivo
	fclose(arquivo);
}

