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
	int num_or_Symbol;		 //0������1�Ƿ���
	int Symbol = -1;		//    + - * % ( ) �ֱ��ʾΪ 0 1 2 3 4 5
	int numer;				//��������ִ�Ϊ����
	int Den = 1;			//��������ִ�Ϊ��ĸ
	int num;

	bool operator == (variable c) {
		return num_or_Symbol == c.num_or_Symbol && Symbol == c.Symbol && numer == c.numer && Den == c.Den && num == c.num;
	}
}var;
//���ɱ��ʽ����
Status Create(var** exp, int size, int* length);

//������ʽ����
Status Calculation(var* exp, int size, var* result, int length);

//������ʽ
void Visit(var* expression, int length, int num);

//mָ���ִ��
void M_instructions(var** expression, int amount, int size, var* result);

// ���ٷ�����ڴ�
void Destrory(var** expression, var* result, int amount);

//�ж϶Դ�
void Correction(int* save, char* answerfile, char* exercisefile);

//��׺���ʽת��׺���ʽ
Status Infix_to_Postfix(var* p, int size, var* Postfix, int length, int& postLen);

//��������������ȼ�
int prio(var element);

//����������ͨ��
void preprocess(var& a, var& b);

//�����׺���ʽ��ֵ
Status calc(var* Postfix, int length, var& ans);

//��ӡ����������
void display(var* a);

//ִ�мӼ��˳��Ĳ������Խ�����л���
Status operate(var a, var b, var oper, var& ret);

//�ɺ�׺���ʽ ��ȡ ��׺�ӱ��ʽ
Status get_Subexpression(var* Postfix, int length, var ans[][3], int& sta_size);

//�ж�������׺�ӱ��ʽ�Ƿ�ȼ�
bool cmp(var a[], var b[]);

//�ж����������Ƿ�ȼ�
Status is_question_same(var* Question, int lenQuest, var* newQuestion, int lenNewQuest, int size);

