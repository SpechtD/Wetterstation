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
#define SMB_MTDB    0xC0;           // (MT) Datenbyte übertragen
#define SMB_MRDB    0x80;           // (MR) Datenbyte empfangen
#define SMB_STDB    0x40;           // (ST) Datenbyte übertragen
#define SMB_STER    0x50;           // (ST) STOP Empfangen währed übertragung
#define SMB_SRAR    0x20;           // (SR) ACK Angefragt
#define SMB_SRLA    0x20;           // (SR) Verbindung verloren
#define SMB_SRSTO   0x10;           // (SR) Verbindung gestrennt während einem STOP
#define SMB_SRDB    0x00;           // (SR) Datenbyte empfangen / Verbindung verlohren beim Übertragen


typedef struct settings_t {
    char SMBEnable      : 1;
    char SMBSlaveInhibit: 1;
    char SMBExtHold     : 1;
    char SMBSCLTimeout  : 1;
    char SMBFreeTimeout : 1;
    char SMBClockSource : 2;
} settings;

unsigned char buffer[20];
unsigned char adrbuffer;

void I2Csettings(struct settings_t *settings) {
    SMB0CF = &settings;

    if (settings.SMBSCLTimeout){

    }
}

void ISR_SMB0(void) interrupt 7 {

    if (SMB0CN & 0xF0 == SMB_MTSTA) {
        SMB0DAT = adrbuffer;
        STA = 0;
    }


}

boolean sendData(unsigned char adress, unsigned char data[]){

    STA = 1;

    adrbuffer = adress << 1 & 11111110;

    Strncpy(buffer, data, sizeof(buffer));

    return 1;
}