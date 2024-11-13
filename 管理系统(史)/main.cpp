#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
using namespace std;

/* 本系统由管理员账户操作
* ·增删学生账号
* ·增删图书
* ·图书损坏判罚
* ·显示所有图书
* ·显示所有学生
* ·管理员账密 Admin 123
*/

class Book;
class Stu;

vector<string> allLogs;
vector<Stu> stus;


void readUsrs()
{
	ifstream usrs;
	string name, psw;
	int mo;

	while (cin >> name)
	{
		cin >> psw >> mo;
		stus.push_back(Stu(name, psw, mo));
	}
}

void readLogs()
{
	ifstream Logs;
	string line;
	Logs.open("logs.txt");
	while (getline(Logs, line)) allLogs.push_back(line);
}


class Book
{
public:
	int code;
	string name;
};

class Stu
{
public:
	string usrName;
	string usrPsw;
	int punishMoney; // 因损坏图书未缴纳的罚款
	// log就不存这了
	Stu(string name, string psw, int pm) : usrName(name), usrPsw(psw), punishMoney(pm) {}
};

ostream& operator<<(ostream& cout, Stu s)
{
	cout << s.usrName << s.punishMoney << endl;
	return cout;
}

// 登录
bool logIn()
{
	ifstream ad_fin;
	ad_fin.open("admin.txt");
	string line;
	getline(ad_fin, line);
	string usrName;
	string usrPsw;
	cout << "+-----------------------------------+" << endl;
	cout << "|                                   |" << endl;
	cout << "| * Library Administration System * |" << endl;
	cout << "| *  Please Administrator log in  * |" << endl;
	cout << "|                                   |" << endl;
	cout << "+-----------------------------------+" << endl;
	int _count = 2;
	for (; _count != -1; --_count)
	{
		cout << "User Name: ";
		cin >> usrName;
		cout << "Password: ";
		cin >> usrPsw;
		if (usrName + ' ' + usrPsw == line)
		{
			cout << "Seccessfully logged in!" << endl;
			return true;
		}
		else
		{
			cout << "Error. You have " << _count << " time(s) to enter." << endl;
		}
	}
	return false;
}

void changePassword(string usrName)
{
}

void mainMenu()
{
	cout << "+---------------------------------+" << endl;
	cout << "|         1. Edit Students        |" << endl;
	cout << "|         2. Edit Books           |" << endl;
	cout << "|         0. Exit System          |" << endl;
	cout << "+---------Key in to select--------+" << endl;
}

// students子菜单
void stuEdit()
{
	cout << "+----------------------------------------+" << endl;
	cout << "|       1. List All Students             |" << endl;
	cout << "|       2. Find One Student              |" << endl;
	cout << "|       3. Change Student Password       |" << endl;
	cout << "|       4. Punish Student                |" << endl;
	cout << "|       5. Delete Student Account        |" << endl;
	cout << "|       0. Back To Main Menu             |" << endl;
	cout << "+------------Key in to select------------+" << endl;
	int sel = -1;
	string usrName;
	while (sel != 0 && sel != 1 && sel != 2 && sel != 3 && sel != 4 && sel != 5)
	{
		cout << "@Admin -> ";
		cin >> sel;
	}
	switch (sel)
	{
	case 1: // 显示所有用户
		for (auto i : stus)
		{
			cout << i;
		}
		break;
	case 2: // 判断学生账号是否存在
		cout << "Input the user name: ";
		cin >> usrName;
		for (Stu i : stus)
		{
			if (i.usrName == usrName) cout << "Found." << endl;
			return;
		}
		cout << "Student Not Found." << endl;
		break;
	case 3: // 修改学生密码
		cout << "Input the user name: ";
		cin >> usrName;
		for (Stu i : stus)
		{
			if (i.usrName == usrName)
			{
				changePassword(usrName);
				return;
			}
		}
		cout << "Student Not Found.";

		break;
	case 4: // 罚款
		break;
	case 5: // 注销学生账户
		break;
	case 0: // 回到主页
		break;
	}
}

// books子菜单
void bookEdit()
{
	cout << "+---------------------------------------+" << endl;
	cout << "|       1. Find One Book                |" << endl;
	cout << "|       2. Change Book Infomation       |" << endl;
	cout << "|       3. Add New Book                 |" << endl;
	cout << "|       4. Erase Book                   |" << endl;
	cout << "|       0. Back To Main Menu            |" << endl;
	cout << "+-----------Key in to select------------+" << endl;
	int sel = -1;
	while (sel != 0 && sel != 1 && sel != 2 && sel != 3 && sel != 4)
	{
		cout << "@Admin -> ";
		cin >> sel;
	}
	switch (sel)
	{
	case 1: // 根据书名或编号(6位)显示书本信息，或书本不存在
		break;
	case 2: // 修改书本信息
		break;
	case 3: // 上架书本
		break;
	case 4: // 下架书本
		break;
	case 0: // 回到主页
		break;
	}
}

bool showMenu()
{
	int sel = -1;
	mainMenu();
	while (sel != 0 && sel != 1 && sel != 2)
	{
		cout << "@Admin -> ";
		cin >> sel;
	}
	switch (sel)
	{
	case 1:
		stuEdit();
		break;
	case 2:
		bookEdit();
		break;
	case 0:
		return 0;
		break;
	}
	return 1;
}

int main()
{
	if (!logIn()) return 0;
	while (showMenu())
		return 0;
}