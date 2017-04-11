#include "bank.h"

int available[MAXRESOURCE];                    //���п�����Դ����  
int maxneed[MAXPROCESS][MAXRESOURCE];          //����������  
int allocation[MAXPROCESS][MAXRESOURCE];	   //������� 
int need[MAXPROCESS][MAXRESOURCE];             //Ŀǰ������������  
int request[MAXPROCESS][MAXRESOURCE];          //������Ҫ��Դ�� 
bool finish[MAXPROCESS];                       //ϵͳ�Ƿ����㹻����Դ����  
int id[MAXPROCESS];                             //��¼���� 
int m,n;									   //m������,n����Դ

void Init()	//��ʼ��
{
	int i,j;  
    printf("������̵ĸ���:"); 
	scanf("%d",&m);
	printf("��������Դ������:"); 
	scanf("%d",&n);
	printf("������ÿ���������������Դ��,���� m * n ��������:\n");		//��������̶Ը���Դ�����������
	for(i=0;i<m;i++) 		
	{			
        for(j=0;j<n;j++) 
		{
            scanf("%d",&maxneed[i][j]); 
		}
	}
	printf("\n"); 


	printf("������ÿ�������Ѿ��������Դ��,���� m * n �������룺\n");		
	for(i=0;i<m;i++)  
	{
        for(j=0;j<n;j++) 
		{ 
            scanf("%d",&allocation[i][j]);						//�����̵�ǰ���������Դ��Ŀ
			need[i][j] = maxneed[i][j] - allocation[i][j];		//�����̵�ǰ����ĸ���Դ��Ŀ
            if(need[i][j]<0)  
            {  
                printf("��%d�����̵ĵ�%d����Դ�ķ���������������������\n",i+1,j+1);	//ĳ���̷�����Դ��Ŀ��������
                j--;  
                continue;  
            } 

		}
	}
	printf("\n"); 


	printf("�����������Դ���е���Ŀ:\n");	//������Դ���е���Ŀ
    for(i=0;i<n;i++)  
    {  
       scanf("%d",&available[i]);  
    }
	printf("\n"); 


   for(i=0;i<m;i++)//��ʼ�������̵�finishiֵ
	{
       finish[i]=false;  
    } 
   	printf("\n"); 


}



void bank()	//���м��㷨
{
    int i,num,flag = 0,p =0;  
    while(1)  
    {  
        show(m,n);  
		printf("\n"); 
input:  
		printf("������Ҫ������Դ�Ľ��̺�(ע:��1�����̺�Ϊ0,��������)\n");
        scanf("%d",&num); 
        if (num > m)  
        {  
			printf("û�иý��̣�����������\n");
            goto input;  
        }  
		printf("������ý���������ĸ���Դ������\n");
        for(i=0;i<n;i++)  
        {  
			scanf("%d",&request[num][i]);
        }
		fflush(stdin);
        for(i=0;i<n;i++)  
        {  
            if(request[num][i]>need[num][i])//����ý��̵ĵ�i����Դ���������ý���Ŀǰ�����i��Դ����  
            {  
				printf("������������������ý���Ŀǰ�������Դ����!\n"); 
                goto input;  
            }  
            if(request[num][i]>available[i])//����ý��̵ĵ�i����Դ��������ϵͳ���еĵ�i����Դ������  
           {  
			   printf("�����������������ϵͳĿǰ���õ���Դ��!\n"); 
                goto input;  
            }  
        } 


		for(i=0;i<n;i++)//������������ô�����Է���
        {  
            available[i]-=request[num][i];		//Ŀǰ������Դ = ԭ������Դ - ���������˵�  
            allocation[num][i]+=request[num][i];//Ŀǰ�������Դ = ԭ���Ѿ��������Դ + ���������˵� 
            need[num][i]-=request[num][i];		//�߳�Ŀǰ����Ҫ����Դ = ԭ������Ҫ����Դ - ��ȥ������õ���  
        }  


        if(safe())//�������AVAILABLE  ALLOCATION  NEED�����䶯���Ƿ�ᵼ��ϵͳ����ȫ  
        {  
			printf("��ȫ��ͬ���������!\n");
		}  
        else  
        {  
			printf("����ȫ���������󱻾ܾ�!\n");
            for(i=0;i<n;i++)		//��Ϊ����ȫ��û�з���ɹ�������һ���ָֻ�������ǰ��״̬
            {  
				available[i]+=request[num][i];		  
				allocation[num][i]-=request[num][i]; 
				need[num][i]+=request[num][i];		 
            }  
        } 

        for (i=0;i<n;i++)		//���ý��̵�ǰ��need�Ƿ��Ѿ�ȫ������
        {  
            if (need[num][i] == 0)  
            {  
                flag++;  
            }  
        }  
        if (flag == n)//���ȫ�����㣬���ͷŸý������з������Դ  
        {  
            for (i=0;i<n;i++)  
            {  
                available[i] += allocation[num][i];  
                allocation[num][i] = 0;  
                need[num][i] = 0;  
            } 
			printf("����%d�������ѱ�ȫ�����㣬�����ͷ���ռ�е���Դ��\n");
            flag = 0;  
        } 

	     for(i=0;i<m;i++)//ÿ���һ�ΰ�ȫ�ԾͿ��ܱ䶯finishֵ�������������۽����Ƿ��ܵõ����䣬��Ҫ�����н������¸�finishֵ
		 {
            finish[i]=false;  
         }  

		printf("�������ٴ����������?���밴1,���밴������\n");
        scanf("%d",&p); 
		fflush(stdin);

        if(p == 1)  
        {  
            continue;  
        } 
        break;  
    } 

}




bool safe()	//��ȫ�Լ��
{
    int i,j,k,s=0,tmp=0;
    int work[MAXRESOURCE];      //��������  
    for(i=0;i<n;i++)  
    {
        work[i]=available[i]; 
    }

	for(i=0;i<m;)  //i++�ڱ��ʽ�л����޸�
	{     
		for(j=0;j<n;j++)//ѭ�����ҵ�i��������Ҫ�ĸ�����Դ�� �Ƿ� ����ϵͳ���еĶ�Ӧ����Դ��  
		{  
			if(need[i][j]>work[j])//��i��������Ҫ�ĵ�j����Դ�� �� ϵͳ���еĵ�j����Դ��  
			{  
				break;  
			}  
		}  

		if(j==n && finish[i]==false)//�����i����������ĸ�����Դ����û�г���ϵͳ���еĶ�Ӧ��Դ�� �����Ҹý��̱��Ϊfalse 
		{   
			printf("P%d��������,��finish[%d] = false\n  ",i,i);
			printf("work =");
			printf("work (");
			for(k=0;k<n;k++)  
			{  
				printf("%d",work[k]);
				if(k<n-1)printf(" , ");
				if(k == n-1)printf(") + ");
				
			} 
			printf("allocation[%d](",i);
			for(k=0;k<n;k++)  
			{  
				printf("%d",allocation[i][k]);
				if(k<n-1)printf(" , ");
				if(k == n-1)printf(") = (");
				
			} 

			
			for(k=0;k<n;k++)  //��work��ֵΪ ��i�����̸����ѷ�����Դ����ϵͳ���еĶ�Ӧ��Դ��
			{  
				work[k]+=allocation[i][k];
				
			}

			
            for(k=0;k<n;k++)  
			{  
				printf("%d",work[k]);
				if(k<n-1)printf(" , ");
				if(k == n-1)printf(")  \n");
				
			} 

			finish[i]=true;		//���ý��̵�finish���Ϊtrue 
			printf("finish[%d] = true\n",i);
			id[s++]=i;	//��¼�Ѿ�������Ľ��̺�  
			i = 0;		//ֻҪ�ҵ��ˣ����ٴ�ͷ��ʼ����
		}  
		else	// ��ǰ������ j!=n || finish[i]!=false,Ҫô�ǽ��̵�������ڿ��õ���Դ����Ҫô�Ǹý����ѱ������
		{
			i++;	//ѭ���������������
			continue;  
		}	
		if(s==m)//�����н��̶���������ʱ  
		{  
			printf("ϵͳ�ǰ�ȫ��\n"); 
			printf("��ȫ����Ϊ:\n"); 
			for(i=0;i<s;i++)
			{  
				printf("%d",id[i]); 
				if(i!=s-1)  
				{  
					printf("-->"); 
				}  
			}
			printf("\n");

			return true;  
		}
	}//forѭ������ 
	
	printf("ϵͳ�ǲ���ȫ��\n");
    return false;

}



void show(int m,int n)	//��ʾ
{
	int i,j,k;   
	printf("ϵͳ��ǰ���õ���Դ��ĿΪ:\n ");
    for(i=0;i<n;i++)
	{
		printf(" %d  ",available[i]);
	}
    printf("\n"); 

	printf("�����̻���Ҫ����Դ��Ŀ��\n"); 
    for(j=0;j<m;j++)     
    {  
		printf("����%d",j);
        for(k=0;k<n;k++) 
		{
			printf(" %d ",need[j][k]); 
		}
		printf("\n");
    }     
    printf("\n");   

	printf("�����̽����Ѿ����䵽����Դ��:\n");
    for(j=0;j<m;j++)     
    {  
		printf("����%d",j);
        for(k=0;k<n;k++) 
		{
			printf(" %d ",allocation[j][k]); 
		}
		printf("\n");        
    }    
	printf("\n"); 
 

}




int main()
{
	Init();
	bank();
	return 0;
}