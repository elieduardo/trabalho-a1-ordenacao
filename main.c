#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include "arquivo.h"

int main(int argc, char *argv[]) {
	//Variáveis
	bool sair = false;
	int qnt = 0, opcao = 0;	
	Lista* lista = criaLista();		
	
	do{
		printf("Digite a quantidade de numeros para a gerecao do arquivo principal: ");		
		scanf("%i", &qnt);	
		if(qnt < 100 || qnt > 999){			
			system("@cls||clear");
			printf("Digite um numero maior que 99 e menor que 999\n");
		} else{
			criarArquivo(qnt);
			popularLista(&lista);	
		}
	}while(qnt < 100 || qnt > 999);
	
	do{
		//Limpa console
		system ("cls");		
		//Menu
		printf("1 - Gerar arquivo invertido\n");
		printf("2 - Gerar arquivo ordenado\n");
		printf("3 - Gerar arquivo com valores medios\n");
		printf("4 - Gerar arquivo com valores em binario\n");
		printf("0 - Sair\n");
		printf("Escolha a opcao desejada\n");
		//Le opcao do usuário
		scanf("%i", &opcao);
		
		switch(opcao){			
			case 0:
				//Opção para sair
				return 0;
				break;
			case 1:
				//Grava arquivo invertido
				gravarArquivoInvertido(lista);
				printf("Arquivo invertido gerado com sucesso\n");
				break;
			case 2:
				//Grava arquivo ordenado
				gravarArquivoOrdenado(lista);
				printf("Arquivo ordenado gerado com sucesso\n");
				break;
			case 3:
				//Grava arquivo de media
				gravarArquivoMedia(lista);
				printf("Arquivo medio gerado com sucesso\n");
				break;
			case 4:
				//Grava arquivo binário
				gravarArquivoBinario(lista);
				printf("Arquivo binario gerado com sucesso\n");
				break;
			default:
				//Informa que a opção é inválida
				printf("Digite uma opcao valida\n");				
				break;
		}
		
		//Pausa o console		
		system("PAUSE");		
	}while(opcao!=0);
	
	return 0;
}
