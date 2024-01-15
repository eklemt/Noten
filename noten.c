/***

Name:			Noten-Durchschnitt ermitteln
Beschreibung:	Programm, in welchem mittlere kWh aus Solarstrahlung f�r verschiedene Standorte berechnet wird. Je nach Makro-Definition werden entweder Berechnungen
				zu Mittelwerten ausgegeben, oder es findet eine Benutzerabfrage statt, wo der User Werte �ber seine PV-Anlage angeben und sich die berechneten
				PV-Ertr�ge in eine .txt-Datei abgespeichert werden.
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
	char modulname[100];
	char kurzform[100];
	float faktor;
	float note;
} tModul;



int main(void) {
	tModul modul;
	int anzahlModule = 0;
	//int* moduleGesamt = NULL;
	//moduleGesamt = (int*)malloc(moduleAnzahl * sizeof(int));


	//w�hrend einlesen von csv mitz�hlen wieviele module eingelesen wurden und moduleAnzahl darauf setzen

	
		//modul anlegen
		strcpy(modul.modulname, "Mathematik");
		strcpy(modul.kurzform, "BEK");
		modul.faktor = 3.0;
		modul.note = 0.0;


		//modul in module gesamt pushen

	

	printf("module %s", modul.modulname);

	

	//abfrage welcher teil des programms ausgef�hrt werden soll (speichern, einlsesn, abrufen, korrigieren...)
	//Funktionen freischalten? Abrufen < Einlesen?


	//Funktion: CSV auslesen und in array speichern malloc

	//Funktion: Nutzereingabe in eigene CSV zur�ckschreiben

	//Funktion:Abschluss note aus gegebenen Werten berechnen

	//Funktion: Noten f�r alle verf�gbaren F�cher abfragen, auf G�ltigkeit (0-15 pr�fen)
	//Summe aller Punkte
	//Leistungspunkte, drei Nachkommastellen

	//Funktion: mega printf csv 1 zu 1 auf konsole ausgeben

	//open CSV
	printf("\n");
	char buffer[1000];
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
	};
	






}


short einlesenEinerZahl( // Funktion, um eine Benutzereingabe einzulesen
	char text[],
	short min,
	short max)
{
	short eingelesenerWert;		// eingegebene Zahl des Benutzers
	bool fertig = false;			// Variable, die anzeigt, ob die Eingabe den Anforderungen einer Lottozahl entspricht
	char ch;						// m�glicher Buchstabe nach der eingegebenen Zahl
	int R�ckgabewert;			// R�ckgabewert von scanf

	do {
		//Einlesen der Zahl 
		printf("%s: ", text);
		ch = '\0';
		R�ckgabewert = scanf("%hd%c", &eingelesenerWert, &ch);

		// �berpr�fen, ob die Zahl den Anforderungen entspricht
		if (R�ckgabewert != 2) printf("Das war keine korrekte Zahl!\n");
		else if (ch != '\n') printf("Unerwartete Zeichen hinter der Zahl!\n");
		else if (eingelesenerWert < min || eingelesenerWert > max) printf("Zahl muss zwischen 1 und %d liegen.\n", max);
		else fertig = true;
		// Input stream leeren 
		while (ch != '\n') {
			char checkChar = scanf("%c", &ch);
		}
		// wiederholen, wenn es nicht beendet ist 
	} while (!fertig);

	// R�ckgabe der eingelesenen Zahl 
	return eingelesenerWert;
}




