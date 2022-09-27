#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <istream> 
#include <stack>

#define EXERCISEFILE	"exercisefile.txt"
#define ANSWERFILE		"answerfile.txt"
#define GRADE			"grade.txt"
#define MAX_LENGTH		20000
using namespace std;

const int maxn = 100;

typedef enum Status
{
	ERROR = 0, SUCCESS = 1
} Status;

typedef struct variable
{
	int num_or_Symbol;		 //0是数字1是符号
	int Symbol = -1;		//    + - * % ( ) 分别表示为 0 1 2 3 4 5
	int numer;				//如果是数字此为分子
	int Den = 1;			//如果是数字此为分母
	int num;

	bool operator == (variable c) {
		return num_or_Symbol == c.num_or_Symbol && Symbol == c.Symbol && numer == c.numer && Den == c.Den && num == c.num;
	}
}var;
//生成表达式函数
Status Create(var** exp, int size, int* length);

//计算表达式函数
Status Calculation(var* exp, int size, var* result, int length);

//输出表达式
void Visit(var* expression, int length, int num);

//m指令的执行
void M_instructions(var** expression, int amount, int size, var* result);

// 销毁分配的内存
void Destrory(var** expression, var* result, int amount);

//判断对错
void Correction(int* save, char* answerfile, char* exercisefile);

//中缀表达式转后缀表达式
Status Infix_to_Postfix(var* p, int size, var* Postfix, int length, int& postLen);

//返回运算符的优先级
int prio(var element);

//将两个分数通分
void preprocess(var& a, var& b);

//计算后缀表达式的值
Status calc(var* Postfix, int length, var& ans);

//打印单个操作数
void display(var* a);

//执行加减乘除的操作并对结果进行化简
Status operate(var a, var b, var oper, var& ret);

//由后缀表达式 获取 后缀子表达式
Status get_Subexpression(var* Postfix, int length, var ans[][3], int& sta_size);

//判断两个后缀子表达式是否等价
bool cmp(var a[], var b[]);

//判断两个问题是否等价
Status is_question_same(var* Question, int lenQuest, var* newQuestion, int lenNewQuest, int size);

