#include <iostream>
#include <string>
using namespace std;

#include "SqliteManager.h"

int main(int argc, char* argv[])
{
    if(argc < 4)
    {
        cout << "CMD: sqliteManager db_name sql type(0 select 1 other)" << endl;
        return 0;
    }

    string sDbName = argv[1];
    string sSql = argv[2];
    string sType = argv[3];
    SqliteManager sqliteManger(sDbName);
    if(sType == "0")
    {
        RowData data;
        sqliteManger.ExecSql(sSql, data);
    } else{
        sqliteManger.ExecSql(sSql);
    }

    /*
    //cout << "hellow world!" << endl;
    SqliteManager sqliteManger("/data/data/com.android.providers.settings/databases/settings.db");

    //sqliteManger.ExecSql("update global set value =1 where name in ('mobile_data0','mobile_data1')");
    sqliteManger.ExecSql("delete from global where name in ('mobile_data0','mobile_data1')");
    sqliteManger.ExecSql("insert into global(name,value) values('mobile_data0','1'),('mobile_data1','1')");

    RowData data;
    sqliteManger.ExecSql("select * from global", data);
     */
    //printf("hello!\n");
    return 0;
}
