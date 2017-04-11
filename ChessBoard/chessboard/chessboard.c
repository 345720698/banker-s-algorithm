#include "chessboard.h"
#include<stdio.h>
#include<stdlib.h>

void  init_board(char board[rows][cols],int x,int y)	//��ʼ������
{
	int i=0;
	int j=0;
	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			board[i][j] = ' ';
		}
	}


}

void display_board(char board[rows][cols],int x,int y)		//��ʾ����
{
	int i;
	for(i=0;i<x;i++)
	{
		printf("%c | %c | %c\n",board[i][0],board[i][1],board[i][2]);
		if(i<(x-1))
		{
			printf("---------\n");
		}
	}

}


void player_move(char board[rows][cols],int x,int y)		//������壬����¡�x��
{
	 int a = 0;  
     int b = 0;  
    while (1)  
    {  
        printf("�����������:");  
        scanf("%d %d", &a, &b);				  
        if ((a > 0 && a <= x) && (b > 0 && b <= y))      //�ж������Ƿ�Ϸ�,�������������꣬�����������±�
        {  
            if (board[a - 1][b - 1] == ' ')				 //�жϴ˴���û�б�����
            {  
                board[a - 1][b - 1] = 'x';  
                break;  
            }  
            else  
            {  
              printf("�˴��������ӣ��������ڴ˴�.\n");  
            }  
        }  
        else  
        {  
            printf("�������벻�Ϸ�\n");  
        }  
    }  

}

void computer_move(char board[rows][cols])		//�������壬�����¡�0��
{
	while (1)  
    {   
		int  x = 0;  
		int  y = 0; 
		x = rand() % 3;			//���±�Ϸ���ȡ������µ�����ֻ��Ϊ0��1��2
        y = rand() % 3;			//ȡ������µ�����ֻ��Ϊ0��1��2
		
		if (board[x][y] == ' ')  
        {  
            board[x][y] = '0'; 
            break;  
		} 
    }  
}


int board_full(char board[rows][cols],int x,int y)		//��������Ƿ��п�λ
{	int i=0,j=0;
	for(i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			if(board[i][j]==' ')
				return 0;
		}
	}
return 1;
}

char check_win(char board[rows][cols],int x,int y)		//�ж���Ӯ
{	
	int i=0,j=0;//�ж���ҵ���Ӯ������µ���x, Ӯ�û�����������x
	int ret = board_full(board,rows,cols );

	for(i=0;i<x;i++)
	{	
		if ((board[i][0]==board[i][1]) && (board[i][1]==board[i][2]) && (board[i][0]=='x'))		//�ж�һ�е������Ƿ����
		{
		return 'x';
		}
	}
		

	for(j=0;j<y;j++)
	{
		if(( board[0][j]==board[1][j]) && (board[1][j]==board[2][j]) &&(board[0][j]=='x'))	//�ж�һ�е������Ƿ����
		{
		return 'x';
		}

	}

	if((board[0][0]==board[1][1]) &&(board[1][1]==board[2][2]) &&(board[0][0]=='x'))	//�ж�һ���Խ��ߵ������Ƿ����
	{	
	
		return 'x';
	}		
	
		
	
	if((board[0][2]==board[1][1]) && (board[1][1]==board[2][0]) &&(board[0][2]=='x'))		//�ж���һ���Խ��ߵ������Ƿ����
	{

		return 'x';
	}
	


	
	for(i=0;i<x;i++)		//�жϵ��Ե���Ӯ�������µ���0, Ӯ�û�����������0,
	{	
		if (( board[i][0]==board[i][1]) && (board[i][1]==board[i][2]) && (board[i][0]=='0'))		
		{
	
		return '0';
		}

	}
	for(j=0;j<y;j++)
	{
		if(( board[0][j]==board[1][j]) && (board[1][j]==board[2][j]) &&(board[0][j]=='0'))	
		{
		return '0';
		}
	}

	if(( board[0][0]==board[1][1]) &&( board[1][1]==board[2][2]) &&(board[0][0]=='0'))		
	{
		return '0';
	}		
	
		
	
	if(( board[0][2]==board[1][1]) && (board[1][1]==board[2][0]) &&(board[0][2]=='0'))		
	{
		return '0';
	}

		if(ret==1)		//�ж������Ƿ�������
	{
		return 'm';
	}
	

return  ' ';

}

