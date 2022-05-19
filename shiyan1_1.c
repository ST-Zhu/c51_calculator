#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2;
uchar t,n,a,i;//t读取P3数据；n计数显示正常;a判断运算符号;i计数
int x,y,z,b,c,q[10];//储存数据
void delay(uchar x)
{
	uchar f,g;
	for(f=x;f>0;f++)
		for(g=110;g>0;g--);
}//延迟函数
void write_command(uchar f)
{
	RS=0;
	RW=0;
	E=0;
	P0=f;
	E=1;
	delay(5);
	E=0;
}//写指令函数
void write_date(uchar g)
{
	RS=1;
	RW=0;
	E=0;
	P0=g;
	E=1;
	delay(5);
	E=0;
}//写数据函数
void init()
{
	uchar j;
	for(j=0;j<10;j++)
		q[j]=10;
	i=0;
	x=0;
	y=0;
	z=0;
	b=0;
	c=0;
	a=0;
	n=0;
	t=0;//初始化数据
	write_command(0x38);
	write_command(0x0f);
	write_command(0x06);
	write_command(0x01);
	write_command(0x80);//初始化LCD1602
}//初始化函数
void shaomiao()
{
	P3=0xfe;
	t=P3;
	if(t!=0xfe)
	{
		delay(50);//按键消抖
		if(t!=0xfe)
		{
			if(t==0xee) init();
			if(t==0xde) {write_date('/');n++;a=1;}
			if(t==0xbe) {write_date('*');n++;a=2;}
			if(t==0x7e) a=5;
		}
		while(P3!=0xfe);//松开按键时跳出语句
	}//第一排按键扫描
	P3=0xfd;
	t=P3;
	if(t!=0xfd)
	{
		delay(50);//按键消抖
		if(t!=0xfd)
		{
			if(t==0xed) {write_date('7');n++;x=7;}
			if(t==0xdd) {write_date('8');n++;x=8;}
			if(t==0xbd) {write_date('9');n++;x=9;}
			if(t==0x7d) {write_date('-');n++;a=3;}
		}
		while(P3!=0xfd);//松开按键时跳出语句
	}//第二排按键扫描
	P3=0xfb;
	t=P3;
	if(t!=0xfb)
	{
		delay(50);//按键消抖
		if(t!=0xfb)
		{
			if(t==0xeb) {write_date('4');n++;x=4;}
			if(t==0xdb) {write_date('5');n++;x=5;}
			if(t==0xbb) {write_date('6');n++;x=6;}
			if(t==0x7b) {write_date('+');n++;a=4;}
		}
		while(P3!=0xfb);//松开按键时跳出语句
	}//第三排按键扫描
	P3=0xf7;
	t=P3;
	if(t!=0xf7)
	{
		delay(50);//按键消抖
		if(t!=0xf7)
		{
			if(t==0xe7) {write_date('0');n++;x=0;}
			if(t==0xd7) {write_date('1');n++;x=1;}
			if(t==0xb7) {write_date('2');n++;x=2;}
			if(t==0x77) {write_date('3');n++;x=3;}
		}
		while(P3!=0xf7);//松开按键时跳出语句
	}//第四排按键扫描
	if(n==16) write_command(0x07);//正常显示
	if(a==0) y=y*10+x;//形成一个数
}//矩阵键盘的扫描
void jisuan()
{
		while(!a)
			shaomiao();
		if(a==1)
		{
			z=y;
			a=0;
			y=0;
			while(!a)
				shaomiao();
			if(a==5)
			{
				b=y;
				c=z/b;
				if(c==0)
				{
					q[9]=0;
					i=8;
				}
				else
					for(i=9;c>0;i--)
					{
						q[i]=c%10;
						c/=10;
					}
				write_command(0x80+0x40);
				for(;i<9;i++)
				{
					write_date(0x30+q[i+1]);
				}
			}
		}
		if(a==2)
		{
			z=y;
			a=0;
			y=0;
			while(!a)
				shaomiao();
			if(a==5)
			{
				b=y;
				c=z*b;
				if(c==0)
				{
					q[9]=0;
					i=8;
				}
				else
					for(i=9;c>0;i--)
					{
						q[i]=c%10;
						c/=10;
					}
				write_command(0x80+0x40);
				for(;i<9;i++)
				{
					write_date(0x30+q[i+1]);
				}
			}
		}
		if(a==3)
		{
			z=y;
			a=0;
			y=0;
			while(!a)
				shaomiao();
			if(a==5)
			{
				b=y;
				c=z-b;
				if(c==0)
				{
					q[9]=0;
					i=8;
				}
				else
					for(i=9;c>0;i--)
					{
						q[i]=c%10;
						c/=10;
					}
				write_command(0x80+0x40);
				for(;i<9;i++)
				{
					write_date(0x30+q[i+1]);
				}
			}
		}
		if(a==4)
		{
			z=y;
			a=0;
			y=0;
			while(!a)
				shaomiao();
			if(a==5)
			{
				b=y;
				c=z+b;
				if(c==0)
				{
					q[9]=0;
					i=8;
				}
				else
					for(i=9;c>0;i--)
					{
						q[i]=c%10;
						c/=10;
					}
				write_command(0x80+0x40);
				for(;i<9;i++)
				{
					write_date(0x30+q[i+1]);
				}
			}
		}
		a=0;
}//计算数并显示
void main()
{		
	init();
	while(1)
	{
		jisuan();
	}
}