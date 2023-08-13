#include<reg51.h>
sbit rs=P1^0;
sbit rw=P1^1;
sbit en=P1^2;
unsigned int msec=0;
unsigned int sec=0;
unsigned int min=24;
unsigned int day=1;
int c;
unsigned char ch1[3]="MON";

void changedisp();
void lcdcmd(unsigned char);
void intdisplay(unsigned int);
void lcddata(unsigned char);
void valuedisplay(unsigned char);
 int hour=10;
int a=5;
int i1=0;
unsigned char ch[2];
unsigned int r;
void delay()
{unsigned int i;
	for(i=0;i<12000;++i);
}
void timerinterrupt (void) interrupt 1
{
	TR0=0;
	msec++;
	if(msec>=1000)
	{ 
		sec++;
		c++;
		if(c==27)
		{	sec=sec+2;
		   c=0;}
		msec=0;
		//lcdcmd(0x86);
		//intdisplay(sec);
		

	}
	if(sec>=60)
	{min++;
		sec=0;
		lcdcmd(0x01);
		
		

	}
	if(min==60)
	{hour++;
		min=0;

	}
	if(hour==24)
	{day=day+1;
		hour=0;

	}
	
	TF0=0;
	TH0=0xFC;
	TL0=0x66;
	TR0=1;
	
}
void timer1()
{
	TMOD=0x01;
TH0=0XFC;
TL0=0X66;
EA=1;
ET0=1;
TR0=1;
}	
void lcdcmd(unsigned char value)
{P2=value;
rs=0;
rw=0;
en=1;
delay();
en=0;
}

void lcddata(unsigned char value)
{P2=value;
rs=1;
rw=0;
en=1;
delay();
en=0;
}

void intdisplay(unsigned int value)
{
	i1=0;
	if(value==0)
	{lcddata('0');}
	while(value>0)
	{
		r=value%10;
		ch[i1]=(char)(r+48);
		value=value/10;
		i1++;
	}
	i1--;
	while(i1>=0)
	{lcddata(ch[i1]);
i1--;
	}
}	
		
	/*void changedisp()
	{lcdcmd(0x80);	
intdisplay(hour);
lcdcmd(0x82);
	lcddata(':');
lcdcmd(0x83);
intdisplay(min);
lcdcmd(0x85);
lcddata(':');
lcdcmd(0x86);
intdisplay(sec);
	}*/
	
void main()
{
P2=0x00;
P3=0x0f;
lcdcmd(0x38);
delay();
lcdcmd(0x01);
delay();
lcdcmd(0x10);
delay();
lcdcmd(0x0c);
delay();
lcdcmd(0x80);
delay();
timer1();

while(1)
{
lcdcmd(0x80);	
intdisplay(hour);
lcdcmd(0x82);
	lcddata(':');
lcdcmd(0x83);
intdisplay(min);
lcdcmd(0x85);
lcddata(':');
lcdcmd(0x86);
intdisplay(sec);	
//lcdcmd(0x01);
lcdcmd(0xc0);
lcddata(ch1[0]);
lcddata(ch1[1]);
lcddata(ch1[2]);
switch(day)
	{ case 2: ch1[0]='T';ch1[1]='U';ch[2]='E';break;
	case 3:ch1[0]='W';ch1[1]='E';ch[2]='D';break;
	case 4: ch1[0]='T';ch1[1]='H';ch[2]='U';break;
	case 5: ch1[0]='F';ch1[1]='R';ch[2]='I';break;
		case 6:ch1[0]='S';ch1[1]='A';ch[2]='T';break;
	case 7:ch1[0]='S';ch1[1]='U';ch[2]='N';day=1;break;}
 		

}

}
