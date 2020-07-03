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

FILE *open_plaintext(char nome_arq[]);

void setup_work_directory();

void close_directory();

char encript(char c, char key);

char get_key();

void write_key(char key);

bool on_acceptable_range(char key);

void write_cipher(char cifra);


int main() {
    setlocale(LC_ALL, "");
    FILE *plaintext;
    char nome_plaintext[100];
    printf("Nome do arquivo a ser encriptado: ");
    scanf("%s", nome_plaintext);

    plaintext = open_plaintext(nome_plaintext);
    srand((unsigned) time(NULL));

    if (plaintext != NULL) {
        char buffer[TAM_BUFFER_READ_FILE];
        int cifra;
        char key;

        setup_work_directory();

        //Fluxo principal
        while (!feof(plaintext)) {
            fgets(buffer, TAM_BUFFER_READ_FILE, plaintext);
            for (int i = 0; i < TAM_BUFFER_READ_FILE || !feof(plaintext); ++i) {
                if (buffer[i] != EOF && buffer[i] != '\0' && buffer[i] != '\n') {
                    if (buffer[i] != ' ') { //para cada caracter lido, diferente de espaço
                        key = get_key(); //gerar uma nova chave
                        cifra = encript(buffer[i], key); //encriptar o caractere com a chave gerada e salvar a cifra
                        write_key(key); //salvar a chave usada
                        write_cipher(cifra); //salvar a cifra
                    }
                } else {
                    break;
                }
            }
        }

    }
    fclose(plaintext);
    close_directory();
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
    putc(EOF, f_key);
    putc(EOF, f_cipher);
    fflush(f_cipher);
    fflush(f_key);
    fclose(f_key);
    fclose(f_cipher);
}

void setup_work_directory() {
    f_key = fopen("key.txt", "w");
    f_cipher = fopen("cipher.txt", "w");
}

FILE *open_plaintext(char nome_arq[]) {
    if (nome_arq != NULL) {
        if (strlen(nome_arq) > 0) {
            return fopen(strcat(nome_arq, ".txt"), "r");
        } else {
            printf("nomeArquivoinvalido");
        }
    } else {
        printf("nomeArquivo nulo");
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