#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
int add1,add2,chip1=10000,chip2=10000,count,cou;  //計算加總的變數  add1=玩家加總,add2=莊家(AI)加總,count=玩家要排次數(用來初始playerCard()中的num) cou=莊家拿牌次數 
void setCard(int);  //將1~52變成4*13 並印出花色 
int playerCard(int player[]);  //將亂數設給玩家
int AICard(int AI[]);  //將亂數設給AI 
void sumPLCard(int);  //加總玩家的牌
void sumAICard(int);  //加總AI的牌 
int asknum();  //A出現時問要+1還是+11
void decide(int,int);  //判斷輸贏
int main(void)
{ 
    int i,j,k=0,pl=0,ai=0,poker[52]; //i,j,k迴圈用; pl,ai接收playerCard(),AICard()中的num 
    char answer;
    
	while(1)
	{
       add1=add2=count=cou=0;    //設為初值 
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_GREEN);
       printf("*****************************************\n");   //規則 
       printf("* 1.A可以作為1或11\t\t\t*\n");
       printf("* 2.2~10作該牌之點數\t\t\t*\n");
       printf("* 3.J,Q,K作十點\t\t\t\t*\n");
       printf("* 4.每一場底價\"500\"贏家每張牌\"+100\"\t*\n");
       printf("* 5.超過21點爆掉:-1000\t\t\t*\n");
       printf("* 6.擁有五張牌且點數小於21則過五關:+3000*\n");
       printf("* 7.小於21點,點數越多者贏\t\t*\n");
       printf("* 8.點數相同時,算莊家贏\t\t\t*\n");
       printf("*****************************************\n");   //規則 
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
       printf(" 玩家籌碼為:%d       莊家籌碼為:%d\n",chip1,chip2);
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
       if(chip1==0)
           {printf("你沒有籌碼了!! 遊戲結束!\n");system("pause");return 0;}
       else if(chip2==0)
           {printf("莊家沒有籌碼了!! 你贏了!\n");system("pause");return 0;} 
       printf("是否開始21點遊戲(y/n):");
       scanf("%c",&answer);
       fflush(stdin);
       printf("\n");
       if(answer=='y' || answer=='Y') //要玩21點 
       {
	      srand(time(0));               //**
	      for(i=0;i<52;i++)             //亂 
	          poker[i]=i+1; 
   	      for(i=0;i<52;i++)             //數 
	      { 
	 	      int j = rand() % 52 + 1;  //產 
              int tmp = poker[i];
              poker[i] = poker[j];      //生 
              poker[j] = tmp;           //**
	      }
	      while(1)   //遊戲內迴圈 
          { 
              if(add1>21)     //判斷玩家是否超過21 
              {
                  printf("你爆了!!\n\n");
                  chip1-=1000;
                  chip2+=1000;
                  system("pause");
                  break;
              }               //判斷玩家是否超過21 
              if(count==0)
              {
                 pl=playerCard(poker);
                 count++;
                 continue;
              }
              printf("是否要取牌(y/n):");
              scanf("%c",&answer);
              fflush(stdin);
              if(answer=='y' || answer=='Y')
              {
                 pl=playerCard(poker);
                 count++;
                 continue;
              }
              else if(answer=='n' || answer=='N')
              {
              	  for(k=0;k<10;k++)   //判斷AI加牌的標準 
                    {
                     
                        if(add2<=15)  //以15為基準,若add2<=15,就繼續拿牌 
                           {ai=AICard(poker);cou++;}
                        else 
                           {AICard(poker); break;} //當add2>15,印出花色 
                    }                   //判斷AI加牌的標準  
                 decide(pl,ai); //傳入玩家與莊家拿牌的次數,並判斷輸贏
                 system("pause"); 
                 break;
              }
              else
              {
                 printf("輸入錯誤，請重新輸入!\n");
                 continue;
              }
          }          //遊戲內迴圈 
          system("cls");
          continue;
       } 
       else if(answer=='n' || answer=='N') //不玩21點 
          break;
       else
       {
          printf("輸入錯誤，請重新輸入!\n\n");
          system("pause");
          system("cls");
          continue;
       }
    }
	return 0;
}
void setCard(int random) //random=接收playerCard(),AICard()中傳來的亂數 
{
	int i,j; //迴圈用 
	char num[13][3]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
	char color[4]={'\6','\3','\4','\5'}; 
	
	for(i=0;i<4;i++)  //印出花色 
	{
		if((random-1)/13==i)
		    printf("%c ",color[i]); 
	} 
	for(j=0;j<13;j++) //印出數字 
	{
		if(random%13==0)
		   {printf("%s",num[12]); break;}
        else if(random%13==j)
            printf("%s",num[j-1]);
    }
    printf("  ");
}
int playerCard(int player[]) 
{
     int i;
     static int num=0; //計算被呼叫次數(發給玩家偶數的牌) 
     if(count==0) //遊戲結束,將num設為初值 
        num=0;
     printf("你抽到了:");
     setCard(player[num]);//將亂數陣列中,第num個數值,傳入setCard() 
     printf("\n");
     sumPLCard(player[num]); //進行玩家點數的加總 
     printf("\n");
     num+=2; //每次執行完+2 
     return num;
}
int AICard(int AI[])
{
     int i;
     static int num=1; //計算被呼叫次數(發給電腦奇數的牌) 
     if(add2>15) //當AI點數加總>15則印出AI手中的牌 
     {
         printf("莊家的牌為:");
         for(i=1;i<num;i++) //將亂數陣列中, 第1,3,5...,num 中的數值 ,傳入setCard() 
             if(i%2==1)
                setCard(AI[i]);
         printf("\n\n");
         num=-1; //遊戲結束,將num設為初值 
     }
     else if(add2<=15 && num%2==1) //加總AI手中牌的點數 
         sumAICard(AI[num]);
     num+=2; //每次執行完+2 
     return num;
}
void sumPLCard(int card)
{
     int i; //迴圈用 
     static int num=0; //計算被呼叫的次數 
     for(i=0;i<13;i++) //進行設值  
     {
         if(card%13==0)
             {num=10; break;}
         else if(card%13==12)
             {num=10; break;}
         else if(card%13==11)
             {num=10; break;}
         else if(card%13==1)
             {num=asknum(); break;}
         else
             {num=card%13; break;}
     }
     add1+=num;
     printf("目前加總為:%d\n",add1);
}
void sumAICard(int card)
{
     int i; //迴圈用
     static int num=0; //計算被呼叫的次數  
     for(i=0;i<13;i++) //進行設值 
     {
         if(card%13==0)
             {num=10; break;}
         else if(card%13==12)
             {num=10; break;}
         else if(card%13==11)
             {num=10; break;}
         else
             {num=card%13; break;}
     }
     add2+=num;
     if(add2>15)
         printf("莊家加總為:%d\n",add2);
} 
int asknum()
{
     int ask; //將A設值為ask 
     while(1)
     {
        printf("請問是要+1還是+11(輸入1or11):");
        scanf("%d",&ask);
        fflush(stdin);
        if(ask==1 || ask==11)
           return ask;
        else
        {
           printf("輸入錯誤，請重新輸入!\n");
           continue;
        }
     }
}
void decide(int pl,int ai)
{
     if(ai>=11 && add2<=21)
        {chip1-=3000;chip2+=3000;printf("莊家過五關!!，你輸了!!\n\n");}
     else if(pl>=10 && add1<=21)
        {chip1+=3000;chip2-=3000;printf("恭喜過五關!!，你贏了!!\n\n");}
     else if(add1>add2 && add1<=21 || add2>21)
        {
           if(add1>add2 && add1<=21)
              {chip1+=500+count*100;chip2-=500+count*100;printf("你贏了!!\n\n");}
           else if(add2>21)
              {chip1+=1000;chip2-=1000;printf("莊家爆了!!\n\n");}
        } 
     else if(add1<add2 && add2<=21 || add1==add2)
        {chip1-=500+cou*100;chip2+=500+cou*100;printf("你輸了!!\n\n");}
}
