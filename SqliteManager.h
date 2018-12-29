//
// Created by shuicg on 2018-12-29.
//

#ifndef _SQLITEMANAGER_H_
#define _SQLITEMANAGER_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "sqlite3.h"

typedef  vector< pair<string, string> > ColData;
typedef  vector<ColData> RowData;

class SqliteManager {
public:
    SqliteManager(const string &sDatabaseName);
    ~SqliteManager();
public:

    bool ExecSql(const string &sSql);
    bool ExecSql(const string &sSql, RowData &vData);
    void ShowData(RowData &vData);

private:
    sqlite3 *m_db;
    bool m_bOpenSuccess;

};


#endif //_SQLITEMANAGER_H_
