#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define LISTS_PATH "./.lists/" 
#define MAX_TITLE_LEN 25
#define MAX_TASK_LEN 256

int fileExists(const char *path);
int dirExists(const char *path);
int createDir(const char *path);
void buildFilename(char *dest, const char *title);

// Verifica se un file esiste o no
int fileExists(const char *path) {
    FILE *fp = fopen(path, "r");
    if (fp) {
        fclose(fp);
        return 1;
    }
    return 0;
}

// Verifica se una directory esiste o no
int dirExists(const char *path) {
    struct stat info;

    // Usare stat() per ottenere informazioni sul path
    if (stat(path, &info) != 0) {
        // Se stat fallisce, il path non esiste
        return 0;
    }

    // Controllare se è una directory
    return (info.st_mode & S_IFDIR) != 0;
}

// Crea una directory
int createDir(const char *path) {
    return mkdir(path, 0775);
}

// Prende in input  il titolo della nota e ne costruisce il filename
void buildFilename(char *dest, const char *title) {
    snprintf(dest, MAX_TITLE_LEN + 15, "%s%s.txt", LISTS_PATH, title);
}