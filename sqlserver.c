//file:sqlserver.c
#include<windows.h>
#include<sql.h>
#include<sqlext.h>
#include<sqltypes.h>
#include<stdio.h>
//GOBAL
SQLRETURN ret;
SQLHENV henv;
SQLHDBC	hdbc;
SQLHSTMT hstmt;
int sql_connect(char* db_name, char* db_user, char* db_password)
{

	ret = SQLAllocHandle(SQL_HANDLE_ENV, NULL, &henv);//创建句柄
	ret = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	ret = SQLConnect(hdbc, (SQLCHAR*)db_name, SQL_NTS, (SQLCHAR*)db_user, SQL_NTS, (SQLCHAR*)db_password, SQL_NTS);

	if (!(ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO))
	{
		//数据库连接失败
		return -1;
	}
	return 0;
}
SQLCHAR* sql_query(char *sql,int num,int* total)
{//sum : 返回第几条信息
	ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	//分配内存
	SQLCHAR *p= calloc(sizeof(SQLCHAR), 20 * 6);
	//默认错误stu.id < 0 先将错误打入
	strncpy_s(p, 120, "-1", 3);
	ret = SQLExecDirect(hstmt, sql, SQL_NTS);
	if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO)
	{
		int i = 1;
		while (SQLFetch(hstmt) != SQL_NO_DATA && num > 0)
		{
			realloc(p, 20 * 6 * i);
			SQLGetData(hstmt, 1, SQL_C_CHAR, 120*(i-1)+p, 20, 0);
			SQLGetData(hstmt, 2, SQL_C_CHAR, 120*(i-1)+p+20, 20, 0);
			SQLGetData(hstmt, 3, SQL_C_CHAR, 120*(i-1)+p+40, 20, 0);
			SQLGetData(hstmt, 4, SQL_C_CHAR, 120*(i-1)+p+60, 20, 0);
			SQLGetData(hstmt, 5, SQL_C_CHAR, 120*(i-1)+p+80, 20, 0);
			SQLGetData(hstmt, 6, SQL_C_CHAR, 120*(i-1)+p+100, 20, 0);
			i++;
			if(total  !=  NULL)
				*total = i-1;
			

		}
		
		

	

	}
	
	return p;
}

int sql_disconnect()
{
	SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
	SQLFreeHandle(SQL_HANDLE_ENV, henv);
	return 0;
}