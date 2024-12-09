/*
- Definire un tipo enumerativo per la codifica dei simboli (sasso, forbici, carta);
- Definire un tipo enumerativo per codificare l’esito di un round/ una partita (pareggio, vittoria utente,
vittoria cpu);
- Per il conteggio delle occorrenze dei simboli giocati, allocare un vettore in area heap
Funzioni richieste:
… simboloValido (...)
Parametri di input: carattere
Parametri di output: valore booleano
Restituisce true se il carattere è ‘S’, ‘C’, o ‘F’, false altrimenti.
… inputSimboloUtente (...)
prende un carattere da tastiera, verifica che sia S, F, C (altrimenti richiede un nuovo input) restituisce il
simbolo (tipo enum) corrispondente.
… simboloCPU (...)
Restituisce uno dei simboli possibili (enum) in maniera casuale
… calcolaVittoriaRound (...)
Prende in ingresso due simboli (uno per utente e uno per CPU) e restituisce l’esito del round (chi ha vinto)
… stampaRiepilogoOccorrenze (...)
Input: vettore di 3 elementi (conteggio occorrenze dei 3 simboli…)
Stampa frazione occorrenze per ciascun simbolo con percentuale
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Definizione dei tipi enumerativi
typedef enum {
    SASSO,
    FORBICI,
    CARTA
} Simbolo;

typedef enum {
    PAREGGIO,
    VITTORIA_UTENTE,
    VITTORIA_CPU
} Esito;

// Funzione per verificare se un simbolo è valido
bool simboloValido(char carattere) {
    return carattere == 'S' || carattere == 'F' || carattere == 'C';
}

// Funzione per convertire un carattere nel simbolo corrispondente
Simbolo charToSimbolo(char carattere) {
    switch (carattere) {
        case 'S': return SASSO;
        case 'F': return FORBICI;
        case 'C': return CARTA;
        default: return -1; // Non valido
    }
}

// Funzione per acquisire il simbolo dell'utente
Simbolo inputSimboloUtente() {
    char input;
    do {
        printf("Inserisci un simbolo (S: Sasso, F: Forbici, C: Carta): ");
        scanf(" %c", &input);
    } while (!simboloValido(input));
    return charToSimbolo(input);
}

// Funzione per generare un simbolo casuale per la CPU
Simbolo simboloCPU() {
    return rand() % 3; // Genera un numero tra 0 e 2
}

// Funzione per calcolare l'esito del round
Esito calcolaVittoriaRound(Simbolo utente, Simbolo cpu) {
    if (utente == cpu) return PAREGGIO;
    if ((utente == SASSO && cpu == FORBICI) ||
        (utente == FORBICI && cpu == CARTA) ||
        (utente == CARTA && cpu == SASSO)) {
        return VITTORIA_UTENTE;
    }
    return VITTORIA_CPU;
}

// Funzione per stampare il riepilogo delle occorrenze
void stampaRiepilogoOccorrenze(int *occorrenze, int totale) {
    const char *simboli[] = {"Sasso", "Forbici", "Carta"};
    for (int i = 0; i < 3; i++) {
        double percentuale = (double)occorrenze[i] / totale * 100;
        printf("%s: %d (%.2f%%)\n", simboli[i], occorrenze[i], percentuale);
    }
}

int main() {
    srand(time(NULL)); // Inizializza il generatore di numeri casuali

    // Vettore per il conteggio delle occorrenze dei simboli
    int *occorrenze = (int *)calloc(3, sizeof(int));
    if (!occorrenze) {
        printf("Errore di allocazione della memoria.\n");
        return 1;
    }

    int totaleGiochi = 0;
    char scelta;

    do {
        Simbolo utente = inputSimboloUtente();
        Simbolo cpu = simboloCPU();
        occorrenze[utente]++;
        totaleGiochi++;

        Esito esito = calcolaVittoriaRound(utente, cpu);
        const char *esitoStr = esito == PAREGGIO ? "Pareggio" :
                               esito == VITTORIA_UTENTE ? "Hai vinto!" : "La CPU ha vinto!";
        printf("Hai giocato: %s, CPU ha giocato: %s. %s\n",
               (utente == SASSO ? "Sasso" : utente == FORBICI ? "Forbici" : "Carta"),
               (cpu == SASSO ? "Sasso" : cpu == FORBICI ? "Forbici" : "Carta"),
               esitoStr);

        printf("Vuoi giocare un altro round? (s/n): ");
        scanf(" %c", &scelta);

    } while (scelta == 's' || scelta == 'S');

    printf("\nRiepilogo:\n");
    stampaRiepilogoOccorrenze(occorrenze, totaleGiochi);

    free(occorrenze); // Dealloca il vettore
    return 0;
}