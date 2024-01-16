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
	float faktor;
	float note;
} tModul;

int printModuleCSV();

int main(void) {

	//int* moduleGesamt = NULL;
	//moduleGesamt = (int*)malloc(moduleAnzahl * sizeof(int));


	//während einlesen von csv mitzählen wieviele module eingelesen wurden und moduleAnzahl darauf setzen

	//modul in module gesamt pushen

	//abfrage welcher teil des programms ausgeführt werden soll (speichern, einlsesn, abrufen, korrigieren...)
	//Funktionen freischalten? Abrufen < Einlesen?


	//Funktion: CSV auslesen und in array speichern malloc

	//Funktion: Nutzereingabe in eigene CSV zurückschreiben

	//Funktion:Abschluss note aus gegebenen Werten berechnen

	//Funktion: Noten für alle verfügbaren Fächer abfragen, auf Gültigkeit (0-15 prüfen)
	//Summe aller Punkte
	//Leistungspunkte, drei Nachkommastellen

	//Funktion: mega printf csv 1 zu 1 auf konsole ausgeben

	//open CSV
	printf("\n");
	tModul moduleGesamt[100]; //array in dem alle module aus CSV eingelesen gespeichert werden sollen

	

	

	/**DATEI**/
	FILE* moduleCSV = fopen("module.csv", "r");

	if (moduleCSV == NULL) {// Fehler?
		printf("Fehler: Datei nicht gefunden");
		return 1;
	}
	printf("Erfolg: Datei gefunden");
	printf("\n");

	//Größe der CSV-Datei, bzw Anzahl der darin gespeicherten Module herausfinden
	int lesen = 0;
	int index = 0;
	while (!feof(moduleCSV)) {
		lesen = fscanf(moduleCSV, "%c", &moduleGesamt[index].modulname);

		if (lesen == 1) index++;
		if (lesen != 1 && !feof(moduleCSV)) { 
			printf("Fehler: Formatierung in CSV fehlerhaft"); 
			return 1;
		}
	};

	fclose(moduleCSV);

	printf("Anzahl einträge: %d\n", index);

	for (int i = 0; i < index; i++) {
		printf("%c\n", moduleGesamt[index].modulname);

	}




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


int printModuleCSV() {
	//open CSV
	printf("\n");
	char buffer[1000];
	int numberOfModules = 0;

	FILE* moduleCSV = fopen("module.csv", "r");
	if (moduleCSV == NULL) {
		printf("Fehler: Datei nicht gefunden");
		return 1;
	}
	printf("Erfolg: Datei gefunden");
	printf("\n");
	//einlesen
	while (fgets(buffer, sizeof(buffer), moduleCSV)) {
		printf("%s\n", buffer);
		numberOfModules++;
	};




	return 0;
}





