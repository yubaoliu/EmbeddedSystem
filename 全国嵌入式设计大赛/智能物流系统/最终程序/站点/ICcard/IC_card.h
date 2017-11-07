#include "tty.h"
#include "stdio.h"
#define uchar unsigned char

/************************************************
master:AA FF 01 01 A1(order) F4(校验）
************************************************/
void Commu_test();


/***********************************************************
 CLR_Set:清读卡器状态到上电时的状态
 command:AA FF 01 01 A3(order) f6(校验)
***********************************************************/
void CLR_Set();


/**************************************************
Set_DefBlock:设置寻卡方式，读写数据的块号，数据区密码
command:AA FF 01 09 A4(Order) 00 01 FF FF FF FF FF FF(6密码) 07(异或校验) 
***************************************************/
void Set_DefBlock(uchar CardB,uchar *CardK);


//读缺省数据记录：A7
//;下传命令：AA FF 01 02(长度) A7 00(关卡标志:不关) f8(校验)
//-------------------------------------------
void Rd_DefBlock(uchar *CardNum,uchar *CardD,uchar ClosOpen);


//---------------------------------------
//命令：A8
//command:AA FF 01 0A(长度) A8(命令) 01 FF FF FF FF FF FF(6密码) 00 01 F7( 
//----------------------------------------
void Rd_Block(uchar *CardNum,uchar *CardD,uchar *CardK,uchar CardB,uchar ClosOpen);


//-----------------------------------------
//command:A9
//Master: AA FF 01 16 A9 C1 C2 C3 C4(四个卡号) data0~data15 00(关卡标志) bcc(校验)
//-------------------------------------------
void Wr_DefCard(uchar *CardNum,uchar *CardD,uchar ClosOpen);


/***************************************************
WR_Block:AA
Command:AA FF 01 1E(长度) AA C1 C2 C3 C4(卡号) 03(块号) ff ff ff ff ff ff(密码)00(验证密码A/B）
			data0~data15 00(关卡标志位) BCC(校验)
******************************************************/
void Wr_Card(uchar *CardNum,uchar *CardD,uchar *CardK,uchar CardB,uchar ClosOpen);


//----------------------------------------
//command:AA FF 01 01(长度) AB(命令) FE(校验)
 
void TurnOff_Card();


//---------------------------------------
//command:AA FF 01 01 AC(order) F9
//----------------------------------------
void ReqState();