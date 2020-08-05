//
// Created by shuicg on 2018-12-29.
//

#include <unistd.h>
#include <errno.h>
#include "SqliteManager.h"

SqliteManager::SqliteManager(const string &sDatabaseName)
{
    m_bOpenSuccess = false;
    int rv = sqlite3_open(sDatabaseName.c_str(), &m_db);
    if(rv)
    {
        cout << "sqlite open error " << sqlite3_errmsg(m_db) << endl;
        sqlite3_close(m_db);
    }
    else
    {
        m_bOpenSuccess = true;
    }
}
SqliteManager::~SqliteManager()
{
    if(m_bOpenSuccess && m_db != NULL)
    {
        sqlite3_close(m_db);
    }
}

void SqliteManager::ShowData(RowData &vData)
{
    for(int i = 0; i < vData.size(); ++i)
    {
        if(i == 0)
        {
            for(int j = 0; j < vData[i].size(); ++j)
            {
                cout << vData[i][j].first << "\t";
            }
            cout<< endl;
        }

        for(int j = 0; j < vData[i].size(); ++j)
        {
            cout << vData[i][j].second << "\t";
        }
        cout<< endl;
    }
}

bool SqliteManager::ExecSql(const string &sSql)
{
    cout << "sSql:" << sSql << endl;
    if(!m_bOpenSuccess)
    {
        cout << "open sqlite error!" << endl;
        return false;
    }
    char *errMsg;

    int rv = sqlite3_exec(m_db, sSql.c_str(), NULL, 0, &errMsg);
    if(rv != SQLITE_OK)
    {
        if(errMsg != NULL)
        {
            cout << "sqlite exec error " << errMsg << ", sql = " << sSql << endl;
            sqlite3_free(errMsg);
        }
        return false;
    }
    return true;
}

bool SqliteManager::ExecSql(const string &sSql, RowData &vData)
{
    cout << "sSql:" << sSql << endl;
    if(!m_bOpenSuccess)
    {
        cout << "open sqlite error!" << endl;
        return false;
    }
    vData.clear();

    char *errMsg;
    char** pResult;
    int nRow = 0, nCol = 0;

    int rv = sqlite3_get_table(m_db, sSql.c_str(), &pResult, &nRow, &nCol, &errMsg);
    //cout << "rv=" << rv << endl;
    if(rv != SQLITE_OK)
    {
        if(errMsg != NULL)
        {
            cout << "sqlite exec error " << errMsg << ", sql = " << sSql << endl;
            sqlite3_free(errMsg);
        }
        return false;
    }
    string strOut;
    int nIndex = nCol;
    for(int i=0;i<nRow;i++)
    {
        ColData colData;
        for(int j=0;j<nCol;j++)
        {
            //cout << pResult[j] << ":" << pResult[nIndex] << endl;
            string sColName, sColValue;
            if(pResult[j] != NULL)
            {
                sColName = pResult[j];
            }
            else
            {
                sColName = "null";
            }

            if(pResult[nIndex] != NULL)
            {
                sColValue = pResult[nIndex];
            }
            else
            {
                sColValue = "null";
            }
            //cout << sColName << ":" << sColValue << endl;
            colData.push_back(make_pair(sColName, sColValue));
            ++nIndex;
        }
        vData.push_back(colData);
    }
    sqlite3_free_table(pResult);
    ShowData(vData);
    return true;
}