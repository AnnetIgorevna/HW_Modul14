#pragma once

#include <iostream>
#include <vector>

constexpr auto ALPHABET_SIZE = (26);

// ��������� ���� ������
struct TrieNode
{
	struct TrieNode* children[ALPHABET_SIZE];
	bool isEndOfWord; 	// isEndOfWord - true, ���� ���� �������� ������ �����
};

struct TrieNode* getNewNode(void);
void insert(TrieNode* root, std::string key);
bool isEmpty(TrieNode* root);
void autoCompleteRec(TrieNode* root, std::string currPrefix);
int printAutoComplete(TrieNode* root, const std::string& prefix);
