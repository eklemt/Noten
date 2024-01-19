/***

Name:			Noten-Durchschnitt ermitteln
Beschreibung:	Programm, in welchem Daten für Module eines Studiengang aus einer CSV-Datei eingelesen werden. Anschließend kann der Nutzer aus mehreren Handlungsoptionen wählen. 
				Er kann Noten für die Module eingeben, seinen Durchschnitt ausgeben lassen, die Module mit Noten sich anzeigen lassen oder die Ergebnisse speichern. 
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


typedef struct REEModule{ // Struktur, die alle Paramter zur Beschreibung eines Moduls beinhaltet 
	char* modulname;
	char* kurzform;
	double faktor;
	double note;
} tModul;

short einlesenEinerZahl( char text[], short min, short max); // Funktion um eine Ganzzahl einzulesen, die aus einem bestimmten Zahlenbereich kommt 
void einlesenDerNoten(tModul* moduleGesamt, int anzahlModule); // Funktion um für alle Module nacheinander eine Note einzugeben 
double durchSchnittBerechnen(tModul* moduleGesamt, int anzahlModule, double durchschnitt); // Funktion, um die Abschlussnote zu berechnen und auszugeben
int ErgebnisseSpeichern(tModul* moduleGesamt, int anzahlModule, double durchschnitt); // Funktion, um die Ergebnisse in eine CSV-Datei zu speichern
void tabelleAusgabe(int anzahlModule, tModul* moduleGesamt); // Funktion, um sich alle Module mit Noten in einer tabellenähnlichen Form ausgeben zu lassen

int main(void) {

	char einleseSpeicher[1000];
	char* daten; 
	int anzahlModule = 0; 


	// Daten aus CSV Datei einlesen 
	FILE* moduleCSV = fopen("module.csv", "r"); 
	if (moduleCSV == NULL) {// abfangen, falls die Datei nicht gefunden werden kann 
		printf("Fehler: Datei nicht gefunden");
		return 1;
	}
	printf("Erfolg: Datei gefunden");
	printf("\n");

	tModul* moduleGesamt = NULL; //Zeiger auf den reservierten Speicherblock & initiale Reservierung des Speichers 
	tModul* moduleSicherungszeiger; // Zeiger für den Fall, dass es Probleme mit realloc gibt. 
  

	// Abspeichern der Werte aus der CSV-Datei im reservierten Speicher und dynamische Speicherallokation je nach Programmgröße
	int i = 0; // Indexvariable 
	while (fgets(einleseSpeicher, sizeof(einleseSpeicher), moduleCSV)) {

		moduleSicherungszeiger = moduleGesamt;
		moduleGesamt = (tModul*)realloc(moduleGesamt, ++anzahlModule * sizeof(tModul)); // Speicher anlegen mithilfe von realloc 
		if (NULL == moduleGesamt) {
			printf("Fehler bei realloc\n");
			moduleGesamt = moduleSicherungszeiger;
			return -1;
		}

		// Speicher für char-Werte von struct allokieren 
		int noetigeSpeichergroesse = 0; // Größe für Speicherreservierung der character

		daten = strtok(einleseSpeicher, ";");
		noetigeSpeichergroesse = ((int)strlen(daten)) + 1;
		moduleGesamt[i].modulname = (char*)malloc(noetigeSpeichergroesse * sizeof(char));
		if (moduleGesamt[i].modulname != NULL) {
			strcpy(moduleGesamt[i].modulname, daten);
		}

		daten = strtok(NULL, ";");
		noetigeSpeichergroesse = ((int)strlen(daten)) + 1;
		moduleGesamt[i].kurzform = (char*)malloc(noetigeSpeichergroesse * sizeof(char));
		if (moduleGesamt[i].kurzform != NULL) {
			strcpy(moduleGesamt[i].kurzform, daten);
		}

	
		daten = strtok(NULL, ";");
		moduleGesamt[i].faktor = atof(daten);

		daten = strtok(NULL, ";");
		moduleGesamt[i].note = atof(daten);

		i++; 
	}

	fclose(moduleCSV); 

	int aktuellerProgrammteil = 0; // Variable für den aktuellen Programmteil
	double durchschnitt = 0; // Variable für den Notendurchschnitt

	// Abfrage des Nutzers, welchen Programmteil er ausführen möchte, die solange läuft, bis der Nutzer das Programm mit x beendet 
	bool ersterDurchlauf = true; 
	bool programmLaeuft = true; 
	while (programmLaeuft) {

		if (ersterDurchlauf) {
			printf("Hallo. Hier kannst du deine Noten fuer alle Module eintragen und dir deinen Notendurchschnitt anzeigen lassen, sowie die Ergebnisse dir ausgeben lassen oder in eine Datei speichern.\n");
			aktuellerProgrammteil = einlesenEinerZahl("Was moechtest du tun?\n(1 = Eintragen, 2 = Durchschnitt berechnen, 3 = Module und Eintraege anzeigen, 4= in Datei speichern)\n", 1, 4);
		}
		else{
			aktuellerProgrammteil = einlesenEinerZahl("Was moechtest du als Naechstes tun?\n(1 = Eintragen, 2 = Durchschnitt berechnen, 3 = Module und Eintraege anzeigen, 4= in Datei speichern)\n", 1, 4); 
		}
		// Ausführung Programmteil 1 zum Einlesen der Noten 
		if (aktuellerProgrammteil == 1) einlesenDerNoten(moduleGesamt, anzahlModule);
		// Ausführung Programmteil 2 zum Durchschnitt berechenen 
		else if (aktuellerProgrammteil == 2) {
			durchschnitt = durchSchnittBerechnen(moduleGesamt, anzahlModule, durchschnitt);
		}
		// Ausführung Programmteil 3 zum Ausgeben der gespeicherten Daten
		else if (aktuellerProgrammteil == 3) tabelleAusgabe(anzahlModule, moduleGesamt);
		// Ausführung Programmteil 4 zum Abspeichern der Ergebnisse 
		else if (aktuellerProgrammteil == 4) ErgebnisseSpeichern(moduleGesamt, anzahlModule, durchschnitt);

		//Beenden der Applikation 
		printf("Wenn du weitere Eintraege machen willst, druecke enter. Wenn nicht, dann druecke 'x' und enter."); 
		if (getchar() == 'x') {
			programmLaeuft = false;
			printf("Danke, dass du das Programm genutzt hast.");
			return 0;
			free(moduleGesamt);
		}
		else {
			system("cls");
		}
	}
	free(moduleGesamt);  // Speicher freigeben
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

void einlesenDerNoten(tModul* moduleGesamt, int anzahlModule) { // Funktion um für alle Module nacheinander eine Note einzugeben 
	for (int j = 1; j < anzahlModule; j++) {
		printf("%s\t", moduleGesamt[j].modulname); // Ausgabe des Modulnamens

		int aktuelleNote = einlesenEinerZahl("Gib nun deine Note ein:", 6, 15); // Einlesen einer Note 


		moduleGesamt[j].note = aktuelleNote; // Note zum passenden Modul eintragen 

		printf("\n");
	}
}

double durchSchnittBerechnen(tModul* moduleGesamt, int anzahlModule, double durchschnitt) { // Funktion, um die Abschlussnote zu berechnen und auszugeben
	double summeallerNoten = 0;
	double gewichtungsfaktorsumme = 0;

	for (int k = 1; k < anzahlModule; k++) { // Berechnung entsprechend der Formel
		summeallerNoten += moduleGesamt[k].note * moduleGesamt[k].faktor;
		gewichtungsfaktorsumme += moduleGesamt[k].faktor;
	}
	durchschnitt = summeallerNoten / gewichtungsfaktorsumme;

	printf("Summe der erreichten Punkte: %.2f\n", summeallerNoten);

	// Ausgabe des Durchschnitts in Worten und als Zahl 
	if (durchschnitt > 12.5 ) {
		printf("Dein Durchschnitt ist %.3f, in Worten: sehr gut\n", durchschnitt);
	}
	else if (durchschnitt < 12.5 && durchschnitt >= 9.5) {
		printf("Dein Durchschnitt ist %.3f, in Worten: gut\n", durchschnitt);
	}
	else if (durchschnitt < 9.5 && durchschnitt >= 6.5) {
		printf("Dein Durchschnitt ist %.3f, in Worten: befriedigend\n", durchschnitt);
	}
	else if (durchschnitt < 6.5 && durchschnitt >= 6.0) {
		printf("Dein Durchschnitt ist %.3f, in Worten: ausreichend\n", durchschnitt);
	}
	else {
		printf("Schlechter kannst du keine Klausur bestanden haben, deine eingegebenen Noten sind falsch.\n");
		printf("Zudem kann ein sinnvoller Durchschnitt erst berechnet werden, wenn du Noten eingegeben hast.\n"); 
	}
	return durchschnitt; 
}

int ErgebnisseSpeichern(tModul* moduleGesamt, int anzahlModule, double durchschnitt) {  // Funktion, um die Ergebnisse in eine CSV-Datei zu speichern
	FILE* fp = fopen("noten.csv", "w");
	if (fp == NULL) {
		printf("Das klappt nicht. Vielleicht gibt es die Datei nicht?");
		return -1; 
	}

	for (int l = 0; l < anzahlModule; l++) { // Ergebnisse pro Zeile einspeichern 
		fprintf(fp, "%s;", moduleGesamt[l].modulname);
		fprintf(fp, "%s;", moduleGesamt[l].kurzform);
		fprintf(fp, "%.2f;", moduleGesamt[l].faktor);
		fprintf(fp, "%.2f;\n", moduleGesamt[l].note);

	}
	fprintf(fp, "Dein Notendurchschnitt: %.2f", durchschnitt); // Einspeichern des Notendurchschnitts 
	fclose(fp);
	return 0;
}

void tabelleAusgabe(int anzahlModule, tModul* moduleGesamt) { // Funktion, um sich alle Module mit Noten in einer tabellenähnlichen Form ausgeben zu lassen
	printf("\n");
	for (int i = 0; i < anzahlModule; i++) {
		printf("%s\n", moduleGesamt[i].modulname);
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205); // macht folgende Ausgabe mit ASCII-Zeichen: ═════════
		printf("%s\t%.2f\t%.2f\n", moduleGesamt[i].kurzform, moduleGesamt[i].faktor, moduleGesamt[i].note);
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205); // macht folgende Ausgabe mit ASCII-Zeichen: ═════════
		printf("\n");
	}
}






