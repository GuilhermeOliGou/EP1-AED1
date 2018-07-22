//--------------------------------------------------------------
// NOMES DOS RESPONS�VEIS: Leonardo Victor Moreira de Souza E Guilherme Oliveira Goularte
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

typedef struct strct {//defini��o b�sica de n�
    char letra;
    struct strct *prox;
} NO;

NO* busca (NO* x, int i, NO* y){//essa fun��o busca e retorna um n� e seu anterior, n�o h� problema com n�s inexistentes pois a procura se d� percorrendo a lista n� a n� e retorna null se estiver vazia
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

NO* inverter(NO* x, int i, int j){//essa fun��o inverte a lista da seguinte forma: � passado a posi��o atual da lista no primeiro parametro e quantas letras voc� quer inverter
    //por exemplo: se quiser inverter o 'lg' em "algoritmo" voc� deve passar como para metro a lista, a posi��o em que o 'g' se encontra (3) e quantas letras voc� quer inverter (2)
    // o resultado ser� agloritmo
    // isso permite fazer a busca das letras na lista usando a fun��o busca
    //Ps.: i >= j && j >= 2 && x != NULL
    NO* aux1 = NULL;
    NO* aux2 = NULL;
    NO* aux3 = NULL;
    NO* ant1 = NULL;
    NO* ant2 = NULL;
    No* resp = NULL;
    int a = 0;
    if (i == j && i > 2){// caso 'i' e 'j' sejam iguais isso significa que a invers�o dever� ser feita no come�o como na caso de "#preparado"
        //por isso alguns passos s�o exclu�dos
        //este bloco n�o cobre o caso onde voc� tenha que inverter somente duas letras, como em "preparado"
        // inverter apenas duas letras � considerado um caso especial e por isso � tratado em um bloco a parte
        aux1 = x;
        aux2 = busca(x, i, ant2);
        aux3 = aux2->prox;
        aux2->prox = aux1->prox;
        ant2->prox = aux1;
        aux1->prox = aux3;
        //as linhas de c�digo nesse bloco at� o momento invertem a primeira e a �ltima letra na sequ�ncia
        //ent�o, caso ainda sobre mais de uma letra para inverter, a fun��o � chamada novamente com outros "i" e "j"
        //por exemplo: "#preparado" ficaria "rp#eparado"
        // j� "#!preparado" ficaria "r#p!eparado" e seria passado para a mesma fun��o com novos par�metro para inverter o '#' e o 'p'
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
    }else if (i == j && i == 2){//esse � o bloco que trata o caso especial onde voc� deve inverter duas letrasno come�o
        aux1 = x;
        aux2 = x->prox;
        aux1->prox = aux2->prox;
        aux2->prox = aux1;
    }else if (i > j && j%2 != 0){//esse bloc trata o caso onde voc� n�o precisa inverter no come�o e o n�mero de letras a serem invertidas � �mpar
    //caso a quantidade de letras a se inverter seja �mpar, a lista nunca cair� no caso especial de ter que inverter apenas duas letras
        while (a < (j-1)/2){//ent�o esse bloco apenas busca as letras e vai invertendo das bordas para os meios
            aux1 = busca(x, i-j+a+1, ant1);
            aux2 = busca(x, i-a, ant2);
            aux3 = aux2->prox;
            ant1->prox = aux2;
            ant2->prox = aux1;
            aux2->prox = aux1->prox;
            aux1->prox = aux3;
            a++;
        }
    }else{//agora esse bloco trata o caso onde o n�mero de invers�es � par e consequentemente cair� numa invers�o de apenas duas letras
        while (a < (j-2)/2){//caso o n�mero de invers�es seja apenas dois, o programa n�o executar� esse bloco de c�digo
            aux1 = busca(x, i-j+a+1, ant1);
            aux2 = busca(x, i-a, ant2);
            aux3 = aux2->prox;
            ant1->prox = aux2;
            ant2->prox = aux1;
            aux2->prox = aux1->prox;
            aux1->prox = aux3;
            a++;
        }//a partir daqui o c�digo altera manualmente altera o caso de duas invers�es
        aux1 = busca(x, i-(j/2), ant1);
        aux2 = busca(x, i-((j/2)+1), ant2);
        ant1->prox = aux2;
        aux1->prox = aux2->prox;
        aux2->prox = aux1;
    }
}

NO* decodificar(NO* p) {//essa fun��o decodifica a frase
	NO* resp = NULL;
	NO* aux = p;
	NO* ant = NULL;
	int tamanho = 0;
	int girar = 0;//a vari�vel tamanho armazena o tamanho da lista enquanto a vari�vel girar armazena quantas letras devem ser invertidas
	if (aux == NULL)//caso a lista esteja vazia o c�digo ir� parar sua execu��o aqui
        return NULL;
	/*while (aux!=NULL){//supondo que a lista n�o esteja vazia iremos executar os blocos de c�digo segintes enquanto a letra atual n�o for nula
        //observe que a vari�vel tamanho s� � incrementada caso o c�digo entre nesse bloco
        NO* atual = (NO*)malloc(sizeof(NO));
        atual->letra = aux->letra;
        if (ant != NULL)
            ant ->prox = atual;
        else
            resp = atual;
        if ((atual->letra == 'A' || atual->letra == 'E' || atual->letra == 'I' || atual->letra == 'O' || atual->letra == 'U' || atual->prox == NULL) && girar >= 2){
            //esse bloco trata o caso onde foi achado uma vogal atr�s de duas ou n�o vogais, portanto � chamada a fun��o inverter com o tamanho atual e o n�mero de invers�o necess�rias
            //observe que o tamanho apenas � incrementado ap�s a invers�o, evitando assim erros
            //em seuq�ncia o quantidade de invers�o � zerada
            ant = atual;
            atual = atual->prox;
            inverter (resp, tamanho, girar);
            tamanho++;
            girar = 0;
        }else if ((atual->letra == 'A' || atual->letra == 'E' || atual->letra == 'I' || atual->letra == 'O' || atual->letra == 'U' || atual->prox == NULL) && girar < 2){
            //esse bloco trata o caso de uma vogal atr�s de apenas uma n�o vogal ou atr�s de outro vogal
            //portanto a fun��o inverter n�o � chamada, o tamanho � incrementado e a quantidade de giros a serem feitos � zerada
            tamanho++;
            ant = atual;
            atual = atual->prox;
            girar = 0;
        }else{//esse bloco trata o caso de uma n�o vogal seguida de outra n�o vogal
            //a fun��o inverter n�o � chamada, o tamanho e a quantidade de giros � incrementado
            tamanho++;
            ant = atual;
            atual = atual->prox;
            girar++;
        }
	}
	//por fim, invertemos a lista inteira passando o tamanho como posi��o atual e como quantidade de invers�es*/
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
