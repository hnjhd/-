
#include <iostream>
#include "topic.h"

var result[MAX_LENGTH];
var* expression[MAX_LENGTH];//���ʽ
int save[MAX_LENGTH];

int main()
{
	int amount; //���ʽ����
	int size = 10;	//��������ȡֵ��Χ
	int n;
	char instructions[300];//�洢ָ��
	srand((int)time(0));
	cout << "ע����������СĬ��ΪС��10������Ȼ������ʹ��ָ�����Ϊ�������0С��2147483647��������\n";
	cout << "    ��ͬʱ���ɵ�����ʽ�����ֵΪ" << MAX_LENGTH << "!\n";
	cout << "    ����ָ������ֵΪ300��\n";
	while (1)
	{
		cout << "Myapp.exe ";
		cin.get(instructions, 300);
		getchar();
		if (instructions[0] == '-')
		{
			int i, j;
			switch (instructions[1])
			{
			case 'n'://����������Ŀ�ĸ���
				n = 2;
				while (instructions[n] == ' ' && n < 300) n++;
				if (n == 2 || n == 300)
				{
					cout << "ָ�������������������룡\n";
					break;
				}
				i = 10;
				amount = 0;
				while (instructions[n] != '\0' && instructions[n] >= '0' && instructions[n] <= '9' && n < 300)
				{
					j = instructions[n] - '0';
					amount = j + amount * i;
					n++;
				}
				if (amount < 1 && n == 300 && amount > MAX_LENGTH)
				{
					cout << "���������������������룡\n";
					break;
				}
				remove(EXERCISEFILE);
				remove(ANSWERFILE);
				M_instructions(expression, amount, size, result);
				Destrory(expression, result, amount);
				break;
			case 'r'://������Ŀ����ֵ����Ȼ������������������ĸ���ķ�Χ
				n = 2;
				while (instructions[n] == ' ' && n < 300) n++;
				size = 0;
				if (n == 2 || n == 300)
				{
					cout << "ָ�������������������룡\n";
					break;
				}
				while (instructions[n] != '\0' && instructions[n] >= '0' && instructions[n] <= '9' && n < 300)
				{
					size = instructions[n] - '0' + size * 10;
					n++;
				}
				if (size <= 0 || n == 300)
				{
					size = 10;
					cout << "���������������������룡\n";
				}
				break;
			case 'e':
				char exercisefile[100];
				char answerfile[100];
				n = 2;
				while (instructions[n] == ' ' && n < 300) n++;
				if (n == 2)
				{
					cout << "ָ�������������������룡\n";
					break;
				}
				i = n;
				while (instructions[n] != ' ' && n - i < 100 && n < 300 && instructions[n] != '\0')
				{
					exercisefile[n - i] = instructions[n];
					n++;
				}
				exercisefile[n - i] = '\0';
				while (instructions[n] == ' ' && n < 300) n++;
				if (instructions[n] != '-' || instructions[n + 1] != 'a')
				{
					cout << "ָ�������������������룡\n";
					break;
				}
				n = n + 2;
				i = n;
				while (instructions[n] == ' ' && n < 300) n++;
				if (i == n)
				{
					cout << "ָ�������������������룡\n";
					break;
				}
				i = n;
				while (instructions[n] != ' ' && n - i < 100 && n < 300 && instructions[n] != '\0')
				{
					answerfile[n - i] = instructions[n];
					n++;
				}
				answerfile[n - i] = '\0';
				if (n == 300)
				{
					cout << "ָ��������������������룡\n";
					break;
				}
				Correction(save, answerfile, exercisefile);
				break;
			default:
				cout << "ָ�������������������룡\n";
				break;
			}
		}
		else
		{
			cout << "ָ�������������������룡\n";
		}
	}
	return 0;
}
