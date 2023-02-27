#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include<ctime>
#include<cstdlib>

using namespace cv;
using namespace std;

int a = 1;

template <typename T>
class node
{
public:
	T data;
	T data2;
	node<T>* next;

	node(T d, T d2)
	{
		this->data = d;
		this->data2 = d2;
		next = nullptr;
	}



};

template <typename T>
class node_0
{
public:
	T data;
	node_0<T>* next;

	node_0(T d)
	{
		this->data = d;
		next = nullptr;
	}
};

template <typename T>
class queue
{
	node<T>* front;
	node<T>* back;
public:
	queue()
	{
		front = back = NULL;
	}
	void push(T x, T y)
	{
		node<T>* n = new node<T>(x, y);
		if (front == NULL)
		{
			back = n;
			front = n;
			return;
		}
		back->next = n;
		back = n;
	}
	void pop()
	{
		if (front == NULL)
		{
			return;
		}
		node<T>* temp = front;
		front = front->next;
		delete temp;
	}
	int getdata_1()
	{
		return front->data;
	}
	int getdata_2()
	{
		return front->data2;
	}
	bool IsEmpty()
	{
		if (front == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

template <typename T>
class Stack
{
	node_0<T>* top;
public:
	Stack()
	{
		top = NULL;
	}
	void push(T x)
	{
		node_0<T>* n = new node_0<T>(x);
		n->data = x;
		n->next = top;
		top = n;
	}
	void pop()
	{
		if (top == NULL)
		{
			return;
		}
		node_0<T>* temp = top;
		top = top->next;
		delete temp;
	}
	T peek()
	{
		if (!IsEmpty())
		{
			return top->data;
		}
	}
	bool IsEmpty()
	{
		if (top == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

template <typename T>
class LRU
{
public:
	LRU()
	{
		front = back = NULL;
		size = 0;
	}
	void push(T x, T y)
	{
		node<T>* n = new node<T>(x, y);
		if (front == NULL)
		{
			back = n;
			front = n;
			return;
		}
		back->next = n;
		back = n;
		size++;
	}
	void pop()
	{
		if (front == NULL)
		{
			return;
		}
		node<T>* temp = front;
		front = front->next;
		delete temp;
		size--;
	}
	string getdata_1()
	{
		return front->data;
	}
	string getdata_2()
	{
		return front->data2;
	}
	int getsize()
	{
		return size;
	}
	bool IsEmpty()
	{
		if (front == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
private:
	int size;
	node<T>* front;
	node<T>* back;
};

template <typename T>
bool compare(LRU<T>& lru, string a)
{
	string temp;
	string temp2;
	LRU<string> temp3;
	while (!lru.IsEmpty())
	{
		temp = lru.getdata_1();
		temp2 = lru.getdata_2();
		if (temp == a)
		{
			while (!temp3.IsEmpty())
			{
				temp = temp3.getdata_1();
				temp2 = temp3.getdata_2();
				lru.push(temp, temp2);
				temp3.pop();
			}
			return true;
		}
		temp3.push(temp, temp2);
		lru.pop();
	}
	temp = temp2 = "";
	while (!temp3.IsEmpty())
	{
		temp = temp3.getdata_1();
		temp2 = temp3.getdata_2();
		lru.push(temp, temp2);
		temp3.pop();
	}
	return false;
}

template <typename T>
void image_pixel_pickeing(float**& image_array, T rows, T cols, Mat image)
{
	image_array = new float* [rows];
	for (int i = 0; i < rows; i++)
	{
		image_array[i] = new float[cols] {0.0};
	}
	T r, b, g;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			r = image.at<Vec3b>(i, j)[0];//red
			b = image.at<Vec3b>(i, j)[1];//blue
			g = image.at<Vec3b>(i, j)[2];//green

			image_array[i][j] = T(r + b + g) / 3;
		}
	}
}

template <typename T>
void display_new_image(T** image_array, int rows, int cols, Mat image, string path)
{
	static int number_op_image = 0;
	Mat ima = imread(path);
	ima.rows = rows;
	ima.cols = cols;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			ima.at<Vec3b>(i, j)[2] = image_array[i][j];
			ima.at<Vec3b>(i, j)[1] = image_array[i][j];
			ima.at<Vec3b>(i, j)[0] = image_array[i][j];
		}
	}
	imshow("Window01.bmp", image);
	imshow("Window02.bmp", ima);
	imwrite("D:/Data Structures/Assignments/A2/images/Output_file/img" +to_string(a)+".bmp", ima);
	a++;
	waitKey(0);
}

template <typename T>
void display(int** image_array, T rows, T cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << image_array[i][j] << " ";
		}
	}
}

int lable_marking(float** arr, int rows, int cols, Mat image, string path)
{
	int lable = 1;
	//8 neighbour connectivity
	for (int i = 0; i < rows - 1; i++)
	{
		for (int j = 0; j < cols - 1; j++)
		{
			if (arr[i][j] != 0)
			{
				arr[i][j] = lable;
				if (arr[i][j + 1] != 0) //right
				{
					arr[i][j + 1] = min(arr[i][j], arr[i][j + 1]);
				}
				if (arr[i][j - 1] != 0) //left
				{
					arr[i][j - 1] = min(arr[i][j], arr[i][j - 1]);
				}
				if (arr[i + 1][j] != 0) //down
				{
					arr[i + 1][j] = min(arr[i][j], arr[i + 1][j]);
				}
				if (arr[i - 1][j] != 0) //up
				{
					arr[i - 1][j] = min(arr[i][j], arr[i - 1][j]);
				}
				if (arr[i - 1][j - 1] != 0) //top left
				{
					arr[i - 1][j - 1] = min(arr[i][j], arr[i - 1][j - 1]);
				}
				if (arr[i - 1][j + 1] != 0) //top right
				{
					arr[i - 1][j + 1] = min(arr[i][j], arr[i - 1][j + 1]);
				}
				if (arr[i + 1][j - 1] != 0) //bottom left
				{
					arr[i + 1][j - 1] = min(arr[i][j], arr[i + 1][j - 1]);
				}
				if (arr[i + 1][j + 1] != 0) //top right
				{
					arr[i + 1][j + 1] = min(arr[i][j], arr[i + 1][j + 1]);
				}
				lable++;
			}
		}
	}
	int p = 0;
	while (p < rows)
	{
		for (int i = 0; i < rows - 1; i++)
		{
			for (int j = 0; j < cols - 1; j++)
			{
				if (arr[i][j] != 0)
				{
					if (arr[i][j + 1] != 0) //right
					{
						arr[i][j + 1] = min(arr[i][j], arr[i][j + 1]);
					}
					if (arr[i][j - 1] != 0) //left
					{
						arr[i][j - 1] = min(arr[i][j], arr[i][j - 1]);
					}
					if (arr[i + 1][j] != 0) //down
					{
						arr[i + 1][j] = min(arr[i][j], arr[i + 1][j]);
					}
					if (arr[i - 1][j] != 0) //up
					{
						arr[i - 1][j] = min(arr[i][j], arr[i - 1][j]);
					}
					if (arr[i - 1][j - 1] != 0) //top left
					{
						arr[i - 1][j - 1] = min(arr[i][j], arr[i - 1][j - 1]);
					}
					if (arr[i - 1][j + 1] != 0) //top right
					{
						arr[i - 1][j + 1] = min(arr[i][j], arr[i - 1][j + 1]);
					}
					if (arr[i + 1][j - 1] != 0) //bottom left
					{
						arr[i + 1][j - 1] = min(arr[i][j], arr[i + 1][j - 1]);
					}
					if (arr[i + 1][j + 1] != 0) //top right
					{
						arr[i + 1][j + 1] = min(arr[i][j], arr[i + 1][j + 1]);
					}
				}
			}
		}
		p++;
	}

	int* frequency = new int[lable];
	for (int i = 0; i < lable; i++)
	{
		frequency[i] = 0;
	}
	for (int j = 0; j < rows; j++)
	{
		for (int k = 0; k < cols; k++)
		{
			int a = int(arr[j][k]);
			frequency[a] += 1;
		}
	}
	int counter = 0;
	for (int i = 1; i < lable; i++)
	{
		if (frequency[i] != 0)
		{
			counter++;
		}
	}
	int ll = 0;
	int* the_lables_of_images = new int[counter];
	for (int i = 1; i < lable; i++)
	{
		if (frequency[i] != 0)
		{
			the_lables_of_images[ll++] = i;
		}
	}
	queue<int>* que = new queue<int>[ll];


	for (int i = 0; i < ll; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			for (int k = 0; k < cols; k++)
			{
				if (the_lables_of_images[i] == arr[j][k])
				{
					que[i].push(j, k);
				}
			}
		}
	}
	int*** array = new int** [ll];

	for (int i = 0; i < ll; i++) {

		array[i] = new int* [rows];

		for (int j = 0; j < rows; j++) {

			array[i][j] = new int[cols];
		}
	}
	for (int i = 0; i < ll; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			for (int k = 0; k < cols; k++)
			{
				array[i][j][k] = 0;
			}
		}
	}
	for (int i = 0; i < ll; i++)
	{
		while (!(que[i].IsEmpty()))
		{

			int a = que[i].getdata_1();
			int b = que[i].getdata_2();
			array[i][a][b] = 255;
			que[i].pop();
		}
	}

	int** image_array_anwer;

	for (int i = 0; i < ll; i++)
	{
		image_array_anwer = array[i];
		display_new_image(image_array_anwer, rows, cols, image, path);
	}
	return ll;
}

bool alph(char a)
{
	if ((a >= 'a' && 'z' >= a) || (a >= 'A' && 'Z' >= a) || (a >= '0' && '9' >= a))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int importace(char a)
{
	if (a == '(')
	{
		return 1;
	}
	if (a == '+' || a == '-' || a == '-' || a == '!' || a == '~' || a == '$')
	{
		return 2;
	}
	else if (a == '*' || a == '/' || a == '%')
	{
		return 3;
	}
	else if (a == '&' || a == '|' || a == '^')
	{
		return 4;
	}
	else
	{
		return -1;
	}
}

bool checking_opeation(char a)
{
	if ((a == '+') || (a == '-') || (a == '*') || (a == '/') || (a == '&') || (a == '|') || (a == '^') || (a == '!'))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool checking_char(char a)
{
	if ((a >= 'a' && 'z' >= a) || (a >= 'A' && 'Z' >= a) || (a >= '0' && '9' >= a))
	{
		return true;
	}
	else
	{
		return false;
	}
}

string post_exp(string equation)
{
	bool flag = 1;
	bool check = 1;
	string temp;
	string b = "";
	Stack<char> p;
	Stack<char> brackets;
	for (int i = 0; i < equation.length(); i++)
	{
		if ((checking_char(equation[i])) || (checking_opeation(equation[i]) && checking_char(equation[i + 1])))
		{
			for (int j = i; j < equation.length(); j++)
			{
				if (equation[j] != ' ' || equation[j] != '(' || equation[j] != ')') {

					temp += equation[j];
				}
				else
				{
					i = j;
					break;
				}
			}
			if (check != 1)
			{
				b = "-*-*-*-*-*-*-*-*-Error Invalid expression-*-*-*-*-*-*-*-*-";
				return b;
			}
			b += temp;
			temp = "";
			check = 0;
		}
		else if ((equation[i] == '('))
		{
			p.push(equation[i]);
			brackets.push(equation[i]);
			check = 1;
		}
		else if ((equation[i] == ')'))
		{

			if (!(brackets.IsEmpty()))
			{
				brackets.pop();
			}
			else
			{
				b = "-*-*-*-*-*-*-*-*-Error Invalid expression-*-*-*-*-*-*-*-*-";

				return b;
				break;
			}
			while ((p.peek() != '(') && (!p.IsEmpty()))
			{
				b += p.peek();
				p.pop();
				flag = 0;
			}
			if ((p.peek() == '(') && flag == 0)
			{
				p.pop();
				flag = 1;
			}
		}
		else if (checking_opeation(equation[i]))
		{
			if (p.IsEmpty())
			{
				p.push(equation[i]);
			}
			else
			{
				if (importace(equation[i]) > importace(p.peek()))
				{
					p.push(equation[i]);
				}
				else if (importace(equation[i]) <= importace(p.peek()))
				{
					do
					{
						b += p.peek();
						p.pop();
					} while (!(p.IsEmpty()) && p.peek() != '(');
					p.push(equation[i]);
				}
			}
			check = 1;
		}
	}
	if (!(brackets.IsEmpty()))
	{
		b = "-*-*-*-*-*-*-*-*-Error Invalid expression-*-*-*-*-*-*-*-*-";

		return b;
	}
	while (!(p.IsEmpty()))
	{
		if (p.peek() == '(')
		{
			b = "-*-*-*-*-*-*-*-*-Error Invalid expression-*-*-*-*-*-*-*-*-";
			break;
		}
		b += p.peek();
		p.pop();
	}

	return b;
}

string pre_exp(string equation)
{
	Stack<char> p;
	Stack<char> bracket;
	char temp;
	string res;
	for (int i = 0, j = equation.length() - 1; ; i++, j--)
	{
		if (i == j)
		{
			break;
		}
		temp = equation[j];
		equation[j] = equation[i];
		equation[i] = temp;
	}

	for (int i = 0; i < equation.length(); i++)
	{
		if ((equation[i] >= 'a' && 'z' >= equation[i]) || (equation[i] >= 'A' && 'Z' >= equation[i]) || (equation[i] >= '0' && '9' >= equation[i]))
		{
			res += equation[i];
		}
		else if (equation[i] == ')')
		{
			p.push(equation[i]);
			bracket.push(equation[i]);
		}
		else if (equation[i] == '(')
		{
			while ((!p.IsEmpty()) && (p.peek() != ')'))
			{
				res += p.peek();
				p.pop();
			}
			if (!p.IsEmpty())
			{
				p.pop();
			}
			bracket.pop();
		}
		else
		{
			while ((!p.IsEmpty()) && (importace(p.peek()) >= importace(equation[i])))
			{
				res += p.peek();
				p.pop();
			}
			p.push(equation[i]);
		}
	}
	while (!p.IsEmpty())
	{
		if (p.peek() != ')')
			res += p.peek();
		p.pop();
	}

	for (int i = 0, j = res.length() - 1; ; i++, j--)
	{
		if (i == j)
		{
			break;
		}
		temp = res[j];
		res[j] = res[i];
		res[i] = temp;
	}

	if (!(bracket.IsEmpty()))
	{
		res = "-*-*-*-*-*-*-*-*-Error Invalid expression-*-*-*-*-*-*-*-*-";
	}

	return res;
}
/// post to infix
string sol_exp(string equation)
{
	string temp3;
	for (int i = 0; i < equation.length(); i++)
	{
		if (equation[i] == '(' || equation[i] == ')')
		{
			temp3 = "-*-*-*-*-*-*-*-*-Error Invalid expression-*-*-*-*-*-*-*-*-";
			return temp3;
		}
	}
	int counter = 0;
	int counter1 = 0;
	for (int i = 0; i < equation.length(); i++)
	{
		if (checking_char(equation[i]))
		{
			counter++;
		}
		if (checking_opeation(equation[i]))
		{
			counter1++;
		}
	}
	if ((counter == counter1) || (counter < counter1))
	{
		temp3 = "-*-*-*-*-*-*-*-*-Error Invalid expression-*-*-*-*-*-*-*-*-";
		return temp3;
	}
	temp3 = "";
	Stack<string> s;
	string temp, temp2;
	for (int i = 0; i < equation.length(); i++) {
		if (equation[i] != ' ')
		{
			if (alph(equation[i]) || (checking_char(equation[i + 1]) && checking_opeation(equation[i]))) {

				for (int j = i; j < equation.length(); j++)
				{
					if (equation[j] != ' ')
					{
						temp3 += equation[j];
					}
					else
					{
						i = j;
						break;
					}
				}
				s.push(temp3);
				temp3 = "";
			}
			else {
				temp = s.peek();
				s.pop();
				temp2 = s.peek();
				s.pop();
				s.push("(" + temp2 + equation[i] + temp + ")");
			}
		}
	}

	return s.peek();
}

string tag_list(string tag)
{
	string b;
	for (int i = 0; i < tag.length(); i++)
	{
		if (tag[i] != '\\')
		{
			b += tag[i];
		}
	}
	return b;
}

string checking_tag(Stack<string>& a, string tag)
{
	Stack<string> temp;
	string b;
	bool flag = 0;
	string c = tag_list(tag);

	while (!(a.IsEmpty()))
	{
		b = a.peek();
		if (b != c)
		{
			temp.push(a.peek());
			a.pop();
		}
		if (b == c)
		{
			a.pop();
			flag = 1;
			while (!(temp.IsEmpty()))
			{
				a.push(temp.peek());
				temp.pop();
			}
			b = "done";
			break;
		}
	}
	if (flag != 1)
	{
		while (!(temp.IsEmpty()))
		{
			a.push(temp.peek());
			temp.pop();
			b = "*-*-*-*-*-*-*-*-*-*-* ERROR " + c + " tag not found *-*-*-*-*-*-*-*-*-*-*";
		}
	}

	return b;
}
