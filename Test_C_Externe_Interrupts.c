/*
;Name:      Captain
;Datum:     25.04.2019
;Aufgabe:   Test C Externe Interrupts
;Controller:C8051F340

;IT0 IN0PL         INT0-Interrupt                 
; 1    0     Active low, edge sensitive            
; 1    1     Active high, edge sensitive           
; 0    0     Active low, level sensitive           
; 0    1     Active high, level sensitive          

;IT1 IN1PL        INT1-Interrupt
; 1    0     Active low, edge sensitive
; 1    1     Active high, edge sensitive
; 0    0     Active low, level sensitive
; 0    1     Active high, level sensitive

;IT01CF Register
;  D7    D6     D5     D4     D3    D2     D1     D0
;IN1PL IN1SL2 IN1SL1 IN1SL0 IN0PL IN0SL2 IN0SL1 IN0SL0

; IN0SL2 SL1 SL0    /INT0 Port Pin
;     0   0   0          P0.0
;     0   0   1          P0.1
;     0   1   0          P0.2
;     0   1   1          P0.3
;     1   0   0          P0.4
;     1   0   1          P0.5
;     1   1   0          P0.6
;     1   1   1          P0.7

; IN1SL2 SL1 SL0    /INT1 Port Pin
;     0   0   0          P0.0
;     0   0   1          P0.1
;     0   1   0          P0.2
;     0   1   1          P0.3
;     1   0   0          P0.4
;     1   0   1          P0.5
;     1   1   0          P0.6
;     1   1   1          P0.7
*/

//-----------------------------------------------------------------------------
// Include Dateien
//-----------------------------------------------------------------------------
#include <C_8051F340.h>                //Erweiterte SFR Zuordnungen
#include <Einstellungen.h>             //beinhaltet die Funktion Grundeinstellungen

//-----------------------------------------------------------------------------
// Pin/Port Zuweisungen
//-----------------------------------------------------------------------------
sfr at P1 LEDs;

//-----------------------------------------------------------------------------
// Eigene Funktionen
//-----------------------------------------------------------------------------
void ISR_Ext0 (void) interrupt 0 //Interrupt Serviceroutine Extern 0 hier P0.2
{
    LEDs=255;
}
//*****************************************************************************
void ISR_Ext1 (void) interrupt 2 //Interrupt Serviceroutine Extern 1 hier P0.1
{
    LEDs=0;
}
//*****************************************************************************
void Interrupt_Initialisierung (void)
{
    IT01CF = 0b10011010;//Ext Int 0 -> P0.2, Ext Int 1 -> P0.1
    IT0 = 1;            //positive Flanke in Verbindung mit IN0PL=1 (D3=1) in IT01CF-Reg
    IT1 = 1;            //positive Flanke in Verbindung mit IN1PL=1 (D7=1) in IT01CF-Reg
    EX0 = 1;            //Freigabe externer Interrupt 0 (P0.2)
    EX1 = 1;            //Freigabe externer Interrupt 1 (P0.1)
    EA  = 1;            //Globale Freigabe Enable All
}

//-----------------------------------------------------------------------------
// Hauptprogramm
//-----------------------------------------------------------------------------
void main (void)
{ 
    Grundeinstellungen(); //siehe Datei Einstellungen.h
    Interrupt_Initialisierung();   
    LEDs=0;
    while(1);
}




