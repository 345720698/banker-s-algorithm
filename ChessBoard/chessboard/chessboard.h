#define _CRT_SECURE_NO_WARNINGS 1


#define rows 3		//��������
#define cols 3		//��������

void  init_board(char board[rows][cols],int x,int y);		//��ʼ������
void display_board(char board[rows][cols],int x,int y);		//��ʾ����
void player_move(char board[rows][cols],int x,int y);		//�������
void computer_move(char board[rows][cols]);					//��������
char check_win(char board[rows][cols],int x,int y);			//�ж���Ӯ


