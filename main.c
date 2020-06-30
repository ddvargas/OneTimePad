//
// Created by Daniel Vargas on 30/06/2020.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define TAM_BUFFER_READ_FILE 10

FILE *cipher;
FILE *key;

FILE *open_plaintext(char nome_arq[]);

void setup_work_directory();

void close_directory();


int main() {
    FILE *plaintext;
    char nome_plaintext[100];
    printf("Nome do arquivo a ser encriptado: ");
    scanf("%s", nome_plaintext);

    plaintext = open_plaintext(nome_plaintext);

    if (plaintext != NULL) {
        char buffer[TAM_BUFFER_READ_FILE];

        setup_work_directory();

        //Fluxo principal
        while (!feof(plaintext)) {
            fgets(buffer, TAM_BUFFER_READ_FILE, plaintext);

            //TODO: para cada caractere transformar em binario
            //TODO: criar um randon binario para codificar o caractere
            //TODO: Adicionar a key no arquivo (Append)
            //TODO: Adicionar a cifra no arquivo (Append)
            //read_length = fread(plaintext, TAM_BUFFER_READ_FILE, buffer);
        }

    }
    fclose(plaintext);
    close_directory();
}

void close_directory() {
    fclose(key);
    fclose(cipher);
}

void setup_work_directory() {
    key = fopen("key.txt", "w");
    cipher = fopen("cipher.txt", "w");
    //TODO: criar arquivo de cifra
    //TODO: criar arquivo de chave
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