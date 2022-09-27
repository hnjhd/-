#include "topic.h"

#define random(a, b) (rand() % ((b) - (a)) + (a))

Status Create(var** exp, int size, int* length)
{
	var* expre;
	int mark_num = random(1, 4);//���������
	int pre = 0;//ǰ�����ڵ�pre������ǰ
	int aft = 0;//�������ڵ�aft�����ֺ�
	int judge = 0;//�жϣ�0д�����֣�1д�����
	int n = 0;
	*length = mark_num + mark_num + 1;
	n = 0;
	if (mark_num > 1)//����������3�������������
	{
		pre = random(1, mark_num);
		if (pre == 1)//����������ס����ʽ��
			aft = random((pre + 1), (mark_num + 1));
		else
			aft = random((pre + 1), (mark_num + 2));
		(*length) += 2;
		expre = new var[*length + 1];
		expre[pre * 2 - 2].num_or_Symbol = 1;
		expre[pre * 2 - 2].Symbol = 4;
		expre[aft * 2].num_or_Symbol = 1;
		expre[aft * 2].Symbol = 5;
	}
	else
	{
		expre = new var[*length + 1];
	}
	n = 0;
	while (n < *length)
	{
		if (expre[n].Symbol < 4)
		{
			if (judge == 0)
			{
				expre[n].num_or_Symbol = 0;
				expre[n].Den = random(2, size);
				expre[n].numer = random(0, expre[n].Den);
				expre[n].num = random(1, size);
				judge = 1;
			}
			else
			{
				expre[n].num_or_Symbol = 1;
				expre[n].Symbol = random(0, 4);
				judge = 0;
			}
		}
		n++;
	}
	*exp = expre;
	return SUCCESS;
}

void Visit(var* expression, int length, int num)
{
	fstream exercise;
	exercise.open(EXERCISEFILE, ios::out | ios::app);
	exercise << num << ".   ";
	int n = 0;
	while (n < length)
	{
		if (expression[n].num_or_Symbol == 0)
		{
			if (expression[n].numer == 0)
			{
				cout << expression[n].num;
				exercise << expression[n].num;
			}
			else
			{
				if (expression[n].num != 0)
				{
					cout << expression[n].num;
					cout << "`";
					exercise << expression[n].num;
					exercise << "`";
				}
				cout << expression[n].numer;
				cout << "/";
				cout << expression[n].Den;
				exercise << expression[n].numer;
				exercise << "/";
				exercise << expression[n].Den;
			}
		}
		else
		{
			switch (expression[n].Symbol)
			{
			case 0:
				cout << " + ";
				exercise << " + ";
				break;
			case 1:
				cout << " - ";
				exercise << " - ";
				break;
			case 2:
				cout << " �� ";
				exercise << " �� ";
				break;
			case 3:
				cout << " �� ";
				exercise << " �� ";
				break;
			case 4:
				cout << '(';
				exercise << '(';
				break;
			case 5:
				cout << ')';
				exercise << ')';
				break;
			default:break;
			}
		}
		n++;
	}

	cout << " = \n";
	exercise << " = ";
	exercise << endl;
	exercise.close();
}

void M_instructions(var** expression, int amount, int size, var* result)
{
	fstream answer;
	answer.open(ANSWERFILE, ios::out | ios::app);
	var results[maxn];//��׺���ʽ
	int length;
	int i = 0;
	int j = 0;
	int k = 0;
	while (i < amount)
	{
		Create(&expression[i], size, &length);
		result[i].Symbol = length;
		if (Calculation(expression[i], size, results, length) == ERROR || results[0].num >= size || results[0].numer >= size || results[0].Den >= size)
		{
			continue;
		}
		result[i].Den = results[0].Den;
		result[i].num = results[0].num;
		result[i].numer = results[0].numer;
		result[i].num_or_Symbol = 0;
		result[i].Symbol = length;
		j = 0;
		while (j < i)
		{
			//���һ�������ʽ����һ��
			if (result[j].Den == result[i].Den && result[j].numer == result[i].numer && result[j].num == result[i].num)
			{
				if (is_question_same(expression[i], result[i].Symbol, expression[j], result[j].Symbol, size))
				{
					break;
				}
			}
			j++;
		}
		if (i != j)
		{
			if (k++ < 20)//����20���ظ��𰸱�������size̫С����amount̫�󣬱��ʽ�����Բ���
				continue;
		}
		Visit(expression[i], length, i + 1);

		answer << i + 1 << ".   ";
		if (result[i].numer == 0)
		{
			answer << result[i].num;
		}
		else
		{
			if (result[i].num != 0)
			{
				answer << result[i].num;
				answer << "`";
			}
			answer << result[i].numer;
			answer << "/";
			answer << result[i].Den;
		}
		answer << endl;
		i++;
		k = 0;
	}
	answer.close();
}

void Correction(int* save, char* answerfile, char* exercisefile)// -e exercisefile.txt -a answerfile.txt
{
	fstream answer;
	fstream exercise;
	fstream grade;
	answer.open(answerfile, ios::in);
	if (!answer)
	{
		cout << "���ļ�������!\n";
		return;
	}
	exercise.open(exercisefile, ios::in);
	if (!exercise)
	{
		cout << "��Ŀ�ļ�������!\n";
		return;
	}
	grade.open(GRADE, ios::out | ios::app);
	char answ[100];
	char exer[100];
	int i, j;
	int n, m;
	int correct = 0;
	int wrong = 0;
	while (!answer.eof() && !exercise.eof())
	{
		answer.getline(answ, 100);
		exercise.getline(exer, 100);
		i = 0, j = 0, n = 0, m = 0;
		while (answ[i] >= '0' && answ[i] <= '9')
			n = answ[i++] - '0' + n * 10;
		while (exer[j] >= '0' && exer[j] <= '9')
			m = exer[j++] - '0' + m * 10;
		if (n == m)
		{
			if (n != 0 && n <= MAX_LENGTH)
			{
				i = 0;
				j = 0;
				while (exer[j++] != '=' && j < 100);
				while (exer[j++] == ' ' && j < 100);
				while (answ[i++] != '.' && i < 100);
				while (answ[i++] == ' ' && i < 100);
				j -= 1;
				i -= 1;
				while (exer[j] != ' ' && exer[j] != '\t' && exer[j] != '\0' && i < 100 && j < 100)
				{
					if (answ[i++] != exer[j++])
						break;
				}
				if (answ[i - 1] == exer[j - 1] && exer[j - 1] != ' ' && answ[i] == '\0')
				{
					save[n] = 1;
					save[n + 1] = -1;
					correct++;
				}
				else
				{
					save[n] = 0;
					save[n + 1] = -1;
					wrong++;
				}
			}
		}
		else
		{
			if (n == 0 && m != 0)
				n = m;
			if (m == 0 && n != 0)
				m = n;
			cout << "����ʧ�ܣ��ļ�" << ANSWERFILE << "��" << n << "���" << EXERCISEFILE << "��" << m << "�ⷢ������\n";
			return;
		}
	}
	i = 1, j = 0;
	grade << "Correct: " << correct << " (";
	while (save[i] >= 0)
	{
		if (save[i] == 1)
		{
			if (j != 0)
				grade << ',';
			else
				j = 1;
			grade << i;
		}
		i++;
	}
	grade << ")" << endl;
	i = 1, j = 0;
	grade << "Wrong: " << wrong << " (";
	while (save[i] >= 0)
	{
		if (save[i] == 0)
		{
			if (j != 0)
				grade << ',';
			else
				j = 1;
			grade << i;
		}
		i++;
	}
	grade << ")" << endl;
	cout << "������¼��" << GRADE << "!\n";
	answer.close();
	exercise.close();
	grade.close();
}

void Destrory(var** expression, var* result, int amount)
{
	int i = 0;
	while (i < amount)
		free(expression[i++]);
}

Status Infix_to_Postfix(var* p, int size, var* Postfix, int length, int& postLen)
{
	//�����postfixҪ�ǵ�Ϊ��
	var stack[maxn];
	int top = 0;
	for (int i = 0; i < length; i++)
	{
		if (p[i].num_or_Symbol == 0)//������
		{
			Postfix[postLen++] = p[i];//�����������
		}
		if (p[i].num_or_Symbol == 1 && p[i].Symbol == 4)//������
		{
			++top;
			stack[top] = p[i];
		}
		while (p[i].num_or_Symbol == 1 && p[i].Symbol != 4 && p[i].Symbol != 5)
		{
			if (top == 0 || stack[top].Symbol == 4 || prio(p[i]) > prio(stack[top]))
			{
				++top;
				stack[top] = p[i];
				break;
			}
			else
			{
				Postfix[postLen++] = stack[top];
				top--;
			}
		}
		if (p[i].num_or_Symbol == 1 && p[i].Symbol == 5)//������
		{
			while (stack[top].Symbol != 4)
			{
				Postfix[postLen++] = stack[top];
				top--;
			}
			top--;
		}
	}
	while (top != 0)
	{
		Postfix[postLen++] = stack[top--];
	}
	return SUCCESS;
}

int prio(var element)
{
	if (element.Symbol == 0 || element.Symbol == 1)
		return 1;
	if (element.Symbol == 2 || element.Symbol == 3)
		return 2;
	return 0;
}

void preprocess(var& a, var& b)
{
	//��ǰ���ϵ���ӽ���ĸ
	if (a.num != 0)
	{
		a.numer += a.num * a.Den;
		a.num = 0;
	}
	if (b.num != 0)
	{
		b.numer += b.num * b.Den;
		b.num = 0;
	}
	//��ĸͨ��
	a.numer *= b.Den;
	b.numer *= a.Den;
	a.Den = b.Den = a.Den * b.Den;
}

int get_gcd(int a, int b) {
	return b == 0 ? a : get_gcd(b, a % b);
}

Status calc(var* Postfix, int length, var& ans)
{
	var stack[maxn];//��Ų�����
	int top = 0;
	for (int i = 0; i < length; i++)//������׺���ʽ
	{
		if (Postfix[i].num_or_Symbol == 0)//�ǲ�����
		{
			stack[top++] = Postfix[i];
		}
		else if (Postfix[i].num_or_Symbol == 1)//�������
		{
			if (top < 2)//�ж�һ�²������Ƿ��㹻���������㹻�򱨴�
			{
				printf("�������󣬲��������㣬�޷��������\n");
				exit(-1);
			}
			var ret;
			if (!operate(stack[top - 2], stack[top - 1], Postfix[i], ret))//��������и��� || ��������г����˳� 0 �ķǷ�����
			{
				return ERROR;
			}
			top -= 2;
			stack[top++] = ret;
		}
	}
	if (top == 1)//���϶�ֻʣһ������
	{
		ans = stack[0];
		return SUCCESS;
	}
	//printf("���㵽���ջ��ʣ��Ĳ�������Ϊһ��\n");
	return ERROR;
}

Status operate(var a, var b, var oper, var& ret)
{
	//��ͨ��
	preprocess(a, b);
	//�ж�ִ�еĲ���
	if (oper.Symbol == 0)//+
	{
		a.numer += b.numer;
	}
	else if (oper.Symbol == 1)//-
	{
		a.numer -= b.numer;
	}
	else if (oper.Symbol == 2)// *
	{
		a.numer *= b.numer;
		a.Den *= b.Den;
	}
	else if (oper.Symbol == 3)// ��
	{
		a.numer *= b.Den;
		a.Den *= b.numer;
	}
	if (a.numer < 0 || a.Den == 0)//��������г����˸��� || ��������г����˳� 0 �ķǷ�����
	{
		return ERROR;
	}
	//����
	ret = a;
	int gcd = get_gcd(ret.numer, ret.Den);
	ret.numer /= gcd, ret.Den /= gcd;
	ret.num = ret.numer / ret.Den;
	ret.numer %= ret.Den;
	return SUCCESS;
}

void display(var* a) {
	if (a->num == 0)
	{
		if (a->Den == 1)
		{
			printf("%d\n", a->numer);
		}
		else {
			printf("%d/%d\n", a->numer, a->Den);
		}
	}
	else {
		if (a->Den == 1)
		{
			printf("%d\n", a->numer + a->num);
		}
		else {
			printf("%d'%d/%d\n", a->num, a->numer, a->Den);
		}
	}
}

void crerat_info(var* expression, int i, int num_or_Symbol, int numer, int den, int Symbol, int num)
{
	expression[i].num_or_Symbol = num_or_Symbol;
	expression[i].Den = den;
	expression[i].numer = numer;
	expression[i].Symbol = Symbol;
	expression[i].num = num;
}

void print(var* result, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (result[i].num_or_Symbol == 0)
		{
			printf("%d", result[i].numer);
		}
		else {
			if (result[i].Symbol == 0)
			{
				printf("+");
			}
			else if (result[i].Symbol == 1)
			{
				printf("-");
			}
			else if (result[i].Symbol == 2)
			{
				printf("*");
			}
			else if (result[i].Symbol == 3)
			{
				printf("��");
			}
		}
	}
	puts("");
}

Status Calculation(var* exp, int size, var* result, int length)
{
	int postLen = 0;
	Infix_to_Postfix(exp, size, result, length, postLen);
	var ans;
	if (!calc(result, postLen, ans))
	{
		return ERROR;
	}
	*result = ans;
	return SUCCESS;
}

Status get_Subexpression(var* Postfix, int length, var ans[][3], int& sta_size)
{
	var stack[maxn];//��Ų�����
	int top = 0;
	for (int i = 0; i < length; i++)//������׺���ʽ
	{
		if (Postfix[i].num_or_Symbol == 0)//�ǲ�����
		{
			stack[top++] = Postfix[i];
		}
		else if (Postfix[i].num_or_Symbol == 1)//�������
		{
			var ret;

			ans[sta_size][0] = stack[top - 2];
			ans[sta_size][1] = stack[top - 1];
			ans[sta_size++][2] = Postfix[i];

			operate(stack[top - 2], stack[top - 1], Postfix[i], ret);
			top -= 2;
			stack[top++] = ret;
		}
	}
	return SUCCESS;
}

bool cmp(var a[], var b[])
{
	//�ж��ӱ��ʽ�Ƿ�ȼ�
	if (a[2] == b[2])//�����
	{
		if (a[0] == b[1] && a[1] == b[0] || (a[0] == b[0] && a[1] == b[1]))//������
		{
			return true;
		}
	}
	return false;
}

Status is_question_same(var* Question, int lenQuest, var* newQuestion, int lenNewQuest, int size)
{
	var Postfix1[maxn], Postfix2[maxn];
	var stack1[3][3], stack2[3][3];
	int len1 = 0, len2 = 0, sta_size1 = 0, sta_size2 = 0;

	//��ȡ��׺���ʽ
	Infix_to_Postfix(Question, size, Postfix1, lenQuest, len1);
	Infix_to_Postfix(newQuestion, size, Postfix2, lenNewQuest, len2);

	//��ȡ�ӱ��ʽ
	get_Subexpression(Postfix1, len1, stack1, sta_size1);
	get_Subexpression(Postfix2, len2, stack2, sta_size2);

	bool flag;
	for (int i = 0; i < sta_size1; i++)
	{
		flag = false;
		for (int j = 0; j < sta_size2; j++)
		{
			//��ʽ�ȼ�
			if (cmp(stack1[i], stack2[j]))
			{
				flag = true;
				stack2[j][2].Symbol = -1;//�����ʽ�������ɾ��
				break;
			}
		}
		if (!flag)//������ڲ�һ���ģ�����not same
		{
			return ERROR;
		}
	}
	return SUCCESS;
}