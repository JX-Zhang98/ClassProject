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
	OS_EXAMPLE_IMPL_EXPORT int Market();
	OS_EXAMPLE_IMPL_EXPORT int Event();
	OS_EXAMPLE_IMPL_EXPORT int Client();
	OS_EXAMPLE_IMPL_EXPORT int Midware();




	class Stock
	{
	public:
		string stockID, name, details;
		float pricee;
	public:
		float getPrice();
		float setPrice(float change);//����Ϊ�ǵ����������ǵ�֮���ֵ��	
		float increase(float range);
	};
	class Having
	{//���еĹ�Ʊ
	public:
		string stockName;
		int number;
		Having();
	};
	class User
	{
	public:
		string name;
		string password;
		float cash;//���
		Having hold[m4x];//����һ�ٸ����˰�
		string care[m4x];//��ֻ���Ʊ����
		int holdNum, careNum;
	public:
		string checkLogin(string userName, string password);
		User(string path);//��path·�����ļ��ж�ȡ�û���Ϣ�����ɶ���
		User() {};
		void saveUser(string path);//������**����ʽд�뵽path�ļ���**
		void buy(string stockname, int num);
		void sell(string stockname, int num);
		void sendMsg(string username, string stockname, int num,int tYpe);
		//bool addCare(string stockID);
	};
	class Exchange
	{//����������
	public:
		vector <Stock> stocks;//
		int cont;//���ɹ�������
	//private:
		Exchange();
		//Exchange* singleInstance;//���д�������
	public:
		//Exchange* getInstance();//ʹ�õ���ģʽ
		//string toBuy(int userID, string stockID, int num);
		//string toSell(int userID, string stoclID, int num);
		void importStock(string filename);//��ȡȫ����Ʊ����Ϣ��
		//void importStocks();//���洢�еĹ�Ʊ��Ϣ��������У��ڳ���ʼִ��ʱ����
		void adjustStocks();//�����ɼ�
		void saveStocks();//����ʱ����Ʊ��Ϣ���������ݿ���

	};
	//Exchange* Exchange::singleInstance = new Exchange();//ֱ�Ӽ��д�������
}
}
}
}
