/*****************************************************
This program was produced by the
CodeWizardAVR V2.05.0 Professional
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : SNR Reader
Version : 3:00
Date    : 5/6/2014
Author  : Sajjadi
Company : 
Comments: 


Chip type               : ATmega32L
Program type            : Application
AVR Core Clock frequency: 4.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*****************************************************/

// W5100 Defenitions
#define     COMMON_BASE     0x0000
#define     MAX_SOCK_NUM    1
#define     time_out        200     // Retransmission time
#define     no_of_retry     8       // Number Of Retransmission
#define     recv_size       1024    // Number of Byte to receive in each try  
#define     source_port     1565    // Source PORT
#define     dest_port       23      // Destinition PORT
#define     link_test       PIND.3  // Link LED

#include <mega32a.h>
#include <delay.h>
#include <spi.h>
#include <W5100.h>
#include <alcd.h>

typedef unsigned char byte;

// Declare your global variables here
flash char gateway[4]={192,168,1,1};                          // gateway IP address
flash char source_mac[6]={0x80,0x08,0xDC,0x01,0x02,0x03};     // MAC address
flash char subnet_mask[4]={255,255,255,0};                    // SubnetMask address
flash char source_ip[4]={192,168,1,10};                       // Source IP address
flash char dest_ip[4] = {192,168,1,1};                        // Destinition IP address
flash char admin[13] = {'a','d','m','i','n', 0x0d , 0x0a};
flash char data[25] = {'w','a','n',' ','a','d','s','l',' ','c','h','a','n','d','a','t','a',0x0d,0x0a};
flash char near[25] = {'w','a','n',' ','a','d','s','l',' ','l','i','n','e','d','a','t','a',' ','n','e','a','r',0x0d,0x0a};
flash char far[25] = {'w','a','n',' ','a','d','s','l',' ','l','i','n','e','d','a','t','a',' ','f','a','r',0x0d,0x0a};
flash byte char0[8] = { 0b0000100,0b0001110,0b0011111,0b0000100,0b0000100,0b0000100,0b0000100,0b0000100 };
flash byte char1[8] = { 0b0000100,0b0000100,0b0000100,0b0000100,0b0000100,0b0011111,0b0001110,0b0000100 };
flash char nvt1[9] = {0xff,0xfa,0x2c,0x32,0x00,0xff,0xf0,0x0d,0x0a};
flash char nvt2[9] = {0xff,0xfa,0x2c,0x32,0x30,0xff,0xf0,0x0d,0x0a};
char recv_buf[1024];
int i = 0;
bit test = 1;
char temp = 0;
char link = 0; 
char upsnr[5]; 
char dnsnr[5];
char upstrm[5];
char dnstrm[5];

//---------------------------------------------------------------
// function used to define user characters
void define_char(byte flash *pc,byte char_code)
{
    byte i,a;
    a=(char_code<<3) | 0x40;
    for (i=0; i<8; i++) lcd_write_byte(a++,*pc++);
}
//---------------------------------------------------------------

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=Out Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=0 State6=P State5=P State4=P State3=P State2=P State1=P State0=P 
PORTA=0x7F;
DDRA=0x80;

// Port B initialization
// Func7=Out Func6=In Func5=Out Func4=Out Func3=In Func2=In Func1=In Func0=In 
// State7=0 State6=T State5=0 State4=1 State3=P State2=T State1=P State0=P 
PORTB=0x1B;
DDRB=0xB0;

// Port C initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=In Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=P State2=0 State1=0 State0=0 
PORTC=0x08;
DDRC=0xF7;

// Port D initialization
// Func7=In Func6=In Func5=Out Func4=In Func3=In Func2=In Func1=Out Func0=In 
// State7=P State6=P State5=0 State4=P State3=T State2=T State1=1 State0=T 
PORTD=0xD2;
DDRD=0x22;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=0xFF
// OC0 output: Disconnected
TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer1 Stopped
// Mode: Normal top=0xFFFF
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2 output: Disconnected
ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=0x00;
MCUCSR=0x00;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=0x00;

// USART initialization
// USART disabled
UCSRB=0x00;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC disabled
ADCSRA=0x00;

// SPI initialization
// SPI Type: Master
// SPI Clock Rate: 1000.000 kHz
// SPI Clock Phase: Cycle Start
// SPI Clock Polarity: Low
// SPI Data Order: MSB First
SPCR=0x50;
SPSR=0x00;

// TWI initialization
// TWI disabled
TWCR=0x00;

// Alphanumeric LCD initialization
// Connections specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 2
// RD - PORTC Bit 0
// EN - PORTC Bit 1
// D4 - PORTC Bit 6
// D5 - PORTC Bit 5
// D6 - PORTC Bit 7
// D7 - PORTC Bit 4
// Characters/line: 20
lcd_init(20);

lcd_gotoxy(0,0);    lcd_putsf("     ADSL  Line     ");
lcd_gotoxy(0,1);    lcd_putsf("   Quality Tester   ");
delay_ms(3000);
lcd_gotoxy(0,0);    lcd_putsf("Designed by:        ");
lcd_gotoxy(0,1);    lcd_putsf("MOHAMMAD L. SAJJADI ");
delay_ms(1000);

STRT:
do
{
    link = 0;
    
    lcd_gotoxy(0,0);    lcd_putsf("Link Status : DOWN  ");
    lcd_gotoxy(0,1);    lcd_putsf("Connecting          ");
    
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100); 
    
    lcd_gotoxy(10,1);   lcd_putchar('.');
    
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
    
    lcd_gotoxy(11,1);   lcd_putchar('.');
    
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
    
    lcd_gotoxy(12,1);   lcd_putchar('.');
    
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
     
    lcd_gotoxy(13,1);   lcd_putchar('.'); 
    
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);
    if( link_test == 0 ) link++; delay_ms(100);

}
while( link <= 17 );

lcd_gotoxy(0,0);    lcd_putsf("Link Status : UP    ");
lcd_gotoxy(0,1);    lcd_putsf("Connected           ");

REP:
if ( temp == SOCK_CLOSED )
{
    // Reset the W5100
    PORTA.7 = 0;
    delay_ms(1000);
    PORTA.7 = 1;
    delay_ms(1000);

    IINCHIP_WRITE(MR,MR_RST);
    delay_ms(1000);
    sysinit(0x55,0x55); 
    setRTR(time_out*10);
    setRCR(no_of_retry);
    setGAR(gateway);
    setSHAR(source_mac);
    setSUBR(subnet_mask);
    setSIPR(source_ip);
    AGI:
    do
    {
        temp = socket(0,Sn_MR_TCP,source_port,0);
    }
    while ( temp == 0 );
        
    do
    {
        connect(0, dest_ip, dest_port);
        delay_ms(10);
        temp = getSn_SR(0);   //read status
        if ( temp == SOCK_CLOSED ) break;
    }
    while ( temp != SOCK_ESTABLISHED );

    if ( temp == SOCK_CLOSED )
    { 
        close(0); 
        delay_ms(10); 
        goto AGI; 
    }   
        
    delay_ms(500);
    send_flash(0,nvt1,9);
    delay_ms(500);
    send_flash(0,nvt2,9);
    recv(0, recv_buf, recv_size);
}

test = 1;
while ( test )
{
    send_flash( 0,admin,7 );
    recv(0, recv_buf, recv_size);
    for( i = 0 ; i < 30 ; i++ ) if( recv_buf[i] == '>' ) test = 0;
}

define_char(char0,0);  //define user character 0
define_char(char1,1);  //define user character 1

lcd_clear();
lcd_gotoxy(0,0);    lcd_putsf("SNR: ");
lcd_gotoxy(6,0);    lcd_putchar(0); 
lcd_gotoxy(13,0);    lcd_putchar(1);
lcd_gotoxy(0,1);    lcd_putsf("Data:");
lcd_gotoxy(6,1);    lcd_putchar(0);
lcd_gotoxy(13,1);    lcd_putchar(1);      

do
{            
    link = 0;
    if( link_test == 0 ) link++;    // Test Link
    send_flash(0,data,19);
    recv(0, recv_buf, recv_size); 
    delay_ms(100);
    if( link_test == 0 ) link++;    // Test Link
    for( i = 0 ; i < 1024 ; i++ )
    {
         if( recv_buf[i] == 'n' )
            if( recv_buf[i+9] == 'i' )
                if( recv_buf[i+17] == 'v' )
                    if( recv_buf[i+37] == ':' )
                    {   
                        dnstrm[0] = recv_buf[i+39];
                        if( recv_buf[i+40] != ' ' ) dnstrm[1] = recv_buf[i+40];
                        else { dnstrm[1] = ' '; dnstrm[2] = ' '; dnstrm[3] = ' '; dnstrm[4] = 0; goto UPSTR; }
                        if( recv_buf[i+41] != ' ' ) dnstrm[2] = recv_buf[i+41];
                        else { dnstrm[2] = ' '; dnstrm[3] = ' '; dnstrm[4] = 0; goto UPSTR; }
                        if( recv_buf[i+42] != ' ' ) dnstrm[3] = recv_buf[i+42];
                        else dnstrm[3] = ' ';
                        dnstrm[4] = 0;
                    }
                                                    
        UPSTR:
        if( recv_buf[i] == 'f' )
            if( recv_buf[i+8] == 'i' )
                if( recv_buf[i+16] == 'v' )
                    if( recv_buf[i+36] == ':' )
                    {
                        upstrm[0] = recv_buf[i+38];
                        if( recv_buf[i+39] != ' ' ) upstrm[1] = recv_buf[i+39];
                        else { upstrm[1] = ' '; upstrm[2] = ' '; upstrm[3] = ' '; upstrm[4] = 0; break; }
                        if( recv_buf[i+40] != ' ' ) upstrm[2] = recv_buf[i+40];
                        else { upstrm[2] = ' '; upstrm[3] = ' '; upstrm[4] = 0; break; }
                        if( recv_buf[i+41] != ' ' ) upstrm[3] = recv_buf[i+41];
                        else upstrm[3] = ' ';
                        upstrm[4] = 0;
                    }
    }
                    
    if( link_test == 0 ) link++;    // Test Link
    send_flash(0,near,24);
    recv(0, recv_buf, recv_size); 
    delay_ms(100);
    if( link_test == 0 ) link++;    // Test Link
    for( i = 0 ; i < 1024 ; i++ )
    {
         if( recv_buf[i] == 'i' )
            if( recv_buf[i+3] == 'd' )
                if( recv_buf[i+5] == 'w' )
                    if( recv_buf[i+13] == ':' )
                    {
                        dnsnr[0] = recv_buf[i+15];
                        if( recv_buf[i+16] != ' ' ) dnsnr[1] = recv_buf[i+16];
                        else { dnsnr[1] = ' '; dnsnr[2] = ' '; dnsnr[3] = ' '; dnsnr[4] = 0; break; }
                        if( recv_buf[i+17] != ' ' ) dnsnr[2] = recv_buf[i+17];
                        else { dnsnr[2] = 0; dnsnr[3] = ' '; dnsnr[4] = 0; break; }
                        if( recv_buf[i+18] != ' ' ) dnsnr[3] = recv_buf[i+18];
                        else dnsnr[3] = ' ';
                        dnsnr[4] = 0;
                    }
    } 
                    
    if( link_test == 0 ) link++;    // Test Link
    send_flash(0,far,23);
    recv(0, recv_buf, recv_size); 
    delay_ms(100);
    if( link_test == 0 ) link++;    // Test Link
    for( i = 0 ; i < 1024 ; i++ )
    {
         if( recv_buf[i] == 'i' )
            if( recv_buf[i+3] == 'u' )
                if( recv_buf[i+5] == 's' )
                    if( recv_buf[i+11] == ':' )
                    {                        
                        upsnr[0] = recv_buf[i+13];
                        if( recv_buf[i+14] != 0x0d ) upsnr[1] = recv_buf[i+14];
                        else { upsnr[1] = ' '; upsnr[2] = ' '; upsnr[3] = ' '; upsnr[4] = 0; break; }
                        if( recv_buf[i+15] != 0x0d ) upsnr[2] = recv_buf[i+15];
                        else { upsnr[2] = ' '; upsnr[3] = ' '; upsnr[4] = 0; break; }
                        if( recv_buf[i+16] != 0x0d ) upsnr[3] = recv_buf[i+16];
                        else upsnr[3] = ' ';
                        upsnr[4] = 0;
                    }
    }
                    
    if( link_test == 0 ) link++;    // Test Link                
    lcd_gotoxy(8,0);    lcd_puts(upsnr);
    lcd_gotoxy(15,0);   lcd_puts(dnsnr);
    lcd_gotoxy(8,1);    lcd_puts(upstrm);
    lcd_gotoxy(15,1);   lcd_puts(dnstrm);
    recv(0, recv_buf, recv_size);
    temp = getSn_SR(0);   //read status
    if ( temp == SOCK_CLOSED ) break; 
}
while( link == 7 ); 
    
if ( temp == SOCK_CLOSED ){ close(0); delay_ms(10); goto REP; }
else goto STRT;
}
