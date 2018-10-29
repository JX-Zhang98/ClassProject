#include "common/example_export.h"
#include <iostream>
#include <vector>
#include <ctime>

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
		float increase(float range);
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
	public:
		User(string path);//��path·�����ļ��ж�ȡ�û���Ϣ�����ɶ���
		User();
		User FlushInfo();//ˢ���û���Ϣ
		void saveUser(string path);//������**����ʽд�뵽path�ļ���**
		bool buy(string stockID, int num);
		bool sell(string stockID, int num);
		bool addCare(string stockID);
		vector <Stock> show();

	};
	class Exchange
	{//����������
	public:
		Stock stocks[m4x];//
		int cont;//���ɹ�������
		bool active;
	private:
		Exchange();
		static Exchange* singleInstance;//���д�������
	public:
		static Exchange* getInstance();//ʹ�õ���ģʽ
		void stopEx();
		void goEx();
		string toBuy(int userID, string stockID, int num);
		string toSell(int userID, string stoclID, int num);
		vector <Stock> getInfo();//��ȡȫ����Ʊ����Ϣ��
		User checkLogin(string userName, string password);
		void importStocks();//���洢�еĹ�Ʊ��Ϣ��������У��ڳ���ʼִ��ʱ����
		void adjustStocks();//�����ɼ�
		void saveStocks();//����ʱ����Ʊ��Ϣ���������ݿ���

	};
	Exchange* Exchange::singleInstance = new Exchange();//ֱ�Ӽ��д�������
}
}
}
}
