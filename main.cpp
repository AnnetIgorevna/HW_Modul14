#include "Autocomplete.h"


int main()
{
	struct TrieNode* root = getNewNode();

	// Создаем базовый словарь
	std::vector<std::string> words = 
	{	"sky", "skill", "skillfactory", 
		"hell", "hello", "help", "helping", 
		"box", "boy", "boyfriend", 
		"mom", "mommy", "mother" };

	// Заполняем дерево
	for (auto &w : words)
		insert(root, w);

	bool exit = false;
	char operation;
	int res;
	std::string prefix;
	std::string addToDictionary;

	std::cout << "\n***** Welcome! *****\n" << std::endl;

	while (!exit)
	{
		bool isValid = true;
		std::cout << "\nSelect an operation:\n" <<
			"1 - Enter the beginning of the word for autocomplete\n" <<
			"2 - Add a word to the dictionary\n" <<
			"3 - Exit" << std::endl;
		std::cin >> operation;
		switch (operation)
		{
		case '1':
			std::cout << "\nEnter prefix (lowercase characters a-z): " << std::endl;
			std::cin >> prefix;
			for (size_t i = 0; i < prefix.length(); i++)
			{
				if (prefix[i] < 'a' || prefix[i] > 'z')
				{
					std::cout << "Incorrect prefix. You must enter the lowercase characters (a-z)\n";
					isValid = false;
					break;
				}
			}
			if (isValid)
			{
				std::cout << "\nAutocomplete words: " << std::endl;
				res = printAutoComplete(root, prefix);

				if (res == 0)
					std::cout << "No other words found with this prefix\n";
				else if (res == -1)
					std::cout << "No words found with this prefix\n";
			}
			break;
		case '2':
			std::cout << "\nAdd word: " << std::endl;
			std::cin >> addToDictionary;
			for (size_t i = 0; i < addToDictionary.length(); i++)
			{
				if (addToDictionary[i] < 'a' || addToDictionary[i] > 'z')
				{
					std::cout << "Incorrect word. You must enter the lowercase characters (a-z)\n";
					isValid = false;
					break;
				}
			}
			if (isValid)
			{
				insert(root, addToDictionary);
			}
			break;
		case '3':
			exit = true;
			break;
		default:
			std::cout << "\nIncorrect operation code! Try again." << std::endl;
			break;
		}
	}
	return 0;
}
