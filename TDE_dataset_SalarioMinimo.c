#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*"evolucao_do_salario_minimo_teste3.csv"*/
#define NOME_ARQ "evolucao_do_salario_minimo_teste3.csv"

void ordenar_maior(double[], int[], int);
void print_dado(char[], char [], char[], double, char[]);
void conversaoPrint(double, char[], char[]);
double conversaoNum(double, char[], char[]);

int main(){
    /*Var de Entrada*/
    int opcao;
    char data[3];

    FILE *arquivo;
    FILE *saida;

    /*Dados dos Arquivos*/
    char legis[164][25];
    char DOU[164][10];
    char vigenD[164][10];
    char vigenM[164][10];
    char vigenAno[164][4];
    char moeda[164][10];
    double salario[164];
    char linha[100];
    char *token;

    /*Var's para a op 2*/
    char escolha1[3];
    char escolha2[3];
    int N1;
    int N2;
    char salarioString[164][20];
    double dinheiroConvertido[164];
    int AnoControle[164];

    /*Controle de vetores*/
    int j, p = 0;
    int i;
    int k;

    do{
            printf("\n\t============================MENU============================\n");
            printf("\n\tDigite uma das opcoes [1-3]\n");
            printf("\t1 - Evolucao do salario minimo em determinado ano\n");
            printf("\t2 - Processamento do maior salario ao menor em um periodo\n");
            printf("\t3 - Sair\n");
            printf("\n\t============================================================\n");
            printf("\t");
            scanf("%i", &opcao);

            switch(opcao){

            case 1:

                printf("\n\tEscolha uma data, pelo seus dois ultimos numeros,\n\tentre 1940 a 2015 e averigue se houve evolucao do salario minimo: ");
                scanf("%s", data);


                arquivo = fopen(NOME_ARQ, "r");

                if(arquivo == NULL){
                    printf("\tErro! Nao consegui abrir o arquivo de leitura\n");
                    return 1;
                }

                fgets(linha, 100, arquivo);
                i=0;

                /*Lendo o arquivo*/
                while(fgets(linha, 100, arquivo) != NULL){
                    token = strtok(linha, ";");
                    strcpy(legis[i], token);
                    token = strtok(NULL, ";");
                    strcpy(DOU[i], token);
                    token = strtok(NULL, ".");
                    strcpy(vigenD[i], token);
                    token = strtok(NULL, ".");
                    strcpy(vigenM[i], token);
                    token = strtok(NULL, ";");
                    strcpy(vigenAno[i], token);
                    token = strtok(NULL, ";");
                    strcpy(moeda[i], token);
                    token = strtok(NULL, ";");

                    /*Salario vem com '.'
                    Professor Guilherme ajudou*/
                    /*///==========================================*/
                    p = 0;
                    for(j = 0; token[j] != '\0'; j++){
                        token[p] = token[j];

                        if(token[j] != '.'){
                            if(token[p] == ','){
                                token[p] = '.';
                            }
                            p++;
                        }
                    }
                    /*///==========================================*/

                    salario[i] = strtof(token, NULL);

                    if(strcmp(data, vigenAno[i]) == 0){
                        print_dado(legis[i], DOU[i], moeda[i], salario[i], vigenAno[i]);
                    }

                    i++;
                }

                fclose(arquivo);
                break;

            case 2:
                printf("\n");
                printf("\tEscolha o intervalo de tempo\n\tDe: ");
                scanf("%s", escolha1);
                printf("\tAte: ");
                scanf("%s", escolha2);

                N1 = strtof(escolha1, NULL);
                if(N1 <= 15) N1 += 100; /*Adicao de 100 para poder entrar no If*/
                N2 = strtof(escolha2, NULL);
                if(N2 <= 15) N2 += 100; /*Adicao de 100 para poder entrar no If*/

                k = 0;

                arquivo = fopen(NOME_ARQ, "r");

                if(arquivo == NULL){
                    printf("\tErro! Nao consegui abrir o arquivo de leitura\n");
                    return 1;
                }

                fgets(linha, 100, arquivo);
                i=0;

                /*Lendo o arquivo*/
                while(fgets(linha, 100, arquivo) != NULL){
                    token = strtok(linha, ";");
                    strcpy(legis[i], token);
                    token = strtok(NULL, ";");
                    strcpy(DOU[i], token);
                    token = strtok(NULL, ".");
                    strcpy(vigenD[i], token);
                    token = strtok(NULL, ".");
                    strcpy(vigenM[i], token);
                    token = strtok(NULL, ";");
                    strcpy(vigenAno[i], token);
                    token = strtok(NULL, ";");
                    strcpy(moeda[i], token);
                    token = strtok(NULL, ";");

                    /*Salario vem com '.'
                    Professor Guilherme ajudou*/
                    /*///==========================================*/
                    p = 0;
                    for(j = 0; token[j] != '\0'; j++){
                        token[p] = token[j];

                        if(token[j] != '.'){
                            if(token[p] == ','){
                                token[p] = '.';
                            }
                            p++;
                        }
                    }
                    /*///==========================================*/

                    /*Convertendo o salario e retornando double em dinheiroConvertido*/
                    salario[i] = strtof(token, NULL);
                    AnoControle[i] = strtof(vigenAno[i], NULL);

                    if(AnoControle[i] <= 15){
                        AnoControle[i] += 100; /*Adicao de 100 para poder entrar no If*/
                    }
                        dinheiroConvertido[i] = conversaoNum(salario[i], vigenAno[i], moeda[i]);
                        i++;

                }
                   /*Salvando a conversao em uma string quando ela se encaixa no intervalo de ano*/
                    for(j = 0; j < 164; j++){
                        if((AnoControle[j] >= N1) && (AnoControle [j]<= N2)){
                            print_dado(legis[j], DOU[j], moeda[j], salario[j], vigenAno[j]);
                            sprintf(salarioString[k], "%.15lf", dinheiroConvertido[j]);
                            AnoControle[k] = AnoControle[j];
                            if(AnoControle[k] >= 100) AnoControle[k] -= 100;
                        k++;
                    }
                }
                fclose(arquivo);

                saida = fopen("evolucao_do_salario_minimo_DataCriado.csv", "w+");

                if(saida == NULL){
                    printf("\tErro! Não consegui abrir o arquivo de leitura\n");
                    return 1;
                }

                fgets(linha, 100, saida);

                /* Anos que comecam de 90 ate os 2000 n esta lendo, precisa deixar por exemplo: 15 > 115*/
                for(j = 0; j <= k; j++){
                    dinheiroConvertido[j] = strtof(salarioString[j], NULL);
                }

                ordenar_maior(dinheiroConvertido, AnoControle, k);

                for(j = 0; j <= k; j++){
                    sprintf(salarioString[j], "%.15lf", dinheiroConvertido[j]);
                    sprintf(vigenAno[j], "%02d", AnoControle[j]);
                }

                /*Vetor para nao puxar nada quando colocar a linha*/
                char nada[1] = { '\0'};
                    strcpy(linha, nada);
                    strcat(linha, "Salario_Minimo");
                    strcat(linha, ";");
                    strcat(linha, "Ano_de_Vigencia");
                    strcat(linha, "\n");
                    fputs(linha, saida);

                for(j = 0; j < k; j++){
                    strcpy(linha, salarioString[j]);
                    strcat(linha, ";");
                    strcat(linha, vigenAno[j]);
                    strcat(linha, "\n");
                    fputs(linha, saida);
                }

                fclose(saida);
                break;

            case 3:
                printf("\n");
                printf("\tPrograma finalizado\n\tAdeus\n");
                break;

            default:
                printf("\n");
                printf("\tNao existe essa opcao\n\tPor favor escolha novamente\n");
                break;
        }
    } while(opcao != 3);

    return 0;
}

/*Funcao Para ordenacao do Maior para o menor*/
void ordenar_maior(double salarioConvetido[], int AnoControle[], int k){
    double aux = 0;
    int aux2;
    int x;
    int y;
    for(x = 0; x < k; x++){
        for(y = x + 1; y < k; y++){
            if(salarioConvetido[y] > salarioConvetido[x]){
                aux = salarioConvetido[y];
                salarioConvetido[y] = salarioConvetido[x];
                salarioConvetido[x] = aux;

                aux2 = AnoControle[y];
                AnoControle[y] = AnoControle[x];
                AnoControle[x] = aux2;
            }
        }
    }
}

/*Funcao de conversao retornando double para se efetuar a ordenacao*/
double conversaoNum(double salario, char vigenAno[],char moeda[]){
    int Ano;
    Ano = strtof(vigenAno, NULL);
    char cruzado[4] = {'C', 'z', '$', '\0'};
    char cruzeiro[4] = {'C', 'r', '$', '\0'};
    char cruzeiroREAL[4] = {'C', 'R', '$', '\0'};
    double dinheiroConvertido;

    if(Ano >= 93){
           if(strcmp(moeda, cruzeiroREAL) == 0){
                dinheiroConvertido = salario/2750;
           }
           else if(strcmp(moeda, cruzeiro) == 0){
                dinheiroConvertido = salario/(1000*2750);
           }
           else{
                dinheiroConvertido = salario;
           }
    }

    else if(Ano >= 86){
           if(strcmp(moeda, cruzado) == 0){
                dinheiroConvertido = salario/(pow(1000, 2)*2750);
           }
           else{
                dinheiroConvertido = salario/(1000*2750);
           }
    }

    else if(Ano >= 67){
         dinheiroConvertido = salario/(pow(1000, 3)*2750);
    }

    else if(Ano >= 40){
         dinheiroConvertido = salario/(pow(1000, 4)*2750);
    }
    else if(Ano >= 95){
        dinheiroConvertido = salario;
    }
    else if(Ano >= 00){
        dinheiroConvertido = salario;
    }

    return dinheiroConvertido;
}

/*Funcao de conversao retornando void para efetuar o printf*/
void conversaoPrint(double salario, char vigenAno[],char moeda[]){
    int Ano;
    Ano = strtof(vigenAno, NULL);
    char cruzado[4] = {'C', 'z', '$', '\0'};
    char cruzeiro[4] = {'C', 'r', '$', '\0'};
    char cruzeiroREAL[4] = {'C', 'R', '$', '\0'};

    if(Ano >= 93){
           if(strcmp(moeda, cruzeiroREAL) == 0){
                printf("\tConversao: R$ %.2lf\n", salario/2750);
           }
           else if(strcmp(moeda, cruzeiro) == 0){
                printf("\tConversao: R$ %.2lf\n", salario/(1000*2750));
           }
           else{
                printf("\tConversao: R$ %.2lf\n", salario);
           }
    }

    else if(Ano >= 86){
           if(strcmp(moeda, cruzado) == 0){
                printf("\tConversao: R$ %.10lf\n", salario/(pow(1000, 2)*2750));
           }
           else{
                printf("\tConversao: R$ %.5lf\n", salario/(1000*2750));
           }
    }

    else if(Ano >= 67){
        printf("\tConversao: R$ %.15lf\n", salario/(pow(1000, 3)*2750));
    }

    else if(Ano >= 40){
        printf("\tConversao: R$ %.15lf\n", salario/(pow(1000, 4)*2750));
    }

    else if(Ano <= 15){
        printf("\tConversao: R$ %.2lf\n", salario);
    }


}

/*Funcao de printar tudo*/
void print_dado(char legis[], char DOU[], char moeda[], double salario, char vigenAno[]){
    printf("\n");
    printf("-------------------------------------------\n");
    printf("> Legislacao: %s\n", legis);
    printf("\tDOU: %s\n", DOU);
    printf("\tAno da Vigencia: %s\n", vigenAno);
    printf("\tSalario: %s %.2lf\n", moeda, salario);

    conversaoPrint(salario, vigenAno, moeda);
    }
