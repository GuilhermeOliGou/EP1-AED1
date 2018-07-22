//--------------------------------------------------------------
// NOMES DOS RESPONSÁVEIS: Leonardo Victor Moreira de Souza E Guilherme Oliveira Goularte
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

// ######### ESCREVA O NROUSP DO PRIMEIRO INTEGRANTE AQUI
char* nroUSP1() {
    return("10387748");
}

// ######### ESCREVA O NROUSP DO SEGUNDO INTEGRANTE AQUI (OU DEIXE COM ZERO)
char* nroUSP2() {
    return("10284409");
}

typedef struct strct {//definição básica de nó
    char letra;
    struct strct *prox;
} NO;

NO* busca (NO* x, int i, NO* y){//essa função busca e retorna um nó e seu anterior, não há problema com nós inexistentes pois a procura se dá percorrendo a lista nó a nó e retorna null se estiver vazia
    int chave = 1;
    NO* atual  = x;
    y = NULL;
    while (chave != i){
        y = atual;
        atual = atual->prox;
        chave++;
    }
    return atual;
}

NO* inverter(NO* x, int i, int j){//essa função inverte a lista da seguinte forma: é passado a posição atual da lista no primeiro parametro e quantas letras você quer inverter
    //por exemplo: se quiser inverter o 'lg' em "algoritmo" você deve passar como para metro a lista, a posição em que o 'g' se encontra (3) e quantas letras você quer inverter (2)
    // o resultado será agloritmo
    // isso permite fazer a busca das letras na lista usando a função busca
    //Ps.: i >= j && j >= 2 && x != NULL
    NO* aux1 = NULL;
    NO* aux2 = NULL;
    NO* aux3 = NULL;
    NO* ant1 = NULL;
    NO* ant2 = NULL;
    No* resp = NULL;
    int a = 0;
    if (i == j && i > 2){// caso 'i' e 'j' sejam iguais isso significa que a inversão deverá ser feita no começo como na caso de "#preparado"
        //por isso alguns passos são excluídos
        //este bloco não cobre o caso onde você tenha que inverter somente duas letras, como em "preparado"
        // inverter apenas duas letras é considerado um caso especial e por isso é tratado em um bloco a parte
        aux1 = x;
        aux2 = busca(x, i, ant2);
        aux3 = aux2->prox;
        aux2->prox = aux1->prox;
        ant2->prox = aux1;
        aux1->prox = aux3;
        //as linhas de código nesse bloco até o momento invertem a primeira e a última letra na sequência
        //então, caso ainda sobre mais de uma letra para inverter, a função é chamada novamente com outros "i" e "j"
        //por exemplo: "#preparado" ficaria "rp#eparado"
        // já "#!preparado" ficaria "r#p!eparado" e seria passado para a mesma função com novos parâmetro para inverter o '#' e o 'p'
        if (i > 3 && i%2 != 0){
            while (a < (j-3)/2){
                aux1 = busca(x, i-j+a+2, ant1);
                aux2 = busca(x, i-a-1, ant2);
                aux3 = aux2->prox;
                ant1->prox = aux2;
                ant2->prox = aux1;
                aux2->prox = aux1->prox;
                aux1->prox = aux3;
                a++;
            }
        }else if (i > 3 && i%2 == 0){
            while (a < (j-4)/2){
                aux1 = busca(x, i-j+a+2, ant1);
                aux2 = busca(x, i-a-1, ant2);
                aux3 = aux2->prox;
                ant1->prox = aux2;
                ant2->prox = aux1;
                aux2->prox = aux1->prox;
                aux1->prox = aux3;
                a++;
            }
            aux1 = busca(x, i-(j/2), ant1);
            aux2 = busca(x, i-((j/2)+1), ant2);
            ant1->prox = aux2;
            aux1->prox = aux2->prox;
            aux2->prox = aux1;
        }        
    }else if (i == j && i == 2){//esse é o bloco que trata o caso especial onde você deve inverter duas letrasno começo
        aux1 = x;
        aux2 = x->prox;
        aux1->prox = aux2->prox;
        aux2->prox = aux1;
    }else if (i > j && j%2 != 0){//esse bloc trata o caso onde você não precisa inverter no começo e o número de letras a serem invertidas é ímpar
    //caso a quantidade de letras a se inverter seja ímpar, a lista nunca cairá no caso especial de ter que inverter apenas duas letras
        while (a < (j-1)/2){//então esse bloco apenas busca as letras e vai invertendo das bordas para os meios
            aux1 = busca(x, i-j+a+1, ant1);
            aux2 = busca(x, i-a, ant2);
            aux3 = aux2->prox;
            ant1->prox = aux2;
            ant2->prox = aux1;
            aux2->prox = aux1->prox;
            aux1->prox = aux3;
            a++;
        }
    }else{//agora esse bloco trata o caso onde o número de inversões é par e consequentemente cairá numa inversão de apenas duas letras
        while (a < (j-2)/2){//caso o número de inversões seja apenas dois, o programa não executará esse bloco de código
            aux1 = busca(x, i-j+a+1, ant1);
            aux2 = busca(x, i-a, ant2);
            aux3 = aux2->prox;
            ant1->prox = aux2;
            ant2->prox = aux1;
            aux2->prox = aux1->prox;
            aux1->prox = aux3;
            a++;
        }//a partir daqui o código altera manualmente altera o caso de duas inversões
        aux1 = busca(x, i-(j/2), ant1);
        aux2 = busca(x, i-((j/2)+1), ant2);
        ant1->prox = aux2;
        aux1->prox = aux2->prox;
        aux2->prox = aux1;
    }
}

NO* decodificar(NO* p) {//essa função decodifica a frase
	NO* resp = NULL;
	NO* aux = p;
	NO* ant = NULL;
	int tamanho = 0;
	int girar = 0;//a variável tamanho armazena o tamanho da lista enquanto a variável girar armazena quantas letras devem ser invertidas
	if (aux == NULL)//caso a lista esteja vazia o código irá parar sua execução aqui
        return NULL;
	/*while (aux!=NULL){//supondo que a lista não esteja vazia iremos executar os blocos de código segintes enquanto a letra atual não for nula
        //observe que a variável tamanho só é incrementada caso o código entre nesse bloco
        NO* atual = (NO*)malloc(sizeof(NO));
        atual->letra = aux->letra;
        if (ant != NULL)
            ant ->prox = atual;
        else
            resp = atual;
        if ((atual->letra == 'A' || atual->letra == 'E' || atual->letra == 'I' || atual->letra == 'O' || atual->letra == 'U' || atual->prox == NULL) && girar >= 2){
            //esse bloco trata o caso onde foi achado uma vogal atrás de duas ou não vogais, portanto é chamada a função inverter com o tamanho atual e o número de inversão necessárias
            //observe que o tamanho apenas é incrementado após a inversão, evitando assim erros
            //em seuqência o quantidade de inversão é zerada
            ant = atual;
            atual = atual->prox;
            inverter (resp, tamanho, girar);
            tamanho++;
            girar = 0;
        }else if ((atual->letra == 'A' || atual->letra == 'E' || atual->letra == 'I' || atual->letra == 'O' || atual->letra == 'U' || atual->prox == NULL) && girar < 2){
            //esse bloco trata o caso de uma vogal atrás de apenas uma não vogal ou atrás de outro vogal
            //portanto a função inverter não é chamada, o tamanho é incrementado e a quantidade de giros a serem feitos é zerada
            tamanho++;
            ant = atual;
            atual = atual->prox;
            girar = 0;
        }else{//esse bloco trata o caso de uma não vogal seguida de outra não vogal
            //a função inverter não é chamada, o tamanho e a quantidade de giros é incrementado
            tamanho++;
            ant = atual;
            atual = atual->prox;
            girar++;
        }
	}
	//por fim, invertemos a lista inteira passando o tamanho como posição atual e como quantidade de inversões*/
	inverter(resp, tamanho, tamanho);
	return resp;
}

int main()
{
    /*NO* a = (NO*)malloc(sizeof(NO));
    a->letra = 'B';
    a->prox = NULL;
    NO* b = (NO*)malloc(sizeof(NO));
    b->letra = 'B';
    b->prox = a;
    NO* c = (NO*)malloc(sizeof(NO));
    c->letra = ' ';
    c->prox = b;
    NO* d = (NO*)malloc(sizeof(NO));
    d->letra = 'E';
    d->prox = c;
    NO* e = (NO*)malloc(sizeof(NO));
    e->letra = 'A';
    e->prox = d;
    NO* f = (NO*)malloc(sizeof(NO));
    f->letra = 'N';
    f->prox = e;
    NO* g = (NO*)malloc(sizeof(NO));
    g->letra = 'R';
    g->prox = f;*/
    NO* p = (NO*)malloc(sizeof(NO));
    p->letra = 'B';
    p->prox = NULL;
    //p->prox = g;
	// aqui vc pode incluir codigo para inserir elementos
	// de teste na sua lista p
	// o EP sera testado com chamadas deste tipo
	NO* teste = NULL;
    teste = decodificar(p);
}
