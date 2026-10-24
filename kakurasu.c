#include <stdio.h>
#include <windows.h>


int S[4096][13];  //Matriz global das combinacoes
char RES[13];  //Array das restricoes

int NUM;  //Soma desejada
int DIM = 9;  //N
int POT = 512;  //2^N
int MAX = 45;  //Soma maxima



void fInicializar() {  //Inicializar TODAS combinacoes
    int pot = 1;  //pot. de 2
    for (int x = 1; x < 13; x++) {
        int a = 1;  //bit
        for (int y = 0; y < 4096; y++) {
            if (y % pot == 0) a = !a;  //troca ciclica
            S[y][x] = a;
        }
        pot *= 2;  //proxima pot.
    }

    for (int i = 0; i < 4096; i++) {
        int sum = 0;
        for (int j = 1; j < 13; j++) {
            if (S[i][j]) sum += j;  //conta os bits ligados
        }
        S[i][0] = sum;
    }
}

void fMostrar() {
    for (int i = 0; i < POT; i++) {
        for (int j = 0; j < DIM+1; j++) {
            printf("%d ", S[i][j]);
        }
        printf("\n");
    }
}

void fMaxima() {
    int m = 0;
    for (int x = 1; x <= DIM; x++) m += x;
    MAX = m;
}

void fPotencia() {
    int p = 2;
    for (int x = 1; x < DIM; x++) p *= 2;
    POT = p;
}

void fLimpaTeclado() {
	char c;
	while((c = getchar()) != EOF && c != '\n'){}
}

int fMenu1() {
    int escolha;
    
    printf("Qual numero vc quer somar: ");
    scanf("%d", &escolha);
    fLimpaTeclado();

    return escolha;
}

int fMenu2() {
    int escolha;
    
    do {
        printf("Qual a dimensao do tabuleiro: ");
        scanf("%d", &escolha);
        fLimpaTeclado();
    } while (escolha < 1 || escolha > 12);

    return escolha;
}

int fChecaRestricao(int row) {
    for (int x = 1; x < DIM+1; x++) {
        if(S[row][x] == 0 && (RES[x-1] == 'c')) return 0;
        
        if (S[row][x] == 1 && RES[x-1] == 'x') return 0;
    }
    return 1;
}

void fObterString() {
    int ticker;

    do {
        ticker = 1;
        printf("Insira a restricao atual: ");
        scanf("%s", RES);
        fLimpaTeclado();

        int s = 0;
        for (int x = 0; RES[x] != '\0' && ticker; x++) {
            if (RES[x] != 'z' && RES[x] != 'x' && RES[x] != 'c') ticker = 0;
            s++;
        }

        if (s != DIM) ticker = 0;

    } while (!ticker);
}

void fKakuro() {
    system("cls");

    int FREQ[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int TOTAL = 0;

    //Calcula quantas combinacoes tem, e a frequencia de cada numero
    for (int i = 0; i < POT; i++) {
        if (S[i][0] == NUM) {
            if (fChecaRestricao(i)) {
                TOTAL++;
                for (int j = 1; j < DIM+1; j++) {
                    if (S[i][j]) FREQ[j-1]++;
                }
            }
        }
    }

    printf("=== RESULTADOS ===\n\n");

    if (TOTAL == 0) {

        printf("Nao existem combinacoes que encaixem na restricao dada\n");
        printf("Voce cometeu algum erro...\n");

    } else {

        printf("Soma: %d\n", NUM);
        printf("Tamanho: %dx%d\n", DIM, DIM);
        printf("Restricao: %s\n\n", RES);

        printf(">>Os numeros obrigatorios sao:\n");
        for (int x = 0; x < DIM; x++) {
            if (FREQ[x] == TOTAL) printf("[%d]", x+1);
        }

        printf("\n\n");

        printf(">>Os numeros proibidos sao:\n");
        for (int x = 0; x < DIM; x++) {
            if (FREQ[x] == 0) printf("[%d]", x+1);
        }

        printf("\n\n");

        printf(">>Frequencias:\n");
        printf("    Num: ");
        for (int x = 0; x < DIM; x++) {
            printf("[%2d]", x+1);
        }
        printf("\n");
        printf("Aparece: ");
        for (int x = 0; x < DIM; x++) {
            printf("[%2d]", FREQ[x]);
        }
        printf("\n");
        printf(">>Total de combinacoes: %d\n", TOTAL);
    }

    printf("\n");
    system("pause");
}

int main () {
    fInicializar();

    do {
        system("cls");

        printf("=== ASSISTENTE DE COMBINACOES DO KAKURASU %dx%d ===\n\n", DIM, DIM);
        printf("[Digite -1 para trocar o tamanho]\n");
        NUM = fMenu1();

        if (NUM >= 0 && NUM <= MAX) {
            fObterString();
            fKakuro();
        } else {
            if (NUM == -1) {
                DIM = fMenu2();
                fPotencia();
                fMaxima();
            } else {
                printf("\nbruh\n"); system("pause");
            }
        }

    } while (1);
}
