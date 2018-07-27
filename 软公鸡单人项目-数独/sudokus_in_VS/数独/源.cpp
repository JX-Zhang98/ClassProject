#include<iostream>
#include<cstdio>
#include<string.h>
#include <ctime>
#include <algorithm>
//#include "generation.cpp"
using namespace std;

bool readsudu(FILE *ques, char sudu[][10]);
void creatsudu(char sudu[][10], int no, char firstrow[10]);
bool solvesudu(char sudu[][10]);
void write2file(char sudu[][10], FILE *p);
void pushback(char su[10], int m, char sou[10]);
void exch_row(char sudu[][10], int row);
int count_blank(char sudu[][10]);
void backtrace(char sudu[][10], int cont);
bool isPlace(char sudu[][10], int count);
int checkargvs(char *argv1, char *argv2);
void switchsudo(char sudu[][10], int st, int ed);
bool flag = 0;//标记当前解是否有效
int main(int argc, char ** argv)
//int main()
{
	int States;
	char sudu99[9][10] = { 0 };
	States = checkargvs(argv[1], argv[2]);
	if (States == 0)//check argvs failed
		return 0;
	else if (States==1)//生成终局
	{		
		int sum = atoi(argv[2]);
		//int sum = 1000000;
		//以下进行数独终局生成
		FILE *p = fopen("suduku.txt", "w");
		char first_row[10] = "12356789";
		time_t time_st, time_ed;
		time_st = time(NULL);
		for (int i = 0; i < sum; i++)
		{
			if (i % 32 == 0)
				next_permutation(first_row, first_row + 8);
			memset(sudu99, 0, 90);
			creatsudu(sudu99, i, first_row);
			write2file(sudu99, p); //暂时在控制台窗口进行输出
		}
		time_ed = time(NULL);
		fclose(p);
		printf("%d sudukus were created in %d seconds\n", sum, difftime(time_ed, time_st));
	}
	else//解决数独问题
	{		
		FILE *question, *p;
		question = fopen(argv[2], "r+");
		p = fopen("suduku.txt", "w");
		int lastone = 1;//让最后一个能够解出来
		while (readsudu(question, sudu99) || lastone--)
		{
			flag = 0;
			if (solvesudu(sudu99))//add:暂时保留求解失败的解决窗口，目前未遇到无法求解的情况。可能加上对初始数独合法性的检验。
				write2file(sudu99, p);
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
		if(atoi(a2)>1000000)
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
bool readsudu(FILE *ques, char sudu[][10])
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
				sudu[i][j++] = line[k];
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
void creatsudu(char sudu[][10], int no, char firstrow[10])
{
	//printf("Creating sudu[%d]:\n", no);
	sudu[0][0] = '4';
	strcat(sudu[0], firstrow);
	int pushlist[9] = { 0,3,6,1,4,7,2,5,8 };
	for (int i = 1; i < 9; i++)
		pushback(sudu[i], pushlist[i], sudu[0]);
	int operation = no % 32;
	exch_row(sudu, operation);
	return;
}
bool solvesudu(char sudu[][10])
{//采用回溯法求解
	backtrace(sudu, 0);
	return true;
}
void write2file(char sudu[][10], FILE *p)
{
	int i, j, cont = 0;
	char ans[180] = { 0 };
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 8; j++)
		{
			ans[cont++] = sudu[i][j];
			ans[cont++] = ' ';
		}
		ans[cont++] = sudu[i][8];
		ans[cont++] = '\n';
	}
	ans[cont++] = '\n';
	fwrite(ans, 163, 1, p);
}
void exch_row(char sudu[][10], int op)
{
	if (op % 2)
		switchsudo(sudu, 1, 2);
	op /= 2;
	switch (op)
	{
	case 0:return;
	case 1:switchsudo(sudu, 3, 4); break;
	case 2:switchsudo(sudu, 5, 4); break;
	case 3:switchsudo(sudu, 3, 5); break;
	case 4:switchsudo(sudu, 6, 7); break;
	case 5:switchsudo(sudu, 6, 8); break;
	case 6:switchsudo(sudu, 7, 8); break;
	case 7:switchsudo(sudu, 3, 4); switchsudo(sudu, 6, 7); break;
	case 8:switchsudo(sudu, 3, 4); switchsudo(sudu, 7, 8); break;
	case 9:switchsudo(sudu, 3, 4); switchsudo(sudu, 6, 8); break;
	case 10:switchsudo(sudu, 4, 5); switchsudo(sudu, 6, 7); break;
	case 11:switchsudo(sudu, 4, 5); switchsudo(sudu, 7, 8); break;
	case 12:switchsudo(sudu, 4, 5); switchsudo(sudu, 6, 8); break;
	case 13:switchsudo(sudu, 3, 5); switchsudo(sudu, 6, 7); break;
	case 14:switchsudo(sudu, 3, 5); switchsudo(sudu, 7, 8); break;
	case 15:switchsudo(sudu, 3, 5); switchsudo(sudu, 6, 8); break;
	}
	return;
}
void switchsudo(char sudu[][10], int st, int ed)
{
	char tmp[10] = { 0 };
	strcpy(tmp, sudu[st]);
	strcpy(sudu[st], sudu[ed]);
	strcpy(sudu[ed], tmp);
}
void pushback(char su[10], int m, char sou[10])
{
	char cop[20] = { 0 };
	strcpy(cop, sou);
	int i;
	for (i = 0; i < 9; i++)
		su[(i + m) % 9] = cop[i];
}
int count_blank(char sudu[][10])
{
	int i, j, cont = 0;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			if (sudu[i][j] == '0')
				cont++;
	return cont;
}
void backtrace(char sudu[][10], int cont)
{
	if (cont == 81 || flag)
	{
		flag = 1;
		return;
	}
	int row = cont / 9;
	int col = cont % 9;
	if (sudu[row][col] == '0')
	{
		for (int i = 1; i <= 9; ++i)
		{
			sudu[row][col] = i + '0';//赋值  
			if (isPlace(sudu, cont)) //可以放  
			{
				backtrace(sudu, cont + 1);//进入下一层
				if (flag)
					return;
			}
		}
		sudu[row][col] = '0';//回溯  
	}
	else
		backtrace(sudu, cont + 1);
}
bool isPlace(char sudu[][10], int cont)
{
	int row = cont / 9;
	int col = cont % 9;
	int j;
	//同一行  
	for (j = 0; j < 9; ++j)
		if (sudu[row][j] == sudu[row][col] && j != col)
			return false;
	//同一列  
	for (j = 0; j < 9; ++j)
		if (sudu[j][col] == sudu[row][col] && j != row)
			return false;
	//同一小格  
	int tempRow = row / 3 * 3;
	int tempCol = col / 3 * 3;
	for (j = tempRow; j < tempRow + 3; ++j)
		for (int k = tempCol; k < tempCol + 3; ++k)
			if (sudu[j][k] == sudu[row][col] && j != row && k != col)
				return false;
	return true;
}