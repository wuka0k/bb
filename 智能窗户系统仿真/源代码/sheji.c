#include<reg52.h>
#include <stdio.h>

#define uchar unsigned char								//�� unsigned char �궨��Ϊ uchar
#define uint unsigned int								//�� unsigned int �궨��Ϊ uint
uint sec,min,hour,date,month,year;
unsigned char code str1[]={""};
unsigned char code str2[]={""};
uint rec_dat[4];   



sbit rst = P3^4;										//���帴λ/Ƭѡ�߽�P3.4
sbit sclk = P3^7;										//���崮��ʱ�����Ž�P3.7
sbit sda = P3^5;										//���崮��������������˽�P3.5

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

sbit M0=P1^0;//��
sbit M1=P1^1;//��

sbit Data=P1^6;   

sbit scl=P2^3;  //ʱ��
sbit sda2=P2^4;  //����

sbit beep=P2^7;

/*��DS1302��ʼ��*/
void ds1302_init(void)
{
	rst = 0;										   //rstΪ�͵�ƽ
	sclk = 0;										   //sclkΪ�͵�ƽʱ�����ܽ�rst��Ϊ�ߵ�ƽ
	rst = 1;										   //rstΪ�ߵ�ƽ
}
/*��DS1302д1�ֽں���*/
void write_ds1302_onebyte(unsigned char dat)	   
{
	unsigned char i;
	for(i = 0;i < 8;i++)							   //ѭ��8�Σ��ó�һ�ֽ�����
	{
		sda = (bit)(dat & 0x01);					  //ǿ��ȡ���λ
		sclk = 0;									  //�͵�ƽ          ������д������
		sclk = 1;									 //�ߵ�ƽ
		dat = dat >> 1;								 //�����ɵ͵�������
	}
}
/*��DS1302��һ�ֽں���*/
uchar read_ds1302_onebyte(void)		
{
	unsigned char i,dat;
	for(i = 0;i < 8;i++)							 //ѭ��8�Σ��ó�һ�ֽ�����
	{
		sclk = 1;									//�͵�ƽ            �½��ض�������
		sclk = 0;									//�ߵ�ƽ
		dat = dat >> 1;								//�ɵ͵��߶���
		if(sda)dat = dat | 0x80;					//���������������1����1ȡ�����������λ
	}
	return(dat);								   //�����ݷ���
}
/*��DS1302��ĳһ��ַдһ�ֽں���*/
void write_ds1302_add_dat(unsigned char add,unsigned char dat)
{
	ds1302_init();			 //����
	write_ds1302_onebyte(add);	//д������
	write_ds1302_onebyte(dat);	//д������
	sclk = 1;					//��ʱ�ӵ�ƽ������֪״̬
	rst = 0;					//��ֹ���ݴ���
}
/*��DS1302��ĳһ��ַ��һ�ֽں���*/
uchar read_ds1302_add(unsigned char add)	//��1302������								
{
   unsigned char dat_temp;
	ds1302_init();				  //����
	write_ds1302_onebyte(add);			//д����
	dat_temp = read_ds1302_onebyte();  //������
	sclk = 1;						  //��ʱ�ӵ�ƽ������֪״̬
	rst = 0;						 //��ֹ���ݴ���
	return(dat_temp);			   //�����ݷ���
}
/*8421BCD�뵽ʮ����ת��*/
uchar BCD_DEC_conv(unsigned char x)
{
	unsigned char dec;
	dec =  0x0f & x;				//��������λ
	x = x >> 4;			   		   //����λ��Ϊ����λ
	dec	= dec + x * 10;			  //ת��Ϊʮ����
	return(dec);
}
/*ʮ����ת����8421BCD��*/
uchar DEC_BCD_conv(unsigned char x)
{
	unsigned char bcd;
	bcd =  x % 10;		  		  //ȡ�࣬����λ
	x = x / 10;					  //ȡ��������λ
	x = x << 4;					  //����λ��Ϊ����λ
	bcd	= bcd | x ;				  //�����㣬�ó�BCD��
	return(bcd);
}
/*���ʱ����Ϣ����*/
void get_ds1302_time(void)													//��ȡ1302��ʱ�����ݣ�ʱ���֡��룩������time1������
{
	unsigned char d;
	d = read_ds1302_add(0x81);												//����
	sec = BCD_DEC_conv(d);													//�õ���	
	d = read_ds1302_add(0x83);												//����
	min = BCD_DEC_conv(d);													//�õ���
	d = read_ds1302_add(0x85);												//��Сʱ
	hour = BCD_DEC_conv(d);													//�õ�Сʱ
	d = read_ds1302_add(0x87);												//����
	date = BCD_DEC_conv(d);													//�õ���
  d = read_ds1302_add(0x89);												//����
	month = BCD_DEC_conv(d);												//�õ���
//	d = read_ds1302_add(0x8b);												//������
//	week = BCD_DEC_conv(d);													//�õ�����
	d = read_ds1302_add(0x8d);												//����
	year = BCD_DEC_conv(d);													//�õ���	
}
//LCD

/*************************lcd1602����**************************/
void delay1ms(unsigned int ms)//��ʱ1����(������ȷ��)
{
	unsigned int i,j;
	for(i=0;i<ms;i++) 
	for(j=0;j<100;j++);
}
void wr_com(unsigned char com)//дָ��//
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
void wr_dat(unsigned char dat)//д����//
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
void lcd_init()//��ʼ������//
{
	delay1ms(15);
	wr_com(0x38);delay1ms(5);
	wr_com(0x08);delay1ms(5);
	wr_com(0x01);delay1ms(5);
	wr_com(0x06);delay1ms(5);
	wr_com(0x0c);delay1ms(5);
}
void display(unsigned char *p)//��ʾ//
{
	while(*p!='\0')
	{
		wr_dat(*p);
		p++;
		delay1ms(1);
	}
}
void init_play()//��ʼ����ʾ
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
void delay()  //��ʱ
{ ;; }
void start()  //��ʼ�ź�  ��sclʱ�Ӹߵ�ƽʱ����sda�ɸߵ�������
{        
        sda2=1;
        scl=1;
        delay();  //��ʱ
        sda2=0;
        delay();  //��ʱ
}

void stop()   //ֹͣ  ��sclʱ�Ӹߵ�ƽʱ����sda�ɵ͵�������
{
        sda2=0;
        scl=1;
        delay();  //��ʱ
        sda2=1;
        delay();  //��ʱ
}

void respons()  //Ӧ��   ��sclʱ�Ӹߵ�ƽʱ�������sda�ɸߵ�������,��������������Ӧ���Զ�����
{
        uchar i;
        scl=1;
        delay();
        while((sda==1)&&(i<250))i++; //��i=250ʱ��Ӧ���Զ�����
        scl=0;
        delay();
}

void init()  //��ʼ��
{
        sda2=1;
        scl=1;
        delay();  //��ʱ
}

void write_byte(uchar date)  //дһ���ֽ�
{
        uchar i,temp;
        temp=date;


        for(i=0;i<8;i ++) //ѭ��8��д��һ���ֽ�
        {
                temp=temp<<1;  //temp�е���������,���λ����CY�洢����,��λ����
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

uchar read_byte()  //��ȡһ���ֽ�
{
        uchar i,k;
        scl=0;
        sda2=1;
        delay();
        for(i=0;i<8;i++)
        {
                scl=1;
                delay();        
                k=(k<<1)|sda2;  //k���Ƶ�λ��sda����(���������sda������),ѭ��8��,ȡ���������ֽ�
                scl=0;
                delay();        
        }
        return k;  //����kֵ
}

void delay1(uchar x) //��ʱ����
{
        uchar a,b;
        for(a=x;a>0;a--)
         for(b=100;b>0;b--);
}

void write_add(uchar address,uchar date)  //������д�ֽڹ���
{
        start();  //��ʼ�ź�
        write_byte(0xa0);  //����Ƭѡ��ѡ��д
        respons();  //Ӧ��
        write_byte(address);   //����Ҫд��ĵ�ַ
        respons();   //Ӧ��
        write_byte(date);   //����Ҫд�������
        respons();    //Ӧ��
        stop();    //ֹͣ
}

uchar read_add(uchar address)  //�����Ķ��ֽڹ���
{
        uchar date;
        start();   //��ʼ�ź�
        write_byte(0xa0);   //����Ƭѡ��ѡ��д
        respons();    //Ӧ��
        write_byte(address);   //����Ҫ��ȡ�ĵ�ַ
        respons();    //Ӧ��
        start();   //��ʼ�ź�
        write_byte(0xa1);  //����Ƭѡ��ѡ���
        respons();     //Ӧ��
        date=read_byte();  //��ȡ����
        stop();   //ֹͣ
        return date;  //����date
}

//�����ն�
void delay2(unsigned int x)
{
unsigned char i;
while(x--)
{
for(i = 0;i < 120;i++);
}
}
//�����ն�
//�ַ����ͺ���
void putcharr(unsigned char data1)
{
SBUF = data1; //�������͵��ַ����뷢�ͻ�����
while(TI == 0); //�ȴ��������
TI = 0;//�����жϱ�־��0
}
//�ַ������ͺ���
void putstring(unsigned char *dat)
{
while(*dat != '\0')//�ж��ַ����Ƿ������
{
putcharr(*dat); //���͵����ַ�
dat++; //�ַ���ַ��1��ָ������һ���ַ�
delay2(5);
}
}

uint ldelay = 1;

void xuni()
{
	SCON = 0x40; //���ڹ�����ʽ����
	TMOD |= 0x20; //��ʱ��������ʽ����
	PCON = 0x00;//�����ʱ�������
	TL1 = 0xfd; //����������
	TH1 = 0xfd; //
	TI = 0; // ��0�����жϱ�־
	TR1 = 1; //������ʱ��
	delay2(200);
	putstring("Receiving from 8051...\r\n"); //�����ַ�������β�س�����
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
	

	xuni();//�����ն�
	init_play();//LCD��ʼ����ʾ
	init(); //IIC��ʼ��
	
//	write_add(23,80);  //��λ��23��д��5a
	delay1(100);  //��ʱ����
	x[0]=read_add(23);  //��λ��23�ж�ȡ���ݲ���P!�ڸ�ֵ
	
//	write_add(24,70);  //��λ��23��д��5a
	delay1(100);  //��ʱ����
	x[1]=read_add(24);  //��λ��23�ж�ȡ���ݲ���P!�ڸ�ֵ
	
//	write_add(25,30);  //��λ��23��д��5a
	delay1(100);  //��ʱ����
	x[2]=read_add(25);  //��λ��23�ж�ȡ���ݲ���P!�ڸ�ֵ
	
//	write_add(26,20);  //��λ��23��д��5a
	delay1(100);  //��ʱ����
	x[3]=read_add(26);  //��λ��23�ж�ȡ���ݲ���P!�ڸ�ֵ
	
//		write_add(27,9);  //��λ��23��д��5a
	delay1(100);  //��ʱ����
	x[5]=read_add(27);  //��λ��23�ж�ȡ���ݲ���P!�ڸ�ֵ
	
//		write_add(28,15);  //��λ��23��д��5a
	delay1(100);  //��ʱ����
	x[6]=read_add(28);  //��λ��23�ж�ȡ���ݲ���P!�ڸ�ֵ
	
	M0=0;
	M1=0;
	beep=1;


	while(1)
	{

		
		//����
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
			

		//�Ӽ�
		
		//ʪ��
		if(x[4] == 0)
		{
			if(key1 == 0)
				x[0]=x[0]-1;
			else if(key2 == 0){
				x[0]=x[0]+1;
			}
		}
		//ʪ��
		if(x[4] == 1)
		{
			if(key1 == 0)
				x[1]=x[1]-1;
			else if(key2 == 0){
				x[1]=x[1]+1;
			}
		}
		
		//����
		if(x[4] == 2)
		{
			if(key1 == 0)
				x[2]=x[2]-1;
			else if(key2 == 0){
				x[2]=x[2]+1;
			}
		}
		//����
		if(x[4] == 3)
		{
			if(key1 == 0)
				x[3]=x[3]-1;
			else if(key2 == 0){
				x[3]=x[3]+1;
			}
		}
		//ȷ��
		if(key3 == 0)
		{
			delay1ms(1);
			if(key3 == 0)
			{
				write_add(23,x[0]);  //��λ��23��д��5a
				delay1(100);  //��ʱ����
		//							x[0]=read_add(23);  //��λ��23�ж�ȡ���ݲ���P!�ڸ�ֵ
				
				write_add(24,x[1]);  //��λ��23��д��5a
				delay1(100);  //��ʱ����
		//							x[1]=read_add(24);  //��λ��23�ж�ȡ���ݲ���P!�ڸ�ֵ
				
				write_add(25,x[2]);  //��λ��23��д��5a
				delay1(100);  //��ʱ����
		//							x[2]=read_add(25);  //��λ��23�ж�ȡ���ݲ���P!�ڸ�ֵ
				
				write_add(26,x[3]);  //��λ��23��д��5a
				delay1(100);  //��ʱ����
		//							x[3]=read_add(26);  //��λ��23�ж�ȡ���ݲ���P!�ڸ�ֵ
				
				write_add(27,x[5]);  //��λ��23��д��5a
				delay1(100);  //��ʱ����
		//							x[3]=read_add(26);  //��λ��23�ж�ȡ���ݲ���P!�ڸ�ֵ
				
				write_add(28,x[6]);  //��λ��23��д��5a
				delay1(100);  //��ʱ����
		//							x[3]=read_add(26);  //��λ��23�ж�ȡ���ݲ���P!�ڸ�ֵ
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
		
			//���ֵ��ʾ				
		sprintf(n,"%d:%d:%d %d",hour,min,sec,x[x[4]]);
		
			wr_com(0x80);
			display(n);
			
			//x[8]ѡģʽ
			
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
			
			//��ʱģʽ
			if(x[8] == 0)
			{
				wr_com(0xcd);
				display(str6);
				
				//�Ӱ�ť��ʱ��ʾʱ�䣨��ʱģʽ��x56 hour,min,sec
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
				
				
					//��ʱ��

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
						write_ds1302_add_dat(0x8e,0x00);						    	//д���������Զ�DS1302����
						write_ds1302_add_dat(0x8c,x[14]);								//д�꣬��20��12��
						write_ds1302_add_dat(0x8e,0x80);								//д����
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
						write_ds1302_add_dat(0x8e,0x00);						    	//д���������Զ�DS1302����
						write_ds1302_add_dat(0x88,x[15]);								//д�£�5��
						write_ds1302_add_dat(0x8e,0x80);								//д����
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
						write_ds1302_add_dat(0x8e,0x00);						    	//д���������Զ�DS1302����
						write_ds1302_add_dat(0x86,x[16]);								//д�գ�28��
						write_ds1302_add_dat(0x8e,0x80);								//д����
						x[13]=1;
				}
			}
				
				
			}
			//�Զ�
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
			//�ֶ�
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
			//����
//				sprintf(a,"%d %d %d %d %d %d",year,month,date,hour,min,sec);
//				putstring(a);
//				putstring("\r\n");
				putstring(v);
				putstring("\r\n");
				if(M0==1&&M1==0)//��
				{
					putstring(s1);
				}
				if(M1==1&&M0==0)//��
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
			//����
//				sprintf(a,"%d %d %d %d %d %d",year,month,date,hour,min,sec);
//				putstring(a);
//				putstring("\r\n");
				putstring(v);
				putstring("\r\n");
				if(M0==1&&M1==0)//��
				{
					putstring(s1);
				}
				if(M1==1&&M0==0)//��
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



