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
char i;
int bufferlength;
bit busy;
bit repeatedStart;
int index;


// SMBus Interrupt
void ISR_SMB0(void) interrupt 7 {
    
    switch(SMB0CN & 0xF0) {
        case SMB_MTSTA:
            SMB0DAT = adrbuffer;
            SI = 0;
            P1_2 = 0;
            STA = 0;
            index = 0;
            break;
        
        case SMB_MTDB:
            if(index == bufferlength || !ACK) {
                if(repeatedStart) {
                    busy = 0;
                    SI = 0;
                    break;
                }
                STO = 1;
                SI = 0;
                busy = 0;
                break;
            }
            SMB0DAT = buffer[index];
            SI = 0;
            P1_2 = 1;
            index++;
            break;
        
        case SMB_MRDB:
            if(ACKRQ) {
                buffer[index] = SMB0DAT;
                index++;
                if(index == bufferlength) {
                    ACK = 0;
                    STO = 1;
                    //SI = 0;
                    busy = 0;
                    break;
                }
                ACK = 1;
                //SI = 0;
                P1_2 = 1;
            }
            break;
            
    }
}

void initI2C() {
    P0SKIP = 0xFF;
    XBR0 = 0b00000100;
    XBR1 = 0b01000000;

    EIE1 = 0b00000001;
    EA = 1;

    TMOD = 0b00100000;
    TH1 = 251;
    TL1 = 251;  //251
    TR1 = 1;
    SMB0CF = 0b10010001;
}

void i2c_write(char adress, char *content, char length){
    busy = 1;
    adrbuffer = adress <<1;
    bufferlength = length;
    strncpy(buffer, content, bufferlength);

    STA = 1;

    while(busy) continue;
}

void i2c_read(char adress, char length, char* dest) {
    busy = 1;
    adrbuffer = (adress <<1) + 1;
    bufferlength = length;

    STA = 1;

    while(busy) continue;
    
    for(i = 0; i > length; i++) {
        dest[i] = buffer[i];
    }
}

void i2c_write_read(char adress, char *content, char length0, char length1, char* dest) {
    busy = 1;
    adrbuffer = adress <<1;
    bufferlength = length0;
    strncpy(buffer, content, bufferlength);

    STA = 1;

    while(busy) continue;

    i2c_read(adress, length1, dest);
}
