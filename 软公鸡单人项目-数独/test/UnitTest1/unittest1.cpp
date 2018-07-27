#include "stdafx.h"
#include "CppUnitTest.h"
#include <string.h>
#include "../test/源.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{

	TEST_CLASS(UnitTest1)
	{
	public:
		//check creat sudokus
		TEST_METHOD(creatsudokus)
		{
			// TODO: 在此输入测试代码
			char sudoku[9][10] = { 0 };
			int no = 1;
			char first_raw[10] = { 0 };
			strcpy(first_raw, "412356798");
			int i;
			for (i = 0; i < 32; i++)
			{
				creatsudo(sudoku, i, first_raw);
				memset(sudoku, 0, sizeof(sudoku));
			}	
		}
		//check argvs
		TEST_METHOD(argvs1)
		{
			// TODO: 在此输入测试代码
			char *a1 = NULL;
			char *a2 = NULL;
			Assert::AreEqual(checkargvs(a1, a2), 0);
			char *b1 = "-c";
			char *b2 = "10000000";
			Assert::AreEqual(checkargvs(b1, b2), 0);
			char *b3 = "1000001";
			Assert::AreEqual(checkargvs(b1, b3), 0);
			char *b4 = "10000c";
			Assert::AreEqual(checkargvs(b1, b4), 0);
			char *b5 = "1000000";
			Assert::AreEqual(checkargvs(b1, b5), 1);
			char *a3 = "cc";
			Assert::AreEqual(checkargvs(a3, b5), 0);
		}
		TEST_METHOD(argvs2)
		{
			// TODO: 在此输入测试代码
			char *a = "-s";
			char *b1 = "question";
			Assert::AreEqual(checkargvs(a, b1), 0);
			char *b2 = "question .txt";
			Assert::AreEqual(checkargvs(a, b2), 0);
			char *b3 = "question2.txt";
			Assert::AreEqual(checkargvs(a, b3), 2);
		}
		//check read sudokus
		TEST_METHOD(readsudokus)
		{
			// TODO: 在此输入测试代码
			FILE *ques2 = fopen("question2.txt", "r+");
			char sudo[9][10] = { 0 };
			Assert::AreEqual(readsudo(ques2, sudo), true);
			fclose(ques2);
			FILE *ques1 = fopen("question1.txt", "r+");
			Assert::AreEqual(readsudo(ques1, sudo), false);
			fclose(ques1);
		}
		//check solve sudokus
		TEST_METHOD(solvesudokus)
		{
			FILE *ques, *p;
			ques = fopen("question1.txt", "r+");
			p = fopen("sudoku.txt", "w+");
			char sudk[9][10] = { 0 };
			readsudo(ques, sudk);
			Assert::AreEqual(solvesudo(sudk), true);
			fclose(p);
			fclose(ques);
		}
		//check write
		TEST_METHOD(writetofile)
		{
			char matrix[9][10] = { "111111111","222222222","333333333","444444444","555555555","666666666","777777777","888888888","999999999" };
			FILE  *test = fopen("test.txt", "w");
			write2file(matrix, test);
			char line[20] = { 0 };
			fgets(line, 18, test);
		}
		TEST_METHOD(MAIN)
		{
			char *arg[10];
			arg[1] = (char*)malloc(10);
			arg[2] = (char*)malloc(10);
			strcpy(arg[1], "-c");
			strcpy(arg[2], "1000");
			Assert::AreEqual(main(3, arg), 0);
			memset(arg[1], 0, sizeof(arg[1]));
			memset(arg[2], 0, sizeof(arg[2]));
			strcpy(arg[1], "-s");
			strcpy(arg[2], "question1.txt");
			Assert::AreEqual(main(3, arg), 0);
		}
	};
}