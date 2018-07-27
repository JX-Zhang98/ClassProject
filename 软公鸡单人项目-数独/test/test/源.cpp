#include<iostream>
#include<cstdio>
#include<string.h>
#include <ctime>
#include <algorithm>
//#include "generation.cpp"
using namespace std;

bool readsudo(FILE *ques, char sudo[][10]);
void creatsudo(char sudo[][10], int no, char firstrow[10]);
bool solvesudo(char sudo[][10]);
void write2file(char sudo[][10], FILE *p);
void pushback(char su[10], int m, char sou[10]);
void exch_row(char sudo[][10], int row);
//int count_blank(char sudo[][10]);
void backtrace(char sudo[][10], int cont);
bool isPlace(char sudo[][10], int count);
int checkargvs(char *argv1, char *argv2);
void switchsudo(char sudo[][10], int st, int ed);
bool flag = 0;//标记当前解是否有效
int main(int argc, char ** argv)
//int main()
{
	int States;
	char sudo99[9][10] = { 0 };
	States = checkargvs(argv[1], argv[2]);
	if (States == 0)//check argvs failed
		return 0;
	else if (States == 1)//生成终局
	{
		int sum = atoi(argv[2]);
		//int sum = 1000000;
		//以下进行数独终局生成
		FILE *p = fopen("sudoku.txt", "w");
		char first_row[10] = "12356789";
		clock_t time_st, time_ed;
		time_st = clock();
		for (int i = 0; i < sum; i++)
		{
			if (i % 32 == 0)
				next_permutation(first_row, first_row + 8);
			memset(sudo99, 0, 90);
			creatsudo(sudo99, i, first_row);
			write2file(sudo99, p); //暂时在控制台窗口进行输出
		}
		time_ed = clock();
		fclose(p);
		printf("%d sudokus were created in %lf seconds\n", sum, time_ed - time_st);
	}
	else//解决数独问题
	{
		FILE *question, *p;
		question = fopen(argv[2], "r+");
		p = fopen("sudoku.txt", "w");
		int lastone = 1;//让最后一个能够解出来
		while (readsudo(question, sudo99) || lastone--)
		{
			flag = 0;
			if (solvesudo(sudo99))//add:暂时保留求解失败的解决窗口，目前未遇到无法求解的情况。可能加上对初始数独合法性的检验。
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

int checkargvs(char *a1, char *a2)
{
	if (a1 == NULL || a2 == NULL)
	{
		printf("Please add enouth argvs\n");
		return 0;
	}
	if (!strcmp(a1, "-c"))
	{
		if (strlen(a2) > 7)
		{
			printf("The num is too large!I can't finish it!\n");
			return 0;
		}
		for (int i = 0; i < strlen(a2); i++)
		{
			if (a2[i] >= '0'&&a2[i] <= '9')
				continue;
			printf("The argv[2] is illegal!\n");
			return 0;
		}
		if (atoi(a2) > 1000000)
		{
			printf("The num is too large!I can't finish it!\n");
			return 0;
		}
		return 1;
	}
	else if (!strcmp(a1, "-s"))
	{
		char path[100] = { 0 };
		FILE *ques = fopen(a2, "r+");
		if (ques == NULL)
		{
			printf("The file path is wrong.\nPlease check your file path.\n");
			return 0;
		}
		fclose(ques);
		return 2;
	}
	else
		return 0;
}
bool readsudo(FILE *ques, char sudo[][10])
{
	int i, j, k;
	char line[20] = { 0 };
	while (1)
	{
		for (i = 0; i < 9; i++)
		{
			fgets(line, 18, ques);
			for (k = j = 0; k < strlen(line); k += 2)
			{
				sudo[i][j++] = line[k];
			}
			getc(ques);
		}
		char c = getc(ques);
		if (c == '\n')
			return true;
		else
			return false;
	}
}
void creatsudo(char sudo[][10], int no, char firstrow[10])
{
	//printf("Creating sudo[%d]:\n", no);
	sudo[0][0] = '4';
	strcat(sudo[0], firstrow);
	int pushlist[9] = { 0,3,6,1,4,7,2,5,8 };
	for (int i = 1; i < 9; i++)
		pushback(sudo[i], pushlist[i], sudo[0]);
	int operation = no % 32;
	exch_row(sudo, operation);
}
bool solvesudo(char sudo[][10])
{//采用回溯法求解
	backtrace(sudo, 0);
	return true;
}
void write2file(char sudo[][10], FILE *p)
{
	int i, j, cont = 0;
	char ans[180] = { 0 };
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 8; j++)
		{
			ans[cont++] = sudo[i][j];
			ans[cont++] = ' ';
		}
		ans[cont++] = sudo[i][8];
		ans[cont++] = '\n';
	}
	ans[cont++] = '\n';
	fwrite(ans, 163, 1, p);
}
void exch_row(char sudo[][10], int op)
{
	if (op % 2)
		switchsudo(sudo, 1, 2);
	op /= 2;
	switch (op)
	{
	case 0:return;
	case 1:switchsudo(sudo, 3, 4); break;
	case 2:switchsudo(sudo, 5, 4); break;
	case 3:switchsudo(sudo, 3, 5); break;
	case 4:switchsudo(sudo, 6, 7); break;
	case 5:switchsudo(sudo, 6, 8); break;
	case 6:switchsudo(sudo, 7, 8); break;
	case 7:switchsudo(sudo, 3, 4); switchsudo(sudo, 6, 7); break;
	case 8:switchsudo(sudo, 3, 4); switchsudo(sudo, 7, 8); break;
	case 9:switchsudo(sudo, 3, 4); switchsudo(sudo, 6, 8); break;
	case 10:switchsudo(sudo, 4, 5); switchsudo(sudo, 6, 7); break;
	case 11:switchsudo(sudo, 4, 5); switchsudo(sudo, 7, 8); break;
	case 12:switchsudo(sudo, 4, 5); switchsudo(sudo, 6, 8); break;
	case 13:switchsudo(sudo, 3, 5); switchsudo(sudo, 6, 7); break;
	case 14:switchsudo(sudo, 3, 5); switchsudo(sudo, 7, 8); break;
	case 15:switchsudo(sudo, 3, 5); switchsudo(sudo, 6, 8); break;
	}
}
void switchsudo(char sudo[][10], int st, int ed)
{
	char tmp[10] = { 0 };
	strcpy(tmp, sudo[st]);
	strcpy(sudo[st], sudo[ed]);
	strcpy(sudo[ed], tmp);
}
void pushback(char su[10], int m, char sou[10])
{
	char cop[20] = { 0 };
	strcpy(cop, sou);
	int i;
	for (i = 0; i < 9; i++)
		su[(i + m) % 9] = cop[i];
}

void backtrace(char sudo[][10], int cont)
{
	if (cont == 81 || flag)
	{
		flag = 1;
		return;
	}
	int row = cont / 9;
	int col = cont % 9;
	if (sudo[row][col] == '0')
	{
		for (int i = 1; i <= 9; ++i)
		{
			sudo[row][col] = i + '0';//赋值  
			if (isPlace(sudo, cont)) //可以放  
			{
				backtrace(sudo, cont + 1);//进入下一层
				if (flag)
					return;
			}
		}
		sudo[row][col] = '0';//回溯  
	}
	else
		backtrace(sudo, cont + 1);
}
bool isPlace(char sudo[][10], int cont)
{
	int row = cont / 9;
	int col = cont % 9;
	int j;
	//同一行  
	for (j = 0; j < 9; ++j)
		if (sudo[row][j] == sudo[row][col] && j != col)
			return false;
	//同一列  
	for (j = 0; j < 9; ++j)
		if (sudo[j][col] == sudo[row][col] && j != row)
			return false;
	//同一小格  
	int tempRow = row / 3 * 3;
	int tempCol = col / 3 * 3;
	for (j = tempRow; j < tempRow + 3; ++j)
		for (int k = tempCol; k < tempCol + 3; ++k)
			if (sudo[j][k] == sudo[row][col] && j != row && k != col)
				return false;
	return true;
}