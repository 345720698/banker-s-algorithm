#include "chessboard.h"
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

void menu()
{
	printf("********************************\n");
	printf("**********1->>��ʼ��Ϸ**********\n");
	printf("**********0->>��Ϸ����**********\n");
	printf("********************************\n");

}
void game()
{	int i=0,j=0;
	char rt = 0;
	char board[rows][cols]={ 0 } ;	//rows �� cols��ֵ�궨�������
	srand((unsigned)time(NULL));		//�������ֵ������
	init_board(board,rows,cols);
	display_board( board,rows,cols);
	do
	{	
		player_move(board,rows,cols);
		display_board( board,rows,cols);
		if((rt = check_win(board,rows,cols))!=' ')
		{
			break;
		}
		printf("������������......\n");
		Sleep(1000);
		computer_move(board);
		display_board( board,rows,cols);
		rt = check_win(board,rows,cols);
	
	}while(rt==' ');

	if(rt=='0')
	{	printf("����Ӯ�ˣ�\n");	}
	if(rt=='x')
	{	printf("���Ӯ�ˣ�\n");	}
	if(rt=='m')
	{	printf("��һ����ƽ�֣�\n");	}
			
}

int main()
{
	int input = 0;
	do
	{
		menu();
		printf("�����룺");
		scanf("%d",&input);
		switch(input)
		{
		case 1:		
			game();		
			break;
		case 0:		
			printf("��Ϸ������\n");		
			break;
		default:
			printf("�������󣡣�\n");
			break;
		}

	}while(input);

return 0;


}