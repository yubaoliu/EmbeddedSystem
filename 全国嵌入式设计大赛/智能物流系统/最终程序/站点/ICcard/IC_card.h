#include "tty.h"
#include "stdio.h"
#define uchar unsigned char

/************************************************
master:AA FF 01 01 A1(order) F4(У�飩
************************************************/
void Commu_test();


/***********************************************************
 CLR_Set:�������״̬���ϵ�ʱ��״̬
 command:AA FF 01 01 A3(order) f6(У��)
***********************************************************/
void CLR_Set();


/**************************************************
Set_DefBlock:����Ѱ����ʽ����д���ݵĿ�ţ�����������
command:AA FF 01 09 A4(Order) 00 01 FF FF FF FF FF FF(6����) 07(���У��) 
***************************************************/
void Set_DefBlock(uchar CardB,uchar *CardK);


//��ȱʡ���ݼ�¼��A7
//;�´����AA FF 01 02(����) A7 00(�ؿ���־:����) f8(У��)
//-------------------------------------------
void Rd_DefBlock(uchar *CardNum,uchar *CardD,uchar ClosOpen);


//---------------------------------------
//���A8
//command:AA FF 01 0A(����) A8(����) 01 FF FF FF FF FF FF(6����) 00 01 F7( 
//----------------------------------------
void Rd_Block(uchar *CardNum,uchar *CardD,uchar *CardK,uchar CardB,uchar ClosOpen);


//-----------------------------------------
//command:A9
//Master: AA FF 01 16 A9 C1 C2 C3 C4(�ĸ�����) data0~data15 00(�ؿ���־) bcc(У��)
//-------------------------------------------
void Wr_DefCard(uchar *CardNum,uchar *CardD,uchar ClosOpen);


/***************************************************
WR_Block:AA
Command:AA FF 01 1E(����) AA C1 C2 C3 C4(����) 03(���) ff ff ff ff ff ff(����)00(��֤����A/B��
			data0~data15 00(�ؿ���־λ) BCC(У��)
******************************************************/
void Wr_Card(uchar *CardNum,uchar *CardD,uchar *CardK,uchar CardB,uchar ClosOpen);


//----------------------------------------
//command:AA FF 01 01(����) AB(����) FE(У��)
 
void TurnOff_Card();


//---------------------------------------
//command:AA FF 01 01 AC(order) F9
//----------------------------------------
void ReqState();