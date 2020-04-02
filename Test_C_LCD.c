/*
;Name:      Captain
;Datum:     25.04.2019
;Aufgabe:   Test C LCD Display (2 x16 Zeichen) am Port 3 angeschlossen
;Controller:C8051F340
*/
//Beachte: Die Datei lcd.c muss im Projektordner sein und mit
//         Add... Item zus�tzlich zu dem Projekt hinzugef�gt werden!!!

#include <stdio.h>									// f�r sprinf											
#include <C_8051F340.h>
#include <Einstellungen.h>
#include <lcd.c>

// externe Funktionen in lcd.c; Diese Datei zum Projekt hinzuf�gen
 extern void initlcd (void);						//	Initialisierung LCD-Display an P0			
 extern void loeschenlcd (void);
 extern void textlcd (unsigned char *text,unsigned char zeile);	
 
void main (void)
	{
	unsigned char buf [20] ;	    // Zwischenspeicher f�r LCD-Text
	unsigned char a,b,c;			// Variablen zum Testen der LCD-Ausgabe
    
    Grundeinstellungen();	
	initlcd ();						//	Initialisierung LCD-Display an P3
 	loeschenlcd ();				    //	Anzeige l�schen	
    
    /*
 	textlcd ("   HGS-Singen",1);	//	Text ausgeben	Achtung " ", nicht  '  '	!	
 	sprintf (buf," Klasse TG13/3");	//	Test sprintf
	textlcd (buf,2);
    */  
	
	a = 36;							
	b = 42;
	c = a + b;							
	sprintf (buf,"a = %d b = %d",a,b);
	// Text mit Variable formatieren und in buf kopieren		
	//	% Ausgabeformat folgt, d Dezimalzahl mit Vorzeichen, a auszugebende Variable	
	textlcd (buf,1);																															
	//	Ausgabe des Textpuffers an Zeile 1 des LCD-Displays													
  	sprintf (buf,"c = %d",c);	
  	textlcd (buf,2);																		
    
	while (1); 
	} 

