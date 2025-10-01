#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *prefix = "";
    if (argc >= 2) { //pokud systém zjistí více argumentů pro funkci main, uživatel zadal prefix
        prefix = argv[1]; // uložení prefixu do proměnné prefix
    }

    char str[1000][101]; //array string
    int i = 0;
    int pocetNalezenych = 0;

    // načítání slov ze stdin - postupné ukládání do proměnné str[i]
    for (i = 0; i < 1000; i++) {
        if (fgets(str[i], 100, stdin) == NULL) break;
        str[i][strcspn(str[i], "\n")] = '\0'; //vymazání prázdných řádek
        if (strlen(str[i]) == 0) break;//pokud nenajde žádné hodnoty ve file
    }

    // porovnávání
    if (argc < 2) { //pokud neexistuje prefix, vytsiknou se všechny slova z file
        for (int k = 0; k < i; k++) {
            printf("%s\n", str[k]);
        }
    }
    else {
        int j=0;
        for ( j = 0; j < i; j++) { //po jednom porovnává slova s prefixem
            if (strncasecmp(str[j], prefix, strlen(prefix)) == 0) { //strncasecmp ignoruje velká/malá písmena
                pocetNalezenych++;
                //printf("\n%d",pocetNalezenych);
                printf("\nNalezeno: %s", str[j]);
            }
        }
        // pokud řešení je více než jedno
        if (pocetNalezenych > 1) {
            printf("\nVyzaduje specifikaci");
        }
        // pokud se nenašlo vůbec nic
        if (pocetNalezenych == 0) {
            printf("Nic nenalezeno\n");
        }
    }

    return 0;
}
