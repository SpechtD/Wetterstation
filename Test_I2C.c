#include <string.h>
#include <stdio.h>									// für sprinf											
#include <C_8051F340.h>
#include <Einstellungen.h>
#include <I2C.h>

unsigned char message[] = "benis";

void main(void) {
    Grundeinstellungen();	
    initI2C();
    while(1){
        while(K1) continue;
        transmitData(4, message);
        while(!K1) continue;
    }
    
}