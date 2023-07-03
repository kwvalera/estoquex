//Kawany Valera Zelinski dos Santos - 1�CS - sistema de estoque - 20/06/2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

const int MAX=50;// limitando o tamanho do vetor
int ordenado=0;// vari�vel p/ controlar a ordena��o dos dados

// Tipo de dado especial (Registro)
typedef struct TProduto{
    long int codigo;
    int grupo;
    int sub_grupo;
    char descricao[41];
    char unidade[3];
    char fornecedor[41];
    float quantidade;
    float pr_compra;
    float pr_venda;
    int lucro;//mostrar lucro
    float estoque_min;
}Tproduto;

//escopo do programa
void leitura(Tproduto estoque[], int *tamanho);//gera o arquivo .dat na primeira vez
void gravacao(Tproduto estoque[], int tamanho);// realiza a grava��o dos dado no arquivo
int pesquisabinaria(Tproduto estoque[], int chave, int tamanho);//pesquisa por descri��o
int pesquisadescricao(Tproduto estoque[], int tamanho);//fun��o para pesquisar por descri��o
int vazio (int tamanho);// fun��o auxiliar para da pesquisa bin�ria
void ordena(Tproduto estoque[], int tamanho);//ordena o cadastro dos produtos por c�digo
void inclusao(Tproduto estoque[],int *tamanho);//cadastro de produtos
void atualiza(Tproduto estoque[],int *tamanho);//atualiza dados do produto j� cadastrado
void relatorio_geral (Tproduto estoque[], int tamanho);//relat�rio de todos os produtos
void relatorio_minimo (Tproduto estoque[], int tamanho);//relat�rio dos produtos com estoque abaixo do m�nimo
void exclusao(Tproduto estoque[], int *tamanho, int resultado);//exclui um produto
void altera_forn(Tproduto estoque[],int *tamanho);//aumento no pr_compra tds produtos de um determinado fornecedor

int main(){
    system("color 5F");
    setlocale(LC_ALL, "Portuguese");
	Tproduto estoque[MAX];
    int tamanho=0, opcao;
    leitura(estoque, &tamanho);// abre o arquivo da base de dados
    do{
        //menu para escolha da a��o
        printf("S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2\n");
        printf("\tS2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 \t ESTOQUEX \tS2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2\n");
        printf("S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2\n");
            printf ("\n 1- CADASTRAR\n");
            printf (" 2- ATUALIZAR\n");
            printf (" 3- EXCLUIR\n");
            printf (" 4- PESQUISAR\n");
            printf (" 5- RELAT�RIO GERAL\n");
            printf (" 6- RELAT�RIO ESTOQUE M�NIMO\n");
            printf (" 7- AJUSTE DE PRE�O\n"); //aumento tudo de um fornecedor
            printf (" 0- SAIR\n");
        printf("\nS2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2\n");
            printf ("\n ESCOLHA A OPCAO DESEJADA: ");
        scanf ("%d",&opcao);
        system("cls");
        switch (opcao){
            case 1:{
                //inclui informa��es no vetor estoque
            	inclusao(estoque, &tamanho);
            	//grava as informa��es no arquivo estoque.dat
            	gravacao(estoque, tamanho);
				break;
			}
            case 2:{
                //edita item do produto escolhido
            	atualiza(estoque, &tamanho);
                //grava as informa��es no arquivo estoque.dat
                gravacao(estoque, tamanho);
				break;
			}
            case 3:{
                int chave, resultado;
                int correto=0;
                 do{
                      printf ("\n Digite o c�digo do item que deseja excluir: ");
                      scanf ("%ld",&chave);
                      fflush(stdin);
                }while (chave <= 0);
                //salva c�digo encontrado pela pesquisa bin�ria para exibir na tela informa��es do produto pesquisado
				resultado = pesquisabinaria(estoque, chave, tamanho);
				    if(resultado != -1){
                        printf("\nItem est� na posi��o %d\n\n",resultado);
                              printf("______________________________________________________________________________________________________________________");
                                printf("\n C�digo: %-8ld \t\t\t Grupo: %-10d \t\t\t Subgrupo: %-8d", estoque[resultado].codigo, estoque[resultado].grupo, estoque[resultado].sub_grupo);
                                printf("\n Descri��o: %-20s \t\t Unidade: %-20s", estoque[resultado].descricao, estoque[resultado].unidade);
                                printf("\n Fornecedor: %-30s", estoque[resultado].fornecedor);
                                printf("\n Pre�o de Compra: %-8.2f \t Pre�o de Venda: %-10.2f \t Lucro: %-8d%%", estoque[resultado].pr_compra, estoque[resultado].pr_venda, estoque[resultado].lucro);
                                printf("\n Quantidade em Estoque: %-20.2f \t Quantidade M�nima: %-10.2f ", estoque[resultado].quantidade, estoque[resultado].estoque_min);
                                printf("\n---------------------------------------------------------------------------------------------------------------------\n\n");
                      fflush(stdin);
                      printf ("\n Deseja mesmo excluir esse item?(1-Sim/2-N�o)"); //valida a a��o do usu�rio
                      scanf("%d",&correto);
                      system("cls");

                          switch(correto){
                            case 1:{
                                //exclui produto da lista
                               exclusao(estoque,&tamanho,resultado);
                               //salva as altera��es no arquivo
                               gravacao(estoque, tamanho);
                               printf ("\tO PRODUTO FOI EXCLUIDO!\n");
                               system("cls");
                               fflush(stdin);
                            break;}
                            default:{
                                printf ("\tOPERA��O DE EXCLUS�O CANCELADA!\n");
                                printf("\tAPERTE ENTER PARA VOLTAR AO MENU");
                                fflush(stdin);
                                getchar();
                                system("cls");
                                fflush(stdin);}
                            }
				    }
                    else{
                        printf("\nNao foi encontrado este valor ( %i ) nos registros\n\n",resultado);
                        system("pause");
                        system("cls");

                    }
				break;
			}
            case 4:{
                int chave, resultado, codigo;
                char descricao;
                printf("REALIZAR PESQUISA POR:\n 1-C�DIGO\n 2-DESCRI��O\n\n");
                scanf("%d", &codigo);
                    switch(codigo){
                    case 1:{
                        printf("\nDigite o c�digo do produto a ser buscado: ");
                        scanf("%d", &chave);
                        fflush(stdin);
                        //salva c�digo encontrado pela pesquisa bin�ria para exibir na tela informa��es do produto pesquisado
                        resultado = pesquisabinaria(estoque, chave, tamanho);
                        if(resultado != -1){
                            printf("\nItem est� na posi��o %d\n\n",resultado);
                              printf("______________________________________________________________________________________________________________________");
                                printf("\n C�digo: %-8ld \t\t\t Grupo: %-10d \t\t\t Subgrupo: %-8d", estoque[resultado].codigo, estoque[resultado].grupo, estoque[resultado].sub_grupo);
                                printf("\n Descri��o: %-20s \t\t Unidade: %-20s", estoque[resultado].descricao, estoque[resultado].unidade);
                                printf("\n Fornecedor: %-30s", estoque[resultado].fornecedor);
                                printf("\n Pre�o de Compra: %-8.2f \t Pre�o de Venda: %-10.2f \t Lucro: %-8d%%", estoque[resultado].pr_compra, estoque[resultado].pr_venda, estoque[resultado].lucro);
                                printf("\n Quantidade em Estoque: %-20.2f \t Quantidade M�nima: %-10.2f ", estoque[resultado].quantidade, estoque[resultado].estoque_min);
                                printf("\n---------------------------------------------------------------------------------------------------------------------\n\n");
                        fflush(stdin);
                        system("pause");
                        system("cls");
                        }
                        else{
                            printf("\nNao foi encontrado este valor ( %i ) nos registros\n\n",resultado);
                            system("pause");
                            system("cls");
                        }
                    break;}
                    case 2:{
                        //realiza
                        pesquisadescricao(estoque, tamanho);
                    break;
                    }
                    default:
                        printf("OPCAO INVALIDA!\n");
                        system("pause");
                        system("cls");
                    }

				break;
			}
            case 5:{
                //exibe relat�rio de todos os produtos
				relatorio_geral (estoque, tamanho);
				break;
			}
            case 6:{
                //exibe relat�rio dos produtos que est�o com estoque abaixo do m�nimo
				relatorio_minimo (estoque, tamanho);
				break;
			}
            case 7:{
                //aumenta pre�o de compra do fornecedor selecionado
            	altera_forn(estoque, &tamanho);
                gravacao(estoque, tamanho);
				break;
			}
            case 0:
				printf("\n Obrigado por usar nosso sistema.\n");
				system("pause");
				exit(0);
				break;
            default: printf("OPCAO INVALIDA!\n");
            	system("pause");
            	system("cls");
        }
    }while (opcao!=0);
        gravacao(estoque, tamanho);// grava ap�s realizada as opera��es
	return 0;
}

//fun��o para excluir um cadastro
void exclusao(Tproduto estoque[], int *tamanho, int resultado){
            //caso a pesquisa bin�ria n�o encontre o c�digo abortar� a a��o
            if (resultado == -1) {
                printf("Erro no processamento.\n");
                return;
            }
            else{
                // Deslocar os produtos seguintes para preencher o espa�o vazio, realizando a exclus�o do item
                for (int j = resultado; j < *tamanho - 1; j++) {
                estoque[j] = estoque[j + 1];
                }
                (*tamanho) --;
                ordenado=0;
                }
    return;
}

//fun��o para abrir arquivo .dat e realizar a leitura
void leitura(Tproduto estoque[], int *tamanho){
    FILE *arquivo;
  	arquivo= fopen("estoque.dat", "a+b");	   /* abrimos para anexar, bin�rio */
  	if (!arquivo){
  		printf("Erro ao abrir arquivo!");
  		return;
  	}
//le os dados do arquivo
    while(!feof(arquivo)){
       fread (&estoque[*tamanho], sizeof (Tproduto) , 1, arquivo);
       (*tamanho)++;
    }
	(*tamanho)--;
//fecha o arquivo
	fclose(arquivo);
	return;
}

//fun��o para salvar as mudan�as e movimenta��es dos produtos
void gravacao(Tproduto estoque[], int tamanho){
    FILE *arquivo;
    int i;
    arquivo= fopen("estoque.dat", "w+b");	   /* abre e apaga o conte�do do arquivo,bin�rio */
  	if (!arquivo){
  		printf("Erro ao abrir arquivo!");
  		return;
  	}
// grava a estrutura no arquivo
    for(i=0;i<tamanho;i++)
       fwrite(&estoque[i], sizeof(Tproduto), 1, arquivo);
// Fecha o arquivo de dados
	fclose(arquivo);
	return;
}

//fun��o para realizar pesquisa binaria com referencia no c�digo de identifica��o do produto
int pesquisabinaria(Tproduto estoque[], int chave, int tamanho){
    if(vazio(tamanho))
       return -1;// vetor vazio
    if (! ordenado){
        ordena(estoque,tamanho);// ordena
        ordenado=1;// variavel global
    }
    int inicio=0,final=tamanho, meio;
    while (inicio<=final){
        meio=(int)(inicio+final)/2;
        if (estoque[meio].codigo==chave)
           return meio; // encontrou
        if (estoque[meio].codigo<chave)
           inicio=meio+1;
        else
           final=meio-1;
    }
    return -1; // n�o encontrou
}

//fun��o que realiza pesquisa com referencia na descri��o do produto
int pesquisadescricao(Tproduto estoque[], int tamanho){
    if(vazio(tamanho))
       return -1;// vetor vazio
    /*if (! ordenado){
        ordena(estoque,tamanho);// ordena
        ordenado=1;// variavel global
    }*/
    int value, i, total;//value:retorno strncmp; total:quantidade de caracteres
    char s1[41];
    printf("\nDigite a descri��o do produto a ser buscado: ");
    scanf("%s", &s1);
        for (i = 0; s1[i] != '\0'; i++) {
            s1[i] = toupper(s1[i]);
        }
    fflush(stdin);

    //funcao strlen para contar quantidades de caracteres em uma string
    int encontra=0;
    for(i=0; i<tamanho; i++){
    //funcao para comparar carateres das strings e retornar um valor 0 quando true
    value = strncmp(s1, estoque[i].descricao, strlen(s1));
        if(value == 0){
                printf("\nItem est� na posi��o %d\n\n",i);
                    printf("______________________________________________________________________________________________________________________");
                    printf("\n C�digo: %-8ld \t\t\t Grupo: %-10d \t\t\t Subgrupo: %-8d", estoque[i].codigo, estoque[i].grupo, estoque[i].sub_grupo);
                    printf("\n Descri��o: %-20s \t\t Unidade: %-20s", estoque[i].descricao, estoque[i].unidade);
                    printf("\n Fornecedor: %-30s", estoque[i].fornecedor);
                    printf("\n Pre�o de Compra: %-8.2f \t Pre�o de Venda: %-10.2f \t Lucro: %-8d%%", estoque[i].pr_compra, estoque[i].pr_venda, estoque[i].lucro);
                    printf("\n Quantidade em Estoque: %-20.2f \t Quantidade M�nima: %-10.2f ", estoque[i].quantidade, estoque[i].estoque_min);
                    printf("\n---------------------------------------------------------------------------------------------------------------------\n\n");
            getchar();
            system("pause");
            encontra++;

        }
    }
    if(encontra == 0){
        printf("\nPRODUTO N�O ENCONTRADO!\n");
        fflush(stdin);
    }
system("cls");
}

//fun��o que retorna valor para indicar se h� algum produto cadastrado
int vazio(int tamanho){
     if(tamanho==0){
        printf("\nREGISTRO VAZIO!\n");
        return 1;// vazio
     }
     return 0;// preenchido
}

//fun��o para ordenar produtos com referencia no c�digo de identifica��o
void ordena(Tproduto estoque[], int tamanho){
	int i,j;
    Tproduto aux;
    //ordena os produtos por c�digos em ordem crescente
    for(i=0;i<tamanho-1;i++)
        for(j=i+1;j<tamanho;j++)
          	if (estoque[i].codigo>estoque[j].codigo){
              	aux=estoque[i];
              	estoque[i]=estoque[j];
              	estoque[j]=aux;
            }
}

//fun��o para atualizar/editar informa��es no cadastro dos produtos
void atualiza(Tproduto estoque[],int *tamanho){
             int chave, j, resultado;
             char correto='n';
             do{
                  printf ("\n Digite o c�digo do item que deseja editar: ");
                  scanf ("%ld",&chave);
				  fflush(stdin);
            }while (chave <= 0);
            resultado = pesquisabinaria(estoque, chave, *tamanho);
                    printf("\nItem est� na posi��o %d\n\n",resultado);
                        printf("______________________________________________________________________________________________________________________");
                        printf("\n C�digo: %-8ld \t\t\t Grupo: %-10d \t\t\t Subgrupo: %-8d", estoque[resultado].codigo, estoque[resultado].grupo, estoque[resultado].sub_grupo);
                        printf("\n Descri��o: %-20s \t\t Unidade: %-20s", estoque[resultado].descricao, estoque[resultado].unidade);
                        printf("\n Fornecedor: %-30s", estoque[resultado].fornecedor);
                        printf("\n Pre�o de Compra: %-8.2f \t Pre�o de Venda: %-10.2f \t Lucro: %-8d%%", estoque[resultado].pr_compra, estoque[resultado].pr_venda, estoque[resultado].lucro);
                        printf("\n Quantidade em Estoque: %-20.2f \t Quantidade M�nima: %-10.2f ", estoque[resultado].quantidade, estoque[resultado].estoque_min);
                        printf("\n---------------------------------------------------------------------------------------------------------------------\n\n");
                      fflush(stdin);
            if (resultado >= 0  ){
                    printf("\nQual campo deseja alterar?\n\n 1-GRUPO\n 2-DESCRI��O\n 3-UNIDADE\n 4-FORNECEDOR\n 5-PRE�O DE COMPRA\n 6-PRE�O DE VENDA\n 7-QUANTIDADE EM ESTOQUE\n 8-QUANTIDADE M�NIMA\n 0-SAIR\n");
                    scanf("\n\n%d", &j);
                        switch(j){
                            case 1:{
                                do{
                                    printf("\n 1 - BEBIDAS\n 2 - ALIMENTOS N�O PEREC�VEIS\n 3 - PRODUTOS DE HIGIENE E LIMPEZA\n");
                                    printf("Digite novo grupo: ");
                                    scanf ("%d",&estoque[resultado].grupo);
                                    switch(estoque[resultado].grupo){
                                        case 1:{
                                            break;
                                        }
                                        case 2:{
                                            break;
                                        }
                                        case 3:{
                                            break;
                                        }
                                        default:
                                            estoque[resultado].grupo = -1;
                                        fflush(stdin);}
                                }while(estoque[resultado].grupo<0);
                                if(estoque[resultado].grupo == 1){
                                    do{
                                        printf("\n 11 - ALCO�LICA\n 12 - N�O ALCO�LICA");
                                        printf (" Subgrupo ...............: ");
                                        scanf ("%d",&estoque[resultado].sub_grupo);
                                            switch(estoque[resultado].sub_grupo){
                                            case 11:{
                                                break;
                                            }
                                            case 12:{
                                                break;
                                            }
                                            default:
                                                estoque[resultado].sub_grupo = -1;
                                            }
                                        fflush(stdin);
                                    }while(estoque[resultado].sub_grupo<0);
                              }
                              if(estoque[resultado].grupo == 2){
                                    estoque[resultado].sub_grupo = 0;
                                    fflush(stdin);
                              }
                              if(estoque[resultado].grupo == 3){
                                    do{
                                        printf("\n 31 - HIGIENE\n 32 - LIMPEZA");
                                        printf (" Subgrupo ...............: ");
                                        scanf ("%d",&estoque[resultado].sub_grupo);
                                            switch(estoque[resultado].sub_grupo){
                                            case 31:{
                                                break;
                                            }
                                            case 32:{
                                                break;
                                            }
                                            default:
                                                estoque[resultado].sub_grupo = -1;
                                            }
                                        fflush(stdin);
                                    }while(estoque[resultado].sub_grupo<0);
                              }
                            break;
                            }
                            case 2:{
                                do{
                                    printf (" Digite a nova descri��o: ");
                                    getchar();
                                    gets (estoque[resultado].descricao);
                                        int i;
                                        for (i = 0; estoque[resultado].descricao[i] != '\0'; i++) {
                                            estoque[resultado].descricao[i] = toupper(estoque[resultado].descricao[i]);
                                        }
                                    fflush(stdin);
                                }while(estoque[resultado].descricao[0] == '\0');
                            break;
                            }
                            case 3:{
                                do{
                                    printf (" Digite a nova unidade de medida: ");
                                    getchar();
                                    gets (estoque[resultado].unidade);
                                        int i;
                                        for (i = 0; estoque[resultado].unidade[i] != '\0'; i++) {
                                            estoque[resultado].unidade[i] = toupper(estoque[resultado].unidade[i]);
                                        }
                                    fflush(stdin);
                                }while(estoque[resultado].unidade[0] == '\0');
                            break;
                            }
                            case 4:{
                                do{
                                    printf (" Digite o novo fornecedor: ");
                                    getchar();
                                    gets (estoque[resultado].fornecedor);
                                        int i;
                                        for (i = 0; estoque[resultado].fornecedor[i] != '\0'; i++) {
                                            estoque[resultado].fornecedor[i] = toupper(estoque[resultado].fornecedor[i]);
                                        }
                                    fflush(stdin);
                                }while(estoque[resultado].fornecedor[0] == '\0');
                            break;
                            }
                            case 5:{
                                do{
                                    printf (" Digite o novo pre�o de compra: ");
                                    scanf ("%f",&estoque[resultado].pr_compra);
                                    fflush(stdin);
                                    estoque[resultado].lucro = 0;
                                    estoque[resultado].lucro = ((estoque[resultado].pr_venda-estoque[resultado].pr_compra)*100)/estoque[resultado].pr_compra;
                                }while(estoque[resultado].pr_compra<0);
                            break;
                            }
                            case 6:{
                                do{
                                    printf (" Digite o novo pre�o de venda: ");
                                    scanf ("%f",&estoque[resultado].pr_venda);
                                    fflush(stdin);
                                    estoque[resultado].lucro = 0;
                                    estoque[resultado].lucro = ((estoque[resultado].pr_venda-estoque[resultado].pr_compra)*100)/estoque[resultado].pr_compra;
                                }while(estoque[resultado].pr_venda<0);
                            break;
                            }
                            case 7:{
                                do{
                                    printf (" Digite o nova quantidade em estoque: ");
                                    scanf ("%f",&estoque[resultado].quantidade);
                                    fflush(stdin);
                                }while(estoque[resultado].quantidade<0);
                            break;
                            }
                            case 8:{
                                do{
                                    printf (" Digite o nova quantidade m�nima: ");
                                    scanf ("%f",&estoque[resultado].estoque_min);
                                    fflush(stdin);
                                }while(estoque[resultado].estoque_min<0);
                            break;
                            }
                            case 0:{
                                break;
                                system("pause");
                                system("cls");
                            break;
                            }
                            default: printf("OPCAO INVALIDA!\n");
                                system("pause");
                                system("cls");
                        }
            }else{
                printf ("\tCODIGO N�O ENCONTRADO!!\n");
                printf("\tAPERTE ENTER PARA VOLTAR AO MENU");
                fflush(stdin);
                getchar();
                system("cls");}
system("cls");
 return;}

//fun��o que aumenta o pre�o de todos os produtos do mesmo fornecedor
void altera_forn(Tproduto estoque[],int *tamanho){
    //salva a porcentagem de aumento dos produtos
    float porcento;
    printf("\nDigite porcentagem de aumento nos produtos: ");
    scanf("%f", &porcento);
    porcento = (porcento/100) + 1;
    fflush(stdin);
        if(vazio(*tamanho))
            return;// vetor vazio
        if (! ordenado){
            ordena(estoque,*tamanho);// ordena
            ordenado=1;// variavel global
        }
    int value, i, total, encontra=0;//value:retorno strncmp; total:quantidade de caracteres
    char s1[41];
    do{
        printf("\nDigite o fornecedor do produto a ser buscado: ");
        scanf("%s", &s1);
        int i;
        for (i = 0; s1[i] != '\0'; i++) {
                s1[i] = toupper(s1[i]);
        }
        fflush(stdin);
    }while(s1[0] == '\0');

    //funcao strlen para contar quantidades de caracteres em uma string
    int decisao;
    for(i=0; i<*tamanho; i++){
        //funcao para comparar carateres das strings e retornar um valor 0 quando true
        value = strncmp(s1, estoque[i].fornecedor, strlen(s1));
            if(value == 0){
                encontra++;
                printf("\nItem est� na posi��o %d\n\n",i);
                    printf("______________________________________________________________________________________________________________________");
                    printf("\n C�digo: %-8ld \t\t\t Grupo: %-10d \t\t\t Subgrupo: %-8d", estoque[i].codigo, estoque[i].grupo, estoque[i].sub_grupo);
                    printf("\n Descri��o: %-20s \t\t Unidade: %-20s", estoque[i].descricao, estoque[i].unidade);
                    printf("\n Fornecedor: %-30s", estoque[i].fornecedor);
                    printf("\n Pre�o de Compra: %-8.2f \t Pre�o de Venda: %-10.2f \t Lucro: %-8d%%", estoque[i].pr_compra, estoque[i].pr_venda, estoque[i].lucro);
                    printf("\n Quantidade em Estoque: %-20.2f \t Quantidade M�nima: %-10.2f ", estoque[i].quantidade, estoque[i].estoque_min);
                    printf("\n---------------------------------------------------------------------------------------------------------------------\n\n");
                    do{
                    printf("Confirma o aumento no pre�o de compra desse produto de %f? (1-SIM/2-N�O/0-VOLTAR AO MENU)", porcento);
                    scanf("%d", &decisao);

                            switch(decisao){
                            case 1:{
                                   printf("ok");
                                   estoque[i].pr_compra = estoque[i].pr_compra*porcento;
                                   estoque[i].lucro = 0;
                                   estoque[i].lucro = ((estoque[i].pr_venda-estoque[i].pr_compra)*100)/estoque[i].pr_compra;

                                break;
                            }
                            case 2:{
                                break;
                            }
                            case 0:{
                                printf("\nOPERA��O CANCELADA COM SUCESSO!\n");
                                fflush(stdin);
                                break;
                            }
                            default:{
                                decisao = -1;
                            }
                            }
                        }while(decisao == -1);
        }
    }
        if(encontra == 0){
        printf(" \nNENHUM PRODUTO ENCONTRADO\n\n");
        system("pause");
    }

system("cls");
 return;}

//cadastra os produtos no vetor
void inclusao(Tproduto estoque[],int *tamanho){
             if (*tamanho==MAX){
                   printf ("\n ERRO! \n ARQUIVO CHEIO.\n");
                   return;
             }
             Tproduto aux;
             //solicita informa��es para o usu�rio
             char correto='n';
             do{
                  printf ("\n C�digo ..............................: ");
                  scanf ("%ld",&aux.codigo);
				  fflush(stdin);
            }while (aux.codigo <= 0);
            if (pesquisabinaria(estoque, aux.codigo, *tamanho) <0){
                  do{
                        printf("\n 1 - BEBIDAS\n 2 - ALIMENTOS N�O PEREC�VEIS\n 3 - PRODUTOS DE HIGIENE E LIMPEZA\n");
                        printf (" Grupo ...............: ");
                        scanf ("%d",&aux.grupo);
                            switch(aux.grupo){
                                case 1:{
                                    break;
                                }
                                case 2:{
                                    break;
                                }
                                case 3:{
                                    break;
                                }
                                default:
                                    aux.grupo = -1;
                            }
						fflush(stdin);
                    }while(aux.grupo<0);
                          if(aux.grupo == 1){
                                do{
                                    printf("\n 11 - ALCO�LICA\n 12 - N�O ALCO�LICA");
                                    printf (" Subgrupo ...............: ");
                                    scanf ("%d",&aux.sub_grupo);
                                        switch(aux.sub_grupo){
                                        case 11:{
                                            break;
                                        }
                                        case 12:{
                                            break;
                                        }
                                        default:
                                            aux.sub_grupo = -1;
                                        }
                                    fflush(stdin);
                                }while(aux.sub_grupo<0);
                          }
                          if(aux.grupo == 2){
                                aux.sub_grupo = 0;
                                fflush(stdin);
                          }
                          if(aux.grupo == 3){
                                do{
                                    printf("\n 31 - HIGIENE\n 32 - LIMPEZA");
                                    printf (" Subgrupo ...............: ");
                                    scanf ("%d",&aux.sub_grupo);
                                        switch(aux.sub_grupo){
                                        case 31:{
                                            break;
                                        }
                                        case 32:{
                                            break;
                                        }
                                        default:
                                            aux.sub_grupo = -1;
                                        }
                                    fflush(stdin);
                                }while(aux.sub_grupo<0);
                          }
                  do{
                        printf (" Descri��o ...............: ");
                        gets (aux.descricao);
                            int i;
                            for (i = 0; aux.descricao[i] != '\0'; i++) {
                                aux.descricao[i] = toupper(aux.descricao[i]);
                            }
						fflush(stdin);
                    }while(aux.descricao[0] == '\0');
                  do{
                        printf (" Unidade de Medida ...............: ");
                        gets (aux.unidade);
                            int i;
                            for (i = 0; aux.unidade[i] != '\0'; i++) {
                                aux.unidade[i] = toupper(aux.unidade[i]);
                            }
						fflush(stdin);
                    }while(aux.unidade[0] == '\0');
                    do{
                        printf (" Fornecedor ...............: ");
                        gets (aux.fornecedor);
                            int i;
                            for (i = 0; aux.fornecedor[i] != '\0'; i++) {
                                aux.fornecedor[i] = toupper(aux.fornecedor[i]);
                            }
						fflush(stdin);
                    }while(aux.fornecedor[0] == '\0');
                  do{
                        printf (" Quantidade do produto ...............: ");
                        scanf ("%f",&aux.quantidade);
						fflush(stdin);
                    }while(aux.quantidade<0);
                  do{
                  		printf (" Preco de compra do produto ..........: ");
                  		scanf ("%f",&aux.pr_compra);
						fflush(stdin);
				  }while(aux.pr_compra<0);
                  do{
                  		printf (" Pre�o de venda do produto ..........: ");
                  		scanf ("%f",&aux.pr_venda);
						fflush(stdin);
						aux.lucro = 0;
						aux.lucro = ((aux.pr_venda-aux.pr_compra)*100)/aux.pr_compra;
				  }while(aux.pr_venda<0);
				  do{
                  		printf (" Estoque M�nimo Permitido ..........: ");
                  		scanf ("%f",&aux.estoque_min);
						fflush(stdin);
				  }while(aux.estoque_min<0);

                  //confirma a a��o
				  printf (" Os dados estao corretos?(S/N)");
                  correto=getchar();
				  fflush(stdin);
				  system("cls");

                  if (correto=='s'||correto=='S'){
                       estoque [*tamanho] = aux;// faz a transfer�ncia
                       (*tamanho) ++;
                       ordenado=0;
                       printf ("\tO PRODUTO FOI INCLUIDO!\n");
					fflush(stdin);
                  }else{
                    printf ("\tOPERA��O CANCELADA!!\n");
                    printf("\tAPERTE ENTER PARA VOLTAR AO MENU");
                    fflush(stdin);
                    getchar();
                    system("cls");}
            }else{
                printf ("\tCODIGO JA CADASTRADO!!\n");
                printf("\tAPERTE ENTER PARA VOLTAR AO MENU");
                fflush(stdin);
                getchar();
                system("cls");}
return;
}

//retorna relat�rio todos os produtos cadastrados em ordem crescente em rela�ao ao c�digo
void relatorio_geral (Tproduto estoque[], int tamanho){
    int i, cont, escolha;
    do{
    printf(" Escolha uma op��o:\n 1-RELAT�RIO DE PRODUTOS\n 2-LISTA DE PRE�OS\n\n");
    scanf("\n%d", &escolha);
    system("cls");
    switch(escolha){
        //relatorio produtos (todas as informa��es) de 2 em 2 produtos por vez
        case 1:
            printf("S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2\n");
            printf("\t\tControle de Estoque - Relat�rio de Produtos\n");
            printf("S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2\n");
            //coloca em ordem crescente os produtos por c�digo
            ordena(estoque, tamanho);
            //lista produtos caso a lista n�o esteja vazia
            if (tamanho > 0) {
                for (i = 0; i < tamanho; i += 2) {
                    for (cont = 0; cont < 2 && (i + cont) < tamanho; cont++) {
                        printf("______________________________________________________________________________________________________________________");
                        printf("\n C�digo: %-8ld \t\t\t Grupo: %-10d \t\t\t Subgrupo: %-8d", estoque[i + cont].codigo, estoque[i + cont].grupo, estoque[i + cont].sub_grupo);
                        printf("\n Descri��o: %-20s \t\t Unidade: %-20s", estoque[i + cont].descricao, estoque[i + cont].unidade);
                        printf("\n Fornecedor: %-30s", estoque[i + cont].fornecedor);
                        printf("\n Pre�o de Compra: %-8.2f \t Pre�o de Venda: %-10.2f \t Lucro: %-8d%%", estoque[i + cont].pr_compra, estoque[i + cont].pr_venda, estoque[i + cont].lucro);
                        printf("\n Quantidade em Estoque: %-20.2f \t Quantidade M�nima: %-10.2f ", estoque[i + cont].quantidade, estoque[i + cont].estoque_min);
                        printf("\n---------------------------------------------------------------------------------------------------------------------\n\n");
                        fflush(stdin);
                    }
                    printf("\nAPERTE QUALQUER TECLA PARA AVAN�AR\n");
                    getchar();
                    system("cls");
                }
            }
            else{
               printf(" \nESTOQUE VAZIO :(\n\n");
               system("pause");
            }
        break;
        //relatorio lista de pre�os dos produtos de 15 em 15 produtos por vez
        case 2:
            printf("S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2\n");
            printf("\t\tControle de Estoque - Lista de Pre�os\n");
            printf("S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2\n");
            //coloca em ordem crescente os produtos por c�digo
            ordena(estoque, tamanho);
            //lista produtos caso a lista n�o esteja vazia
            if (tamanho > 0) {
                printf("==========================================================================\n\n");
                printf("C�digo\tDescri��o\t\t\t\t\tPre�o\n");
                printf("--------------------------------------------------------------------------\n");

                for (i = 0; i < tamanho; i += 15) {
                    for (cont = 0; cont < 15 && (i + cont) < tamanho; cont++) {

                        // loop para printar as informa��es
                            printf("\n%-6ld\t%-50s\t%.2f\n", estoque[i + cont].codigo, estoque[i + cont].descricao, estoque[i + cont].pr_venda);

                    }
                    printf("\n--------------------------------------------------------------------------\n");
                    system("pause");
                    getchar();
                    system("cls");
                }
            }
            else{
               printf(" \nESTOQUE VAZIO :(\n\n");
               system("pause");
            }
        break;
        default:
            printf("\nC�DIGO INV�LIDO!\n");
            system("pause");
            getchar();
            system("cls");
            escolha = -1;
    }
    }while(escolha ==  -1);
    printf("\nAPERTE ENTER PARA VOLTAR AO MENU\n");
    getchar();
    system("cls");
}

//retorna relatorio de todos os produtos com estoque abaixo do m�nimo permitido
void relatorio_minimo (Tproduto estoque[], int tamanho){
	int i, encontra=0;
    printf("S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2\n");
	printf("\t\tControle de Estoque - Relat�rio Produto com Estoque Abaixo do M�nimo\n");
    printf("S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2 S2\n");
    //coloca em ordem crescente os produtos por c�digo
    ordena(estoque, tamanho);
    //lista produtos caso a lista n�o esteja vazia
    if(tamanho > 0){
    for(i=0; i<tamanho; i++){
            //verifica se quantidade do produto est� devida em rela��o a quantidade de estoque m�nima exigida, caso contr�rio exibe produtos na tela
            if(estoque[i].quantidade < estoque[i].estoque_min){
                        printf("______________________________________________________________________________________________________________________");
                        printf("\n C�digo: %-8ld \t\t\t Grupo: %-10d \t\t\t Subgrupo: %-8d", estoque[i].codigo, estoque[i].grupo, estoque[i].sub_grupo);
                        printf("\n Descri��o: %-20s \t\t Unidade: %-20s", estoque[i].descricao, estoque[i].unidade);
                        printf("\n Fornecedor: %-30s", estoque[i].fornecedor);
                        printf("\n Pre�o de Compra: %-8.2f \t Pre�o de Venda: %-10.2f \t Lucro: %-8d%%", estoque[i].pr_compra, estoque[i].pr_venda, estoque[i].lucro);
                        printf("\n Quantidade em Estoque: %-20.2f \t Quantidade M�nima: %-10.2f ", estoque[i].quantidade, estoque[i].estoque_min);
                        printf("\n---------------------------------------------------------------------------------------------------------------------\n\n");
                        fflush(stdin);
                        encontra++;
            }
    }
    }
    else{
        printf(" \nESTOQUE VAZIO :(\n\n");
        system("pause");
    }
    if(encontra == 0){
        printf(" \nTODOS OS PRODUTOS EST�O OK! :)\n\n");
        system("pause");
    }
    printf("\nAPERTE ENTER PARA VOLTAR AO MENU\n");
    getchar();
    system("cls");
return;}
