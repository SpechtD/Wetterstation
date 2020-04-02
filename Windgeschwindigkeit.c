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

unsigned char buf [20];

unsigned int umdrehungen;
unsigned char timerUeberlaufe;
float geschwindigkeit;
unsigned char messzeit = 5;

void ISR_EX0(void) interrupt 0 {
    umdrehungen++;
}

void ISR_T0(void) interrupt 1 {
    TR0 = 0;
    timerUeberlaufe++;
    TH0 = 0x3C;
    TL0 = 0xB0;
    if(timerUeberlaufe == (messzeit*20)){
        timerUeberlaufe = 0;
        geschwindigkeit = (0.40841 * (umdrehungen/messzeit)) * 3.6;
        umdrehungen = 0;
        geschwindigkeit = (int) (geschwindigkeit * 1000 + 5); //Nachkommastellen wegschneiden
        geschwindigkeit = geschwindigkeit / 1000;
        loeschenlcd(); 
        sprintf(buf, "Geschwindigkeit:");
        textlcd(buf,  1);
        sprintf(buf, "%f km/h",geschwindigkeit);
        textlcd(buf,  2);
    }
    TR0 = 1;
}

void init(void) {
    EA = 1;
    EX0 = 1;
    ET0 = 1;
    
    IT0 = 1;
    IT01CF = 0b00001100;

    TMOD = 0b00000001;

    TH0 = 0x3C;
    TL0 = 0xB0;

    TR0 = 1;
}

void main (void) {
    Grundeinstellungen();	
    initlcd ();						//	Initialisierung LCD-Display an P3
 	loeschenlcd ();				    //	Anzeige löschen	
    init();

    sprintf(buf, "Geschwindigkeit:");
    textlcd(buf,  1);
    sprintf(buf, "Messung laeuft...");
    textlcd(buf,  2);

    while(1);
}
