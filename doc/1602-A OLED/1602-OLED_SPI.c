#include	<reg51.h>
#include 	<stdio.h>          
#include 	<INTRINS.H>       
#define  	Cword	16 
#define	one		0x80 							
#define	two		0xc0 
sbit		CS		=P3^6;
sbit	 	SCL	=P1^5;
sbit		SDI	=P1^7;
sbit		SDO	=P1^6;
sbit        sw1=P2^0;
sbit        sw2=P2^1;									  
unsigned char code MSG1[Cword]  =" SMIaIR display ";
unsigned char code MSG3[Cword]  ={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char code MSG4[Cword]  =" www.lcd-lcm.cn ";
unsigned char code MSG5[Cword]  ="ABCDEFGH01234567";
unsigned char code MSG6[Cword]  ={0xa7,0xa7,0xa7,0xa7,0xa7,0xa7,0xa7,0xa7,0xa7,0xa7,0xa7,0xa7,0xa7,0xa7,0xa7,0xa7};
unsigned char code CGRAM1[8] ={0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,};  
unsigned char code CGRAM2[8] ={0xff,0x11,0x11,0x11,0x11,0x11,0x11,0xff,}; 



//=================================
void WriteIns(unsigned char ins)
{
	unsigned char i;
	
	CS=0;
	SDI = 0; //RS = 0
	_nop_();
	SCL = 1;
	_nop_();
	SCL = 0;
	_nop_();
	SDI = 0; //RW = 0
	SCL = 1;
	_nop_();
	SCL = 0;

	 for (i=0x80;i;i>>=1)
	 {
	 	SDI = ins & i;

		SCL = 1;
		_nop_();
		SCL = 0;
	 }
     CS=1;	 
}
//=================================
void scan()
{
	while(sw2)
	{
		if(sw1 ==1)
		break;
	}
}
void WriteData(unsigned char dat)
{
	unsigned char i;
	
	 for (i=0x80;i;i>>=1)
	 {
	 	SDI = dat & i;

		SCL = 1;
		_nop_();
		SCL = 0;
	 }
}
//=================================
void WriteOneData(unsigned char dat)
{
	CS=0;
	SDI = 1; //RS = 1
	_nop_();
	SCL = 1;
	_nop_();
	SCL = 0;
	SDI = 0; //RW = 0
	_nop_();
	SCL = 1;
	_nop_();
	SCL = 0;

	WriteData(dat);
	CS=1;
}

//=================================
void WriteSerialData(unsigned char count,unsigned char * MSG)
{
	unsigned char  i;
	
	CS=0;
	SDI = 1; //RS = 1
	_nop_();
	SCL = 1;
	_nop_();
	SCL = 0;
	SDI = 0; //RW = 0
	_nop_();
	SCL = 1;
	_nop_();
	SCL = 0;

	for(i = 0; i<count;i++)
	{
		WriteData(MSG[i]);
	}
	CS=1;
}

//=================================
void Initial_ks0066(void)
{
	WriteIns(0x38);//function set
	WriteIns(0x06);//entry mode set
	WriteIns(0x02);
	WriteIns(0x01);//clear display
	WriteIns(0x0c);//display on
}
//============================================
//==================================
void delay(unsigned char m)
{
	unsigned char i,j,k;
	 for(j = 0;j<m;j++)
 	{
	 	for(k = 0; k<200;k++)
	 	{
			for(i = 0; i<100;i++)
			{
			}
		}
 	}	
}
//==================================
void CGRAM(void)
{
	WriteIns(0x40);    
					   	  
	WriteSerialData(8,CGRAM1);

	WriteIns(0x48);	   
					  	  
	WriteSerialData(8,CGRAM2);
}

void main(void)
{
	unsigned char i;
	
	SCL=0;
	Initial_ks0066();
	CGRAM();
	while(1)
	{
		
		CGRAM(); 
		WriteIns(one);
		WriteSerialData(Cword,MSG3);
		WriteIns(two);
		WriteSerialData(Cword,MSG3);
		delay(20);
		scan();


		WriteIns(one);
		for(i=0;i<16;i++)
		{
			WriteOneData(0x00);
		}
		
		WriteIns(two);
		for(i=0;i<16;i++)
		{
			WriteOneData(0x00);
		}
		delay(20);
		scan();

		/*WriteIns(one);
		for(i=0;i<16;i++)
		{
			WriteOneData(0x01);
		}
		
		WriteIns(two);
		for(i=0;i<16;i++)
		{
			WriteOneData(0x01);
		}
		delay(20);
		scan();*/
    WriteIns(one);
		WriteSerialData(Cword,MSG5);
		WriteIns(two);
		WriteSerialData(Cword,MSG5);
		delay(20);
		scan();

		
		WriteIns(one);
		WriteSerialData(Cword,MSG1);
		WriteIns(two);
		WriteSerialData(Cword,MSG1);
		delay(20);
		scan();

		WriteIns(one);
		WriteSerialData(Cword,MSG4);
		WriteIns(two);
		WriteSerialData(Cword,MSG4);
		delay(20);
		scan();
		
		/*
		WriteIns(one);
		WriteSerialData(Cword,MSG1);
		WriteIns(two);
		WriteSerialData(Cword,MSG1);
		delay(20);
		scan();
		*/	
		
	
	}	
}

