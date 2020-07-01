//
// Created by Daniel Vargas on 30/06/2020.
//

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define TAM_BUFFER_READ_FILE 10

FILE *f_cipher;
FILE *f_key;
char last_char;

FILE *open_plaintext(char nome_arq[]);

void setup_work_directory();

void close_directory();

char encript(char c, char key);

char get_key();

void write_key(int *key);

void write_cipher(char *cifra);


int main() {
    FILE *plaintext;
    char nome_plaintext[100];
    printf("Nome do arquivo a ser encriptado: ");
    scanf("%s", nome_plaintext);

    plaintext = open_plaintext(nome_plaintext);

    if (plaintext != NULL) {
        char buffer[TAM_BUFFER_READ_FILE];
        int cifra;
        char key;

        setup_work_directory();

        //Fluxo principal
        while (!feof(plaintext)) {
            fgets(buffer, TAM_BUFFER_READ_FILE, plaintext);

            for (int i = 0; i < TAM_BUFFER_READ_FILE; ++i) {
                if (buffer[i] != EOF) {
                    if (buffer[i] != ' ') { //para cada caracter lido, diferente de espaço
                        key = get_key(); //gerar uma nova chave
                        cifra = encript(buffer[i], key); //encriptar o caractere com a chave gerada e salvar a cifra
                        write_key(&key); //salvar a chave usada
                        write_cipher(&cifra); //salvar a cifra
                    }
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
void write_key(int *key) {
    printf("Recebido o caractere: %c", key);
    putc(key, f_key);
    //TODO: implementar a escrita da chave no arquivo f_key
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
    char key; //gerará um char para que o número de bits seja igual ao dos caracteres do texto original

    srand(time(NULL));

    while (key == last_char) {
        key = (char) rand();
    }
    return key;
}

/**
 * Escreve no arquivo de cifra a cifra gerada com a chave
 * @param cifra gerada a ser salva no arquivo
 */
void write_cipher(char *cifra) {
    //TODO: escrever a cifra no arquivo de cifra
}