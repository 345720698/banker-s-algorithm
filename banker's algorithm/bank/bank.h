#define _CRT_SECURE_NO_WARNINGS 1
#ifndef _BANK_H_
#define _BANK_H_
#include<stdio.h>
#include<windows.h>


#define MAXPROCESS 50       //��������  
#define MAXRESOURCE 100		//�����Դ����

void Init();	//��ʼ��
void bank();	//���м��㷨
bool safe();	//��ȫ�Լ��
void show(int,int);	//��ʾ



#endif




