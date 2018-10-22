
/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to  PrismTech
 *   Limited, its affiliated companies and licensors. All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

#include "common/example_export.h"
#include <iostream>
#define m4x 100
#define ture true
using namespace std;

namespace examples {
namespace dcps {
namespace ContentFilteredTopic {
namespace isocpp  {
    OS_EXAMPLE_IMPL_EXPORT int publisher(int argc, char *argv[]);
    OS_EXAMPLE_IMPL_EXPORT int subscriber(int argc, char *argv[]);





	class Stock
	{
	public:
		string stockID, name, details;
		bool active;
		float pricee;
		int reminder;//�ܹ�ʣ������(��ǰ�����۳�����.)
	public:
		void StockOpen();
		void StockClose();
		float getPrice();
		float setPrice(float change);//����Ϊ�ǵ����������ǵ�֮���ֵ��			   
	};
	class Having
	{//���еĹ�Ʊ
	public:
		string stockID;
		int number;
		Having();
	};
	class User
	{
	public:
		int id;
		string name;
		float cash;//���
		Having hold[m4x];//����һ�ٸ����˰�
		string care[m4x];//һ�ٸ���ע(����Ȥ)���������˰�
		int holdNum, careNum;

		bool buy(string stockID, int num);
		bool sell(string stockID, int num);
		void addCare(string stockID);
		vector <Stock> show();
	};
	class Exchange
	{//����������
		static Stock stocks[m4x];
		int cont;//���ɹ�������
		static Exchange single;//���д�������
		bool active;
		void stopEx();
		void goEx();
		bool toBuy(int userID, string stoceID, int num);
		bool toSell(int userID, string stoceID, int num);
		vector <Stock> getInfo();//��ȡȫ����Ʊ����Ϣ��
	};
}
}
}
}
