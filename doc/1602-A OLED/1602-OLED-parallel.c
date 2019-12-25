
 #include<reg52.h>
 #include<intrins.h>
 #define uchar unsigned char
 #define uint  unsigned	int
sbit RS=P3^0;    
sbit RWB=P3^7;    
sbit RDB=P3^4;     
sbit BF=P1^7;
sbit sw1=P2^0;
sbit sw2=P2^1;
uchar code string2[ ]={0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20};
uchar code string3[ ]={0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00};
uchar code string4[ ]={"ABCDEFGH01234567"};
uchar code string5[ ]={" SIMaIR display "};
uchar code string6[ ]={" www.lcd-lcm.cn "};
uchar code string1[ ]={0xA7,0xA7,0xA7,0xA7,0xA7,0xA7,0xA7,0xA7,0xA7,0xA7,0xA7,0xA7,0xA7,0xA7,0xA7,0xA7,0xA7,0xA7};
void delay(uint i)
{
  
   uchar j;
   while(i--)
   {
   	 for(j=0;j<125;j++)
	 {
	 }
   }
}
void scan()
{
	while(sw2)
	{
		if(sw1 ==1)
		break;
	}
}
 uchar BusyTest(void)
  {
    bit result;
	RS=0;       
    RDB=0;    
    _nop_();   
    _nop_();
    _nop_(); 
    _nop_();   	
    result=BF;  
	RDB=1;
    return result;
  }
  void WriteInstruction (uchar dictate)
{   
    while(BusyTest()==1); 
	 RS=0;                  
	 RWB=0;                      
                             
	 _nop_();
	 _nop_();             
	 P1=dictate;            
	 _nop_();
	 _nop_();
	 _nop_();
	 _nop_();              
	 RWB=1;                                   
 }
 void WriteAddress(uchar x)
 {
     WriteInstruction(x|0x80); 
 }

 void WriteData(uchar y)
 {
    while(BusyTest()==1);  
	  RS=1;                  
	  RWB=0;           
                       
	  P1=y;           
	  _nop_();
	  _nop_();
 	  _nop_();
     _nop_();       
	  RWB=1;                     
 }
 void cgram()
 {
	uchar m;
	for(m=0;m<8;m++)
	{
		WriteInstruction(0x40|m);
		WriteData(0x1f);
	}
	WriteInstruction(0x48);
	WriteData(0x1f);
	for(m=1;m<7;m++)
	{
		WriteInstruction(0x48|m);
		WriteData(0x11);
	
	}
	WriteInstruction(0x4f);
	WriteData(0x1f);
	for(m=0;m<8;m++)
	{
		if(m%2)
		{
			WriteInstruction(0x50|m);
			WriteData(0x15);
		}
		else
		{
			WriteInstruction(0x50|m);
			WriteData(0x0a);
		}
	
	}
 
 
 
 }

 uchar read()
 {
 	uchar A;
	while(BusyTest()==1);
	P1=0xff;  
	  RS=1;          
	  RDB=0;           
                       
	  A=P1;           
	  _nop_();
	  _nop_();
 	  _nop_();
     _nop_();       
	  RDB=1;          
 	 return A;
 
 
 }

 void Initiate()
{
   delay(15);
   WriteInstruction(0x01);
   delay(5);            
   WriteInstruction(0x38);
   delay(5);     
	WriteInstruction(0x38);
	delay(5);
	WriteInstruction(0x38);
	delay(5); 
	WriteInstruction(0x0c);
	delay(5);   
	WriteInstruction(0x06);
	delay(5);   
	WriteInstruction(0x01);
	delay(5);   
 }
void main()           
 {
  unsigned char i,j;
  Initiate();
  cgram();          
  delay(1); 
  WriteInstruction(0x01);
  while(1)
     {

		WriteAddress(0x00);  
	  	 for(i=0;i<20;i++)
		 {
		   WriteData(0x00);
		   
		 
		 }	 
		 WriteAddress(0x40);
		 for(i=0;i<20;i++)
		 {
		   WriteData(0x00);
		   
		 
		 }
		 delay(1000);
		 scan();
		 
		 
		/* j=read();	 	 
		WriteInstruction(0x01);	 
		 WriteAddress(0x00);  
	  	 for(i=0;i<20;i++)
		 {
		   WriteData(0x01);
		 
		 }	 
		 WriteAddress(0x40);
		 for(i=0;i<20;i++)
		 {
		   WriteData(0x01);
		 
		 }
		 delay(1000);
		 scan();*/
		 
		 /*WriteInstruction(0x01);	 
		 WriteAddress(0x00);  
	  	 for(i=0;i<20;i++)
		 {
		   WriteData(~j);
		 
		 }	 
		 WriteAddress(0x40);  
	  	 for(i=0;i<20;i++)
		 {
		   WriteData(~j);
		 
		 }
		 delay(1000);
		 scan();*/
		 /*WriteInstruction(0x01);
		 WriteAddress(0x00);  
	  	     i = 0;
		while(string6[i] != '\0')    
			{					
					WriteData(string6[i]);
					i++;
			}
			
		 WriteAddress(0x40);  
	  	     i = 0;
		while(string6[i] != '\0')   
			{						
					WriteData(string6[i]);
					i++;
			}
			delay(1000);
			scan();*/
			
		 WriteInstruction(0x01);	 	 
		 WriteAddress(0x00); 
	  	 for(i=0;i<20;i++)
		 {
		   WriteData(0x02);
		 
		 }	 
		 WriteAddress(0x40);
		 for(i=0;i<20;i++)
		 {
		   WriteData(0x02);
		 
		 }
		 delay(1000);
		 scan();
		 
		 WriteInstruction(0x01);	 	 
		 WriteAddress(0x00); 
	  	 for(i=0;i<20;i++)
		 {
		   WriteData(string4[i]);
		 
		 }	 
		 WriteAddress(0x40);
		 for(i=0;i<20;i++)
		 {
		   WriteData(string4[i]);
		 
		 }
		 delay(1000);
		 scan();

		 WriteInstruction(0x01);	 	 
		 WriteAddress(0x00); 
	  	 for(i=0;i<20;i++)
		 {
		   WriteData(string5[i]);
		 
		 }	 
		 WriteAddress(0x40);
		 for(i=0;i<20;i++)
		 {
		   WriteData(string5[i]);
		 
		 }
		 delay(1000);
		 scan();	 	 
				
			 WriteInstruction(0x01);
		 WriteAddress(0x00);  
	  	     i = 0;
		while(string6[i] != '\0')    
			{					
					WriteData(string6[i]);
					i++;
			}
			
		 WriteAddress(0x40);  
	  	     i = 0;
		while(string6[i] != '\0')   
			{						
					WriteData(string6[i]);
					i++;
			}
			delay(1000);
			scan();
	 
		}
			  
		
}
