/*
file:student.c
By:1940706248_林永浩
视频演示地址：https://www.bilibili.com/video/BV1MV411d713/
2020/4/24
数据文件请参考:./db.sql
*/
#include<stdio.h>
#include "sqlserver.h"
#include<string.h>
#include<stdlib.h>
#include<windows.h>
struct student
{
	int id;
	int uid;
	char name[20];
	int chinese;
	int math;
	int english;
};
int main(void)//程序入口
{
	//函数声明：
	struct student getStudentInfo(char* p, int num, int total);
	void student_input();
	void student_search();
	void student_update();
	void student_delete();
	void quit();
	void color(short x);
	int confirmWindow();
	void student_printAll();
	//数据库连接
	int res;
	res = sql_connect("sql_db", "sa", "123456");
	sql_query("USE student", 0,NULL);

	//界面：
	while (1)
	{
		int sel;
		system("cls");
		printf("*****学生成绩管理系统*****\n\n");
		printf("请选择以下管理功能:\n");
		printf("1.学生成绩信息输入\n");
		printf("2.学生成绩信息查询\n");
		printf("3.学生成绩信息更改\n");
		printf("4.学生成绩信息删除\n");
		printf("0.退出\n");
		printf("**************************\n");
		printf("请选择（0~4）");
		scanf_s("%d", &sel);
		switch (sel)
		{
		case 1:student_input(); break;
		case 2:student_search(); break;
		case 3:student_update(); break;
		case 4:student_delete(); break;
		case 0:quit(); break;
		default:
			system("cls");
			printf("无效操作,2s后返回主菜单");
			Sleep(2000);
			break;
		}
	}
	
	
	

	
	
	

}
struct student getStudentInfo(char* p, int num,int total)
{
	struct student stu;
	stu.id = 0;
	if (num == NULL) num = 1;
	if(total >= num)
	{
	

		
		char temp[20];
		strncpy_s(&temp, 20, 120 * (num - 1)+p, 20);
		stu.id = atoi(temp);
		if (stu.id < 0)
		{	//检测是否为空
			return stu;
		}
		strncpy_s(&temp, 20, 120*(num-1)+p+20, 20);
		stu.uid = atoi(temp);
		strncpy_s(&temp, 20, 120*(num - 1)+p + 40, 20);
		strncpy_s(stu.name, 20,temp,20);
		strncpy_s(&temp,20, 120*(num-1)+p + 60, 20);
		stu.chinese = atoi(temp);
		strncpy_s(&temp, 20, 120*(num-1)+p + 80, 20);
		stu.math = atoi(temp);
		strncpy_s(&temp, 20, 120*(num-1)+p + 100, 20);
		stu.english = atoi(temp);
		return stu;
	}
	return ;

}
void student_input()
{
	struct student stu;
	system("cls");
	printf("请输入新同学的学号:");
	scanf_s("%d", &stu.uid);
	printf("请输入新同学的姓名:");
	scanf_s("%s", stu.name,20);
	printf("请输入新同学的语文成绩");
	scanf_s("%d", &stu.chinese);
	printf("请输入新同学的数学成绩:");
	scanf_s("%d", &stu.math);
	printf("请输入新同学的英语成绩:");
	scanf_s("%d", &stu.english);

	if (stu.uid == 0 || stu.name == "")
	{
		
		printf("!学号或者姓名不能为空!\n");
	}

	//这里使用字符串连接方法，不安全!!!
	char sql_[256] = "INSERT INTO stu_info (uid,name,chinese,math,english) VALUES ('";//记得右括号
	char temp[20];
	_itoa_s(stu.uid, &temp,20, 10);
	strcat_s(sql_,sizeof(sql_), temp);
	strcat_s(sql_, sizeof(sql_), "','");
	strcat_s(sql_, sizeof(sql_), stu.name);
	strcat_s(sql_, sizeof(sql_), "',");
	_itoa_s(stu.chinese, &temp, 20, 10);
	strcat_s(sql_, sizeof(sql_), temp);
	strcat_s(sql_, sizeof(sql_), ",");
	_itoa_s(stu.math, &temp, 20, 10);
	strcat_s(sql_, sizeof(sql_), temp);
	strcat_s(sql_, sizeof(sql_), ",");
	_itoa_s(stu.english, &temp, 20, 10);
	strcat_s(sql_, sizeof(sql_), temp);
	strcat_s(sql_, sizeof(sql_), ")");
	printf(sql_);

	color(4);
	printf("\n添加学生\n");
	color(7);
	printf("学号：%d,姓名：%s,语文成绩：%d,数学成绩%d,英语成绩:%d\n", stu.uid, stu.name, stu.chinese, stu.math, stu.english);
	if (confirmWindow("是否确认添加该学生") != 0)
	{
		color(2);
		sql_query(sql_, 0,NULL);
		printf("添加成功！3秒后自动返回主菜单！\n");
		Sleep(3000);
		
	}
	else
	{
		color(4);
		printf("添加失败,3秒后自动返回主菜单！\n");
		Sleep(3000);
	}







	
}
void student_search()
{
	//二级菜单
	int in;
	char msg[20];
	while(1)
	{
		system("cls");
		printf("*******成绩查询*******\n");
		printf("1.按学号查询\n");
		printf("2.按姓名查询\n");
		printf("3.显示所有学生\n");
		printf("4.返回主菜单\n");
		scanf_s("%d", &in);
		if (in == 3)
		{
			student_printAll();
			int flag[3];
			printf("按任意键返回主菜单!");
			getchar();
			getchar();

		}
		else if (in == 4)
		{
			break;
		}
		else
		{


			printf("请输入需要查找的%s\n", in == 1 ? "学号" : "姓名");
			scanf_s("%s", msg, 20);
			//SELECT* FROM stu_info WHERE uid = '19470606248'
			char sql_[256];
			if (in == 1)
			{
				strcpy_s(sql_, 256, "SELECT * FROM stu_info WHERE uid='");//字符串拼接
			}
			else if (in == 2)
			{
				strcpy_s(sql_, 256, "SELECT * FROM stu_info WHERE name='");//字符串拼接

			}


			strcat_s(sql_, sizeof(sql_), msg);
			strcat_s(sql_, sizeof(sql_), "'");
			//printf("%s", sql_);
			SQLCHAR* sum = sql_query(sql_, 1, NULL);
			struct student stu = getStudentInfo(sum, 1, 1);
			color(4);
			printf("查询结果:\n\n");
			color(7);
			if (stu.id > 0)
			{
				printf("学号:%d,姓名：%s,语文成绩:%d,数学成绩：%d,英语成绩:%d\n\n", stu.uid, stu.name, stu.chinese, stu.math, stu.english);

			}
			else
			{
				printf("查询失败，找不到该学生?\n\n");
			}
			if (confirmWindow("是否继续查询") != 0)
			{
				//继续查询
				student_search();
			}
			else
			{
				Sleep(2000);
				free(sum);
			}
		}
	}
	





	}
void student_update()
{
	student_printAll();
	printf("\n请输入需要修改的方式(1.按序号 2.按学号 3.按姓名)\n");
	int mode = 0;
	char str[10];
	char flag[10];
	//"UPDATE stu_info SET english = 100 WHERE name = '林永浩'";
	char sql_[256] = "UPDATE stu_info SET ";
	char input[20],uid[20],name[20],math[20],chinese[20],english[20];
	int temp = 0;
	scanf_s("%d", &mode);
	
	switch (mode)
	{
	case 1:strcpy_s(str, 5, "序号"); strcpy_s(flag, 10, "id"); break;
	case 2:strcpy_s(str, 5, "学号"); strcpy_s(flag, 10, "uid"); break;
	case 3:strcpy_s(str, 5, "姓名"); strcpy_s(flag, 10, "name"); break;
	case 0:return;


		
	default:

		break;
	}
	color(10);
	printf("\n请输入需要修改信息的同学的%s:", str);
	color(7);
	scanf_s("%s", &input, 20);
	color(10);
	printf("\n请输入修改后的学号?不需要修改(n):");
	color(7);
	scanf_s("%s", &uid, 20);
	color(10);
	printf("\n请输入修改后的姓名?不需要修改(n):");
	color(7);
	scanf_s("%s", &name, 20);
	color(10);
	printf("\n请输入修改后的语文成绩?不需要修改(n):");
	color(7);
	scanf_s("%s", &chinese, 20);
	color(10);
	printf("\n请输入修改后的数学成绩?不需要修改(n):");
	color(7);
	scanf_s("%s", &math, 20);
	color(10);
	printf("\n请输入修改后的英语成绩?不需要修改(n):");
	color(7);
	scanf_s("%s", &english, 20);
	if (strcmp(uid, "n") != 0)
	{
		strcat_s(sql_, 256, " uid= '");
		strcat_s(sql_, 256, uid);
		strcat_s(sql_, 256, "'");
		temp = 1;
	}

	if (strcmp(name, "n") != 0)
	{
		if (temp == 1)
		{
			strcat_s(sql_, 256, ",");

		}
		strcat_s(sql_, 256, " name ='");
		strcat_s(sql_, 256, name);
		strcat_s(sql_, 256, " '");
		temp = 1;
	}

	if (strcmp(chinese, "n") != 0)
	{
		if (temp == 1)
		{
			strcat_s(sql_, 256, ",");


		}
		strcat_s(sql_, 256, " chinese = ");
		strcat_s(sql_, 256, chinese);
		temp = 1;
	}

	if (strcmp(math, "n") != 0)
	{
		if (temp == 1)
		{
			strcat_s(sql_, 256, ",");


		}
		strcat_s(sql_, 256, " math = ");
		strcat_s(sql_, 256, math);
		temp = 1;
	}

	if (strcmp(english, "n") != 0)
	{
		if (temp == 1)
		{
			strcat_s(sql_, 256, ",");


		}
		strcat_s(sql_, 256, " english = ");
		strcat_s(sql_, 256, english);
	}
	
	strcat_s(sql_, 256, " WHERE ");
	strcat_s(sql_, 256, flag);
	strcat_s(sql_, 256, " = ");
	if (mode == 3 || mode == 2)
	{
		strcat_s(sql_, 256, "'");
		strcat_s(sql_, 256, input);
		strcat_s(sql_, 256, "'");

	}
	else
	{
		strcat_s(sql_, 256, input);

	}
	sql_query(sql_, 0, NULL);
	//printf("%s", sql_);
	printf("执行修改成功！3s后返回主菜单!\n");
	Sleep(3000);




}
void student_delete()
{
	student_printAll();
	printf("\n请输入需要删除的方式(1.按序号 2.按学号 3.按姓名)\n");
	int mode = 0;
	char str[10];
	char flag[10], input[20];
	//DELETE FROM stu_info WHERE name = '林永浩';
	char sql_[256] = "DELETE FROM stu_info WHERE ";
	scanf_s("%d", &mode);

	switch (mode)
	{
	case 1:strcpy_s(str, 5, "序号"); strcpy_s(flag, 10, "id"); break;
	case 2:strcpy_s(str, 5, "学号"); strcpy_s(flag, 10, "uid"); break;
	case 3:strcpy_s(str, 5, "姓名"); strcpy_s(flag, 10, "name"); break;
	case 0:return;



	default:

		break;
	}
	color(10);
	printf("\n请输入需要删除信息的同学的%s:", str);
	color(7);
	scanf_s("%s", &input, 20);


	strcat_s(sql_, 256, flag);
	strcat_s(sql_, 256, " = ");

	if (mode == 3)
	{
		strcat_s(sql_, 256, "'");
		strcat_s(sql_, 256, input);
		strcat_s(sql_, 256, "'");

	}
	else
	{
		strcat_s(sql_, 256, input);

	}
	sql_query(sql_, 0, NULL);

	printf("执行删除成功！3s后返回主菜单!\n");
	Sleep(3000);



}
void quit()
{
	sql_disconnect();
	exit(0);
}
void student_printAll()
{
	char sql_[256];

	strcpy_s(sql_, 256, "SELECT * FROM stu_info");//字符串拼接

	struct student stu;


	system("cls");
	int j = 0;
	SQLCHAR* sum = sql_query(sql_, 1,&j);
	for (int i = 0; i < j; i++)
	{
		stu = getStudentInfo(sum, i+1, j);
		if (stu.id > 0 && i == 0)//第一次循环打印标题
		{
			printf("┌────┬──────────┬──────┬───────────┬───────────┬───────────┐\n");
			printf("│序号│ 学号     │ 姓名 │语文成绩   │数学成绩   │   英语成绩│\n");
			printf("├────┼──────────┼──────┼───────────┼───────────┼───────────┤\n");
		}
		printf("│%4d│%-10d│%6s│%11d│%11d│%11d│\n", stu.id, stu.uid, stu.name, stu.chinese, stu.math, stu.english);

	}
	printf("└────┴──────────┴──────┴───────────┴───────────┴───────────┘\n");



	


}
//helper
void color(short x) //自定义函根据参数改变颜色   
{
	if (x >= 0 && x <= 15)//参数在0-15的范围颜色  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);    //只有一个参数，改变字体颜色   
	else//默认的颜色白色  
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	/*
	　　0=黑色                8=灰色　　 
  　1=蓝色                9=淡蓝色        十六进制        　　                         
　　2=绿色                10=淡绿色       0xa        　　 
　　3=湖蓝色              11=淡浅绿色     0xb　 
　　4=红色                12=淡红色       0xc　　 
　　5=紫色                13=淡紫色       0xd        　　 
　　6=黄色                14=淡黄色       0xe        　　 
　　7=白色                15=亮白色       0xf  
  */
}
int confirmWindow(char *msg)
{
	char isconfirm;
	color(5);
	printf("\n%s(y/n)",msg);
	getchar();//去除换行符
	scanf_s("%c", &isconfirm,1);
	if (isconfirm == 'y')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
