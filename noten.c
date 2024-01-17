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

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


typedef struct REEModule{
	char* modulname;
	char* kurzform;
	float faktor;
	float note;
} tModul;

short einlesenEinerZahl( // Funktion, um eine Benutzereingabe einzulesen
	char text[],
	short min,
	short max); 

void ausgabeAllerModule(tModul* moduleGesamt, int anzahlModule); 
void einlesenDerNote(tModul* moduleGesamt, int anzahlModule);
int durchSchnittBerechnen(tModul* moduleGesamt, int anzahlModule, float durchschnitt); 
int ErgebnisseSpeichern(tModul* moduleGesamt, int anzahlModule, float durchschnitt); 

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

		// Speicher f�r chat-Werte von struct allokieren
		moduleGesamt[i].modulname = (char*)malloc(100 * sizeof(char));
		moduleGesamt[i].modulname = "text"; 
		moduleGesamt[i].kurzform = (char*)malloc(10 * sizeof(char));
		moduleGesamt[i].kurzform = "text";


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
		float durchschnitt = 0;

		if (ersterDurchlauf) {
			printf("Hallo. Hier kannst du deine Noten f�r alle Module eintragen und dir deinen Notendurchschnitt anzeigen lassen.\n");
			aktuellerProgrammteil = einlesenEinerZahl("Was m�chtest du tun?\n(1 = Eintragen, 2 = Durchschnitt berechnen, 3 = Module und Eintr�ge anzeigen, 4= in Datei speichern)\n", 1, 4);
		}
		else{
			aktuellerProgrammteil = einlesenEinerZahl("Was m�chtest du als N�chstes tun?\n(1 = Eintragen, 2 = Durchschnitt berechnen, 3 = Module und Eintr�ge anzeigen, 4= in Datei speichern)\n", 1, 4); 
		}

		if (aktuellerProgrammteil == 1) einlesenDerNote(moduleGesamt, anzahlModule);
		else if (aktuellerProgrammteil == 2) {
			durchschnitt = durchSchnittBerechnen(moduleGesamt, anzahlModule, durchschnitt);
		}
		else if (aktuellerProgrammteil == 3) ausgabeAllerModule(moduleGesamt, anzahlModule);

		else if (aktuellerProgrammteil == 4) ErgebnisseSpeichern(moduleGesamt, anzahlModule, durchschnitt);

		//Beenden des Spiels 
		printf("Wenn du weitere Eintr�ge machen willst, dr�cke enter. Wenn nicht, dann dr�cke 'x' und enter."); 
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
		else if (eingelesenerWert < min || eingelesenerWert > max) printf("Zahl muss zwischen %d und %d liegen. Anders kannst du keine Klausur an deiner Hochschule bestehen\n", min, max);
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


// Ausgabe aller Module 
void ausgabeAllerModule (tModul* moduleGesamt, int anzahlModule){
printf("\n");
printf("Ausgabe gespeicherte Module:\n");

	for (int u = 0; u < anzahlModule; u++) {
		printf("%s, %s %.2f %.2f", moduleGesamt[u].modulname, moduleGesamt[u].kurzform, moduleGesamt[u].faktor, moduleGesamt[u].note);
		printf("\n");
	}
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

int durchSchnittBerechnen(tModul* moduleGesamt, int anzahlModule, float durchschnitt) {
	float summeallerNoten = 0;
	float gewichtungsfaktorsumme = 0;

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
		printf("Schlechter kannst du keine Klausur bestanden haben, deine eingegebenen Noten sind falsch\n");
	}
	return durchschnitt; 
}

int ErgebnisseSpeichern(tModul* moduleGesamt, int anzahlModule, float durchschnitt) {
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






