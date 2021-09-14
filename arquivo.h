typedef struct no{
	int valor;
	struct no* ant;
	struct no* prox;
}No;

typedef struct lista{
	No* inicio;
	No* fim;
}Lista;

Lista* criaLista();

void criarArquivo(int qntNumeros);

void popularLista(Lista** lista);

void gravarArquivoInvertido(Lista* lista);

void gravarArquivoOrdenado(Lista* lista);
	
void gravarArquivoMedia(Lista* lista);

void gravarArquivoBinario(Lista* lista);

