//--------------------------------------------------
// Abkürzungen:
// M = Master
// S = Slave
// T = Transmit
// R = Receive
//
// Bsp.: MT = Master Transmit
//-------------------------------------------------

#define TIMER0  0b00
#define TIMER1  0b01
#define TIMER2H 0b10
#define TIMER2L 0b11

// Status Vektoren - Nur die oberen 4 Bits
#define SMB_MTSTA   0xE0           // (MT) START gesendet
#define SMB_MTDB    0xC0           // (MT) Datenbyte Übertragen
#define SMB_MRDB    0x80           // (MR) Datenbyte empfangen
#define SMB_STDB    0x40           // (ST) Datenbyte Übertragen
#define SMB_STER    0x50           // (ST) STOP Empfangen währed Übertragung
#define SMB_SRAR    0x20           // (SR) ACK Angefragt
#define SMB_SRLA    0x20           // (SR) Verbindung verloren
#define SMB_SRSTO   0x10           // (SR) Verbindung gestrennt während einem STOP
#define SMB_SRDB    0x00           // (SR) Datenbyte empfangen / Verbindung verloren beim Übertragen

unsigned char buffer[20];
unsigned char adrbuffer;
int index;

// SMBus Interrupt
void ISR_SMB0(void) interrupt 7 {
    
    switch(SMB0CN & 0xF0) {
        case SMB_MTSTA:
            SI = 0;
            SMB0DAT = adrbuffer;
            P1_2 = 0;
            STA = 0;
            index = 0;
            break;
        
        case SMB_MTDB:
            SI = 0;
            P1_2 = 1;
            SMB0DAT = buffer[index];
            index++;
            if(index == 20) STO = 1;
    }
}

void initI2C() {
    P0SKIP = 0xFF;
    XBR0 = 0b00000100;
    XBR1 = 0b01000000;

    EIE1 = 0b00000001;
    EA = 1;

    TMOD = 0b00100000;
    TH1 = 150;
    TL1 = 150;  //251
    TR1 = 1;
    SMB0CF = 0b10000001;
}

void transmitData(char adress, char *content){

    adrbuffer = adress <<1;
    
    //adrbuffer += 1;
    strncpy(buffer, content, 20);

    STA = 1;
}
