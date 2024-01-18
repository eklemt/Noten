/***

Name:			Noten-Durchschnitt ermitteln
Beschreibung:	Programm, in welchem mittlere kWh aus Solarstrahlung für verschiedene Standorte berechnet wird. Je nach Makro-Definition werden entweder Berechnungen
				zu Mittelwerten ausgegeben, oder es findet eine Benutzerabfrage statt, wo der User Werte über seine PV-Anlage angeben und sich die berechneten
				PV-Erträge in eine .txt-Datei abgespeichert werden.
Autorinnen:	    Emily Klemt, Carolin Altstaedt
Datum:		    17.01.2024
Version:		1

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
	double faktor;
	double note;
} tModul;

short einlesenEinerZahl( // Funktion, um eine Benutzereingabe einzulesen
	char text[],
	short min,
	short max); 

void einlesenDerNote(tModul* moduleGesamt, int anzahlModule);
double durchSchnittBerechnen(tModul* moduleGesamt, int anzahlModule, double durchschnitt); 
int ErgebnisseSpeichern(tModul* moduleGesamt, int anzahlModule, double durchschnitt); 
void tabelleAusgabe(int anzahlModule, tModul* moduleGesamt);

int main(void) {
	//open CSV

	char buffer[1000];
	char* data; 
	int anzahlModule = 1; 


	/**DATEI**/
	FILE* moduleCSV = fopen("module.csv", "r");
	if (moduleCSV == NULL) {// Fehler?
		printf("Fehler: Datei nicht gefunden");
		return 1;
	}
	printf("Erfolg: Datei gefunden");
	printf("\n");

	tModul* moduleGesamt = (tModul*)malloc(anzahlModule * sizeof(tModul));
	tModul* modulBackUp; 
  
	fgets(buffer, sizeof(buffer), moduleCSV); 
	printf("%s\n", buffer); 

	// Ausgabe der csv-Datei und abspeichwern in reservieertem SPeicher
	int i = 0;
	while (fgets(buffer, sizeof(buffer), moduleCSV)) {

		// Speicher für chat-Werte von struct allokieren
		moduleGesamt[i].modulname = (char*)malloc(100 * sizeof(char));

		moduleGesamt[i].kurzform = (char*)malloc(10 * sizeof(char));



		modulBackUp = moduleGesamt; 
		moduleGesamt = (tModul*)realloc(moduleGesamt, ++anzahlModule * sizeof(tModul));
		if (NULL == moduleGesamt) {
			printf("Fehler bei malloc\n");
			return -1;
		}

		data = strtok(buffer, ";");
		strcpy(moduleGesamt[i].modulname, data);

		data = strtok(NULL, ";");
		strcpy(moduleGesamt[i].kurzform, data);

	
		data = strtok(NULL, ";");
		moduleGesamt[i].faktor = atof(data);

		data = strtok(NULL, ";");
		moduleGesamt[i].note = atof(data);

		i++; 
	}

	fclose(moduleCSV); 
	anzahlModule = anzahlModule - 1;

	int aktuellerProgrammteil = 0; 

	bool ersterDurchlauf = true; 
	bool programmLaeuft = true; 
	while (programmLaeuft) {
		double durchschnitt = 0;

		if (ersterDurchlauf) {
			printf("Hallo. Hier kannst du deine Noten für alle Module eintragen und dir deinen Notendurchschnitt anzeigen lassen.\n");
			aktuellerProgrammteil = einlesenEinerZahl("Was möchtest du tun?\n(1 = Eintragen, 2 = Durchschnitt berechnen, 3 = Module und Einträge anzeigen, 4= in Datei speichern)\n", 1, 4);
		}
		else{
			aktuellerProgrammteil = einlesenEinerZahl("Was möchtest du als Nächstes tun?\n(1 = Eintragen, 2 = Durchschnitt berechnen, 3 = Module und Einträge anzeigen, 4= in Datei speichern)\n", 1, 4); 
		}
		// Ausführung Programmteil 1 zum Einlesen der Noten 
		if (aktuellerProgrammteil == 1) einlesenDerNote(moduleGesamt, anzahlModule);
		else if (aktuellerProgrammteil == 2) {
			durchschnitt = durchSchnittBerechnen(moduleGesamt, anzahlModule, durchschnitt);
		}
		else if (aktuellerProgrammteil == 3) tabelleAusgabe(anzahlModule, moduleGesamt);

		else if (aktuellerProgrammteil == 4) ErgebnisseSpeichern(moduleGesamt, anzahlModule, durchschnitt);

		//Beenden des Spiels 
		printf("Wenn du weitere Einträge machen willst, drücke enter. Wenn nicht, dann drücke 'x' und enter."); 
		if (getchar() == 'x') {
			programmLaeuft = false;
			printf("Danke, dass du das Programm genutzt hast.");
			return 0;
		}
		else {
			system("cls");
		}
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

// Einlesen aller Noten
void einlesenDerNote(tModul* moduleGesamt, int anzahlModule) {
	for (int j = 0; j < anzahlModule; j++) {
		printf("%s\t", moduleGesamt[j].modulname);


		int aktuelleNote = einlesenEinerZahl("Gib nun deine Note ein:", 6, 15);


		moduleGesamt[j].note = aktuelleNote;

		printf("\n");
	}
}

double durchSchnittBerechnen(tModul* moduleGesamt, int anzahlModule, double durchschnitt) {
	double summeallerNoten = 0;
	double gewichtungsfaktorsumme = 0;

	for (int k = 0; k < anzahlModule; k++) {
		summeallerNoten += moduleGesamt[k].note * moduleGesamt[k].faktor;
		gewichtungsfaktorsumme += moduleGesamt[k].faktor;

	}
	durchschnitt = summeallerNoten / gewichtungsfaktorsumme;
	printf("Dein Durchschnitt ist: %.2f\n", durchschnitt);

	if (durchschnitt > 12.5 ) {
		printf("Dein Durchschnitt ist %.2f, in Worten: sehr gut\n", durchschnitt);
	}
	else if (durchschnitt < 12.5 && durchschnitt >= 9.5) {
		printf("Dein Durchschnitt ist %.2f, in Worten: gut\n", durchschnitt);
	}
	else if (durchschnitt < 9.5 && durchschnitt >= 6.5) {
		printf("Dein Durchschnitt ist %.2f, in Worten: befriedigend\n", durchschnitt);
	}
	else if (durchschnitt < 6.5 && durchschnitt >= 6.0) {
		printf("Dein Durchschnitt ist %.2f, in Worten: ausreichend\n", durchschnitt);
	}
	else {
		printf("Schlechter kannst du keine Klausur bestanden haben, deine eingegebenen Noten sind falsch.\n");
		printf("Zudem kann ein sinnvoller Durchschnitt erst berechnet werden, wenn du Noten eingegeben hast.\n"); 
	}
	return durchschnitt; 
}

int ErgebnisseSpeichern(tModul* moduleGesamt, int anzahlModule, double durchschnitt) {
	FILE* fp = fopen("noten.csv", "w");
	if (fp == NULL) {
		printf("Das klappt nicht");
		return -1; 
	}

	for (int l = 0; l < anzahlModule; l++) {
		fprintf(fp, "%s;", moduleGesamt[l].modulname);
		fprintf(fp, "%s;", moduleGesamt[l].kurzform);
		fprintf(fp, "%.2f;", moduleGesamt[l].faktor);
		fprintf(fp, "%.2f;\n", moduleGesamt[l].note);

	}
	fprintf(fp, "Dein Notendurchschnitt: %2.f", durchschnitt); 
	fclose(fp);
	return 0;
}

// Ausgabe aller Module
void tabelleAusgabe(int anzahlModule, tModul* moduleGesamt) { // Funktion, die das aktuelle Spielfeld ausgibt
	printf("\n");
	for (int i = 0; i < anzahlModule; i++) {
		printf("%s\n", moduleGesamt[i].modulname);
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205); // macht folgende Ausgabe mit ASCII-Zeichen: ═════════
		printf("%s\t%.2f\t%.2f\n", moduleGesamt[i].kurzform, moduleGesamt[i].faktor, moduleGesamt[i].note);
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205); // macht folgende Ausgabe mit ASCII-Zeichen: ═════════
		printf("\n");
	}
}






