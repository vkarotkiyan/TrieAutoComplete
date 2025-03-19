#include "trie.h"
#include <iostream>
#include <string>
using namespace  std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

	TrieNode* dictionary = new TrieNode(); // Инициализация словаря
	loadDictionary(dictionary, "words.txt"); // Загрузка словаря из файла
	
	string wordVariants = ""; // переменная для всех вариантов слов для автоподстановки
	string versionWord; // вариант выбранного слова из предложенных автоподстановкой
	string inputWord; // вводимое слово
	string fullText; // всё, что ввёл пользователь
	string tempWord; // переменная для хранения необработанных слов
	bool space = true; // проверка наличия пробелов

	cout << "Start typing. [Enter] (without a space) to select a word variant. To exit the program, type \"quit\"" << endl;
	while (cin) { // программа будет работать пока пользователь не закроет терминал
		getline(cin, inputWord);
		if (inputWord == "quit") // Выход из программы
			break;
		for (size_t i = 0, ib = 0; i < inputWord.length(); ++i) { // заполняем введённым текстом 
			fullText.push_back(inputWord[i]);
			tempWord.push_back(inputWord[i]);
			if (inputWord[i] == ' ') // если пользователь закончил вводить слово
				tempWord.clear(); // убираем его из необработанных слов
		}
		wordSubstitution(dictionary, wordVariants, tempWord); // незаконченное слово отправляем на поиск слов для автоподстановки
		if (wordVariants.empty()) { // если в словаре нет вариантов
			tempWord.clear();
			cout << fullText;
			continue;
		}
		wordVariants.erase(wordVariants.length() - 1); // убираем пробел
		int choice = 1; // нумерация вариантов
		cout << endl << choice << " ";
		for (size_t i = 0; i < wordVariants.length(); ++i) { // выводим нумерованнй список слов на экран
			if (wordVariants[i] == ' ') {
				choice++;
				cout << endl << choice;
			}
			cout << wordVariants[i];
		}
		cout << "\nSelect the appropriate word by tapping its number. If there is no suitable word, press 0\n";  // выбор слова
		cin >> choice;
		cin.ignore(32767, '\n');
		for (size_t i = 0; i < wordVariants.length(); ++i) { // выбранное слово заносим в VersionWord
			if (choice == 1)
				versionWord.push_back(wordVariants[i]);
			if (wordVariants[i] == ' ')
				--choice;
			if (choice < 1)
				break;
		}
		if (!versionWord.empty()) { // если пользователь выбрал какой либо вариант
			fullText.erase(fullText.length() - tempWord.length());
			fullText += versionWord;
			tempWord.clear();
			cout << fullText;
		}
		else // если не выбрал
			cout << fullText;
		wordVariants.clear();
		versionWord.clear();
	}

	delete dictionary;
    return 0;
}
