#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
int add1,add2,chip1=10000,chip2=10000,count,cou;  //�p��[�`���ܼ�  add1=���a�[�`,add2=���a(AI)�[�`,count=���a�n�Ʀ���(�ΨӪ�lplayerCard()����num) cou=���a���P���� 
void setCard(int);  //�N1~52�ܦ�4*13 �æL�X��� 
int playerCard(int player[]);  //�N�üƳ]�����a
int AICard(int AI[]);  //�N�üƳ]��AI 
void sumPLCard(int);  //�[�`���a���P
void sumAICard(int);  //�[�`AI���P 
int asknum();  //A�X�{�ɰݭn+1�٬O+11
void decide(int,int);  //�P�_��Ĺ
int main(void)
{ 
    int i,j,k=0,pl=0,ai=0,poker[52]; //i,j,k�j���; pl,ai����playerCard(),AICard()����num 
    char answer;
    
	while(1)
	{
       add1=add2=count=cou=0;    //�]����� 
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_GREEN);
       printf("*****************************************\n");   //�W�h 
       printf("* 1.A�i�H�@��1��11\t\t\t*\n");
       printf("* 2.2~10�@�ӵP���I��\t\t\t*\n");
       printf("* 3.J,Q,K�@�Q�I\t\t\t\t*\n");
       printf("* 4.�C�@������\"500\"Ĺ�a�C�i�P\"+100\"\t*\n");
       printf("* 5.�W�L21�I�z��:-1000\t\t\t*\n");
       printf("* 6.�֦����i�P�B�I�Ƥp��21�h�L����:+3000*\n");
       printf("* 7.�p��21�I,�I�ƶV�h��Ĺ\t\t*\n");
       printf("* 8.�I�ƬۦP��,����aĹ\t\t\t*\n");
       printf("*****************************************\n");   //�W�h 
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
       printf(" ���a�w�X��:%d       ���a�w�X��:%d\n",chip1,chip2);
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
       if(chip1==0)
           {printf("�A�S���w�X�F!! �C������!\n");system("pause");return 0;}
       else if(chip2==0)
           {printf("���a�S���w�X�F!! �AĹ�F!\n");system("pause");return 0;} 
       printf("�O�_�}�l21�I�C��(y/n):");
       scanf("%c",&answer);
       fflush(stdin);
       printf("\n");
       if(answer=='y' || answer=='Y') //�n��21�I 
       {
	      srand(time(0));               //**
	      for(i=0;i<52;i++)             //�� 
	          poker[i]=i+1; 
   	      for(i=0;i<52;i++)             //�� 
	      { 
	 	      int j = rand() % 52 + 1;  //�� 
              int tmp = poker[i];
              poker[i] = poker[j];      //�� 
              poker[j] = tmp;           //**
	      }
	      while(1)   //�C�����j�� 
          { 
              if(add1>21)     //�P�_���a�O�_�W�L21 
              {
                  printf("�A�z�F!!\n\n");
                  chip1-=1000;
                  chip2+=1000;
                  system("pause");
                  break;
              }               //�P�_���a�O�_�W�L21 
              if(count==0)
              {
                 pl=playerCard(poker);
                 count++;
                 continue;
              }
              printf("�O�_�n���P(y/n):");
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
              	  for(k=0;k<10;k++)   //�P�_AI�[�P���з� 
                    {
                     
                        if(add2<=15)  //�H15�����,�Yadd2<=15,�N�~�򮳵P 
                           {ai=AICard(poker);cou++;}
                        else 
                           {AICard(poker); break;} //��add2>15,�L�X��� 
                    }                   //�P�_AI�[�P���з�  
                 decide(pl,ai); //�ǤJ���a�P���a���P������,�çP�_��Ĺ
                 system("pause"); 
                 break;
              }
              else
              {
                 printf("��J���~�A�Э��s��J!\n");
                 continue;
              }
          }          //�C�����j�� 
          system("cls");
          continue;
       } 
       else if(answer=='n' || answer=='N') //����21�I 
          break;
       else
       {
          printf("��J���~�A�Э��s��J!\n\n");
          system("pause");
          system("cls");
          continue;
       }
    }
	return 0;
}
void setCard(int random) //random=����playerCard(),AICard()���ǨӪ��ü� 
{
	int i,j; //�j��� 
	char num[13][3]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
	char color[4]={'\6','\3','\4','\5'}; 
	
	for(i=0;i<4;i++)  //�L�X��� 
	{
		if((random-1)/13==i)
		    printf("%c ",color[i]); 
	} 
	for(j=0;j<13;j++) //�L�X�Ʀr 
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
     static int num=0; //�p��Q�I�s����(�o�����a���ƪ��P) 
     if(count==0) //�C������,�Nnum�]����� 
        num=0;
     printf("�A���F:");
     setCard(player[num]);//�N�üư}�C��,��num�Ӽƭ�,�ǤJsetCard() 
     printf("\n");
     sumPLCard(player[num]); //�i�檱�a�I�ƪ��[�` 
     printf("\n");
     num+=2; //�C�����槹+2 
     return num;
}
int AICard(int AI[])
{
     int i;
     static int num=1; //�p��Q�I�s����(�o���q���_�ƪ��P) 
     if(add2>15) //��AI�I�ƥ[�`>15�h�L�XAI�⤤���P 
     {
         printf("���a���P��:");
         for(i=1;i<num;i++) //�N�üư}�C��, ��1,3,5...,num �����ƭ� ,�ǤJsetCard() 
             if(i%2==1)
                setCard(AI[i]);
         printf("\n\n");
         num=-1; //�C������,�Nnum�]����� 
     }
     else if(add2<=15 && num%2==1) //�[�`AI�⤤�P���I�� 
         sumAICard(AI[num]);
     num+=2; //�C�����槹+2 
     return num;
}
void sumPLCard(int card)
{
     int i; //�j��� 
     static int num=0; //�p��Q�I�s������ 
     for(i=0;i<13;i++) //�i��]��  
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
     printf("�ثe�[�`��:%d\n",add1);
}
void sumAICard(int card)
{
     int i; //�j���
     static int num=0; //�p��Q�I�s������  
     for(i=0;i<13;i++) //�i��]�� 
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
         printf("���a�[�`��:%d\n",add2);
} 
int asknum()
{
     int ask; //�NA�]�Ȭ�ask 
     while(1)
     {
        printf("�аݬO�n+1�٬O+11(��J1or11):");
        scanf("%d",&ask);
        fflush(stdin);
        if(ask==1 || ask==11)
           return ask;
        else
        {
           printf("��J���~�A�Э��s��J!\n");
           continue;
        }
     }
}
void decide(int pl,int ai)
{
     if(ai>=11 && add2<=21)
        {chip1-=3000;chip2+=3000;printf("���a�L����!!�A�A��F!!\n\n");}
     else if(pl>=10 && add1<=21)
        {chip1+=3000;chip2-=3000;printf("���߹L����!!�A�AĹ�F!!\n\n");}
     else if(add1>add2 && add1<=21 || add2>21)
        {
           if(add1>add2 && add1<=21)
              {chip1+=500+count*100;chip2-=500+count*100;printf("�AĹ�F!!\n\n");}
           else if(add2>21)
              {chip1+=1000;chip2-=1000;printf("���a�z�F!!\n\n");}
        } 
     else if(add1<add2 && add2<=21 || add1==add2)
        {chip1-=500+cou*100;chip2+=500+cou*100;printf("�A��F!!\n\n");}
}
