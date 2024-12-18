#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "src/todo.h"

int main() {

    cleanConsole();

    int choice;
    do {

		menu();
        scanf("%d", &choice);
		getchar();
        cleanConsole();

        switch (choice) {
        case 1: // Creazione Lista

			char title[MAX_TITLE_LEN];
    		printf(YEL "Inserisci il titolo per la lista da creare (max %d caratteri): " RESET, MAX_TITLE_LEN);
    		fgets(title, MAX_TITLE_LEN, stdin);
    		title[strcspn(title, "\n")] = '\0';

            if (strlen(title) == 0) {
		    	cleanConsole();
                printf(RED "[!] Il titolo della lista non può essere vuoto.\n\n" RESET);
                break;
            }

            creaLista(title);
            break;

        case 2: // Elenco di tutte le liste presenti
			elencaListe();
            break;

        case 3: // Visualizzazione di una lista
			char v_title[MAX_TITLE_LEN];

    		printf(YEL "Inserisci il titolo per la lista da visualizzare (max %d caratteri): " RESET, MAX_TITLE_LEN);
    		fgets(v_title, MAX_TITLE_LEN, stdin);
    		v_title[strcspn(v_title, "\n")] = '\0';
			cleanConsole();

            if (strlen(v_title) == 0) {
                printf(RED "[!] Il titolo della lista non può essere vuoto.\n\n" RESET);
                break;
            }

			printLista(v_title);
            break;

		case 4: // Elimina una lista
			char e_title[MAX_TITLE_LEN];

    		printf(YEL "Inserisci il titolo per la lista da visualizzare (max %d caratteri): " RESET, MAX_TITLE_LEN);
    		fgets(e_title, MAX_TITLE_LEN, stdin);
    		e_title[strcspn(e_title, "\n")] = '\0';
			cleanConsole();

            if (strlen(e_title) == 0) {
                printf(RED "[!] Il titolo della lista non può essere vuoto.\n\n" RESET);
                break;
            }

			eliminaLista(e_title);
			break;

        case 0: // Exit
            break;
        default:
            printf(RED "[!] Input non valido.\n\n" RESET);
            break;
        }
    } while (choice != 0);
    return 0;
}