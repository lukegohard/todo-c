#include <stdio.h>

// Macros per colori della console
#define RESET "\x1B[0m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"

void menu();
void cleanConsole();

// Print menu
void menu() {
    printf(GRN "[1] " RESET "Crea Lista.\n\n");
    printf(GRN "[2] " RESET "Elenca Liste.\n\n");
    printf(GRN "[3] " RESET "Visualizza Lista.\n\n");
    printf(GRN "[4] " RESET "Elimina Lista.\n\n");
    printf(RED "[0] " RESET "Esci.\n\n");
    printf(YEL "> " RESET);
}

// Pulisce la console
void cleanConsole() {
    printf("\033[H\033[J");
}