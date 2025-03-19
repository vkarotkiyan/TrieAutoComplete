## TrieAutoComplete

Реализация прототипа программы, выполняющей автодополнение введенного слова по изначально заданному словарю.

Реализованы: 
- структура префиксного дерева и функции для работы с ним. Обрабатываются только строчные символы английского алфавита
- заполнение префиксного дерева словарем из текстового файла. Словарь из примерно 112000 слов занимает в памяти около 60 Мб
- слова в вводимой строке разделяются пробелом. Для выбора продолжения слова по нажатию [Enter] выводится нумерованный список слов. Пользователь вводит номер выбранного слова или 0 для отказа от выбора и возврата к вводимой строке. Для окончания работы с программой нужно ввести ключевое слово "quit"
- Поиск в словаре подходящих вариантов продолжения слова осуществляет функция wordSubstitution(dictionary, wordVariants, tempWord)

Обьявления структуры префиксного дерева и функций для работы с ним:
```cpp
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

```

Примечание: текстовый файл со словами "words.txt" должен находиться в одном каталоге с исполняемым файлом.
