#pragma once
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;
const int BUF_SIZE = 26;

struct TrieNode { // Структура узла дерева
	struct TrieNode* children[ALPHABET_SIZE];
	bool isEndOfWord; // isEndOfWord - true, если ключ является концом слова
};

TrieNode* getNewNode(void); // Подготовка нового узла
void insert(TrieNode*, string);
bool search(TrieNode*, string);
bool isEmpty(TrieNode*);
TrieNode* remove(TrieNode*, string, int depth = 0);
void hasPrefix(TrieNode*, int&);
void findMinPrefixes(TrieNode*, char[], int, string&);
void wordSubstitution(TrieNode*, string&, string); // поиск слов для подстановки
void wordSubstitutionInner(TrieNode*, char[], int, string&, int&, bool); // рекурсионная функция поиска слов для подстановки
TrieNode* loadDictionary(TrieNode*, const string&); // Загрузка словаря из файла
