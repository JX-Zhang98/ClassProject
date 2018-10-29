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
		int reminder;//总股剩余数量(当前最大可售出数量.)
	public:
		void StockOpen();
		void StockClose();
		float getPrice();
		float setPrice(float change);//参数为涨跌幅，返回涨跌之后的值。	
		float increase(float range);
	};
	class Having
	{//持有的股票
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
		float cash;//余额
		Having hold[m4x];//给你一百个够了吧
		string care[m4x];//一百个关注(感兴趣)能满足你了吧
		int holdNum, careNum;
	public:
		User(string path);//从path路径的文件中读取用户信息，生成对象。
		User();
		User FlushInfo();//刷新用户信息
		void saveUser(string path);//将对象**按格式写入到path文件中**
		bool buy(string stockID, int num);
		bool sell(string stockID, int num);
		bool addCare(string stockID);
		vector <Stock> show();

	};
	class Exchange
	{//单例交易所
	public:
		Stock stocks[m4x];//
		int cont;//收纳股种数量
		bool active;
	private:
		Exchange();
		static Exchange* singleInstance;//急切创建单例
	public:
		static Exchange* getInstance();//使用单例模式
		void stopEx();
		void goEx();
		string toBuy(int userID, string stockID, int num);
		string toSell(int userID, string stoclID, int num);
		vector <Stock> getInfo();//获取全部股票的信息。
		User checkLogin(string userName, string password);
		void importStocks();//将存储中的股票信息导入程序中，在程序开始执行时启动
		void adjustStocks();//调整股价
		void saveStocks();//闭市时将股票信息保存在数据库中

	};
	Exchange* Exchange::singleInstance = new Exchange();//直接急切创建单例
}
}
}
}
