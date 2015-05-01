#include <mysql.h>
#include <iostream>

using namespace std;

int main()
{
	cout <<"Mysql Client version" << mysql_get_client_info();
}
