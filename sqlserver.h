//file:sqlserver.h
#pragma once
#include<windows.h>
#include<sql.h>
#include<sqlext.h>
#include<sqltypes.h>
#include<stdio.h>
#define SQL_FAIL -1
int sql_connect(char* db_name, char* db_user, char* db_password);
SQLCHAR* sql_query(char* sql, int num,int*);
int sql_disconnect();

