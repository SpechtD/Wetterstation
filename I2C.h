//--------------------------------------------------
// Abkürzungen:
// M = Master
// S = Slave
// T = Transmit
// R = Receive
//
// Bsp.: MT = Master Transmit
//-------------------------------------------------

#define TIMER0  0b00;
#define TIMER1  0b01;
#define TIMER2H 0b10;
#define TIMER2L 0b11;

// Status Vektoren - Nur die oberen 4 Bits
#define SMB_MTSTA   0xE0;           // (MT) START gesendet
#define SMB_MTDB    0xC0;           // (MT) Datenbyte Übertragen
#define SMB_MRDB    0x80;           // (MR) Datenbyte empfangen
#define SMB_STDB    0x40;           // (ST) Datenbyte Übertragen
#define SMB_STER    0x50;           // (ST) STOP Empfangen währed Übertragung
#define SMB_SRAR    0x20;           // (SR) ACK Angefragt
#define SMB_SRLA    0x20;           // (SR) Verbindung verloren
#define SMB_SRSTO   0x10;           // (SR) Verbindung gestrennt während einem STOP
#define SMB_SRDB    0x00;           // (SR) Datenbyte empfangen / Verbindung verloren beim Übertragen

unsigned char buffer[20];
unsigned char adrbuffer;

// SMBus Interrupt
void ISR_SMB0(void) interrupt 7 {

    if (SMB0CN & 0xF0 == SMB_MTSTA) {
        SMB0DAT = adrbuffer;
        STA = 0;
    }
}

void initI2C() {
    
}

void sendData(unsigned char adress, unsigned char data[]){

    STA = 1;

    adrbuffer = adress << 1 & 11111110;

    Strncpy(buffer, data, sizeof(buffer));
}
