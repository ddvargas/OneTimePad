//
// Created by Daniel Vargas on 30/06/2020.
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

#define TAM_BUFFER_READ_FILE 255
#define TAM_DICIONARIO 52

FILE *f_cipher;
FILE *f_key;
FILE *f_plaintext;
char last_char;

FILE *open_file(char nome_arq[], char mode[]);

void setup_work_directory();

void close_directory();

char encript(char c, char key);

char get_key();

void write_key(char key);

bool on_acceptable_range(char key);

void write_cipher(char cifra);

void write_plaintext(char plaintext);

char decript(char cifra, char key);

int main() {
    //Ajustes iniciais do ambiente
    setlocale(LC_ALL, "");

    // declaração de variáveis
    char nome_arquivo[100];
    int opcao_menu_principal;

    printf("\n\n************ Bem vindo ao One-Time Pad ************\n");
    do {
        printf("\n1-Encriptar  2-Decriptar  0-Sair\nSelecione: ");
        scanf("%d", &opcao_menu_principal);

        switch (opcao_menu_principal) {
            case 1: //encriptar
                printf("Nome do arquivo a ser encriptado: ");
                scanf("%s", nome_arquivo);

                f_plaintext = open_file(nome_arquivo, "r");
                srand((unsigned) time(NULL));

                if (f_plaintext != NULL) {
                    char buffer[TAM_BUFFER_READ_FILE];
                    int cifra;
                    char key;

                    setup_work_directory();

                    //Fluxo principal
                    while (!feof(f_plaintext)) {
                        fgets(buffer, TAM_BUFFER_READ_FILE, f_plaintext);
                        for (int i = 0; i < TAM_BUFFER_READ_FILE || !feof(f_plaintext); ++i) {
                            if (buffer[i] != EOF && buffer[i] != '\0' && buffer[i] != '\n') {
                                if (buffer[i] != ' ') { //para cada caracter lido, diferente de espaço
                                    key = get_key(); //gerar uma nova chave
                                    cifra = encript(buffer[i],
                                                    key); //encriptar o caractere com a chave gerada e salvar a cifra
                                    write_key(key); //salvar a chave usada
                                    write_cipher(cifra); //salvar a cifra
                                }
                            } else {
                                break;
                            }
                        }
                    }
                    printf("Encriptação concluída\n");
                    close_directory();
                } else {
                    printf("Arquivo não encontrado.\n");
                    opcao_menu_principal = 1;
                }
                break;
            case 2: //decriptar
                printf("Arquivo da chave: ");
                scanf("%s", nome_arquivo);
                f_key = open_file(nome_arquivo, "r");

                if (f_key != NULL) {
                    printf("Arquivo com a cifra: ");
                    scanf("%s", nome_arquivo);
                    f_cipher = open_file(nome_arquivo, "r");

                    if (f_cipher != NULL) {
                        printf("Defina o nome do arquivo de saida: ");
                        scanf("%s", nome_arquivo);

                        f_plaintext = open_file(nome_arquivo, "w");

                        if (f_plaintext != NULL) {
                            char buffer_key[TAM_BUFFER_READ_FILE];
                            char buffer_cipher[TAM_BUFFER_READ_FILE];

                            while (!feof(f_cipher) && !feof(f_key)) {
                                fgets(buffer_cipher, TAM_BUFFER_READ_FILE, f_cipher);
                                fgets(buffer_key, TAM_BUFFER_READ_FILE, f_key);

                                for (int i = 0; i < TAM_BUFFER_READ_FILE; i++) {
                                    if (buffer_key[i] != EOF && buffer_key[i] != '\0' && buffer_key[i] != '\n') {
                                        write_plaintext(decript(buffer_cipher[i], buffer_key[i]));
                                    } else {
                                        break;
                                    }
                                }
                            }
                            close_directory();
                            printf("Decriptação concluída, verifique a mensagem em %s\n", nome_arquivo);
                        }
                    }
                }
                break;
            case 0: //sair
                printf("Bye\n");
                break;
            default:
                printf("Opção desconhecida digite um número do menú\n");
        }
    } while (opcao_menu_principal != 0);
}

/**
 * Escreve a chave usada no arquivo que contém a chave
 * @param key chave que foi usada na encriptação
 */
void write_key(char key) {
    if (key != NULL) {
        putc(key, f_key);
    }
}

/**
 * Função que recebe um caractere e escreve-o no arquivo de saída do plaintext
 * @param c caractere a ser escrito
 */
void write_plaintext(char c) {
    if (c != NULL) {
        putc(c, f_plaintext);
    }
}

/**
 * Faz a cifra de um caractere usando uma chave
 * @param c caractere a ser encritado
 * @param key chave usada para encriptar
 * @return a cifra
 */
char encript(char c, char key) {
    if (c != NULL && key != NULL) {
        return c ^ key;
    }
}

/**
 * Decripta um caractere usando a chave
 * @param cifra caractere vindo da cifra
 * @param key caractere da chave correspondente à cifra
 * @return o caractere resultante da decriptação
 */
char decript(char cifra, char key) {
    if (cifra != NULL && key != NULL) {
        return cifra ^ key;
    }
}

/**
 * Fecha os arquivos sendo usados pelo programa
 */
void close_directory() {
    if (f_cipher != NULL) {
        fflush(f_cipher);
        fclose(f_cipher);
    }
    if (f_plaintext != NULL) {
        fflush(f_plaintext);
        fclose(f_plaintext);
    }
    if (f_key != NULL) {
        fflush(f_key);
        fclose(f_key);
    }
}

/**
 * Abre e cria os arquivos necessarios para encriptar. Cria o arquivo de cifra e de chave, sobreescreve
 * caso já existam.
 */
void setup_work_directory() {
    f_key = fopen("key.txt", "w");
    f_cipher = fopen("cipher.txt", "w");
}

/**
 * Abre um arquivo para usar dentro do programa já enviando
 * @param nome_arq nome do arquivo que se deseja abrr sem a extensão
 * @param mode modo de abertura
 * @return ponteiro do arquivo
 */
FILE *open_file(char nome_arq[], char mode[]) {
    FILE *f;
    if (nome_arq != NULL) {
        if (strlen(nome_arq) > 0) {
            do {
                f = fopen(strcat(nome_arq, ".txt"), mode);
                if (f == NULL) {
                    printf("Não foi possível localizar/abrir o arquivo\nDigite o nome do arquivo: ");
                    scanf("%s", nome_arq);
                }
            } while (f == NULL);
        } else {
            printf("Nome do arquivo inválido.\n");
        }
    } else {
        printf("Nome do arquivo inválido.\n");
    }
}

/**
 * Gera uma chave randomica
 * @return a chave gerada a ser salva no arquivo
 */
char get_key() {
    char key = rand();; //gerará um char para que o número de bits seja igual ao dos caracteres do texto original

    while ((key == last_char) || !on_acceptable_range(key)) {
        key = (unsigned) rand() % 135; //impede criar caractere acima do máximo usado (ç)
    }
    last_char = key;
    return key;
}

/**
 * Escreve no arquivo de cifra a cifra gerada com a chave
 * @param cifra gerada a ser salva no arquivo
 */
void write_cipher(char cifra) {
    if (cifra != NULL) {
        putc(cifra, f_cipher);
    }
}

/**
 * Verifica se o caractere gerado está no intervalo aceitável da Tabela UTF-8
 * @param c caractere a ser verificado
 * @return true caso esteja no intervalo e false caso não esteja no intervalo
 */
bool on_acceptable_range(char c) {
    if (c != NULL) {
        if (c > 64 && c < 91) return true;
        if (c > 96 && c < 123) return true;
        if (c == 128 || c == 135) return true;
    }
    return false;
}