#include "Autocomplete.h"

// ¬озвращает новый узел с пустыми детьми
struct TrieNode* getNewNode(void)
{
	// ¬ыдел€ем пам€ть под новый узел
	struct TrieNode* pNode = new TrieNode;
	// устанавливаем флаг конца слова в false
	pNode->isEndOfWord = false;
	// инициализируем детей нулевым указателем
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = nullptr;

	return pNode;
}

// ¬ставл€ет ключ в дерево, если его нет.
// ≈сли ключ €влетс€ префиксом узла дерева, помечает в качестве листового т.е. конец слова
void insert(TrieNode* root, std::string key)
{
	struct TrieNode* node = root;
	for (size_t i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!node->children[index])
			node->children[index] = getNewNode();

		node = node->children[index];
	}

	node->isEndOfWord = true;
}

// ¬озвращает true если корень имеет лист, иначе false 
bool isEmpty(TrieNode* root)
{
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return false;
	return true;
}

// Recursive function to print auto-suggestions for given node.
void autoCompleteRec(TrieNode* currentNode, std::string currPrefix)
{
	// если дошли до конца слова (isEndOfWord = true) - выводим его
	if (currentNode->isEndOfWord)
		std::cout << currPrefix << std::endl;

	for (size_t i = 0; i < ALPHABET_SIZE; i++)
		if (currentNode->children[i]) {
			// значение дочернего узла
			char child = 'a' + i;
			autoCompleteRec(currentNode->children[i], currPrefix + child);
		}
}

int printAutoComplete(TrieNode* root, const std::string& prefix)
{
	struct TrieNode* node = root;

	for (size_t i = 0; i < prefix.length(); i++)
	{
		int index = prefix[i] - 'a';
		// провер€ем, если нет дочернего узла с таким символом, завершаем поиск
		if (!node->children[index]) // в дереве не представлены строки с искомым префиксом
			return -1;
		// присваиваем текущему узлу дочерний узел текущего узла
		node = node->children[index];
	}

	// ≈сли префикс присутствует в виде слова, но под последним соответствующим узлом нет поддерева
	if (isEmpty(node)) 
	{
		std::cout << prefix << std::endl;
		return 0;
	}
	// вызываем рекурсивную функцию автопродолжени€ слова по введенному префиксу
	autoCompleteRec(node, prefix);
	return 1;
}




