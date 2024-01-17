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

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


typedef struct REEModule{
	char* modulname;
	char* kurzform;
	int faktor;
	int note;
} tModul;

short einlesenEinerZahl( // Funktion, um eine Benutzereingabe einzulesen
	char text[],
	short min,
	short max); 


int main(void) {
	//open CSV

	char buffer[1000]; 
	char* data; 
	int anzahlModule = 35; 

	/**DATEI**/
	FILE* moduleCSV = fopen("module.csv", "r");
	if (moduleCSV == NULL) {// Fehler?
		printf("Fehler: Datei nicht gefunden");
		return 1;
	}
	printf("Erfolg: Datei gefunden");
	printf("\n");

	tModul* moduleGesamt = (tModul*)malloc(anzahlModule * sizeof(tModul));
  
	fgets(buffer, sizeof(buffer), moduleCSV); 
	printf("%s\n", buffer); 

	// Ausgabe der csv-Datei und abspeichwern in reservieertem SPeicher
	int i = 0;
	while (fgets(buffer, sizeof(buffer), moduleCSV)) {

		// Speicher für chat-Werte von struct allokieren
		moduleGesamt[i].modulname = (char*)malloc(100 * sizeof(char));
		moduleGesamt[i].kurzform = (char*)malloc(10 * sizeof(char));

		data = strtok(buffer, ";");
		printf("%s,", data);
		strcpy(moduleGesamt[i].modulname, data);

		data = strtok(NULL, ";");
		printf("%s,", data);
		strcpy(moduleGesamt[i].kurzform, data);

		data = strtok(NULL, ";");
		printf("%s,", data);
		moduleGesamt[i].faktor = atoi(data);

		data = strtok(NULL, ";");
		printf("%s,", data);
		moduleGesamt[i].note = atoi(data);

		printf("\n");
		i++; 
	}

	fclose(moduleCSV);

	// Ausgabe aller Module 

	printf("\n");
	printf("Ausgabe gespeicherte Module:\n");

	for (int i = 0; i < anzahlModule; i++) {
		printf("%s, %s %d %d", moduleGesamt[i].modulname, moduleGesamt[i].kurzform, moduleGesamt[i].faktor, moduleGesamt[i].note); 
		printf("\n");

	}

	printf("\n");
	// Einlesen aller Noten

	for (int j = 0; j < anzahlModule; j++) {
		printf("%s\t", moduleGesamt[j].modulname);


		int aktuelleNote = einlesenEinerZahl("Gib nun deine Note ein:", 6, 15); 


		moduleGesamt[j].note = aktuelleNote; 

		printf("\n");
	}
	// Durchschnitt ausrechnen und Ausgabe des DUrchsnitts 
	int summeallerNoten = 0; 
	int durchschnitt = 0; 
	int gewichtungsfaktorsumme = 0; 

	for (int k = 0; k < anzahlModule; k++) {
		summeallerNoten += moduleGesamt[k].note * moduleGesamt[k].faktor; 
		gewichtungsfaktorsumme += moduleGesamt[k].faktor; 

	}
	durchschnitt = summeallerNoten / gewichtungsfaktorsumme; 
	printf("Dein Durchschnitt ist: %d", durchschnitt); 

	if (i == 15 || i == 14 || i == 13) {
		printf("Dein Durchschnitt ist %d, in Worten: sehr gut", durchschnitt); 
	}
	else if (i == 12 || i == 11 || i == 10) {
		printf("Dein Durchschnitt ist %d, in Worten: gut", durchschnitt);
	}
	else if (i == 9 || i == 8 || i == 7) {
		printf("Dein Durchschnitt ist %d, in Worten: befriedigend", durchschnitt);
	}
	else if (i == 6 ) {
		printf("Dein Durchschnitt ist %d, in Worten: ausreichend", durchschnitt);
	}
	else {
		printf("Schlechter kannst du keine Klausur bestanden haben, deine eingegebenen Noten sind falsch"); 
	}

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
		else if (eingelesenerWert < min || eingelesenerWert > max) printf("Zahl muss zwischen %d und %d liegen. Anders kannst du keine Klausur an deiner Hochschule bestehen\n", min, max);
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








