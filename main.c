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
char last_char;

FILE *open_file(char *nome_arq, char mode);

void setup_work_directory();

void close_directory();

char encript(char c, char key);

char get_key();

void write_key(char key);

bool on_acceptable_range(char key);

void write_cipher(char cifra);


int main() {
    //Ajustes iniciais do ambiente
    setlocale(LC_ALL, "");

    // declaração de variáveis
    FILE *f_plaintext;
    FILE *f_cipher;
    FILE *f_key;
    char nome_arquivo[100];
    int opcao_menu_principal;

    printf(" ************ Bem vindo ao One-Time Pad ************\n");
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
                    fclose(f_plaintext);
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

                printf("Arquivo com a cifra: ");
                scanf("%s", nome_arquivo);

                f_cipher = open_file(nome_arquivo, "r");
                f_plaintext = open_file("plainText", "w");

                if (f_cipher != NULL) {
                    if (f_key != NULL) {
                        char buffer_key[TAM_BUFFER_READ_FILE];
                        char buffer_cipher[TAM_BUFFER_READ_FILE];
                        char message;

                        while (!feof(f_cipher) && !feof(f_key)) {
                            fgets(buffer_cipher, TAM_BUFFER_READ_FILE, f_cipher);
                            fgets(buffer_key, TAM_BUFFER_READ_FILE, f_key);

                            for (int i = 0; i < TAM_BUFFER_READ_FILE; i++) {
                                if (buffer_key[i] != EOF && buffer_key[i] != '\0' && buffer_key[i] != '\n') {
                                    //para cada caractere decriptá-lo
                                    //message = decript();
                                    //escrever no arquivo plantext
                                }
                            }
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
    putc(key, f_key);
}

/**
 * Faz a cifra de um caractere usando uma chave
 * @param c caractere a ser encritado
 * @param key chave usada para encriptar
 * @return a cifra
 */
char encript(char c, char key) {
    return c ^ key;
}

void close_directory() {
    fflush(f_cipher);
    fflush(f_key);
    fclose(f_key);
    fclose(f_cipher);
}

void setup_work_directory() {
    f_key = fopen("key.txt", "w");
    f_cipher = fopen("cipher.txt", "w");
}

FILE *open_file(char *nome_arq, char mode) {
    if (nome_arq != NULL) {
        if (strlen(nome_arq) > 0) {
            return fopen(strcat(nome_arq, ".txt"), mode);
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
    putc(cifra, f_cipher);
}

/**
 * Verifica se o caractere gerado está no intervalo aceitável da Tabela UTF-8
 * @param c caractere a ser verificado
 * @return true caso esteja no intervalo e false caso não esteja no intervalo
 */
bool on_acceptable_range(char c) {
    if (c > 64 && c < 91) return true;
    if (c > 96 && c < 123) return true;
    if (c == 128 || c == 135) return true;
    return false;
}