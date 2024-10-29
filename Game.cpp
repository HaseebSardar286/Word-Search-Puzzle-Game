#include<iostream>
#include<fstream>
using namespace std;


void highRecode(int score);
bool wordSearch(char** board, int length, char* word, int size);
void playerNew(char* name);
void inputBoard(char** board, int size);
void outputBoard(char** board, int size);
bool checkPause();
int wordInput(char* word);
bool checkWord(char* word, int length);
int level();
bool fRow(char** board, int length, char* word, int size);
bool fColumn(char** board, int length, char* word, int size);
bool bRow(char** board, int length, char* word, int size);
bool bColumn(char** board, int length, char* word, int size);
bool fDiagonal(char** board, int length, char* word, int size);
bool bDiagonal(char** board, int length, char* word, int size);
bool fReverseDiagonal(char** board, int length, char* word, int size);
bool bReverseDiagonal(char** board, int length, char* word, int size);
void pauseGame(char* name, int score, int lifes);
bool resume(char* name, int& score, int& lifes);
void solveWord(char* word);
void game(char** board, int size, char* word, char* name, int score, int lifes, int lvl);
void inputHigRecord();
int maxScore(int* arr, int size);

int main() 
{
	char name[20] = {};
	while (true)
	{
		int size = 15, score = 0, lifes = 3;
		char select = '\0';
		cout << endl << endl;
		cout << "\t\t\tWORD SEARCH GAME" << endl;
		cout << endl;
		cout << endl << "\t\t\t\tMENU" << endl << endl;
		cout << "\t\tPress n for New Game" << endl;
		cout << "\t\tPress r for Resume Game" << endl;
		cout << "\t\tPress l for Level Selection" << endl;
		cout << "\t\tPress h for High Score" << endl;
		cout << "\t\tPress e for Exit" << endl;
		cout << "Option : ";
		cin >> select;
		char word[20] = {};
		char** board = new char*[size];
		for (int i = 0; i < size; i++)
		{
			board[i] = new char[size];
		}
		if (select == 'n' || select == 'N')
		{
			playerNew(name);
			cout <<endl<< "Please Select Game Level" << endl;
		}
		else if (select == 'r' || select == 'R')
		{
			bool res = resume(name, score, lifes);
			if (res == true)
			{ 
				cout << endl;
				cout << "\tYOUR PREVIOUS SCORE: " << score << "\t\t" << "YOUR REMAINING LIFES: " << lifes << endl;
				int lvl = level();
				game(board, size, word, name, score, lifes, lvl);
			}
			else 
			{

				cout << "\t\tNO ANY GAME PAUSED!" << endl;
				cout<<" PLEASE PLAY NEW GAME." << endl;
			}

		}
		else if (select == 'L' || select == 'l')
		{
			int lvl = level();
			game(board, size, word, name, score, lifes, lvl);
		}
		else if (select == 'h' || select == 'H')
		{
			inputHigRecord();
			cout << endl;
		}
		else if (select == 'e' || select == 'E')
		{
			break;
		}
		else
		{
			cout << "Wrong input!" << endl;
		}
	}
	return 0;
}

void playerNew(char* name)
{
	cout << "Enter Your Name: ";
	cin >> name;
	ofstream file("solves.txt");
	file.close();
}

void inputBoard(char** board, int size)
{
	ifstream fin("board.txt");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fin >> board[i][j];
		}

	}
	fin.close();
}

void outputBoard(char** board, int size)

{
	cout << endl;
	cout << "\t\t      Word Search GAME" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << "\t\t    ";
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;

	}
}

bool checkPause()
{
	bool flag;
	char temp;

	cout << endl << "Press P for pause game." << endl;
	cout << "Press c for continue game." << endl;
	cin >> temp;
	if (temp == 'P' || temp == 'p')
	{
		flag = true;
	}
	else
	{
		flag = false;
	}
	return flag;
}

int wordInput(char* word)
{
	cout << endl << "Enter  word (Capital Letters input only):" << endl;
	cin >> word;
	int i = 0;
	for (; word[i] != '\0'; i++);
	return i;
}

bool checkWord(char* word, int length)
{
	bool flag = false, flag2 = false;
	char temp[15] = {};
	char temp2[15] = {};
	ifstream solve("solves.txt");
	ifstream  fin("dictionary.txt");
	while (!fin.eof())
	{

		fin >> temp;
		int i = 0;
		for (; temp[i] != '\0'; i++);
		if (length == i)
		{
			for (int k = 0; k < length; k++)
			{
				if (temp[k] != word[k])
				{
					break;
				}
				else
				{
					flag = true;
				}
			}

		}
	}
	fin.close();
	while (!solve.eof())
	{

		solve >> temp2;
		int i = 0;
		for (; temp2[i] != '\0'; i++);
		if (length == i)
		{
			for (int k = 0; k < length; k++)
			{
				if (temp2[k] != word[k])
				{
					break;
				}
				else
				{
					flag2 = true;
				}
			}

		}
	}
	if (flag != true)
	{
		cout << "\t\tEnter Right Word. This Word is not in Dictionary" << endl;
		return false;
	}
	else {
		if (flag == true && flag2 == true)
		{
			cout << "\t\tTHIS WORD ALREADY SOLVE!" << endl;
			flag = false;
		}
	}


	fin.close();
	solve.close();
	return flag;
}

int level()
{
	int temp = 0;
	cout << "\t\t\tPress 1 for Easy" << endl;
	cout << "\t\t\tPress 2 for Medium" << endl;
	cout << "\t\t\tPress 3 for Hard" << endl;
	while (true)
	{
		cout << endl << "Enter Your Choice: ";
		cin >> temp;
		if (temp >= 1 && temp <= 3)
		{
			break;
		}
		else
		{
			cout << "Wrong! Please select Level(1 to 3)" << endl;
		}

	}

	return temp;
}


bool fRow(char** board, int length, char* word, int size)
{

	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0, l = 0; j < size; j++)
		{

			if (board[i][j] == word[l])
			{
				flag = false;
				for (int c = j + 1; l < length; c++)
				{
					l++;
					if (board[i][c] == word[l])
					{
						if (l == length - 1)
						{
							flag = true;
							break;
						}

					}
					else
					{
						break;
					}


				}


			}
			if (flag == true)
			{
				break;
			}
		}
		if (flag == true)
		{
			break;
		}
	}
	return flag;
}

bool fColumn(char** board, int length, char* word, int size)
{
	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0, l = 0; j < size; j++)
		{

			if (board[j][i] == word[l])
			{
				flag = false;
				for (int c = j + 1; l < length; c++)
				{
					l++;
					if (board[c][i] == word[l])
					{
						if (l == length - 1)
						{
							flag = true;
							break;
						}

					}
					else
					{
						break;
					}


				}


			}
			if (flag == true)
			{
				break;
			}
		}
		if (flag == true)
		{
			break;
		}
	}
	return flag;
}

bool bRow(char** board, int length, char* word, int size)
{

	bool flag = false;
	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = size - 1, l = 0; j >= 0; j--)
		{

			if (board[i][j] == word[l])
			{
				flag = false;
				for (int c = j - 1; l < length; c--)
				{
					l++;
					if (board[i][c] == word[l])
					{
						if (l == length - 1)
						{
							flag = true;
							break;
						}

					}
					else
					{
						break;
					}


				}


			}
			if (flag == true)
			{
				break;
			}
		}
		if (flag == true)
		{
			break;
		}
	}
	return flag;
}

bool bColumn(char** board, int length, char* word, int size)
{
	bool flag = false;
	for (int i = size - 1; i >= 0; i--)
	{
		for (int j = size - 1, l = 0; j >= 0; j--)
		{

			if (board[j][i] == word[l])
			{
				flag = false;
				for (int c = j - 1; l < length; c--)
				{
					l++;
					if (board[c][i] == word[l])
					{
						if (l == length - 1)
						{
							flag = true;
							break;
						}

					}
					else
					{
						break;
					}


				}


			}
			if (flag == true)
			{
				break;
			}
		}
		if (flag == true)
		{
			break;
		}
	}
	return flag;
}

bool fDiagonal(char** board, int length, char* word, int size)
{

	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0, l = 0, n = i; j < size - 1; j++, n++)
		{

			if (board[j][n] == word[l])
			{
				flag = false;
				for (int c = j + 1, k = n + 1; l < length; c++, k++)
				{
					l++;
					if (board[c][k] == word[l])
					{
						if (l == length - 1)
						{
							flag = true;
							break;
						}

					}
					else
					{
						break;
					}


				}


			}
			if (flag == true)
			{
				break;
			}
		}
		if (flag == true)
		{
			break;
		}
	}
	if (flag != true)
	{
		bool flag = false;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0, l = 0, n = i; j < size - 1; j++, n++)
			{

				if (board[n][j] == word[l])
				{
					flag = false;
					for (int c = n + 1, k = j + 1; l < length; c++, k++)
					{
						l++;
						if (board[c][k] == word[l])
						{
							if (l == length - 1)
							{
								flag = true;
								break;
							}

						}
						else
						{
							break;
						}


					}


				}
				if (flag == true)
				{
					break;
				}
			}
			if (flag == true)
			{
				break;
			}
		}
	}
	return flag;
}

bool bDiagonal(char** board, int length, char* word, int size)
{

	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1, n = (size - 1) - i, l = 0; j >= 0 + i; j--, n--)
		{

			if (board[n][j] == word[l])
			{
				flag = false;
				for (int c = j - 1, k = n - 1; l < length; c--, k--)
				{
					l++;
					if (board[k][c] == word[l])
					{
						if (l == length - 1)
						{
							flag = true;
							break;
						}

					}
					else
					{
						break;
					}


				}


			}
			if (flag == true)
			{
				break;
			}
		}
		if (flag == true)
		{
			break;
		}
	}
	if (flag != true)
	{

		bool flag = false;
		for (int i = 0; i < size; i++)
		{
			for (int j = size - 1, n = (size - 1) - i, l = 0; j >= 0 + i; j--, n--)
			{

				if (board[j][n] == word[l])
				{
					flag = false;
					for (int c = j - 1, k = n - 1; l < length; c--, k--)
					{
						l++;
						if (board[c][k] == word[l])
						{
							if (l == length - 1)
							{
								flag = true;
								break;
							}

						}
						else
						{
							break;
						}


					}


				}
				if (flag == true)
				{
					break;
				}
			}
			if (flag == true)
			{
				break;
			}
		}

	}

	return flag;
}

bool fReverseDiagonal(char** board, int length, char* word, int size)
{

	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = size - 1, l = 0, n = 0; j >= 0; j--, n++)
		{

			if (board[n][j] == word[l])
			{
				flag = false;
				for (int c = j - 1, k = n + 1; l < length; c--, k++)
				{
					l++;
					if (board[k][c] == word[l])
					{
						if (l == length - 1)
						{
							flag = true;
							break;
						}

					}
					else
					{
						break;
					}


				}


			}
			if (flag == true)
			{
				break;
			}
		}
		if (flag == true)
		{
			break;
		}
	}
	if (flag != true)
	{
		bool flag = false;
		for (int i = 0; i < size; i++)
		{
			for (int j = size - 1, l = 0, n = 0 + i; j >= i; j--, n++)
			{

				if (board[n][j] == word[l])
				{
					flag = false;
					for (int c = j - 1, k = n + 1; l < length; c--, k++)
					{
						l++;
						if (board[k][c] == word[l])
						{
							if (l == length - 1)
							{
								flag = true;
								break;
							}

						}
						else
						{
							break;
						}


					}


				}
				if (flag == true)
				{
					break;
				}
			}
			if (flag == true)
			{
				break;
			}
		}
	}
	return flag;
}

bool bReverseDiagonal(char** board, int length, char* word, int size)
{

	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0, n = (size - 1) - i, l = 0; j < size - i; j++, n--)
		{

			if (board[n][j] == word[l])
			{
				flag = false;
				for (int c = j + 1, k = n - 1; l < length; c++, n--)
				{
					l++;
					if (board[k][c] == word[l])
					{
						if (l == length - 1)
						{
							flag = true;
							break;
						}

					}
					else
					{
						break;
					}


				}


			}
			if (flag == true)
			{
				break;
			}
		}
		if (flag == true)
		{
			break;
		}
	}
	if (flag != true)
	{

		bool flag = false;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0, n = (size - 1) - i, l = 0; j < size - i; j++, n--)
			{

				if (board[n][j] == word[l])
				{
					flag = false;
					for (int c = j + 1, k = n - 1; l < length; c++, n--)
					{
						l++;
						if (board[k][c] == word[l])
						{
							if (l == length - 1)
							{
								flag = true;
								break;
							}

						}
						else
						{
							break;
						}


					}


				}
				if (flag == true)
				{
					break;
				}
			}
			if (flag == true)
			{
				break;
			}
		}
	}

	return flag;
}


void pauseGame(char* name, int score, int lifes)
{
	ofstream file("Pausegame.txt");
	file << name << " " << score << " " << lifes << endl;
	file.close();
}

bool resume(char* name, int& score, int& lifes)
{
	bool flag = false;
	ifstream file("Pausegame.txt");
	int i = 0;
	while (!file.eof())
	{
		file >> name >> score >> lifes;
	}

	if (score != 0)
	{
		flag = true;
	}
	file.close();
	return flag;
}

void solveWord(char* word)
{
	ofstream fout("solves.txt", ios::app | ios::out);
	fout << word << endl;
	fout.close();
}

void game(char** board, int size, char* word, char* name, int score, int lifes, int lvl)
{

	inputBoard(board, size);
	outputBoard(board, size);
	if (lvl == 1)
	{
		while (true)
		{
			int length;
			while (true)
			{
				length = wordInput(word);
				if (checkWord(word, length) == false)
				{
					cout << "Try Again!" << endl;
				}
				else
				{
					break;
				}
			}
			if (wordSearch(board, length, word, size) == true)
			{
				score += 10;
				cout << "Score:" << score << endl;
				solveWord(word);
			}
			else 
			{
				lifes--;
				cout << "LIFE:" << lifes << endl;
			}
			if (lifes == 0)
			{
				cout << "YOU LOSE THE GAME!" << endl;
				highRecode(score);
				ofstream file("Pausegame.txt");
				file.close();
				break;
			}
			if (checkPause() == true)
			{
				pauseGame(name, score, lifes);
				cout << "GAME PAUSED!" << endl;
				break;
			}
		}


	}
	else if (lvl == 2)
	{
		while (true)
		{
			int length;
			while (true)
			{
				length = wordInput(word);
				if (checkWord(word, length) == false)
				{
					cout << "Try Again:" << endl;
				}
				else
				{
					break;
				}
			}
			if (wordSearch(board, length, word, size) == true)
			{
				score += 10;
				cout << "Score:" << score << endl;
				solveWord(word);
			}
			else
			{
				lifes--;
				cout << "LIFE:" << lifes << endl;
			}
			if (lifes == 0)
			{
				cout << "YOU LOSE THE GAME!" << endl;
				highRecode(score);
				ofstream file("Pausegame.txt");
				file.close();
				break;
			}
			if (checkPause() == true)
			{
				pauseGame(name, score, lifes);
				cout << "GAME PAUSED!" << endl;
				break;
			}
		}
	}
	else if (lvl == 3)
	{
		while (true)
		{
			int length;
			while (true)
			{
				length = wordInput(word);
				if (checkWord(word, length) == false)
				{
					cout << "Try Again" << endl;
				}
				else
				{
					break;
				}
			}
			if (wordSearch(board, length, word, size) == true)
			{
				score += 10;

				cout << "Score:" << score << endl;

				solveWord(word);
			}
			else
			{
				lifes--;
				cout << "LIFE:" << lifes << endl;
			}
			if (lifes == 0) {
				cout << "YOU LOSE THE GAME!" << endl;
				highRecode(score);
				ofstream file("Pausegame.txt");
				file.close();
				break;
			}
			if (checkPause() == true)
			{
				pauseGame(name, score, lifes);
				cout << "GAME PAUSED!" << endl;
				break;
			}
		}
	}
}



void highRecode(int score)
{
	int i = 0;
	const int index = 5;
	int h_s[index] = {};
	ifstream file("highrecode.txt");
	while (!file.eof())
	{
		file >> h_s[i];
		i++;
	}
	file.close();
	int l = i + 1;
	int* temp = new int[l];
	for (int j = 0, k = 0; j < l; j++)
	{
		if (h_s[k] > score)
		{
			temp[j] = h_s[k];
			k++;
		}
		else
		{
			temp[j] = score;
			score = 0;
		}

	}
	ofstream fout("highrecode.txt");
	if (l > 4)
	{
		l = 5;
	}
	for (int m = 0; m < l; m++)
	{
		fout << temp[m] << endl;
	}
	fout.close();
	delete[]temp;
}

void inputHigRecord()
{
	const int s = 5;
	int h_s[s] = {};
	int i = 0;
	cout << "HIGH SCORES:" << endl;
	ifstream file("highrecode.txt");
	while (!file.eof())
	{
		file >> h_s[i];
		i++;
	}
	file.close();
	for (int f = 0; f < s; f++)
	{
		if (h_s[f] != 0)
		{
			cout << h_s[f] << endl;
		}

	}
}

int maxScore(int* arr, int size)
{
	int max = arr[0];
	for (int i = 1; i < size; i++)
	{
		if (max < arr[i])
		{
			max = arr[i];
		}

	}
	return max;
}

bool wordSearch(char** board, int length, char* word, int size)
{

	bool flag = false;

	if (fRow(board, length, word, size) == true || bRow(board, length, word, size) == true || fDiagonal(board, length, word, size) == true || bDiagonal(board, length, word, size) == true)
	{
		flag = true;
	}
	else
	{
		if (fColumn(board, length, word, size) == true || bColumn(board, length, word, size) == true || fReverseDiagonal(board, length, word, size) == true || bReverseDiagonal(board, length, word, size) == true)
		{
			flag = true;
		}
		else
		{
			flag = false;
		}
	}
	return flag;
}

