/***

Name:			Noten-Durchschnitt ermitteln
Beschreibung:	Programm, in welchem mittlere kWh aus Solarstrahlung für verschiedene Standorte berechnet wird. Je nach Makro-Definition werden entweder Berechnungen
				zu Mittelwerten ausgegeben, oder es findet eine Benutzerabfrage statt, wo der User Werte über seine PV-Anlage angeben und sich die berechneten
				PV-Erträge in eine .txt-Datei abgespeichert werden.
Autorinnen:	    Emily Klemt, Carolin Altstaedt
Datum:		    22.12.2023
Version:			1

***/

#define _CRT_SECURE_NO_WARNINGS
//#define ausgabe_berechnung

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
	char modulname[100][100];
	char kurzform[100][100];
	int faktor;
	int note;
} tModul;


int main(void) {
	//open CSV
	printf("\n");

	char buffer[1000]; 
	char* data; 
	int anzahlModule = 0; 

	/**DATEI**/
	FILE* moduleCSV = fopen("module.csv", "r");
	if (moduleCSV == NULL) {// Fehler?
		printf("Fehler: Datei nicht gefunden");
		return 1;
	}
	printf("Erfolg: Datei gefunden");
	printf("\n");

	tModul* a = (tModul*)calloc(36, sizeof(tModul));
	if (a == NULL) {// Fehler?
		printf("Fehler: Zeiger zeigt auf nichts");
		return 1;
	}
	a->faktor = 15;
	   
	fgets(buffer, sizeof(buffer), moduleCSV); 
	printf("%s\n", buffer); 

	int i = 0;
	while (fgets(buffer, sizeof(buffer), moduleCSV)) {
		data = strtok(buffer, ";");
		printf("%s,", data);
		strcpy(a[i].modulname, data);

		data = strtok(NULL, ";");
		printf("%s,", data);
		strcpy(a[i].kurzform, data);

		data = strtok(NULL, ";");
		printf("%s,", data);
		a[i].faktor = atoi(data);

		data = strtok(NULL, ";");
		printf("%s,", data);
		a[i].note = atoi(data);

		printf("\n");
		++i; 
	}

	fclose(moduleCSV);
	

		free(anzahlModule);


		return 0;
}




/*
short einlesenEinerZahl( // Funktion, um eine Benutzereingabe einzulesen
	char text[],
	short min,
	short max)
{
	short eingelesenerWert;		// eingegebene Zahl des Benutzers
	bool fertig = false;			// Variable, die anzeigt, ob die Eingabe den Anforderungen einer Lottozahl entspricht
	char ch;						// möglicher Buchstabe nach der eingegebenen Zahl
	int Rückgabewert;			// Rückgabewert von scanf

	do {
		//Einlesen der Zahl 
		printf("%s: ", text);
		ch = '\0';
		Rückgabewert = scanf("%hd%c", &eingelesenerWert, &ch);

		// Überprüfen, ob die Zahl den Anforderungen entspricht
		if (Rückgabewert != 2) printf("Das war keine korrekte Zahl!\n");
		else if (ch != '\n') printf("Unerwartete Zeichen hinter der Zahl!\n");
		else if (eingelesenerWert < min || eingelesenerWert > max) printf("Zahl muss zwischen 1 und %d liegen.\n", max);
		else fertig = true;
		// Input stream leeren 
		while (ch != '\n') {
			char checkChar = scanf("%c", &ch);
		}
		// wiederholen, wenn es nicht beendet ist 
	} while (!fertig);

	// Rückgabe der eingelesenen Zahl 
	return eingelesenerWert;
}
*/







