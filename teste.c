#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Limpa a tela, funciona no Windows e no Mac/Linux
void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Faz o programa esperar o usuário apertar ENTER para continuar, funciona no Windows e Mac/Linux
void pausar() {
    #ifdef _WIN32
        system("pause");
    #else
        printf("Pressione ENTER para continuar...");
        getchar();
    #endif
}

void registro() {
    char arquivo[40], cpf[40], nome[40], sobrenome[40], cargo[40];

    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);
    getchar(); // limpa o ENTER que fica no final do teclado

    strcpy(arquivo, cpf); // nome do arquivo vai ser o cpf

    // Criar arquivo novo com o nome do CPF e escrever o CPF e uma vírgula
    FILE *file = fopen(arquivo, "w");
    fprintf(file, "%s,", cpf);
    fclose(file);

    printf("Digite o nome a ser cadastrado: ");
    scanf("%s", nome);
    getchar();

    // Abrir o arquivo para acrescentar o nome e uma vírgula
    file = fopen(arquivo, "a");
    fprintf(file, "%s,", nome);
    fclose(file);

    printf("Digite o sobrenome a ser cadastrado: ");
    scanf("%s", sobrenome);
    getchar();

    file = fopen(arquivo, "a");
    fprintf(file, "%s,", sobrenome);
    fclose(file);

    printf("Digite o seu cargo a ser cadastrado: ");
    scanf("%s", cargo);
    getchar();

    file = fopen(arquivo, "a");
    fprintf(file, "%s", cargo);
    fclose(file);

    pausar();
}

void consulta() 
{
    setlocale(LC_ALL, "Portuguese");

    char cpf[40];
    char conteudo[200];

    printf("Digite o CPF a ser verificado: ");
    scanf("%s", cpf);
    getchar(); // limpar o ENTER

    // Abrir o arquivo que tem o nome do CPF para ler
    FILE *file = fopen(cpf, "r");

    if(file == NULL) // Se não achou o arquivo
    {
        printf("Arquivo não localizado \n");
        pausar();    // Espera o usuário apertar ENTER
        return;      // Sai da função pra não dar erro
    }

    printf("\nEssas são as informações do usuário:\n");

    // Ler linha por linha e mostrar na tela
    while(fgets(conteudo, sizeof(conteudo), file) != NULL)
    {
        printf("%s", conteudo);
    }

    fclose(file); // Fecha o arquivo

    printf("\n");
    pausar();
}

void deletar() {
    
    char cpf[40];

    printf("Digite o CPF a ser removido: ");
    scanf("%s", cpf);

    remove(cpf);

    FILE *file;
    file = fopen(cpf, "r");
    
    if(file ==NULL)
    {
        printf("USUÁRIO NÃO ENCONTRA-SE NO SISTEMA. \n");
        fclose(file); // Fecha o arquivo
    }
}

int main() {
    int opcao = 0;

    setlocale(LC_ALL, "Portuguese");

    while (1) {
        limpar_tela();
        printf("### Cartório da EBAC ### \n\n");
        printf("Escolha a opção desejada no menu\n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n");
        printf("\t0 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa ENTER

        limpar_tela();

        switch (opcao) {
            case 1: registro(); break;
            case 2: consulta(); break;
            case 3: deletar(); break;
            case 0: exit(0);
            default:
                printf("Essa opção não está disponível!\n");
                pausar();
        }
    }
}
