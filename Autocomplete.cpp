#include "Autocomplete.h"

// ���������� ����� ���� � ������� ������
struct TrieNode* getNewNode(void)
{
	// �������� ������ ��� ����� ����
	struct TrieNode* pNode = new TrieNode;
	// ������������� ���� ����� ����� � false
	pNode->isEndOfWord = false;
	// �������������� ����� ������� ����������
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = nullptr;

	return pNode;
}

// ��������� ���� � ������, ���� ��� ���.
// ���� ���� ������� ��������� ���� ������, �������� � �������� ��������� �.�. ����� �����
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

// ���������� true ���� ������ ����� ����, ����� false 
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
	// ���� ����� �� ����� ����� (isEndOfWord = true) - ������� ���
	if (currentNode->isEndOfWord)
		std::cout << currPrefix << std::endl;

	for (size_t i = 0; i < ALPHABET_SIZE; i++)
		if (currentNode->children[i]) {
			// �������� ��������� ����
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
		// ���������, ���� ��� ��������� ���� � ����� ��������, ��������� �����
		if (!node->children[index]) // � ������ �� ������������ ������ � ������� ���������
			return -1;
		// ����������� �������� ���� �������� ���� �������� ����
		node = node->children[index];
	}

	// ���� ������� ������������ � ���� �����, �� ��� ��������� ��������������� ����� ��� ���������
	if (isEmpty(node)) 
	{
		std::cout << prefix << std::endl;
		return 0;
	}
	// �������� ����������� ������� ��������������� ����� �� ���������� ��������
	autoCompleteRec(node, prefix);
	return 1;
}




