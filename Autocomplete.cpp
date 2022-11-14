#include "Autocomplete.h"

// Âîçâðàùàåò íîâûé óçåë ñ ïóñòûìè äåòüìè
struct TrieNode* getNewNode(void)
{
	// Âûäåëÿåì ïàìÿòü ïîä íîâûé óçåë
	struct TrieNode* pNode = new TrieNode;
	// óñòàíàâëèâàåì ôëàã êîíöà ñëîâà â false
	pNode->isEndOfWord = false;
	// èíèöèàëèçèðóåì äåòåé íóëåâûì óêàçàòåëåì
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = nullptr;

	return pNode;
}

// Âñòàâëÿåò êëþ÷ â äåðåâî, åñëè åãî íåò.
// Åñëè êëþ÷ ÿâëåòñÿ ïðåôèêñîì óçëà äåðåâà, ïîìå÷àåò â êà÷åñòâå ëèñòîâîãî ò.å. êîíåö ñëîâà
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

// Âîçâðàùàåò true åñëè êîðåíü èìååò ëèñò, èíà÷å false 
bool isEmpty(TrieNode* root)
{
	for (size_t i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return false;
	return true;
}

void autoCompleteRec(TrieNode* currentNode, std::string currPrefix)
{
	// åñëè äîøëè äî êîíöà ñëîâà (isEndOfWord = true) - âûâîäèì åãî
	if (currentNode->isEndOfWord)
		std::cout << currPrefix << std::endl;

	for (size_t i = 0; i < ALPHABET_SIZE; i++)
		if (currentNode->children[i]) {
			// çíà÷åíèå äî÷åðíåãî óçëà
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
		// ïðîâåðÿåì, åñëè íåò äî÷åðíåãî óçëà ñ òàêèì ñèìâîëîì, çàâåðøàåì ïîèñê
		if (!node->children[index]) // â äåðåâå íå ïðåäñòàâëåíû ñòðîêè ñ èñêîìûì ïðåôèêñîì
			return -1;
		// ïðèñâàèâàåì òåêóùåìó óçëó äî÷åðíèé óçåë òåêóùåãî óçëà
		node = node->children[index];
	}

	// Åñëè ïðåôèêñ ïðèñóòñòâóåò â âèäå ñëîâà, íî ïîä ïîñëåäíèì ñîîòâåòñòâóþùèì óçëîì íåò ïîääåðåâà
	if (isEmpty(node)) 
	{
		std::cout << prefix << std::endl;
		return 0;
	}
	// âûçûâàåì ðåêóðñèâíóþ ôóíêöèþ àâòîïðîäîëæåíèÿ ñëîâà ïî ââåäåííîìó ïðåôèêñó
	autoCompleteRec(node, prefix);
	return 1;
}




