#include<reg52.h>
#include <stdio.h>

#define uchar unsigned char								//把 unsigned char 宏定义为 uchar
#define uint unsigned int								//把 unsigned int 宏定义为 uint
uint sec,min,hour,date,month,year;
unsigned char code str1[]={""};
unsigned char code str2[]={""};
uint rec_dat[4];   



sbit rst = P3^4;										//定义复位/片选线接P3.4
sbit sclk = P3^7;										//定义串行时钟引脚接P3.7
sbit sda = P3^5;										//定义串行数据输入输出端接P3.5

sbit RS=P2^0;
sbit RW=P2^1;
sbit EN=P2^2;
sbit key0=P1^2;
sbit key1=P1^3;
sbit key2=P1^4;
sbit key3=P1^5;

sbit key4=P2^5;
sbit key5=P2^6;

sbit key6=P3^2;
sbit key7=P3^3;
sbit key8=P3^6;

sbit key9=P1^7;

sbit M0=P1^0;//右
sbit M1=P1^1;//左

sbit Data=P1^6;   

sbit scl=P2^3;  //时钟
sbit sda2=P2^4;  //数据

sbit beep=P2^7;

/*对DS1302初始化*/
void ds1302_init(void)
{
	rst = 0;										   //rst为低电平
	sclk = 0;										   //sclk为低电平时，才能将rst置为高电平
	rst = 1;										   //rst为高电平
}
/*对DS1302写1字节函数*/
void write_ds1302_onebyte(unsigned char dat)	   
{
	unsigned char i;
	for(i = 0;i < 8;i++)							   //循环8次，得出一字节数据
	{
		sda = (bit)(dat & 0x01);					  //强制取最低位
		sclk = 0;									  //低电平          上升沿写入数据
		sclk = 1;									 //高电平
		dat = dat >> 1;								 //数据由低到高输入
	}
}
/*从DS1302读一字节函数*/
uchar read_ds1302_onebyte(void)		
{
	unsigned char i,dat;
	for(i = 0;i < 8;i++)							 //循环8次，得出一字节数据
	{
		sclk = 1;									//低电平            下降沿读出数据
		sclk = 0;									//高电平
		dat = dat >> 1;								//由低到高读出
		if(sda)dat = dat | 0x80;					//如果读出的数据是1，将1取出，放在最高位
	}
	return(dat);								   //将数据返回
}
/*对DS1302的某一地址写一字节函数*/
void write_ds1302_add_dat(unsigned char add,unsigned char dat)
{
	ds1302_init();			 //启动
	write_ds1302_onebyte(add);	//写入命令
	write_ds1302_onebyte(dat);	//写入数据
	sclk = 1;					//将时钟电平置于已知状态
	rst = 0;					//禁止数据传递
}
/*从DS1302的某一地址读一字节函数*/
uchar read_ds1302_add(unsigned char add)	//读1302的数据								
{
   unsigned char dat_temp;
	ds1302_init();				  //启动
	write_ds1302_onebyte(add);			//写命令
	dat_temp = read_ds1302_onebyte();  //读数据
	sclk = 1;						  //将时钟电平置于已知状态
	rst = 0;						 //禁止数据传递
	return(dat_temp);			   //将数据返回
}
/*8421BCD码到十进制转换*/
uchar BCD_DEC_conv(unsigned char x)
{
	unsigned char dec;
	dec =  0x0f & x;				//保留低四位
	x = x >> 4;			   		   //高四位变为低四位
	dec	= dec + x * 10;			  //转换为十进制
	return(dec);
}
/*十进制转换到8421BCD码*/
uchar DEC_BCD_conv(unsigned char x)
{
	unsigned char bcd;
	bcd =  x % 10;		  		  //取余，低四位
	x = x / 10;					  //取整，高四位
	x = x << 4;					  //低四位变为高四位
	bcd	= bcd | x ;				  //或运算，得出BCD码
	return(bcd);
}
/*获得时间信息函数*/
void get_ds1302_time(void)													//获取1302的时间数据（时、分、秒），存入time1数组中
{
	unsigned char d;
	d = read_ds1302_add(0x81);												//读秒
	sec = BCD_DEC_conv(d);													//得到秒	
	d = read_ds1302_add(0x83);												//读分
	min = BCD_DEC_conv(d);													//得到分
	d = read_ds1302_add(0x85);												//读小时
	hour = BCD_DEC_conv(d);													//得到小时
	d = read_ds1302_add(0x87);												//读日
	date = BCD_DEC_conv(d);													//得到日
  d = read_ds1302_add(0x89);												//读月
	month = BCD_DEC_conv(d);												//得到月
//	d = read_ds1302_add(0x8b);												//读星期
//	week = BCD_DEC_conv(d);													//得到星期
	d = read_ds1302_add(0x8d);												//读年
	year = BCD_DEC_conv(d);													//得到年	
}
//LCD

/*************************lcd1602程序**************************/
void delay1ms(unsigned int ms)//延时1毫秒(不够精确的)
{
	unsigned int i,j;
	for(i=0;i<ms;i++) 
	for(j=0;j<100;j++);
}
void wr_com(unsigned char com)//写指令//
{ 
	delay1ms(1);
	RS=0;
	RW=0;
	EN=0;
	P0=com;
	delay1ms(1);
	EN=1;
	delay1ms(1);
	EN=0;
}
void wr_dat(unsigned char dat)//写数据//
{ 
	delay1ms(1);;
	RS=1;
	RW=0;
	EN=0;
	P0=dat;
	delay1ms(1);
	EN=1;
	delay1ms(1);
	EN=0;
}
void lcd_init()//初始化设置//
{
	delay1ms(15);
	wr_com(0x38);delay1ms(5);
	wr_com(0x08);delay1ms(5);
	wr_com(0x01);delay1ms(5);
	wr_com(0x06);delay1ms(5);
	wr_com(0x0c);delay1ms(5);
}
void display(unsigned char *p)//显示//
{
	while(*p!='\0')
	{
		wr_dat(*p);
		p++;
		delay1ms(1);
	}
}
void init_play()//初始化显示
{
	lcd_init();
	wr_com(0xc0);
	display(str1);
	wr_com(0xc7);
	display(str2);
}

//DHT11
void DHT11_delay_us(uchar n)
{
    while(--n);
}
void DHT11_delay_ms(uint z)
{
   uint i,j;
   for(i=z;i>0;i--)
      for(j=110;j>0;j--);
}
void DHT11_start()
{
   Data=1;
   DHT11_delay_us(2);
   Data=0;
   DHT11_delay_ms(30);   
   Data=1;
   DHT11_delay_us(30);
}
uchar DHT11_rec_byte()      
{
   uchar i,dat=0;
  for(i=0;i<8;i++)    
   {          
      while(!Data);   
      DHT11_delay_us(8);    
      dat<<=1;           
      if(Data==1)    
         dat+=1;
      while(Data);     
    }  
    return dat;
}
void DHT11_receive()     
{
    uchar R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise; 
    DHT11_start();
    if(Data==0)
    {
        while(Data==0);       
        DHT11_delay_us(40);  
        R_H=DHT11_rec_byte();      
        R_L=DHT11_rec_byte();     
        T_H=DHT11_rec_byte();     
        T_L=DHT11_rec_byte();    
        revise=DHT11_rec_byte(); 
        DHT11_delay_us(25);    
        if((R_H+R_L+T_H+T_L)==revise)      
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
        }  
        rec_dat[0]=(RH/10);
        rec_dat[1]=(RH%10);
        rec_dat[2]=(TH/10);
        rec_dat[3]=(TH%10); 
    }
}

//IIC
void delay()  //延时
{ ;; }
void start()  //开始信号  在scl时钟高电平时数据sda由高到低跳变
{        
        sda2=1;
        scl=1;
        delay();  //延时
        sda2=0;
        delay();  //延时
}

void stop()   //停止  在scl时钟高电平时数据sda由低到高跳变
{
        sda2=0;
        scl=1;
        delay();  //延时
        sda2=1;
        delay();  //延时
}

void respons()  //应答   在scl时钟高电平时检测数据sda由高到低跳变,经过几个周期无应答自动跳过
{
        uchar i;
        scl=1;
        delay();
        while((sda==1)&&(i<250))i++; //当i=250时无应答自动跳过
        scl=0;
        delay();
}

void init()  //初始化
{
        sda2=1;
        scl=1;
        delay();  //延时
}

void write_byte(uchar date)  //写一个字节
{
        uchar i,temp;
        temp=date;


        for(i=0;i<8;i ++) //循环8次写入一个字节
        {
                temp=temp<<1;  //temp中的数据左移,最高位移入CY存储器中,低位补零
                scl=0;
          delay();
                sda2=CY;
                delay();
                scl=1;
                delay();
        }
        scl=0;
        delay();
        sda2=1;
        delay();
}

uchar read_byte()  //读取一个字节
{
        uchar i,k;
        scl=0;
        sda2=1;
        delay();
        for(i=0;i<8;i++)
        {
                scl=1;
                delay();        
                k=(k<<1)|sda2;  //k左移低位用sda代替(左移完后与sda与运算),循环8次,取出完整的字节
                scl=0;
                delay();        
        }
        return k;  //返回k值
}

void delay1(uchar x) //延时函数
{
        uchar a,b;
        for(a=x;a>0;a--)
         for(b=100;b>0;b--);
}

void write_add(uchar address,uchar date)  //完整的写字节过程
{
        start();  //开始信号
        write_byte(0xa0);  //发送片选并选择写
        respons();  //应答
        write_byte(address);   //发送要写入的地址
        respons();   //应答
        write_byte(date);   //发送要写入的数据
        respons();    //应答
        stop();    //停止
}

uchar read_add(uchar address)  //完整的读字节过程
{
        uchar date;
        start();   //开始信号
        write_byte(0xa0);   //发送片选并选择写
        respons();    //应答
        write_byte(address);   //发送要读取的地址
        respons();    //应答
        start();   //开始信号
        write_byte(0xa1);  //发送片选并选择读
        respons();     //应答
        date=read_byte();  //读取数据
        stop();   //停止
        return date;  //返回date
}

//虚拟终端
void delay2(unsigned int x)
{
unsigned char i;
while(x--)
{
for(i = 0;i < 120;i++);
}
}
//虚拟终端
//字符发送函数
void putcharr(unsigned char data1)
{
SBUF = data1; //将待发送的字符送入发送缓冲器
while(TI == 0); //等待发送完成
TI = 0;//发送中断标志请0
}
//字符串发送函数
void putstring(unsigned char *dat)
{
while(*dat != '\0')//判断字符串是否发送完毕
{
putcharr(*dat); //发送单个字符
dat++; //字符地址加1，指向先下一个字符
delay2(5);
}
}

uint ldelay = 1;

void xuni()
{
	SCON = 0x40; //串口工作方式设置
	TMOD |= 0x20; //定时器工作方式设置
	PCON = 0x00;//波特率倍增设置
	TL1 = 0xfd; //波特率设置
	TH1 = 0xfd; //
	TI = 0; // 清0发送中断标志
	TR1 = 1; //开启定时器
	delay2(200);
	putstring("Receiving from 8051...\r\n"); //发送字符串，结尾回车换行
	putstring("----------------------\r\n");
	delay2(50);
}


void main(void)
{ 
	uchar  code s1[3]={"kai"};
	
	uint k[2]={75,75};
	uint k2[2]={25,25};
	uint v[4];
//	uchar a[6];
	uint H,T;
	uint X[4];
	uint x[17];
	uchar n[7];
	uint N1[1];
	uint N2[1];
	uchar code str4[]={"S"};
	uchar code str5[]={"Z"};
	uchar code str6[]={"D"};
	uchar code str7[]={"G"};
	uchar  code s2[4]={"guan"};

	x[10]=21;
	x[11]=6;
	x[12]=25;
	

	xuni();//虚拟终端
	init_play();//LCD初始化显示
	init(); //IIC初始化
	
//	write_add(23,80);  //在位置23中写入5a
	delay1(100);  //延时函数
	x[0]=read_add(23);  //在位置23中读取数据并对P!口赋值
	
//	write_add(24,70);  //在位置23中写入5a
	delay1(100);  //延时函数
	x[1]=read_add(24);  //在位置23中读取数据并对P!口赋值
	
//	write_add(25,30);  //在位置23中写入5a
	delay1(100);  //延时函数
	x[2]=read_add(25);  //在位置23中读取数据并对P!口赋值
	
//	write_add(26,20);  //在位置23中写入5a
	delay1(100);  //延时函数
	x[3]=read_add(26);  //在位置23中读取数据并对P!口赋值
	
//		write_add(27,9);  //在位置23中写入5a
	delay1(100);  //延时函数
	x[5]=read_add(27);  //在位置23中读取数据并对P!口赋值
	
//		write_add(28,15);  //在位置23中写入5a
	delay1(100);  //延时函数
	x[6]=read_add(28);  //在位置23中读取数据并对P!口赋值
	
	M0=0;
	M1=0;
	beep=1;


	while(1)
	{

		
		//设置
		if(key0 == 0)
		{
			delay1ms(1);
			if(key0 == 0)
			{
				if(x[4] == 0)
				{
					x[4]=1;
				}
				else if(x[4] == 1)
				{
					x[4]=2;
				}
				else if(x[4] == 2)
				{
					x[4]=3;
				}
				else if(x[4] == 3)
				{
					x[4]=0;
				}
			}
			while(!key0);
		}
			

		//加减
		
		//湿上
		if(x[4] == 0)
		{
			if(key1 == 0)
				x[0]=x[0]-1;
			else if(key2 == 0){
				x[0]=x[0]+1;
			}
		}
		//湿下
		if(x[4] == 1)
		{
			if(key1 == 0)
				x[1]=x[1]-1;
			else if(key2 == 0){
				x[1]=x[1]+1;
			}
		}
		
		//温上
		if(x[4] == 2)
		{
			if(key1 == 0)
				x[2]=x[2]-1;
			else if(key2 == 0){
				x[2]=x[2]+1;
			}
		}
		//温下
		if(x[4] == 3)
		{
			if(key1 == 0)
				x[3]=x[3]-1;
			else if(key2 == 0){
				x[3]=x[3]+1;
			}
		}
		//确定
		if(key3 == 0)
		{
			delay1ms(1);
			if(key3 == 0)
			{
				write_add(23,x[0]);  //在位置23中写入5a
				delay1(100);  //延时函数
		//							x[0]=read_add(23);  //在位置23中读取数据并对P!口赋值
				
				write_add(24,x[1]);  //在位置23中写入5a
				delay1(100);  //延时函数
		//							x[1]=read_add(24);  //在位置23中读取数据并对P!口赋值
				
				write_add(25,x[2]);  //在位置23中写入5a
				delay1(100);  //延时函数
		//							x[2]=read_add(25);  //在位置23中读取数据并对P!口赋值
				
				write_add(26,x[3]);  //在位置23中写入5a
				delay1(100);  //延时函数
		//							x[3]=read_add(26);  //在位置23中读取数据并对P!口赋值
				
				write_add(27,x[5]);  //在位置23中写入5a
				delay1(100);  //延时函数
		//							x[3]=read_add(26);  //在位置23中读取数据并对P!口赋值
				
				write_add(28,x[6]);  //在位置23中写入5a
				delay1(100);  //延时函数
		//							x[3]=read_add(26);  //在位置23中读取数据并对P!口赋值
			}
			while(!key3);
		}	
			

		
			get_ds1302_time();
			DHT11_receive();
			
			H=rec_dat[0]*10+rec_dat[1];
			T=rec_dat[2]*10+rec_dat[3];
			sprintf(X,"%d%%%dV",H,T);
			wr_com(0xc0);
			display(X);
		
			//最大值显示				
		sprintf(n,"%d:%d:%d %d",hour,min,sec,x[x[4]]);
		
			wr_com(0x80);
			display(n);
			
			//x[8]选模式
			
			if(key9==0)
			{
				delay1ms(1);
				if(key9==0)
				{
					x[8]=x[8]+1;
				}
				while(!key9);
			}
			
			if(x[8] == 3)
				x[8]=0;
			
			//定时模式
			if(x[8] == 0)
			{
				wr_com(0xcd);
				display(str6);
				
				//加按钮定时显示时间（定时模式）x56 hour,min,sec
				sprintf(N1,"%d",x[5]);
				wr_com(0xc7);
				display(N1);
				sprintf(N2,"%d",x[6]);
				wr_com(0xca);
				display(N2);
				
				if(key6==0)
				{
					delay1ms(1);
					if(key6==0)
					{
						x[9]=x[9]+1;
					}
					while(!key6);
				}
				
				if(x[9]==5)
					x[9]=0;
				
				if(x[9]==0)
				{
					if(key7==0)
					{
						delay1ms(1);
						if(key7==0)
						{
							x[5]--;
						}
						while(!key7);
					}else if(key8==0){
						delay1ms(1);
						if(key8==0)
						{
							x[5]++;
						}
						while(!key8);
					}
				}
				if(x[9]==1)
				{
					if(key7==0)
					{
						delay1ms(1);
						if(key7==0)
						{
							x[6]--;
						}
						while(!key7);
					}else if(key8==0){
						delay1ms(1);
						if(key8==0)
						{
							x[6]++;
						}
						while(!key8);
					}
				}

				if(x[5]==hour&&x[6]==min)
				{
					M1=1;
					M0=0;
				}
				if(x[5]!=hour||x[6]!=min)
				{
					M1=0;
					M0=0;
				}
				
				
					//改时间

			if(x[9]==2)
			{
				wr_com(0xcd);
				display(str7);
				
				if(key7==0)
				{
					delay1ms(1);
					if(key7==0)
					{
						x[10]--;
						x[13]=0;
					}
					while(!key7);
				}else if(key8==0){
					delay1ms(1);
					if(key8==0)
					{
						x[10]++;
						x[13]=0;
					}
					while(!key8);
				}
				if(x[13]==0)
				{
						x[14] = DEC_BCD_conv(x[10]);
						write_ds1302_add_dat(0x8e,0x00);						    	//写操作，可以对DS1302调整
						write_ds1302_add_dat(0x8c,x[14]);								//写年，（20）12年
						write_ds1302_add_dat(0x8e,0x80);								//写保护
					  x[13]=1;
				}
			}
			if(x[9]==3)
			{
				wr_com(0xcd);
				display(str7);
				
				if(key7==0)
				{
					delay1ms(1);
					if(key7==0)
					{
						x[11]--;
						x[13]=0;
					}
					while(!key7);
				}else if(key8==0){
					delay1ms(1);
					if(key8==0)
					{
						x[11]++;
						x[13]=0;
					}
					while(!key8);
				}
				if(x[13]==0)
				{
						x[15] = DEC_BCD_conv(x[11]);
						write_ds1302_add_dat(0x8e,0x00);						    	//写操作，可以对DS1302调整
						write_ds1302_add_dat(0x88,x[15]);								//写月，5月
						write_ds1302_add_dat(0x8e,0x80);								//写保护
						x[13]=1;
				}
			}
			if(x[9]==4)
			{
				wr_com(0xcd);
				display(str7);
				
				if(key7==0)
				{
					delay1ms(1);
					if(key7==0)
					{
						x[12]--;
						x[13]=0;
					}
					while(!key7);
				}else if(key8==0){
					delay1ms(1);
					if(key8==0)
					{
						x[12]++;
						x[13]=0;
					}
					while(!key8);
				}
				if(x[13]==0)
				{
						x[16] = DEC_BCD_conv(x[12]);
						write_ds1302_add_dat(0x8e,0x00);						    	//写操作，可以对DS1302调整
						write_ds1302_add_dat(0x86,x[16]);								//写日，28日
						write_ds1302_add_dat(0x8e,0x80);								//写保护
						x[13]=1;
				}
			}
				
				
			}
			//自动
			if(x[8] == 1)
			{
				wr_com(0xcd);
				display(str5);
				
				if(sec%5==0)
				{
					if(x[7]==2)
						x[7]=0;
					if(x[7]==0)
					{	
						M1=0;
						M0=1;
					}
					if(x[7]==1)
					{
						M0=0;
						M1=1;
					}
					x[7]=x[7]+1;
				}
			}
			//手动
			if(x[8]==2)
			{
				wr_com(0xcd);
				display(str4);
				
				if(key4 == 0)
				{
					delay1ms(1);
					if(key4 == 0)
					{
						M0=1;
						M1=0;
					}
					while(!key4);
				}
				
				if(key5 == 0)
				{
					delay1ms(1);
					if(key5 == 0)
					{
						M1=1;
						M0=0;
					}
					while(!key5);
				}
			}
		
			
		sprintf(v,"%d %d",H,T);
		k[0]=k[1];
		k[1]=H;
		
		if(k[1]!=k[0])
		{
			//虚拟
//				sprintf(a,"%d %d %d %d %d %d",year,month,date,hour,min,sec);
//				putstring(a);
//				putstring("\r\n");
				putstring(v);
				putstring("\r\n");
				if(M0==1&&M1==0)//开
				{
					putstring(s1);
				}
				if(M1==1&&M0==0)//关
				{
					putstring(s2);
				}
				putstring("\r\n-------------\r\n");
	//			delay(100);
		}

		
		k2[0]=k2[1];
		k2[1]=T;
		
		if(k2[1]!=k2[0])
		{
			//虚拟
//				sprintf(a,"%d %d %d %d %d %d",year,month,date,hour,min,sec);
//				putstring(a);
//				putstring("\r\n");
				putstring(v);
				putstring("\r\n");
				if(M0==1&&M1==0)//开
				{
					putstring(s1);
				}
				if(M1==1&&M0==0)//关
				{
					putstring(s2);
				}
				putstring("\r\n-------------\r\n");
	//			delay(100);
		}
			
	
			if(H<x[1]||H>x[0]||T<x[3]||T>x[2])
			{
				beep=0;
			}
			if(((H)>=x[1]&&(H)<=x[0])&&((T)>=x[3]&&(T)<=x[2]))
			{
				beep=1;
			}
			
	}
}



