#include<iostream>
#include<cstdio>
#include<string.h>
#include <algorithm>
#include "generation.cpp"
using namespace std;

int main(int argc, char ** argv)
//int main()
{
	int States;
	char sudo99[9][10] = { 0 };
	States = checkargvs(argv[1], argv[2]);
	if (States == 0)//check argvs failed
		return 0;
	else if (States == 1)//�����վ�
	{
		int sum = atoi(argv[2]);
		//int sum = 1000000;
		//���½��������վ�����
		FILE *p = fopen("sudoku.txt", "w");
		char first_row[10] = "12356789";
		for (int i = 0; i < sum; i++)
		{
			if (i % 32 == 0)
				next_permutation(first_row, first_row + 8);
			memset(sudo99, 0, 90);
			creatsudo(sudo99, i, first_row);
			write2file(sudo99, p); //��ʱ�ڿ���̨���ڽ������
		}
		fclose(p);
		printf("%d sudokus were created successfully\n", sum);
	}
	else//�����������
	{
		FILE *question, *p;
		question = fopen(argv[2], "r+");
		p = fopen("sudoku.txt", "w");
		int lastone = 1;//�����һ���ܹ������
		while (readsudo(question, sudo99) || lastone--)
		{
			flag = 0;
			if (solvesudo(sudo99))//add:��ʱ�������ʧ�ܵĽ�����ڣ�Ŀǰδ�����޷�������������ܼ��϶Գ�ʼ�����Ϸ��Եļ��顣
				write2file(sudo99, p);
			else
				printf("This sudoku can't be solved\n");
		}
		fclose(p);
		fclose(question);
		printf("Finished\n");
	}
	return 0;
}
