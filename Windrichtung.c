/*
;Name:      David Specht
;Datum:     27.02.2020
;Aufgabe:   Ermittlung der Windrichtung mit dem W132 von Ventus
;Controller:C8051F340
*/

#include <stdio.h>									// für sprinf											
#include <C_8051F340.h>
#include <Einstellungen.h>
#include <lcd.c>

#define NORD 0b00000001 
#define OST 0b00000010 
#define SUD 0b00000100 
#define WEST 0b00001000

#define NORD_OST 0b00000011 
#define SUD_OST 0b00000110 
#define SUD_WEST 0b00001100 
#define NORD_WEST 0b00001001 

unsigned char buf [20];
unsigned char wind;

void main (void){
    Grundeinstellungen();	
    initlcd ();						//	Initialisierung LCD-Display an P3
 	loeschenlcd ();				    //	Anzeige löschen	
    wind = P0 & 0b00001111;
    
	while (1){
        if(!(wind == (P0 & 0b00001111))){
            loeschenlcd();
            sprintf(buf, "Windrichtung:");
            textlcd(buf, 1);
            wind = P0 & 0b00001111;
            switch(wind){
                case NORD: sprintf(buf, "Nord"); break;
                case SUD: sprintf(buf, "Sued"); break;
                case OST: sprintf(buf, "Ost"); break;
                case WEST: sprintf(buf, "West"); break;
                case NORD_WEST: sprintf(buf, "Nord West"); break;
                case NORD_OST: sprintf(buf, "Nord Ost"); break;
                case SUD_WEST: sprintf(buf, "Sued West"); break;
                case SUD_OST: sprintf(buf, "Sued Ost"); break;
                default: break;
            }    
            textlcd(buf, 2);
            
        }
     }
}
