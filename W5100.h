/*
file        W5100.h
MOHAMAD SAJJADI 2010.10.05

Define number of your sockets and COMMON_BASE address in your program first!
#define COMMON_BASE 0x????
#define MAX_SOCK_NUM ?

*/


typedef char SOCKET;

static char         I_STATUS[MAX_SOCK_NUM];
static unsigned int SMASK[MAX_SOCK_NUM]; /**< Variable for Tx buffer MASK in each channel */
static unsigned int RMASK[MAX_SOCK_NUM]; /**< Variable for Rx buffer MASK in each channel */
static unsigned int SSIZE[MAX_SOCK_NUM]; /**< Max Tx buffer size by each channel */
static unsigned int RSIZE[MAX_SOCK_NUM]; /**< Max Rx buffer size by each channel */
static unsigned int SBUFBASEADDRESS[MAX_SOCK_NUM]; /**< Tx buffer base address by each channel */
static unsigned int RBUFBASEADDRESS[MAX_SOCK_NUM]; /**< Rx buffer base address by each channel */
static unsigned int local_port;

#pragma used+
char getISR(char s)
{
    return I_STATUS[s];
}

void putISR(SOCKET s, char val)
{
   I_STATUS[s] = val;
}

unsigned int getIINCHIP_RxMAX(SOCKET s)
{
   return RSIZE[s];
}
unsigned int getIINCHIP_TxMAX(SOCKET s)
{
   return SSIZE[s];
}
unsigned int getIINCHIP_RxMASK(SOCKET s)
{
   return RMASK[s];
}
unsigned int getIINCHIP_TxMASK(SOCKET s)
{
   return SMASK[s];
}
unsigned int getIINCHIP_RxBASE(SOCKET s)
{
   return RBUFBASEADDRESS[s];
}
unsigned int getIINCHIP_TxBASE(SOCKET s)
{
   return SBUFBASEADDRESS[s];
}
#pragma used-

// Mode Register address
#define MR                  (COMMON_BASE + 0x0000)

// Gateway IP Register address
#define GAR0                (COMMON_BASE + 0x0001)

// Subnet mask Register address
#define SUBR0               (COMMON_BASE + 0x0005)

// Source MAC Register address
#define SHAR0               (COMMON_BASE + 0x0009)

// Source IP Register address
#define SIPR0               (COMMON_BASE + 0x000F)

// Interrupt Register
#define IR                  (COMMON_BASE + 0x0015)

// Interrupt mask register
#define IMR                 (COMMON_BASE + 0x0016)

// Timeout register address( 1 is 100us )
#define RTR0                (COMMON_BASE + 0x0017)

// Retry count reigster
#define RCR                 (COMMON_BASE + 0x0019)

// Receive memory size reigster
#define RMSR                (COMMON_BASE + 0x001A)

// Transmit memory size reigster
#define TMSR                (COMMON_BASE + 0x001B)

// Authentication type register address in PPPoE mode
#define PATR0               (COMMON_BASE + 0x001C)

//#define PPPALGO           (COMMON_BASE + 0x001D)
#define PTIMER              (COMMON_BASE + 0x0028)
#define PMAGIC              (COMMON_BASE + 0x0029)

// Unreachable IP register address in UDP mode
#define UIPR0               (COMMON_BASE + 0x002A)

// Unreachable Port register address in UDP mode
#define UPORT0              (COMMON_BASE + 0x002E)


// socket register
#define CH_BASE             (COMMON_BASE + 0x0400)

// size of each channel register map
#define CH_SIZE        0x0100

// socket Mode register
#define Sn_MR(ch)           (CH_BASE + (ch * CH_SIZE) + 0x0000)

// channel Sn_CR register
#define Sn_CR(ch)           (CH_BASE + (ch * CH_SIZE) + 0x0001)

// channel interrupt register
#define Sn_IR(ch)           (CH_BASE + (ch * CH_SIZE) + 0x0002)

// channel status register
#define Sn_SR(ch)           (CH_BASE + (ch * CH_SIZE) + 0x0003)

// source port register
#define Sn_PORT0(ch)        (CH_BASE + (ch * CH_SIZE) + 0x0004)

// Peer MAC register address
#define Sn_DHAR0(ch)        (CH_BASE + (ch * CH_SIZE) + 0x0006)

// Peer IP register address
#define Sn_DIPR0(ch)        (CH_BASE + (ch * CH_SIZE) + 0x000C)

// Peer port register address
#define Sn_DPORT0(ch)       (CH_BASE + (ch * CH_SIZE) + 0x0010)

// Maximum Segment Size(Sn_MSSR0) register address
#define Sn_MSSR0(ch)        (CH_BASE + (ch * CH_SIZE) + 0x0012)

// Protocol of IP Header field register in IP raw mode
#define Sn_PROTO(ch)        (CH_BASE + (ch * CH_SIZE) + 0x0014)

// IP Type of Service(TOS) Register 
#define Sn_TOS(ch)          (CH_BASE + (ch * CH_SIZE) + 0x0015)

// IP Time to live(TTL) Register 
#define Sn_TTL(ch)          (CH_BASE + (ch * CH_SIZE) + 0x0016)

// Transmit free memory size register
#define Sn_TX_FSR0(ch)      (CH_BASE + (ch * CH_SIZE) + 0x0020)

// Transmit memory read pointer register address
#define Sn_TX_RD0(ch)       (CH_BASE + (ch * CH_SIZE) + 0x0022)

// Transmit memory write pointer register address
#define Sn_TX_WR0(ch)       (CH_BASE + (ch * CH_SIZE) + 0x0024)

// Received data size register
#define Sn_RX_RSR0(ch)      (CH_BASE + (ch * CH_SIZE) + 0x0026)

// Read point of Receive memory
#define Sn_RX_RD0(ch)       (CH_BASE + (ch * CH_SIZE) + 0x0028)

// Write point of Receive memory
#define Sn_RX_WR0(ch)       (CH_BASE + (ch * CH_SIZE) + 0x002A)



/* MODE register values */
#define MR_RST            0x80   /**< reset */
#define MR_PB             0x10   /**< ping block */
#define MR_PPPOE          0x08   /**< enable pppoe */
#define MR_LB             0x04   /**< little or big endian selector in indirect mode */
#define MR_AI             0x02   /**< auto-increment in indirect mode */
#define MR_IND            0x01   /**< enable indirect mode */

/* IR register values */
#define IR_CONFLICT       0x80          /**< check ip confict */
#define IR_UNREACH        0x40          /**< get the destination unreachable message in UDP sending */
#define IR_PPPoE          0x20          /**< get the PPPoE close message */
#define IR_SOCK(ch)      (0x01 << ch)   /**< check socket interrupt */

/* Sn_MR values */
#define Sn_MR_CLOSE         0x00        /**< unused socket */
#define Sn_MR_TCP           0x01        /**< TCP */
#define Sn_MR_UDP           0x02        /**< UDP */
#define Sn_MR_IPRAW         0x03        /**< IP LAYER RAW SOCK */
#define Sn_MR_MACRAW        0x04        /**< MAC LAYER RAW SOCK */
#define Sn_MR_PPPOE         0x05        /**< PPPoE */
#define Sn_MR_ND            0x20        /**< No Delayed Ack(TCP) flag */
#define Sn_MR_MULTI         0x80        /**< support multicating */


/* Sn_CR values */
#define Sn_CR_OPEN          0x01        /**< initialize or open socket */
#define Sn_CR_LISTEN        0x02        /**< wait connection request in tcp mode(Server mode) */
#define Sn_CR_CONNECT       0x04        /**< send connection request in tcp mode(Client mode) */
#define Sn_CR_DISCON        0x08        /**< send closing reqeuset in tcp mode */
#define Sn_CR_CLOSE         0x10        /**< close socket */
#define Sn_CR_SEND          0x20        /**< updata txbuf pointer, send data */
#define Sn_CR_SEND_MAC      0x21        /**< send data with MAC address, so without ARP process */
#define Sn_CR_SEND_KEEP     0x22        /**<  send keep alive message */
#define Sn_CR_RECV          0x40        /**< update rxbuf pointer, recv data */

#ifdef __DEF_IINCHIP_PPP__
    #define Sn_CR_PCON                   0x23         
    #define Sn_CR_PDISCON                0x24         
    #define Sn_CR_PCR                    0x25         
    #define Sn_CR_PCN                    0x26        
    #define Sn_CR_PCJ                    0x27        
#endif

/* Sn_IR values */
#ifdef __DEF_IINCHIP_PPP__
    #define Sn_IR_PRECV            0x80        
    #define Sn_IR_PFAIL            0x40        
    #define Sn_IR_PNEXT            0x20        
#endif
#define Sn_IR_SEND_OK              0x10        /**< complete sending */
#define Sn_IR_TIMEOUT              0x08        /**< assert timeout */
#define Sn_IR_RECV                 0x04        /**< receiving data */
#define Sn_IR_DISCON               0x02        /**< closed socket */
#define Sn_IR_CON                  0x01        /**< established connection */

/* Sn_SR values */
#define SOCK_CLOSED                0x00        /**< closed */
#define SOCK_INIT                  0x13        /**< init state */
#define SOCK_LISTEN                0x14        /**< listen state */
#define SOCK_SYNSENT               0x15        /**< connection state */
#define SOCK_SYNRECV               0x16        /**< connection state */
#define SOCK_ESTABLISHED           0x17        /**< success to connect */
#define SOCK_FIN_WAIT              0x18        /**< closing state */
#define SOCK_CLOSING               0x1A        /**< closing state */
#define SOCK_TIME_WAIT             0x1B        /**< closing state */
#define SOCK_CLOSE_WAIT            0x1C        /**< closing state */
#define SOCK_LAST_ACK              0x1D        /**< closing state */
#define SOCK_UDP                   0x22        /**< udp socket */
#define SOCK_IPRAW                 0x32        /**< ip raw mode socket */
#define SOCK_MACRAW                0x42        /**< mac raw mode socket */
#define SOCK_PPPOE                 0x5F        /**< pppoe socket */

/* IP PROTOCOL */
#define IPPROTO_IP              0           /**< Dummy for IP */
#define IPPROTO_ICMP            1           /**< Control message protocol */
#define IPPROTO_IGMP            2           /**< Internet group management protocol */
#define IPPROTO_GGP             3           /**< Gateway^2 (deprecated) */
#define IPPROTO_TCP             6           /**< TCP */
#define IPPROTO_PUP             12          /**< PUP */
#define IPPROTO_UDP             17          /**< UDP */
#define IPPROTO_IDP             22          /**< XNS idp */
#define IPPROTO_ND              77          /**< UNOFFICIAL net disk protocol */
#define IPPROTO_RAW             255         /**< Raw IP packet */

#pragma used+
//---------------------------------------------------------------
// W5100 Functions
//---------------------------------------------------------------
// This function writes the data into W5100 registers
void IINCHIP_WRITE(unsigned int addr,char data)
{
    PORTB.4 = 0;    // Set SS Low
    spi(0xF0);
    spi((addr & 0xFF00) >> 8);
    spi(addr & 0x00FF);
    spi(data);
    PORTB.4 = 1;    // Set SS High
}

//---------------------------------------------------------------
// This function reads the value from W5100 registers
char IINCHIP_READ(unsigned int addr)
{
    char data;
    PORTB.4 = 0;    // Set SS Low
    spi(0x0F);
    spi((addr & 0xFF00) >> 8);
    spi(addr & 0x00FF);    
    data = spi(0);
    PORTB.4 = 1;    // Set SS High
    return data;
}
//---------------------------------------------------------------
// This function writes into W5100 memory(Buffer)
unsigned int wiz_write_buf(unsigned int addr,char* buf,unsigned int len)
{
    unsigned int idx = 0;
    for(idx=0;idx<len;idx++)
    {
        PORTB.4 = 0;    // Set SS Low
        spi(0xF0);
        spi(((addr+idx) & 0xFF00) >> 8);
        spi((addr+idx) & 0x00FF);
        spi(buf[idx]);
        PORTB.4 = 1;    // Set SS High
    }
    return len;
}
//---------------------------------------------------------------
// This function reads from W5100 memory(Buffer)
unsigned int wiz_read_buf(unsigned int addr, char* buf,unsigned int len)
{
    unsigned int idx = 0;
    for (idx=0; idx<len; idx++)
    {
        PORTB.4 = 0;    // Set SS Low 
        spi(0x0F);
        spi(((addr+idx) & 0xFF00) >> 8);
        spi((addr+idx) & 0x00FF);
        buf[idx] = spi(0);
        PORTB.4 = 1;    // Set SS High       
    }
    return len;
}
//---------------------------------------------------------------
/*This function set the transmit & receive buffer size as per the channels is used

Note for TMSR and RMSR bits are as follows
bit 1-0 : memory size of channel #0 
bit 3-2 : memory size of channel #1 
bit 5-4 : memory size of channel #2 
bit 7-6 : memory size of channel #3 
Maximum memory size for Tx, Rx in the W5100 is 8K Bytes,
In the range of 8KBytes, the memory size could be allocated dynamically by each channel.
Be attentive to sum of memory size shouldn't exceed 8Kbytes
and to data transmission and receiption from non-allocated channel may cause some problems.
If the 8KBytes memory is already  assigned to centain channel, 
other 3 channels couldn't be used, for there's no available memory.
If two 4KBytes memory are assigned to two each channels, 
other 2 channels couldn't be used, for there's no available memory.
tx_size Tx memory size (00 - 1KByte, 01- 2KBtye, 10 - 4KByte, 11 - 8KByte)
rx_size Rx memory size (00 - 1KByte, 01- 2KBtye, 10 - 4KByte, 11 - 8KByte)
*/ 
void sysinit(char tx_size, char rx_size)
{
	int i;
	int ssum = 0;
	int rsum = 0;
	IINCHIP_WRITE(TMSR,tx_size);    /* Set Tx memory size for each channel */
	IINCHIP_WRITE(RMSR,rx_size);	/* Set Rx memory size for each channel */
	SBUFBASEADDRESS[0] = (unsigned int)(0x4000);	/* Set base address of Tx memory for channel #0 */
	RBUFBASEADDRESS[0] = (unsigned int)(0x6000);	/* Set base address of Rx memory for channel #0 */
    for (i = 0 ; i < MAX_SOCK_NUM; i++)       // Set the size, masking and base address of Tx & Rx memory by each channel
	{
		SSIZE[i] = (int)(0);
		RSIZE[i] = (int)(0);
		if (ssum < 8192)
		{
         switch((tx_size >> i*2) & 0x03)  // Set Tx memory size
			{
			case 0:
				SSIZE[i] = (int)(1024);
				SMASK[i] = (unsigned int)(0x03FF);
				break;
			case 1:
				SSIZE[i] = (int)(2048);
				SMASK[i] = (unsigned int)(0x07FF);
				break;
			case 2:
				SSIZE[i] = (int)(4096);
				SMASK[i] = (unsigned int)(0x0FFF);
				break;
			case 3:
				SSIZE[i] = (int)(8192);
				SMASK[i] = (unsigned int)(0x1FFF);
				break;
			}
		}
		if (rsum < 8192)
		{
         switch((rx_size >> i*2) & 0x03)     // Set Rx memory size
			{
			case 0:
				RSIZE[i] = (int)(1024);
				RMASK[i] = (unsigned int)(0x03FF);
				break;
			case 1:
				RSIZE[i] = (int)(2048);
				RMASK[i] = (unsigned int)(0x07FF);
				break;
			case 2:
				RSIZE[i] = (int)(4096);
				RMASK[i] = (unsigned int)(0x0FFF);
				break;
			case 3:
				RSIZE[i] = (int)(8192);
				RMASK[i] = (unsigned int)(0x1FFF);
				break;
			}
		}
		ssum += SSIZE[i];
		rsum += RSIZE[i];
        if (i != 0)             // Sets base address of Tx and Rx memory for channel #1,#2,#3
		{
			SBUFBASEADDRESS[i] = SBUFBASEADDRESS[i-1] + SSIZE[i-1];
			RBUFBASEADDRESS[i] = RBUFBASEADDRESS[i-1] + RSIZE[i-1];
		}
	}
}
//---------------------------------------------------------------
// This function sets the MR register
void setMR(char val)
{
	IINCHIP_WRITE(MR,val);
}
//---------------------------------------------------------------
// This function writes gateway IP address
void setGAR(flash char * addr)
{
    IINCHIP_WRITE((GAR0 + 0),addr[0]);
    IINCHIP_WRITE((GAR0 + 1),addr[1]);
    IINCHIP_WRITE((GAR0 + 2),addr[2]);
    IINCHIP_WRITE((GAR0 + 3),addr[3]);
}
//---------------------------------------------------------------
// This function reads gateway IP address
void getGWIP(char * addr)
{
    addr[0] = IINCHIP_READ((GAR0 + 0));
    addr[1] = IINCHIP_READ((GAR0 + 1));
    addr[2] = IINCHIP_READ((GAR0 + 2));
    addr[3] = IINCHIP_READ((GAR0 + 3));
}
//---------------------------------------------------------------
// This function sets up SubnetMask address
void setSUBR(flash char * addr)
{
    IINCHIP_WRITE((SUBR0 + 0),addr[0]);
    IINCHIP_WRITE((SUBR0 + 1),addr[1]);
    IINCHIP_WRITE((SUBR0 + 2),addr[2]);
    IINCHIP_WRITE((SUBR0 + 3),addr[3]);
}
//---------------------------------------------------------------
// This function sets up MAC address
void setSHAR(flash char * addr)
{
    IINCHIP_WRITE((SHAR0 + 0),addr[0]);
    IINCHIP_WRITE((SHAR0 + 1),addr[1]);
    IINCHIP_WRITE((SHAR0 + 2),addr[2]);
    IINCHIP_WRITE((SHAR0 + 3),addr[3]);
    IINCHIP_WRITE((SHAR0 + 4),addr[4]);
    IINCHIP_WRITE((SHAR0 + 5),addr[5]);
}
//---------------------------------------------------------------
// This function sets up Source IP address
void setSIPR(flash char * addr)
{
	IINCHIP_WRITE((SIPR0 + 0),addr[0]);
	IINCHIP_WRITE((SIPR0 + 1),addr[1]);
	IINCHIP_WRITE((SIPR0 + 2),addr[2]);
	IINCHIP_WRITE((SIPR0 + 3),addr[3]);
}
//---------------------------------------------------------------
// This function gets Interrupt register in common register
char getIR( void )
{
   return IINCHIP_READ(IR);
}
//---------------------------------------------------------------
// This function sets up Retransmission time
void setRTR(unsigned int timeout)
{
	IINCHIP_WRITE(RTR0,(char)((timeout & 0xff00) >> 8));
	IINCHIP_WRITE((RTR0 + 1),(char)(timeout & 0x00ff));
}
//---------------------------------------------------------------
// This function sets the number of Retransmission
void setRCR(char retry)
{
	IINCHIP_WRITE(RCR,retry);
}
//---------------------------------------------------------------
// This function sets the interrupt mask: Enable/Disable appropriate Interrupt
void setIMR(char mask)
{
	IINCHIP_WRITE(IMR,mask);
}
//---------------------------------------------------------------
// This function gets the Gateway IP address
void getGAR(char * addr)
{
	addr[0] = IINCHIP_READ(GAR0);
	addr[1] = IINCHIP_READ(GAR0+1);
	addr[2] = IINCHIP_READ(GAR0+2);
	addr[3] = IINCHIP_READ(GAR0+3);
}
//---------------------------------------------------------------
// This function gets the SubnetMask address
void getSUBR(char * addr)
{
	addr[0] = IINCHIP_READ(SUBR0);
	addr[1] = IINCHIP_READ(SUBR0+1);
	addr[2] = IINCHIP_READ(SUBR0+2);
	addr[3] = IINCHIP_READ(SUBR0+3);
}
//---------------------------------------------------------------
// This function gets the Source Hardware Address (MAC Address)
void getSHAR(char * addr)
{
	addr[0] = IINCHIP_READ(SHAR0);
	addr[1] = IINCHIP_READ(SHAR0+1);
	addr[2] = IINCHIP_READ(SHAR0+2);
	addr[3] = IINCHIP_READ(SHAR0+3);
	addr[4] = IINCHIP_READ(SHAR0+4);
	addr[5] = IINCHIP_READ(SHAR0+5);
}
//---------------------------------------------------------------
// This function gets the Source IP address
void getSIPR(char * addr)
{
	addr[0] = IINCHIP_READ(SIPR0);
	addr[1] = IINCHIP_READ(SIPR0+1);
	addr[2] = IINCHIP_READ(SIPR0+2);
	addr[3] = IINCHIP_READ(SIPR0+3);
}
//---------------------------------------------------------------
// This function gets the Destination Hardware Address (MAC Address)
void getSn_DHAR(SOCKET s, char * addr)
{
	addr[0] = IINCHIP_READ(Sn_DHAR0(s));
	addr[1] = IINCHIP_READ(Sn_DHAR0(s)+1);
	addr[2] = IINCHIP_READ(Sn_DHAR0(s)+2);
	addr[3] = IINCHIP_READ(Sn_DHAR0(s)+3);
	addr[4] = IINCHIP_READ(Sn_DHAR0(s)+4);
	addr[5] = IINCHIP_READ(Sn_DHAR0(s)+5);
}
//---------------------------------------------------------------
// This function sets the Destination Hardware Address (MAC Address)
void setSn_DHAR(SOCKET s, flash char * addr)
{
	IINCHIP_WRITE((Sn_DHAR0(s) + 0),addr[0]);
	IINCHIP_WRITE((Sn_DHAR0(s) + 1),addr[1]);
	IINCHIP_WRITE((Sn_DHAR0(s) + 2),addr[2]);
	IINCHIP_WRITE((Sn_DHAR0(s) + 3),addr[3]);
	IINCHIP_WRITE((Sn_DHAR0(s) + 4),addr[4]);
	IINCHIP_WRITE((Sn_DHAR0(s) + 5),addr[5]);
}
//---------------------------------------------------------------
// This function gets the Destination IP address
void getSn_DIPR(SOCKET s, char * addr)
{
	addr[0] = IINCHIP_READ(Sn_DIPR0(s));
	addr[1] = IINCHIP_READ(Sn_DIPR0(s)+1);
	addr[2] = IINCHIP_READ(Sn_DIPR0(s)+2);
	addr[3] = IINCHIP_READ(Sn_DIPR0(s)+3);
}
//---------------------------------------------------------------
// This function sets the Destination IP address
void setSn_DIPR(SOCKET s, flash char * addr)
{
	IINCHIP_WRITE((Sn_DIPR0(s) + 0),addr[0]);
	IINCHIP_WRITE((Sn_DIPR0(s) + 1),addr[1]);
	IINCHIP_WRITE((Sn_DIPR0(s) + 2),addr[2]);
	IINCHIP_WRITE((Sn_DIPR0(s) + 3),addr[3]);
}
//---------------------------------------------------------------
// This function gets the Destination Port
void getSn_DPORT(SOCKET s, char * addr)
{
	addr[0] = IINCHIP_READ(Sn_DPORT0(s));
	addr[1] = IINCHIP_READ(Sn_DPORT0(s)+1);
}
//---------------------------------------------------------------
// This function sets the Destination Port
void setSn_DPORT(SOCKET s, char * addr)
{
	IINCHIP_WRITE((Sn_DPORT0(s) + 0),addr[0]);
	IINCHIP_WRITE((Sn_DPORT0(s) + 1),addr[1]);
}
//---------------------------------------------------------------
// This function sets the maximum segment size of TCP in Active Mode, while in Passive Mode this is set by peer
void setSn_MSS(SOCKET s, unsigned int Sn_MSSR0)
{
	IINCHIP_WRITE(Sn_MSSR0(s),(char)((Sn_MSSR0 & 0xff00) >> 8));
	IINCHIP_WRITE((Sn_MSSR0(s) + 1),(char)(Sn_MSSR0 & 0x00ff));
}
//---------------------------------------------------------------
// This function sets the TTL of socket(s)
void setSn_TTL(SOCKET s, char ttl)
{
   IINCHIP_WRITE(Sn_TTL(s), ttl);
}
//---------------------------------------------------------------
// This function sets up the Protocol Field of IP Header when executing the IP Layer RAW mode
void setSn_PROTO(SOCKET s, char proto)
{
	IINCHIP_WRITE(Sn_PROTO(s),proto);
}
//---------------------------------------------------------------
// This function gets the socket(s) interrupt status
char getSn_IR(SOCKET s)
{
   return IINCHIP_READ(Sn_IR(s));
}
//---------------------------------------------------------------
// This function gets socket(s) status
char getSn_SR(SOCKET s)
{
   return IINCHIP_READ(Sn_SR(s));
}
//---------------------------------------------------------------
// This function gets socket(s) TX free buf size
unsigned int getSn_TX_FSR(SOCKET s)
{
	unsigned int val=0,val1=0;
	do
	{
		val1 = IINCHIP_READ(Sn_TX_FSR0(s));
		val1 = (val1 << 8) + IINCHIP_READ(Sn_TX_FSR0(s) + 1);
        if (val1 != 0)
        {
            val = IINCHIP_READ(Sn_TX_FSR0(s));
            val = (val << 8) + IINCHIP_READ(Sn_TX_FSR0(s) + 1);
        }
	} while (val != val1);
   return val;
}
//---------------------------------------------------------------
// This function gets socket(S) RX recv buf size
unsigned int getSn_RX_RSR(SOCKET s)
{
	unsigned int val=0,val1=0;
	do
	{
		val1 = IINCHIP_READ(Sn_RX_RSR0(s));
		val1 = (val1 << 8) + IINCHIP_READ(Sn_RX_RSR0(s) + 1);
        if(val1 != 0)
		{
   			val = IINCHIP_READ(Sn_RX_RSR0(s));
   			val = (val << 8) + IINCHIP_READ(Sn_RX_RSR0(s) + 1);
		}
	} while (val != val1);
   return val;
}
//---------------------------------------------------------------
// This function is	for copy the data form application buffer to Transmite buffer of the chip
void write_data(SOCKET s, volatile char * src, volatile char * dst, unsigned int len)
{
	unsigned int size;
	unsigned int dst_mask;
	char * dst_ptr;
	dst_mask = (unsigned int)dst & getIINCHIP_TxMASK(s);
	dst_ptr = (char *)(getIINCHIP_TxBASE(s) + dst_mask);
    if (dst_mask + len > getIINCHIP_TxMAX(s)) 
	{
		size = getIINCHIP_TxMAX(s) - dst_mask;
		wiz_write_buf((unsigned int)dst_ptr, (char*) src, size);
		src += size;
		size = len - size;
		dst_ptr = (char *)(getIINCHIP_TxBASE(s));
		wiz_write_buf((unsigned int)dst_ptr, (char*) src, size);
	} 
	else
	{
		wiz_write_buf((unsigned int)dst_ptr, (char*) src, len);
	}
}
//---------------------------------------------------------------
// This function is being used for copy the data form Receive buffer of the chip to application buffer
void read_data(SOCKET s, volatile char * src, volatile char * dst, unsigned int len)
{
	unsigned int size;
	unsigned int src_mask;
	char * src_ptr;
	src_mask = (unsigned int)src & getIINCHIP_RxMASK(s);
	src_ptr = (char *)(getIINCHIP_RxBASE(s) + src_mask);
    if( (src_mask + len) > getIINCHIP_RxMAX(s) ) 
	{
		size = getIINCHIP_RxMAX(s) - src_mask;
		wiz_read_buf((unsigned int)src_ptr, (char*) dst,size);
		dst += size;
		size = len - size;
		src_ptr = (char *)(getIINCHIP_RxBASE(s));
		wiz_read_buf((unsigned int)src_ptr, (char*) dst,size);
	} 
	else
	{
		wiz_read_buf((unsigned int)src_ptr, (char*) dst,len);
	}
}
//---------------------------------------------------------------
// This function is being called by send() and sendto() function also 
void send_data_processing(SOCKET s, char *data, unsigned int len)
{
	unsigned int ptr;
	ptr = IINCHIP_READ(Sn_TX_WR0(s));
	ptr = ((ptr & 0x00ff) << 8) + IINCHIP_READ(Sn_TX_WR0(s) + 1);
	write_data(s, data, (char *)(ptr), len);
	ptr += len;
	IINCHIP_WRITE(Sn_TX_WR0(s),(char)((ptr & 0xff00) >> 8));
	IINCHIP_WRITE((Sn_TX_WR0(s) + 1),(char)(ptr & 0x00ff));
}
//---------------------------------------------------------------
// This function is being called by recv()
void recv_data_processing(SOCKET s, char *data, unsigned int len)
{
	unsigned int ptr;
	ptr = IINCHIP_READ(Sn_RX_RD0(s));
	ptr = ((ptr & 0x00ff) << 8) + IINCHIP_READ(Sn_RX_RD0(s) + 1);
	read_data(s, (char *)ptr, data, len); // read data
	ptr += len;
	IINCHIP_WRITE(Sn_RX_RD0(s),(char)((ptr & 0xff00) >> 8));
	IINCHIP_WRITE((Sn_RX_RD0(s) + 1),(char)(ptr & 0x00ff));
}
//---------------------------------------------------------------
// This function close the socket(s)
void close(SOCKET s)
{
	IINCHIP_WRITE(Sn_CR(s),Sn_CR_CLOSE);
	while( IINCHIP_READ(Sn_CR(s)) );
}
//---------------------------------------------------------------
// This Socket function initialize the channel in perticular mode, and set the port and wait for W5100 done it  
char socket(SOCKET s, char protocol, unsigned int port, char flag)
{
	char ret;
	if ( protocol == Sn_MR_TCP )
	{
		close(s);
		IINCHIP_WRITE(Sn_MR(s),protocol | flag);
		if (port != 0) 
        {
			IINCHIP_WRITE(Sn_PORT0(s),(char)((port & 0xff00) >> 8));
			IINCHIP_WRITE((Sn_PORT0(s) + 1),(char)(port & 0x00ff));
		} 
        else 
        {
			local_port++;
			IINCHIP_WRITE(Sn_PORT0(s),(char)((local_port & 0xff00) >> 8));
			IINCHIP_WRITE((Sn_PORT0(s) + 1),(char)(local_port & 0x00ff));
		}
		IINCHIP_WRITE(Sn_CR(s),Sn_CR_OPEN);
		while( IINCHIP_READ(Sn_CR(s)) );
		ret = 1;
	}
	else ret = 0;
	return ret;
}
//---------------------------------------------------------------
// This function established  the connection for the channel in passive (server) mode. This function waits for the request from the peer
char listen(SOCKET s)
{
	char ret;
	if (IINCHIP_READ(Sn_SR(s)) == SOCK_INIT)
	{
		IINCHIP_WRITE(Sn_CR(s),Sn_CR_LISTEN);
		while( IINCHIP_READ(Sn_CR(s)) );
		ret = 1;
	}
	else ret = 0;
	return ret;
}
//---------------------------------------------------------------
// This function established  the connection for the channel in Active (client) mode 
// This function waits untill the connection is established
char connect(SOCKET s, flash char * addr, unsigned int port)
{
	char ret;
    // set destination IP
    IINCHIP_WRITE(Sn_DIPR0(s),addr[0]);
    IINCHIP_WRITE((Sn_DIPR0(s) + 1),addr[1]);
    IINCHIP_WRITE((Sn_DIPR0(s) + 2),addr[2]);
    IINCHIP_WRITE((Sn_DIPR0(s) + 3),addr[3]);
    IINCHIP_WRITE(Sn_DPORT0(s),(char)((port & 0xff00) >> 8));
    IINCHIP_WRITE((Sn_DPORT0(s) + 1),(char)(port & 0x00ff));
    IINCHIP_WRITE(Sn_CR(s),Sn_CR_CONNECT);
    while ( IINCHIP_READ(Sn_CR(s)) ); 
    ret = 1;
	return ret;
}
//---------------------------------------------------------------
// This function used for disconnect the socket and parameter is "s" which represent the socket number
void disconnect(SOCKET s)
{
	IINCHIP_WRITE(Sn_CR(s),Sn_CR_DISCON);
	while( IINCHIP_READ(Sn_CR(s)) );
}
//---------------------------------------------------------------
// This function used to send the data in TCP mode  
unsigned int send(SOCKET s, const char * buf, unsigned int len)
{
	char status=0;
	unsigned int ret=0;
	unsigned int freesize=0;
    if (len > getIINCHIP_TxMAX(s)) ret = getIINCHIP_TxMAX(s);
    else ret = len;
	do 
	{
		freesize = getSn_TX_FSR(s);
		status = IINCHIP_READ(Sn_SR(s));
		if ((status != SOCK_ESTABLISHED) && (status != SOCK_CLOSE_WAIT))
		{
			ret = 0; 
			break;
		}
	}
    while (freesize < ret);
	send_data_processing(s, (char *)buf, ret);
	IINCHIP_WRITE(Sn_CR(s),Sn_CR_SEND);
	while( IINCHIP_READ(Sn_CR(s)) );	
  	return ret;
}
//---------------------------------------------------------------
// This function is an application I/F function which is used to receive the data in TCP mode
// It continues to wait for data as much as the application wants to receive
unsigned int recv(SOCKET s, char * buf, unsigned int len)
{
	unsigned int ret=0;
	if ( len > 0 )
	{
		recv_data_processing(s, buf, len);
		IINCHIP_WRITE(Sn_CR(s),Sn_CR_RECV);
		while( IINCHIP_READ(Sn_CR(s)) );
		ret = len;
	}
	return ret;
}
//---------------------------------------------------------------
// This function used to send the flash data in TCP mode 
void send_flash( SOCKET s, flash char * buf, unsigned int len )
{
	int i;
    char temp[len];
    for( i = 0 ; i < len ; i++ )temp[i] = *buf++;
	send(0,temp,len);
}
//---------------------------------------------------------------
#pragma used-
