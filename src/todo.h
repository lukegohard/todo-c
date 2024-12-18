#include "helpers.h"
#include "console.h"

void creaLista(char *title);
void elencaListe();
void printLista(char *title);
void eliminaLista(char *title);


// Prende in input il titolo della nota.
// Dal titolo costruisce il filename, e crea il file (se non esiste).
// Con un ciclo vengono aggiunti le voci alla nota, fino a quando l'utente insersci "END".
void creaLista(char *title){

	// crea cartella se non esiste
	if (!dirExists(LISTS_PATH)) {
		if (createDir(LISTS_PATH)) {
			printf(RED "[!] Errore nella creazione della cartella.\n" RESET);
			return;
		}
	}

	// Partendo dal titolo crea il filename per la lista
    char filename[MAX_TITLE_LEN+15];
	buildFilename(filename, title);

	if (fileExists(filename)) {
		printf(RED "[!] Esiste già una lista con questo titolo.\n\n" RESET);
		return;
	}

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf(RED "[!] Errore nell'apertura del file.\n" RESET);
        fclose(fp);
        return;
    }

	printf(MAG "Inserisci tutte le task che vuoi (END per terminare).\n\n" RESET);
	while(1) {

		char task[MAX_TASK_LEN];

		printf(YEL "> " RESET);
		fgets(task, MAX_TASK_LEN, stdin);
		task[strcspn(task, "\n")] = '\0';

		if (strcmp(task, "END") == 0) {
			fclose(fp);
			break;
		}

		fprintf(fp, "- %s\n", task);
		fflush(fp);
	}

	cleanConsole();
	printf(GRN "[+] Lista creata con successo!\n\n" RESET);
}

// Prima verifica che la directory delle liste esista.
// Poi tramite un ciclo while ricava ogni singola lista e la mostra a schermo
void elencaListe() {

	struct dirent *entry;
	DIR *dir = opendir(LISTS_PATH);
	if (dir == NULL) {
		printf(RED "[-] Nessuna lista presente.\n\n" RESET);
		return;
	}

	int tot = 0;
	printf(BLU "Elenco Liste:\n");
	while ((entry = readdir(dir)) != NULL) {

		const char *filename = entry->d_name;
		const char *estensione = strrchr(filename, '.');

		if (estensione != NULL && strcmp(estensione, ".txt") == 0) {
			size_t len = strlen(filename) - strlen(estensione);
			printf(CYN "\t- %.*s\n" RESET, (int)len, filename);
			tot++;
		}

	}

	if (tot == 0){
		cleanConsole();
		printf(RED "[-] Nessuna lista presente.\n\n" RESET);
	}

	closedir(dir);
}

// Prende in input il titolo di una nota.
// Se esiste printa il titolo e il suo contenuto.
void printLista(char *title) {
    
	char filename[MAX_TITLE_LEN+15] = LISTS_PATH;
	strcat(filename, title);
	strcat(filename, ".txt");
	
	if (!fileExists(filename)) {
		printf(RED "[-] La lista inserita non esiste.\n\n" RESET);
		return;
	}

	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf(RED "[!] Errore nell'apertura del file.\n" RESET);
		return;	
	}

	char task[256];
	printf(BLU "%s:\n" RESET, title);
	while(fgets(task, MAX_TASK_LEN, fp)) {
		printf(CYN "\t%s" RESET, task);
	}

	fclose(fp);
	printf("\n");
}

// Prende in input il titolo di una nota.
// Se esiste, chiede conferma ed elimina.
void eliminaLista(char *title) {

	char filename[MAX_TITLE_LEN+15];
	buildFilename(filename, title);
	
	if (!fileExists(filename)) {
		printf(RED "[-] La lista inserita non esiste.\n\n" RESET);
		return;
	}

	int confirm;
	printf(YEL "Sicuro di voler eliminare la lista?\n" RESET);
	printf(YEL "1 per confermare, 0 per annullare: " RESET);
	scanf("%d", &confirm);
	getchar();
	
	cleanConsole();

	if (confirm == 1) {
		if (remove(filename) == 0) {
			printf(GRN "[+] Lista eliminata con successo!\n\n" RESET);
		} else printf(RED "[!] Errore durante l'eliminazione della lista.\n\n" RESET);
	} else {
		printf(MAG "[=] Operazione Annullata.\n\n" RESET);
	}
}