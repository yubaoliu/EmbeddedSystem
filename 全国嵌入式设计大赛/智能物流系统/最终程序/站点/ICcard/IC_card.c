#include "IC_card.h"
uchar tmpResult;
uchar CardStatus;	
uchar SearMode = 0x01;

void CLR_Set()
{	uchar i;
	uchar	txbuff[8];
	uchar rxbuff[7];
	CardStatus=0;
	txbuff[0]=0xAA;
	txbuff[1]=0xFF;
	txbuff[2]=0x01;
	txbuff[3]=0x01;
	txbuff[4]=0xA3;	//search mode
	txbuff[5]=0;
	for(i=0;i<5;i++) txbuff[5]^=txbuff[i];
        tty_write(txbuff, 6);

       tty_read(rxbuff, 6);
       for(i=0;i<6;i++){
		rxbuff[7]^=rxbuff[i];
	}	
	if(rxbuff[4]==0x55){
   	CardStatus=0x01; 
	}
}

void Rd_DefBlock(uchar *CardNum,uchar *CardD,uchar ClosOpen)
{	uchar i;
	uchar txbuff[7];
	uchar rxbuff[28];
	CardStatus=0;
	txbuff[0]=0xAA;
	txbuff[1]=0xFF;
	txbuff[2]=0x01;
	txbuff[3]=0x02;				//������
	txbuff[4]=0xA7;
	txbuff[5]=ClosOpen;			//��ؑ�����־
	txbuff[6]=0;
	for(i=0;i<6;i++) txbuff[6]^=txbuff[i];
	tty_write(txbuff, 7);


	tty_read(rxbuff, 28);
	rxbuff[27]=0;
	for(i=0;i<26;i++){
		rxbuff[27]^=rxbuff[i];
//		printf(" %x",rxbuff[i]);
	}
	if(rxbuff[27]==rxbuff[26])
	  if(rxbuff[3]==0x16)				//��ɑ���ȡ�����Б�đֵ
	  {	CardStatus=0x01;
		for(i=0;i<16;i++)
			*CardD++=rxbuff[10+i];
	  }
	for(i=0;i<4;i++)
		*CardNum++=rxbuff[6+i];		//�ȡ������
}
//---------------------------------------
//������A8
//command:AA FF 01 0A(������) A8(������) 01 FF FF FF FF FF FF(6��ܑ��) 00 01 F7( 
//----------------------------------------
void Rd_Block(uchar *CardNum,uchar *CardD,uchar *CardK,uchar CardB,uchar ClosOpen)
{
	uchar i;
	uchar txbuff[15];
	uchar rxbuff[26];
	CardStatus=0;
	txbuff[0]=0xAA;
	txbuff[1]=0xFF;
	txbuff[2]=0x01;
	txbuff[3]=0x0A;			//length
	txbuff[4]=0xA8;			//order
	txbuff[5]=CardB;			//block
	for(i=0;i<6;i++)
		txbuff[6+i]=*CardK++;	//Card Key
	txbuff[12]=0;		
	txbuff[13]=ClosOpen;		//sign of close card
	txbuff[14]=0;	
	for(i=0;i<14;i++) txbuff[14]^=txbuff[i];
	tty_write(txbuff, 15);

	tty_read(rxbuff, 26);
	if(rxbuff[3]==0x14)
	{  rxbuff[25]=0;
	   for(i=0;i<24;i++)
			rxbuff[25]^=rxbuff[i];
	   if(rxbuff[25]==rxbuff[24])
		{   CardStatus=0x01;
			for(i=0;i<4;i++)
				*CardNum++=rxbuff[i+4];
			for(i=0;i<16;i++)
				*CardD++=rxbuff[i+8];
		}
	}		
}	
//-----------------------------------------
//command:A9
//Master: AA FF 01 16 A9 C1 C2 C3 C4(��đ��������) data0~data15 00(��ؑ�����־) bcc(�У���)
//-------------------------------------------
void Wr_DefCard(uchar *CardNum,uchar *CardD,uchar ClosOpen)
{	uchar i;
	uchar	txbuff[27];
	uchar rxbuff[7];
	CardStatus=0;
	txbuff[0]=0xAA;
	txbuff[1]=0xFF;
	txbuff[2]=0x01;
	txbuff[3]=0x16;
	txbuff[4]=0xA9;	//order
	for(i=0;i<4;i++)
		txbuff[5+i]=*CardNum++;		//cardNO.
	for(i=0;i<16;i++)
		txbuff[9+i]=*CardD++;
	txbuff[25]=ClosOpen;
	txbuff[26]=0;
	for(i=0;i<26;i++) 
		txbuff[26]^=txbuff[i];
	tty_write(txbuff, 27);
	
//--------------------------------------
//right7:BB FF 01 02 01(�Ѱ�������ʽ���55 13(�У���)
//Error6:BB FF 01 01(������) 33 77(�У���)
//---------------------------------------
	tty_read(rxbuff, 7);
	if(rxbuff[3]==0x02)
		CardStatus=0x01;
}
/***************************************************
WR_Block:AA
Command:AA FF 01 1E(������) AA C1 C2 C3 C4(������) 03(��鑺�) ff ff ff ff ff ff(��ܑ��)00(���֤��ܑ��A/B���
			data0~data15 00(��ؑ�����־�λ) BCC(�У���)
******************************************************/
void Wr_Card(uchar *CardNum,uchar *CardD,uchar *CardK,uchar CardB,uchar ClosOpen)
{	uchar i;
	uchar	txbuff[35];
	uchar rxbuff[7];
	CardStatus=0;
	txbuff[0]=0xAA;
	txbuff[1]=0xFF;
	txbuff[2]=0x01;
	txbuff[3]=0x1E;
	txbuff[4]=0xAA;	//order	
	for(i=0;i<4;i++)
		txbuff[5+i]=*CardNum++;		//cardNO.
	txbuff[9]=CardB;			//block number
	for(i=0;i<6;i++)
		txbuff[10+i]=*CardK++;
	txbuff[16]=0;
	for(i=0;i<16;i++)
		txbuff[17+i]=*CardD++;
	txbuff[33]=ClosOpen;
	txbuff[34]=0;
	for(i=0;i<34;i++) txbuff[34]^=txbuff[i];		//72
	tty_write(txbuff, 35);
	
//--------------------------------------
//right7:BB FF 01 02 01(�Ѱ�������ʽ���55 13(�У���)
//Error6:BB FF 01 01(������) 33 77(�У���)
//---------------------------------------
	tty_read(rxbuff, 7);
	if(rxbuff[3]==0x02)
		CardStatus=0x01;
}
//----------------------------------------
//command:AA FF 01 01(������) AB(������) FE(�У���)
 
void TurnOff_Card()
{	uchar i;
	uchar txbuff[8];
	uchar rxbuff[8];
	CardStatus=0;
	txbuff[0]=0xAA;
	txbuff[1]=0xFF;
	txbuff[2]=0x01;
	txbuff[3]=0x01;
	txbuff[4]=0xAB;	//search mode
	txbuff[5]=0XFE;
	tty_write(txbuff, 8);
//--------------------------------------
//right:BB FF 01 02 55 01(�Ѱ�������ʽ) 13(�У���)
//Error:BB FF 01 01(������) 33 77 
//---------------------------------------
	tty_read(rxbuff, 8);
	if(rxbuff[3]==0x02)
	{	rxbuff[7]=0;
		for(i=0;i<6;i++)
			rxbuff[7]^=rxbuff[i];
		if(rxbuff[7]==rxbuff[6])
			CardStatus=0x01;
	}
}
//---------------------------------------
//command:AA FF 01 01 AC(order) F9
//----------------------------------------
void ReqState()
{
	uchar i;
	uchar txbuff[7];
	uchar rxbuff[8];
	CardStatus=0;
	txbuff[0]=0xAA;
	txbuff[1]=0xFF;
	txbuff[2]=0x01;
	txbuff[3]=0x01;		//length
	txbuff[4]=0xAC;
	txbuff[5]=0;
	for(i=0;i<5;i++)
		txbuff[5]^=txbuff[i];
	tty_write(txbuff, 7);
//--------------------------------------
//right:BB FF 01 03 01(��ё���) 03(��鑺�) 00(�Ѱ�������ʽ) 44
//Error:BB FF 01 01(������) 33 77
//---------------------------------------
	tty_read(rxbuff, 8);
	if(rxbuff[3]==0x03)
		CardStatus=0x01;
}

void _console(void){
   uchar c[1];
   tty_read(c,1);
   printf("_");
}
