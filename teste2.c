#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#ifdef _WIN32
    #include <direct.h> // Para criar pasta no Windows
#else
    #include <sys/stat.h> // Para criar pasta no Linux/Mac
    #include <sys/types.h>
    #include <errno.h>
#endif

// Cria a pasta "dados" caso não exista
void criar_pasta_dados() {
    #ifdef _WIN32
        _mkdir("dados"); // Cria pasta no Windows
    #else
        // Cria pasta no Linux/Mac, se não existir
        if (mkdir("dados", 0755) == -1) {
            if (errno != EEXIST) {
                printf("Erro ao criar pasta 'dados'\n");
                exit(1); // Sai do programa se não conseguir criar pasta
            }
        }
    #endif
}

// Limpa a tela no Windows ou Linux/Mac
void limpar_tela() {
    #ifdef _WIN32
        system("cls"); // Comando do Windows para limpar tela
    #else
        system("clear"); // Comando do Linux/Mac para limpar tela
    #endif
}

// Pausa o programa até o usuário apertar ENTER
void pausar() {
    #ifdef _WIN32
        system("pause"); // Pausa no Windows
    #else
        printf("Pressione ENTER para continuar...");
        getchar(); // Espera o ENTER no Linux/Mac
    #endif
}

// Função para registrar os dados do usuário em arquivo
void registro() {
    char arquivo[100], cpf[40], nome[40], sobrenome[40], cargo[40];

    criar_pasta_dados();  // Garante que a pasta "dados" existe

    printf("Digite o CPF a ser cadastrado: ");
    scanf("%s", cpf);
    getchar(); // Limpa o ENTER sobrando no teclado

    // Cria o caminho completo do arquivo dentro da pasta "dados"
    snprintf(arquivo, sizeof(arquivo), "dados/%s", cpf);

    // Abre o arquivo para escrita (cria ou substitui)
    FILE *file = fopen(arquivo, "w");
    if(file == NULL) {
        printf("Erro ao criar arquivo.\n");
        pausar();
        return; // Sai da função se erro
    }
    fprintf(file, "%s,", cpf); // Escreve o CPF seguido de vírgula
    fclose(file); // Fecha o arquivo

    // Pergunta e salva o nome
    printf("Digite o nome a ser cadastrado: ");
    scanf("%s", nome);
    getchar();

    file = fopen(arquivo, "a"); // Abre para acrescentar (append)
    if(file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        pausar();
        return;
    }
    fprintf(file, "%s,", nome); // Escreve nome e vírgula
    fclose(file);

    // Pergunta e salva o sobrenome
    printf("Digite o sobrenome a ser cadastrado: ");
    scanf("%s", sobrenome);
    getchar();

    file = fopen(arquivo, "a");
    if(file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        pausar();
        return;
    }
    fprintf(file, "%s,", sobrenome); // Escreve sobrenome e vírgula
    fclose(file);

    // Pergunta e salva o cargo
    printf("Digite o seu cargo a ser cadastrado: ");
    scanf("%s", cargo);
    getchar();

    file = fopen(arquivo, "a");
    if(file == NULL) {
        printf("Erro ao abrir arquivo.\n");
        pausar();
        return;
    }
    fprintf(file, "%s", cargo); // Escreve o cargo (último campo, sem vírgula)
    fclose(file);

    pausar(); // Espera o usuário para continuar
}

// Função para consultar os dados de um usuário pelo CPF
void consulta() 
{
    setlocale(LC_ALL, "Portuguese");

    char cpf[40];
    char arquivo[100];
    char conteudo[200];

    printf("Digite o CPF a ser verificado: ");
    scanf("%s", cpf);
    getchar(); // Limpa o ENTER

    // Monta o caminho do arquivo dentro da pasta "dados"
    snprintf(arquivo, sizeof(arquivo), "dados/%s", cpf);

    // Abre o arquivo para leitura
    FILE *file = fopen(arquivo, "r");

    if(file == NULL) {
        printf("Arquivo não localizado \n");
        pausar();
        return; // Sai se arquivo não existe
    }

    printf("\nEssas são as informações do usuário:\n");

    // Lê linha por linha e imprime na tela
    while(fgets(conteudo, sizeof(conteudo), file) != NULL) {
        printf("%s", conteudo);
    }

    fclose(file);
    printf("\n");
    pausar();
}

// Função para deletar arquivo do usuário pelo CPF
void deletar() {
    char cpf[40];
    char arquivo[100];

    printf("Digite o CPF a ser removido: ");
    scanf("%s", cpf);
    getchar(); // Limpa o ENTER

    // Monta o caminho do arquivo dentro da pasta "dados"
    snprintf(arquivo, sizeof(arquivo), "dados/%s", cpf);

    // Verifica se o arquivo existe
    FILE *file = fopen(arquivo, "r");
    if(file == NULL) {
        printf("USUÁRIO NÃO ENCONTRA-SE NO SISTEMA.\n");
        pausar();
        return;
    }
    fclose(file);

    // Tenta apagar o arquivo
    if(remove(arquivo) == 0) {
        printf("Usuário removido com sucesso!\n");
    } else {
        printf("Erro ao remover o usuário.\n");
    }
    pausar();
}

int main() {
    int opcao = 0;

    setlocale(LC_ALL, "Portuguese");

    while(1) {
        limpar_tela();

        // Mostra o menu para o usuário escolher
        printf("### Cartório da EBAC ### \n\n");
        printf("Escolha a opção desejada no menu\n\n");
        printf("\t1 - Registrar nomes\n");
        printf("\t2 - Consultar nomes\n");
        printf("\t3 - Deletar nomes\n\n");
        printf("\t0 - Sair\n");
        printf("Opção: ");

        scanf("%d", &opcao);
        getchar(); // Limpa o ENTER

        limpar_tela();

        // Escolhe a ação de acordo com a opção digitada
        switch(opcao) {
            case 1:
                registro();
                break;
            case 2:
                consulta();
                break;
            case 3:
                deletar();
                break;
            case 0:
                printf("Obrigado por utilizar o sistema!\n");
                exit(0); // Sai do programa
                break;
            default:
                printf("Essa opção não está disponível!\n");
                pausar();
        }
    }
}
