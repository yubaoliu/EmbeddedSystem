



tBoolean newTimeSet(void)
{
  char *str="����ʱ���趨ģʽ";
  char *str1="1.Сʱ�趨:";
  char *str2="2.�����趨:";
  char *str3="3.���趨:";
  char *str4;
  static char hour;
  static char minte;
  static char second;
  char h[2];
  char m[2];
  char s[2];
  char key;
  int i=0;
  tBoolean f=true;
  kboainit();
  lcdInit();
  clearAll();
  lcdWriteStr(1,1,str); 
  lcdWriteStr(2,1,str1);
  lcdWriteStr(3,1,str2);
  lcdWriteStr(4,1,str3);
  
  key=readkeyboard();
  //hour set
  if(key==1)
  {
    while(f)
    {
      clearAll();
      lcdWriteStr(1,1,str1);//"1.Сʱ�趨:"
      key=readkeyboard();
      if(key=='E')//�費��Ҫ������
      {
        hour=(h[0]-'0')*10+h[1]-'0';//����������
        f=false; 
        return true;
      }
      else
      {
        h[i++]=key;
        str4=&key;
        lcdWriteStr(2,i,str4);
      }
    }
  }
  //minite set
  else if(key==2)
  {
    while(f)
    {
      clearAll();
      lcdWriteStr(1,1,str2);
      key=readkeyboard();
      if(key=='E')//�費��Ҫ������
      {
        minte=(m[0]-'0')*10+m[1]-'0';//����������
        f=false;  
        return true;
      }
      else
      {
        m[i++]=key;
        str4=&key;
        lcdWriteStr(2,i,str4);
      }
    }
  }
  //second set
  else if(key==3)
  {
    while(f)
    {
      clearAll();
      lcdWriteStr(1,1,str3);
      key=readkeyboard();
     if(key=='E')//�費��Ҫ������
     {
       second=(s[0]+'0')*10+s[1]-'0';//����������
       f=false; 
       return true;
     }
    else
    {
      s[i++]=key;
      str4=&key;
      lcdWriteStr(2,i,str4);
    }
   }
  }
  else if(key=='E')
  {
    setTime(hour,minte,second);
    return false;
  }
 
}