#include <string.h>
#include <stdio.h>									// für sprinf											
#include <C_8051F340.h>
#include <Einstellungen.h>
#include <I2C.h>

unsigned char message[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,80,19};

void main(void) {
    Grundeinstellungen();	
    initI2C();
    while(1){
        while(K1) continue;
        transmitData(4, message);
        while(!K1) continue;
    }
    
}