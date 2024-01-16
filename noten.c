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
	char modulname;
	char kurzform;
	char faktor;
	char note;
} tModul;

int printModuleCSV();

int main(void) {

 

	//open CSV
	printf("\n");
	tModul moduleGesamt[100]; //array in dem alle module aus CSV eingelesen gespeichert werden sollen

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
	   
	fgets(buffer, sizeof(buffer), moduleCSV); 
	printf("%s\n", buffer); 

	while (fgets(buffer, sizeof(buffer), moduleCSV)) {
		data = strtok(buffer, ";");
		printf("%s,", data);

		data = strtok(NULL, ";");
		printf("%s, ", data);

		data = strtok(NULL, ";");
		printf("%s,", data);

		data = strtok(NULL, ";");
		printf("%s,", data);

		printf("\n"); 
		anzahlModule++; 
	}

	tModul *w = (tModul*)malloc(36 * sizeof(tModul)); 

	fgets(buffer, sizeof(buffer), moduleCSV);

	for (int i = 1; i <= anzahlModule; i++) {
		data = strtok(buffer, ";");
		w[i].modulname = data;

		data = strtok(NULL, ";");
		w[i].kurzform = data;

		data = strtok(NULL, ";");
		w[i].faktor = data;

		data = strtok(NULL, ";");
		w[i].note = data;

		printf("\n");
	}

	fclose(moduleCSV);

	printf("%s", w[22].modulname); 

	/*
	// Ab hier Speicher allokieren 

	tModul* Array; // Zeiger für dynamischen Speicher 
	int size;

	size = anzahlModule * (sizeof(tModul));

	Array = (tModul*)calloc(anzahlModule, size);


	FILE* moduleCSV = fopen("module.csv", "r");
	if (moduleCSV == NULL) {// Fehler?
		printf("Fehler: Datei nicht gefunden");
		return 1;
	}
	printf("Erfolg: Datei gefunden");
	printf("\n");



	for (int i = 1; i <= anzahlModule; i++) {
		data = strtok(buffer, ";");
		Array[i].modulname = data; 

		data = strtok(NULL, ";");
		Array[i].kurzform = data;

		data = strtok(NULL, ";");
		Array[i].faktor = data;

		data = strtok(NULL, ";");
		Array[i].note = data;

		printf("\n");
	}

	fclose(moduleCSV); 
	
	*/



	

	/**DATEI**/
	//moduleGesamt = (tModul*)malloc(numberOfModules * sizeof(tModul)); // Speicher allokieren für module, die gleich kommen. Anzahl der Module ist jetzt bekannt
	/*
	if (moduleGesamt == NULL) { // Fehler?
		printf("Fehler: Speicher konnte nicht allokiert werden");
		return 1;
	}
	/*
	for (int i = 0; i < numberOfModules; i++) {
		moduleGesamt[i].modulname = (char*)malloc(100);
		moduleGesamt[i].kurzform = (char*)malloc(100);
		moduleGesamt[i].faktor = 0;
		moduleGesamt[i].note = 0;

		moduleGesamt[i].modulname = (char*)malloc(100);
		moduleGesamt[i].kurzform = (char*)malloc(100);
		moduleGesamt[i].faktor = 0;
		moduleGesamt[i].note = 0;

		
	}*/

	

	// Free memory for the array of tModul elements
	free(moduleGesamt);
	





	return 0; 
}


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







