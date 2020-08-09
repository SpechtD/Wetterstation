#include <string.h>
#include <stdio.h>
#include <C_8051F340.h>
#include <Einstellungen.h>
#include <I2C.h>


#define SSD1306_LCDWIDTH      128
#define SSD1306_LCDHEIGHT      64
#define SSD1306_SETCONTRAST   0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

unsigned char message[20];
char tempReadout[8];

void  ssd1306_command(char c)
{
 
    message[0] = 0x80;
    message[1] = c;
    i2c_write(0b0111100, message, 2);
}

void initSSD(){

    // Init sequence for 128x64 OLED module
    ssd1306_command(SSD1306_DISPLAYOFF);                    // 0xAE

    ssd1306_command(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
    ssd1306_command(0x80);                 // the suggested ratio 0x80
   
    ssd1306_command(SSD1306_SETMULTIPLEX);                  // 0xA8
    ssd1306_command(0x3F);
   
    ssd1306_command(SSD1306_SETDISPLAYOFFSET);              // 0xD3
    ssd1306_command(0x0);                                   // no offset
   
    ssd1306_command(SSD1306_SETSTARTLINE);// | 0x0);        // line #0
   
    ssd1306_command(SSD1306_CHARGEPUMP);                    // 0x8D
    ssd1306_command(0x14);  // using internal VCC
   
    ssd1306_command(SSD1306_MEMORYMODE);                    // 0x20
    ssd1306_command(0x00);          // 0x00 horizontal addressing
   
    ssd1306_command(SSD1306_SEGREMAP | 0x1); // rotate screen 180
   
    ssd1306_command(SSD1306_COMSCANDEC); // rotate screen 180
   
    ssd1306_command(SSD1306_SETCOMPINS);                    // 0xDA
    ssd1306_command(0x12);
   
    ssd1306_command(SSD1306_SETCONTRAST);                   // 0x81
    ssd1306_command(0xCF);
   
    ssd1306_command(SSD1306_SETPRECHARGE);                  // 0xd9
    ssd1306_command(0xF1);
   
    ssd1306_command(SSD1306_SETVCOMDETECT);                 // 0xDB
    ssd1306_command(0x40);
   
    ssd1306_command(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
   
    ssd1306_command(SSD1306_NORMALDISPLAY);                 // 0xA6
 
    ssd1306_command(SSD1306_DISPLAYON);                     //switch on OLED

}


void setColAddress()
{
  ssd1306_command(SSD1306_COLUMNADDR); // 0x21 COMMAND
  ssd1306_command(0); // Column start address
  ssd1306_command(SSD1306_LCDWIDTH-1); // Column end address
}

void setPageAddress()
{
  ssd1306_command(SSD1306_PAGEADDR); // 0x22 COMMAND
  ssd1306_command(0); // Start Page address
  ssd1306_command((SSD1306_LCDHEIGHT/8)-1);// End Page address
}

void main(void) {
    Grundeinstellungen();	
    initI2C();
    while(1){
        while(K1) continue;
        message[0] = 0xF2; 
        message[1] = 0x01;
        message[2] = 0xF4;
        message[3] = 0b10101010;
        i2c_write(0b1110110, message, 4);
        i2c_write_read(0b1110110, message, 1, 8, tempReadout);
        //i2c_read(0b1110110, 8, tempReadout);
        while(!K1) continue;
    }
    
}