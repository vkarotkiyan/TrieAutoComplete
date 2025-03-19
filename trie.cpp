#include <fstream>
#include <sstream>
#include <string>
#include "trie.h"
using namespace std;

constexpr char alphabetStart = 'a';
constexpr char alphabetEnd = 'z';

TrieNode* getNewNode(void) {
    TrieNode* pNode = new TrieNode; // Выделяем память под новый узел
    pNode->isEndOfWord = false; // устанавливаем флаг конца слова в false
    for (int i = 0; i < ALPHABET_SIZE; i++) // инициализируем детей нулевым указателем
        pNode->children[i] = nullptr;
    return pNode;
}

// Вставляет ключ в дерево, если его нет, иначе если ключ явлется префиксом узла дерева 
// помечает в качестве листового, т.е. конец слова
void insert(TrieNode* root, string key) {
    TrieNode* node = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a'; // вычисляем индекс в алфавите через смещение отнсительно первой буквы
        if (!node->children[index]) // если указатель пустой, т.е. детей с таким префиксом нет, создаем новый узел
            node->children[index] = getNewNode();
        node = node->children[index];
    }
    node->isEndOfWord = true; // помечаем последний узлел как лист, т.е. конец слова
}

bool search(TrieNode* root, string key) {
    TrieNode* node = root;
    for (int i = 0; i < key.length(); i++) {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;
        node = node->children[index];
    }
    return (node != nullptr && node->isEndOfWord);
}

bool isEmpty(TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

TrieNode* remove(TrieNode* root, string key, int depth) {
    if (!root) // Если дерево пустое
        return nullptr;
    if (depth == key.size()) { // Если дошли до конца ключа
        if (root->isEndOfWord) // Этот узел больше не конец слова, поэтому снимаем метку
            root->isEndOfWord = false;
        if (isEmpty(root)) { // Если ключ не является префиксом, удаляем его
            delete (root);
            root = nullptr;
        }
        return root;
    }
    // Пока не дошли до конца ключа или определили, что его нет в дереве, 
    // рекурсивно вызываем для ребенка соответствующего символа
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    // Если у корня нет дочернего слова
    // (удален только один его дочерний элемент),
    // и он не заканчивается другим словом.
    if (isEmpty(root) && root->isEndOfWord == false) {
        delete (root);
        root = nullptr;
    }
    return root; // возвращаем новый корень
}

void hasPrefix(TrieNode* current, int& countEnds) {
    if (current->isEndOfWord) // если слово закончилось, добавить в счетчик
        countEnds++;
    for (size_t i = 0; i < ALPHABET_SIZE; i++) // зайти в дерево и сосчитать концы слов
        if (current->children[i])
            hasPrefix(current->children[i], countEnds);
}

void findMinPrefixes(TrieNode* root, char buf[], int ind, string& res) {
    if (!root)
        return;
    int count = 0;
    hasPrefix(root, count);
    if (count == 1) {
        buf[ind] = '\0'; // конец строки
        res += std::string(buf) + " "; // добавить к концу результата пробел
        return; // возврат из рекурсии
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        if (root->children[i]) {
            char currentChar = i + 'a';
            buf[ind] = currentChar;
            findMinPrefixes(root->children[i], buf, ind + 1, res);
        }
}

void wordSubstitution(TrieNode* root, string& result, string currentWord) {
    if (!root) // если дерево пустое
        return;
    if (currentWord.empty())// если не с чем сравнивать
        return;
    char buf[50]; // буфер, в которой будем класть символы, подходящие для автоподстановки
    size_t indexChar = 0; // индекс для буфера
    int counterWords = 0; // счётчик слов, которые будут предложены для авттоподстановки
    bool charPresence = true; // проверка наличия символов дерева совпадающих с введённым
    while (indexChar < currentWord.length()) { // ищем совпадения введённой строки с наличием в дереве
        if (!charPresence) // если нет хотя бы одного совпадения 
            return;
        charPresence = false;
        for (int i = 0; i < ALPHABET_SIZE; ++i) { // ищем совпадение в узле
            if (root->children[i]) { // если есть символ в узле
                if (currentWord[indexChar] == i + 'a') { // и если он совпадает с текущим символом введённой строки 
                    buf[indexChar] = i + 'a';  //  в буфер добавляем символ
                    indexChar++; // увеличиваем индекс
                    root = root->children[i]; // переходим в дочерний узел
                    charPresence = true; // соообщаем что символ нашли
                    i = ALPHABET_SIZE;
                    if (root->isEndOfWord && indexChar == currentWord.length()) { // если последний символ введённого слова совпадает с концом слова в словаре
                        buf[indexChar] = '\0'; // закончить строку
                        result += string(buf) + " "; // добавить слово в результат 
                        counterWords++; // увеличить счётчик слов
                    }
                    else if (indexChar == currentWord.length()) { // если просто закончилось введённое слово 
                        buf[indexChar] = '\0'; // закончить строку                  
                        result += string(buf); // добавить слово в результат 
                    }
                }
            }
        }
    }
    if (counterWords == 0) // если слова для автоподставления не найдены
        result.clear(); // очищаем результат
    charPresence = false; // т.к isEndOfWord может быть true, переменная исполнит роль флага окончания строки
    wordSubstitutionInner(root, buf, indexChar, result, counterWords, charPresence); // запускаем алгоритм поиска слов
}

void wordSubstitutionInner(TrieNode* root, char buf[], int indexChar, string& result, int& counterWords, bool endWord) {
    if (endWord) { // если дошли до конца слова
        buf[indexChar] = '\0'; // закончить строку
        result += string(buf) + " "; // добавить к результату
        counterWords++; // увеличить счётчик
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i) { // ищем продолжение слова
        if (root->children[i]) { // если есть следующий символ
            buf[indexChar] = i + 'a';
            endWord = root->children[i]->isEndOfWord;
            wordSubstitutionInner(root->children[i], buf, indexChar + 1, result, counterWords, endWord);
        }
    }
}

TrieNode* loadDictionary(TrieNode* trie, const string& fileName) {
    const unsigned char wordMinLength = 3; // Добавляются только слова длиной больше 3 букв
    string newWord;
    bool wordIsOk;
    ifstream fs(fileName);
    if (fs.is_open()) {
        while (getline(fs, newWord)) { // Цикл по строкам файла
            wordIsOk = newWord.length() > wordMinLength;
            for (unsigned char i = 0; i < newWord.length(); ++i) // Цикл по буквам строки
                if ((newWord[i] < alphabetStart) || (newWord[i] > alphabetEnd)) { // Проверка слова на соответствие алфавиту
                    wordIsOk = false;
                    break;
                }
            if (wordIsOk) {
                insert(trie, newWord);
            }
        }
        fs.close();
    }
    return trie;
}
