/*
;Name:      Captain
;Datum:     25.04.2019
;Aufgabe:   Test C Timer Interrupt, Starten mit der Betätigung des Tasters K1
;           Blinklicht mit 1Hz -> 1s (1000ms) -> 500ms an, 500ms aus
;           500000/65536 = 7,629..  -> 8 Überläufe
;           Startwert -> 8*65536-500000 = 24288 = 5EE0h
;Controller:C8051F340
*/

//-----------------------------------------------------------------------------
// Include Dateien
//-----------------------------------------------------------------------------
#include <C_8051F340.h>                //Erweiterte SFR Zuordnungen
#include <Einstellungen.h>             //beinhaltet die Funktion Grundeinstellungen

//-----------------------------------------------------------------------------
// Pin/Port Zuweisungen
//-----------------------------------------------------------------------------
sfr  at P1   LEDs;
sbit at P1_0 LED; //Blink-LED

//-----------------------------------------------------------------------------
// Globale Variablen (Datentypen)
//-----------------------------------------------------------------------------
unsigned char n;    //Überlaufzähler Timer 0

//-----------------------------------------------------------------------------
// Eigene Funktionen
//-----------------------------------------------------------------------------
void ISR_Timer0 (void) interrupt 1 //Interrupt Serviceroutine Timer 0
{
    n--;
    if(n==0)
    {
        LED  = ~LED;    //LED am Port P1.0 invertieren
        TR0  = 0;       //Timer 0 stoppen
        TH0  = 0x5E;    //Startwert TH0
        TL0  = 0xE0;    //Startwert TL0  
        n    = 8;       //Überlaufzähler wieder setzen
        TR0  = 1;       //Timer 0 wieder starten
    }
}
//*****************************************************************************
void Timer_Initialisierung (void)
{
    TMOD = 1;       //Timer 0 16Bit Modus
    TH0  = 0x5E;    //Startwert TH0
    TL0  = 0xE0;    //Startwert TL0 
    n    = 8;       //Anzahl der Timer 0 Überläufe für 500ms
}
//*****************************************************************************
void Interrupt_Initialisierung (void)
{
    ET0 = 1;        //Freigabe Timer 0 Interrupt
    EA  = 1;        //Globale Freigabe Enable All
}
//*****************************************************************************

//-----------------------------------------------------------------------------
// Hauptprogramm
//-----------------------------------------------------------------------------
void main (void)
{
    Grundeinstellungen(); //Grundeinstellungen für den C8051F340 (siehe Einstellungen.h)    
    Timer_Initialisierung();
    Interrupt_Initialisierung();
    LEDs=0;
    D2 = 0;         //lösche LED D2 auf dem µC-Board
    D3 = 0;         //lösche LED D3 auf dem µC-Board

    while (K1==1);  //warten auf die Tasterbetätigung von K1 auf dem µC-Board (P2.0) Low-aktiv!
    TR0 = 1;        //Timer 0 starten      
    while(1);       //Endlosschleife
}

