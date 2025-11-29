#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


//struktura pro jeden Tok
typedef struct {
    int flow_id;
    char src_ip[16];
    char dst_ip[16];
    int total_bytes;
    int flow_duration;
    double packet_count;
    double avg_interarrival_time;
    double avg_packet_length; //následně se vypočítá
    int poradi[250];
} Tok;

//struktura pro jeden Shluk
typedef struct {
    int pocetToku;
    int nazevTok[250];
    int poradi[250];
} Shluk;


int nacteniToku(FILE *soubor, Tok tok[]); //načtení všech toků z přidaného soubrou
double eukleidova(Tok *t1, Tok *t2, double WB, double WT, double WD, double WS); //funkce pro vypočítání vzdálenosti mezi dvěmi toky
void vytvareniShluku(int pocetVsechToku, Tok tok[], int pozadovanyPocetShluku, double WB, double WT, double WD, double WS); //vytváří shluky a náaslědně je slučuje, pokdu potřeba
void seraditTokyVeShluku(Tok tok[], Shluk *shluk);
void seraditShluky(Shluk shluk[], int pocet, Tok tok[]);
int jsouVeStejnemShluku(Shluk shluk[], int pocetShluku, int nazevTokPrvni, int nazevTokDruhy);
void spojShluky(Shluk shluk[], int i, int j, int *pocetShluku);
double vzdalenostShluku(Shluk *shlukKPorovnaniPrvni, Shluk *shlukKporovnaniDruhy, Tok tok[], double WB, double WT, double WD, double WS);

int main(int argc, char *argv[])
{
    double WB = 0, WT = 0, WD = 0, WS = 0; //váhy
    int pozadovanyPocetShluku = -1;

    if (argc == 6) { //pokud nebyl zadáno N, tedy požadovaný počet shluků, musíme všem vahám posunout = argument o jedno doleva
        //char *fileOutput = argv[1];

        char* ukazatel;
        WB = strtod(argv[2], &ukazatel);
        if ((*ukazatel != '\0')|| WB<0) return 0; //pokud se nepovede konverze nebo váha je <0, error

        WT = strtod(argv[3], &ukazatel);
        if ((*ukazatel != '\0')||WT<0) return 0;

        WD = strtod(argv[4], &ukazatel);
        if ((*ukazatel != '\0')||WD<0) return 0;

        WS = strtod(argv[5], &ukazatel);
        if ((*ukazatel != '\0')||WS<0) return 0;
    }

    else if (argc == 7) {

        char *ukazatel;

        pozadovanyPocetShluku = strtod(argv[2], &ukazatel);
        if ((*ukazatel != '\0')||pozadovanyPocetShluku<0) {printf("Nespravny argument pro: pozadovanyPocetShluku");return 0;} //ošetření špatného vstupu

        WB = strtod(argv[2], &ukazatel);
        if ((*ukazatel != '\0')|| WB<0) {printf("Nespravny argument pro: WB");return 0;} //pokud se nepovede konverze nebo váha je <0, error

        WT = strtod(argv[3], &ukazatel);
        if ((*ukazatel != '\0')||WT<0) {printf("Nespravny argument pro: WT");return 0;}

        WD = strtod(argv[4], &ukazatel);
        if ((*ukazatel != '\0')||WD<0) {printf("Nespravny argument pro: WD");return 0;}

        WS = strtod(argv[5], &ukazatel);
        if ((*ukazatel != '\0')||WS<0) {printf("Nespravny argument pro: WS");return 0;}
    }
    else { //Uzivatel musí zadat alespoň všechny hodnoty vah nebo jich zadal až moc
        printf("Chyba na vstupnich argumentech");
        return 0;
    }

    FILE *soubor = fopen(argv[1], "r");  //otevření souboru
    if (!soubor) {
        printf("Soubor se nepodarilo otevrit.\n");
        return 0;
    }

    Tok tok[250];//vytvoření struktury pole TOK

    int pocet = nacteniToku(soubor, tok);

    vytvareniShluku(pocet, tok, pozadovanyPocetShluku,  WB,  WT,  WD,  WS);

    //zavření souboru
    fclose(soubor);
    return 1;
}




int nacteniToku(FILE *soubor, Tok tok[])

{
    char prvniRadek[256];
    fgets(prvniRadek, sizeof(prvniRadek), soubor);

    int pocetToku = 0;
    if(sscanf(prvniRadek, "count=%d", &pocetToku) != 1) {printf("Nespravny input poctu toku");return 0;}//ošetření správného vstupu//Nutné dva řádky?
    sscanf(prvniRadek, "count=%d", &pocetToku); //načíst pomocí sscanf počet toků v souboru
    if (pocetToku <0) {printf("Nespravny input poctu toku");return 0;} //ošetření počtu toků

    char radek[256];
    int flow, total, duration;
    double packet, avg;
    char src[16], dst[16];

    for (int i = 0; i < pocetToku; i++) //počet opakování na základě počtu načtených toků ze vstuúního souboru
    {
        if (fgets(radek, sizeof(radek), soubor) == NULL) {printf("Chyba pri cteni ze souboru");break;}
        if(sscanf(radek, "%d %s %s %d %d %lf %lf", &flow, src, dst, &total, &duration, &packet, &avg) != 7) return 0;
        sscanf(radek, "%d %s %s %d %d %lf %lf",
               &flow, src, dst, &total, &duration, &packet, &avg); //řádek po řádku načítání atributů daného toku

        tok[i].flow_id = flow;
        strcpy(tok[i].src_ip, src);
        strcpy(tok[i].dst_ip, dst);
        tok[i].total_bytes = total;
        tok[i].flow_duration = duration;
        tok[i].packet_count = packet;
        tok[i].avg_interarrival_time = avg;
        tok[i].avg_packet_length = total / packet;
    }

    return pocetToku;
}


double eukleidova(Tok *t1, Tok *t2, double WB, double WT, double WD, double WS)//t1 a t2 musí pouze odkazovat na nějakou paměť, aby jsme mohli
                                                                                //měnit měřené toky
{
    return sqrt(
        WB * pow(t1->total_bytes - t2->total_bytes, 2) + // t1 pouze odkazuje na "jeho" atribut, proto -> a ne t1.total_bytes
        WT * pow(t1->flow_duration - t2->flow_duration, 2) +
        WD * pow(t1->avg_interarrival_time - t2->avg_interarrival_time, 2) +
        WS * pow(t1->avg_packet_length - t2->avg_packet_length, 2)
    );
}

void vytvareniShluku(int pocetVsechToku, Tok tok[], int pozadovanyPocetShluku,
                     double WB, double WT, double WD, double WS)
{
    Shluk shluk[250];
    int pocetShlukuAktualne = pocetVsechToku;

    // inicializace: každý tok je samostatný shluk
    for (int i = 0; i < pocetVsechToku; i++) {
        shluk[i].pocetToku = 1;
        shluk[i].nazevTok[0] = i; // index do pole tok[]
    }

    // hlavní slučovací smyčka
    while (pocetShlukuAktualne > pozadovanyPocetShluku) {
        double minDist = INFINITY;
        int bestI = -1, bestJ = -1;

        // najdi nejbližší dvojici shluků
        for (int i = 0; i < pocetShlukuAktualne; i++) {
            for (int j = i+1; j < pocetShlukuAktualne; j++) {
                double dist = vzdalenostShluku(&shluk[i], &shluk[j], tok, WB, WT, WD, WS);
                if (dist < minDist) {
                    minDist = dist;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        // spoj nejbližší dvojici
        if (bestI != -1 && bestJ != -1) {
            spojShluky(shluk, bestI, bestJ, &pocetShlukuAktualne);
        }
        // seřaď toky uvnitř nového shluku
        seraditTokyVeShluku(tok, &shluk[bestI]);

        // seřaď celé pole shluků podle nejmenšího flow_id
        seraditShluky(shluk, pocetShlukuAktualne, tok);

    }

    // výpis výsledku
    printf("\nClusters:");
    for (int i = 0; i < pocetShlukuAktualne; i++) {
        printf("\ncluster %d: ", i);
        for (int j = 0; j < shluk[i].pocetToku; j++) {
            printf("%d ", tok[shluk[i].nazevTok[j]].flow_id);
        }
    }
}


void seraditTokyVeShluku(Tok tok[], Shluk *shluk) {

    for (int i = 0; i < shluk->pocetToku - 1; i++) {

        // když je tok i větší než tok i+1
            if (tok[shluk->nazevTok[i]].flow_id > tok[shluk->nazevTok[i+1]].flow_id) {

            int nejmensi = shluk->nazevTok[i+1];
            int j = i;

            // posouvání vlevo, dokud je větší
            while (j >= 0 && tok[nejmensi].flow_id < tok[shluk->nazevTok[j]].flow_id) {
                shluk->nazevTok[j+1] = shluk->nazevTok[j];
                j--;
            }
            shluk->nazevTok[j+1] = nejmensi;
        }
    }
}
void seraditShluky(Shluk shluk[], int pocet, Tok tok[])
{
    for (int i = 0; i < pocet - 1; i++) {

        if (tok[shluk[i].nazevTok[0]].flow_id > tok[shluk[i+1].nazevTok[0]].flow_id)
        {
           printf("\n\n tok[shluk[i].nazevTok[0]].flow_id = %d a tok[shluk[i+1].nazevTok[0]].flow_id = %d",tok[shluk[i].nazevTok[0]].flow_id ,tok[shluk[i+1].nazevTok[0]].flow_id);
        }
    }
}

int jsouVeStejnemShluku(Shluk shluk[], int pocetShluku, int nazevTokPrvni, int nazevTokDruhy) {
    for (int i = 0; i < pocetShluku; i++) {
        int nalezen1 = 0, nalezen2 = 0;

        for (int j = 0; j < shluk[i].pocetToku; j++) {
            if (shluk[i].nazevTok[j] == nazevTokPrvni) nalezen1 = 1;
            if (shluk[i].nazevTok[j] == nazevTokDruhy) nalezen2 = 1;
        }
        if (nalezen1 && nalezen2) return 1; // oba ve stejném shluku
    }
    return 0;
}

// Spojí shluk j do shluku i
void spojShluky(Shluk shluk[], int i, int j, int *pocetShluku) {
    // Přidání všech toků ze shluku j do shluku i
    for (int k = 0; k < shluk[j].pocetToku; k++) {
        shluk[i].nazevTok[shluk[i].pocetToku++] = shluk[j].nazevTok[k];
    }
    // Odstranění shluku j -> posunutí pole o jedno doleva
    for (int k = j; k < (*pocetShluku) - 1; k++) {
        shluk[k] = shluk[k+1];
    }

    (*pocetShluku)--; // snížení počtu shluků
}
double vzdalenostShluku(Shluk *shlukKPorovnaniPrvni, Shluk *shlukKporovnaniDruhy, Tok tok[], double WB, double WT, double WD, double WS) {
    double sum = 0;
    int pocet = 0;
    for (int i = 0; i < shlukKPorovnaniPrvni->pocetToku; i++) {
        for (int j = 0; j < shlukKporovnaniDruhy->pocetToku; j++) {
            sum += eukleidova(&tok[shlukKPorovnaniPrvni->nazevTok[i]], &tok[shlukKporovnaniDruhy->nazevTok[j]], WB, WT, WD, WS);
            pocet++;
        }
    }
    return sum / pocet;
}