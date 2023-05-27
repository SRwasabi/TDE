#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*"evolucao_do_salario_minimo_teste3.csv"*/
#define NOME_ARQ "evolucao_do_salario_minimo_teste3.csv"


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
    char vigenAno[164][3];
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
    int AnoControle;

    /*Controle de vetores*/
    int j, p = 0;
    int i;
    int k;

    do{
            printf("\n\t================MENU================\n");
            printf("\tDigite uma das opcoes [1-3]\n");
            printf("\t1 - Exibir todas as linhas\n");
            printf("\t2 - Exibir somente o menor valor e a sua posicao\n");
            printf("\t3 - Sair\n");

            scanf("%i", &opcao);

            switch(opcao){

            case 1:

                printf("\tEscolha uma data entre 1940 a 2015 pela sua dezena e unidade: ");
                scanf("%s", data);


                arquivo = fopen(NOME_ARQ, "r");

                if(arquivo == NULL){
                    printf("\tErro! Não consegui abrir o arquivo de leitura\n");
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
            printf("\tEscolha o intervalo de data\n De: ");
                scanf("%s", escolha1);
                printf(" Ate: ");
                scanf("%s", escolha2);

                N1 = strtof(escolha1, NULL);

                N2 = strtof(escolha2, NULL);

                k = 0;

                arquivo = fopen(NOME_ARQ, "r");

                if(arquivo == NULL){
                    printf("\tErro! Não consegui abrir o arquivo de leitura\n");
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
                    AnoControle = strtof(vigenAno[i], NULL);

                    dinheiroConvertido[i] = conversaoNum(salario[i], vigenAno[i], moeda[i]);

                    /*Salvando a conversao em uma string quando ela se encaixa no intervalo de ano*/
                    if((AnoControle >= N1) && (AnoControle <= N2)){
                        print_dado(legis[i], DOU[i], moeda[i], salario[i], vigenAno[i]);
                        sprintf(salarioString[k], "%.15lf", dinheiroConvertido[i]);
                        k++;
                    }

                    i++;
                }

                fclose(arquivo);

                saida = fopen("evolucao_do_salario_minimo_teste3V2.csv", "w+");

                if(saida == NULL){
                    printf("\tErro! Não consegui abrir o arquivo de leitura\n");
                    return 1;
                }

                fgets(linha, 100, saida);

                /* Anos que comecam de 90 ate os 2000 n esta lendo, precisa deixar por exemplo: 15 > 115*/
                for(j = 0; j < k; j++){
                    strcpy(linha, salarioString[j]);
                    strcat(linha, "\n");
                    fputs(linha, saida);
                }

                fclose(saida);
                break;

            case 3:
                printf("\tAdeus\n");
                break;

            default:
                printf("\t Nao existe essa opcao!!\n");
                break;
        }
    } while(opcao != 3);

    return 0;
}

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
    return dinheiroConvertido;
}

void conversaoPrint(double salario, char vigenAno[],char moeda[]){
    int Ano;
    Ano = strtof(vigenAno, NULL);
    char cruzado[4] = {'C', 'z', '$', '\0'};
    char cruzeiro[4] = {'C', 'r', '$', '\0'};
    char cruzeiroREAL[4] = {'C', 'R', '$', '\0'};

    if(Ano >= 93){
           if(strcmp(moeda, cruzeiroREAL) == 0){
                printf("\tConversao: R$ %.1lf\n", salario/2750);
           }
           else if(strcmp(moeda, cruzeiro) == 0){
                printf("\tConversao: R$ %.2lf\n", salario/(1000*2750));
           }
           else{
                printf("\tConversao: R$ %.3lf\n", salario);
           }
    }

    else if(Ano >= 86){
           if(strcmp(moeda, cruzado) == 0){
                printf("\tConversao: R$ %.4lf\n", salario/(pow(1000, 2)*2750));
           }
           else{
                printf("\tConversao: R$ %.5lf\n", salario/(1000*2750));
           }
    }

    else if(Ano >= 67){
        printf("\tConversao: R$ %.6lf\n", salario/(pow(1000, 3)*2750));
    }

    else if(Ano >= 40){
        printf("\tConversao: R$ %.7lf\n", salario/(pow(1000, 4)*2750));
    }

    else if(Ano <= 15){
        printf("\tConversao: R$ %.8lf\n", salario);
    }


}

void print_dado(char legis[], char DOU[], char moeda[], double salario, char vigenAno[]){
    printf("\n");
    printf("-------------------------------------------\n");
    printf("> Legislacao: %s\n", legis);
    printf("\tDOU: %s\n", DOU);
    printf("\tSalario: %s %.2lf\n", moeda, salario);

    conversaoPrint(salario, vigenAno, moeda);
    }


