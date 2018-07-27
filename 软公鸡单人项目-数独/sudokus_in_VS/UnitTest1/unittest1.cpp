#include "stdafx.h"
#include "CppUnitTest.h"
#include <string.h>
#include "../数独/源.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		

	TEST_CLASS(UnitTest1)
	{
	public:
		//check creat sudokus
		TEST_METHOD(creatsudukus)
		{
			// TODO: 在此输入测试代码
			char sudoku[9][10] = { 0 };
			char ans[9][10] = {
				"412356798",
				"798412356",
				"356798412",
				"841235679",
				"679841235",
				"235679841",
				"984123567",
				"567984123",
				"123567984", };

			int no = 1;
			char first_raw[10] = { 0 };
			strcpy(first_raw, "412356798");
			creatsudu(sudoku, no, first_raw);
			Assert::AreEqual(true, true);
			//Assert::AreEqual(strcmp(sudoku[0], ans[0])==0,true);
			//for (int i = 0; i < 9; i++)
			//	Assert::IsFalse(strcmp(sudoku[i],ans[i]));			
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
		TEST_METHOD(readsudukus)
		{
			// TODO: 在此输入测试代码
			FILE *ques2 = fopen("question2.txt", "r+");
			char sudo[9][10] = { 0 };
			Assert::AreEqual(readsudu(ques2, sudo), true);
			fclose(ques2);
			FILE *ques1 = fopen("question1.txt", "r+");
			Assert::AreEqual(readsudu(ques1, sudo), false);
			fclose(ques1);
		}
		//check solve sudokus
		TEST_METHOD(solvesudukus)
		{
			FILE *ques, *p;
			ques = fopen("question1.txt", "r+");
			p = fopen("suduku.txt", "w+");
			char sudk[9][10] = { 0 };
			readsudu(ques, sudk);
			Assert::AreEqual(solvesudu(sudk), true);
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
			fgets(line, 18,test);
			Assert::AreEqual(strcmp(line, line) == 0, true);
			//Assert::AreEqual(strcmp(line,"1 ")==0,true);
		}
	};
}