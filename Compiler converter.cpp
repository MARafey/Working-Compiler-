#include<fstream>
#include<string>
#include<iostream>
#include"Header.h"
using namespace std;

string seperation(string text)
{
	int i = 0;
	string a = "";
	bool flag = 1;
	while (text[i] != '\n')
	{
		if ('|' == text[i] && flag == 1)
		{
			a = a + text[i];
			flag = 0;
			i++;
			continue;
		}
		if ('|' == text[i] && flag == 0)
		{
			a += text[i];
			break;
		}
		a += text[i];
		i++;
	}
	return a;
}

int main()
{
	Stack<string> tags, equation;
	string text;
	fstream Myfile, file,cppfile;
	string saving_file = "";
	string delta = "|";
	LRU<string> lru;
	int file_0 = 0;
	bool flag = 1;
	bool flag_priority = 0;
	string path;
	int hits = 0;
	int missed = 0;
	file.open("D:/Answer-Test.txt", 'w');
	for (int m = 1; m <= 7; m++)
	{
		flag_priority = 1;
		path = "D:/Data Structures/Assignments/A2/Test_files/Test-"+to_string(m) + ".txt";
		Myfile.open(path);

		while (getline(Myfile, text))
		{
			if (text[0] == '|')
			{
				saving_file = seperation(text);
			}
			if (saving_file == "|start|")
			{
				tags.push(saving_file);
				saving_file = "";
				continue;
			}


			for (int i = 0; i < text.length(); i++)
			{
				if (text[i] != '|')
				{
					if (flag_priority == 1 && (text[i] >= '0' && text[i] <= '9'))
					{
						for (int j = i; j < text.length(); j++)
						{
							saving_file += char(text[j]);
						}
						i = i + saving_file.length();
						if (lru.getsize() < 4) {
							lru.push(saving_file, path);
							missed++;
						}
						else
						{
							if (compare(lru, saving_file))
							{
								hits++;
							}
							else
							{
								missed++;
							}
							lru.pop();
							lru.push(saving_file, path);
						}
						
						saving_file = "";
						continue;
					}
					else {
						file << text[i];
					}
				}
				if (text[i] == '|' && flag == 1)
				{

					for (int j = i + 1; j < text.length(); j++)
					{
						if (text[j] != '|') {
							delta += char(text[j]);
						}
						else
						{
							delta += char(text[j]);
							break;
						}
					}
					saving_file = seperation(delta);
					i = i + delta.length();
					if (saving_file == "|priorty|")
					{
						tags.push(saving_file);
						flag_priority = 1;
						delta = "|";
						saving_file = "";
						continue;
					}
					if (saving_file == "|\\priorty|")
					{
						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						flag_priority = 0;
						saving_file = "";
						delta = "|";
						continue;
					}

					if (saving_file == "|pre_exp|")
					{
						tags.push(saving_file);
						flag_priority = 1;
						delta = "|";
						saving_file = "";
						for (int j = i; j < text.length(); j++)
						{
							if ((text[j + 1] == '\\' && text[j] == '|') || text[j] == '.')
							{
								i = j;
								i--;
								break;
							}
							if (text[j] != ' ')
								saving_file += text[j];

						}
						if ((text[i + 1] != '|'))
						{
							file << "*-*-*-*-*-*-*-*-*Syntax error*-*-*-*-*-*-*-*-*";
						}
						else
						{
							delta = pre_exp(saving_file);
							file << delta;
						}

						delta = "|";
						saving_file = "";
						continue;
					}
					if (saving_file == "|\\pre_exp|")
					{
						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						flag_priority = 0;
						saving_file = "";
						delta = "|";
						i--;
						continue;
					}
					if (saving_file == "|post_exp|" || saving_file == "|In_exp|")
					{

						tags.push(saving_file);
						flag_priority = 1;
						delta = "|";
						saving_file = "";
						for (int j = i; j < text.length(); j++)
						{
							if ((text[j + 1] == '\\' && text[j] == '|') || text[j] == '.')
							{
								i = j;
								i--;
								break;
							}

							saving_file += text[j];

						}
						if ((text[i + 1] != '|'))
						{
							file << "*-*-*-*-*-*-*-*-*Syntax error*-*-*-*-*-*-*-*-*";
						}
						else
						{
							delta = post_exp(saving_file);
							file << delta;
						}

						delta = "|";
						saving_file = "";
						continue;
					}
					if (saving_file == "|\\post_exp|" || saving_file == "|\\In_exp|")
					{
						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						flag_priority = 0;
						saving_file = "";
						delta = "|";
						i--;
						continue;
					}
					if (saving_file == "|sol_exp|")
					{
						tags.push(saving_file);
						flag_priority = 1;
						delta = "|";
						saving_file = "";
						for (int j = i; j < text.length(); j++)
						{
							if ((text[j + 1] == '\\' && text[j] == '|') || text[j] == '.')
							{
								i = j;
								i--;
								break;
							}
							saving_file += text[j];

						}
						if ((text[i + 1] != '|'))
						{
							file << "*-*-*-*-*-*-*-*-*Syntax error*-*-*-*-*-*-*-*-*";
						}
						else
						{

							delta = sol_exp(saving_file);
							file << delta;
						}

						delta = "|";
						saving_file = "";
						continue;
					}
					if (saving_file == "|\\sol_exp|")
					{
						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						flag_priority = 0;
						saving_file = "";
						delta = "|";
						i--;
						continue;
					}


					if (saving_file == "|head|")
					{
						tags.push(saving_file);
						saving_file = "";
						delta = "|";
						continue;
					}
					if (saving_file == "|\\head|")
					{
						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						saving_file = "";
						delta = "|";

						continue;
					}
					if (saving_file == "|paragraph|")
					{
						tags.push(saving_file);
						saving_file = "";
						delta = "|";
						file << '\t';
					}
					if (saving_file == "|\\paragraph|")
					{

						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						saving_file = "";
						delta = "|";
						i--;
					}

					if (saving_file == "|src|")
					{
						tags.push(saving_file);
						saving_file = "";
						delta = "|";

						for (int j = i; j < text.length(); j++)
						{
							if (text[j] != '|')
							{
								saving_file += char(text[j]);
							}
							else
							{
								break;
							}
						}

						i = i + saving_file.length() - 1;
						for (int k = 0; k < saving_file.length(); k++)
						{
							if (saving_file[k] == '\\')
							{
								saving_file[k] = '/';
							}
							if (saving_file[k] == ' ')
							{
								continue;
							}
						}
						delta = "";
						for (int k = 0; k < saving_file.length(); k++)
						{
							if (saving_file[k] == ' ')
							{
								continue;
							}
							delta += saving_file[k];
						}
						saving_file = delta;
						delta = "|";
						if (text[i + 1] != '|')
						{
							file << "*-*-*-*-*-*-*-*-*Syntax error*-*-*-*-*-*-*-*-*";
						}
						else
						{

							string path = "D:/" + saving_file + ".bmp";
							float** image_array;
							Mat image = imread(path);
							image_pixel_pickeing(image_array, image.rows, image.cols, image);
							int a = lable_marking(image_array, image.rows, image.cols, image, path);
							file << a;
						}

						saving_file = "";
						continue;

					}
					if (saving_file == "|\\src|")
					{
						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						saving_file = "";
						delta = "|";

						i--;
					}

					if (saving_file == "|tab|")
					{
						tags.push(saving_file);
						saving_file = "";
						delta = "|";
						file << '\t';
						file << '\t';
						i--;
					}
					if (saving_file == "|\\tab|")
					{
						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						saving_file = "";
						delta = "|";

						i--;
					}
					if (saving_file == "|chk|")
					{
						tags.push(saving_file);
						saving_file = "";
						delta = "|";
					}
					if (saving_file == "|\\chk|")
					{
						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						saving_file = "";
						delta = "|";
						i--;
					}
					if (saving_file == "|Function|")
					{
						tags.push(saving_file);
						saving_file = "";
						delta = "|";
						cppfile.open("D:/Data Structures/Assignments/A2/Code_Files/file_" + to_string(file_0) + ".cpp");
						file_0++;
						while (getline(Myfile, text))
						{
							if (text == "|\\Function|")
							{
								break;
							}
							cppfile << text;
						}
						cppfile.close();
					}




					if (saving_file == "|\\Function|")
					{

						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						saving_file = "";
						delta = "|";
						i--;
					}
					if (saving_file == "|tick|")
					{
						tags.push(saving_file);
						saving_file = "";
						delta = "|";
					}
					if (saving_file == "|\\tick|")
					{
						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						saving_file = "";
						delta = "|";
						i--;
					}
					if (saving_file == "|hick|")
					{
						tags.push(saving_file);
						saving_file = "";
						delta = "|";
					}
					if (saving_file == "|\\hick|")
					{
						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						saving_file = "";
						delta = "|";
						i--;
					}
					if (saving_file == "|pick|")
					{
						tags.push(saving_file);
						saving_file = "";
						delta = "|";

					}
					if (saving_file == "|\\pick|")
					{
						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						saving_file = "";
						delta = "|";
						i--;
					}
					if (saving_file == "|\\start|")
					{
						saving_file = checking_tag(tags, saving_file);
						if (saving_file[0] == '*')
						{
							file << saving_file;
						}
						saving_file = "";
						delta = "|";
						continue;
					}

				}
			}
			file << '\n';
		}
		if (tags.IsEmpty() != true)
		{
			file << "There seems to be an error in this file";
			file << '\n';
			while (!tags.IsEmpty())
			{
				file << tags.peek() + " closing tag not found.";
				file << '\n';
				tags.pop();
			}
		}

		Myfile.close();
	}
	file.close();
	cout << "Hits = " << hits << endl;
	cout << "Misses = " << missed << endl;
}
