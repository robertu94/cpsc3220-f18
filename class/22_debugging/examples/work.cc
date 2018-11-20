#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>

auto get_words()
{
	std::vector<std::string> words;
	std::ifstream word_file("/usr/share/dict/words");

	for (std::string line; std::getline(word_file, line);) {
		words.emplace_back(line);
	}

	return words;
}

template <class T>
auto find_anagrams(T begin, T end)
{
	auto hash = [](auto const& word){
		std::vector<int> letters(26);
		std::for_each(std::begin(word), std::end(word),
				[&letters](char c) { letters.at(std::tolower(c)-'a')++; });
		size_t hash_value = 0;

		for (int i = 0; i < 26; ++i) {
			hash_value *= 13;
			hash_value += letters[i];
		}

		return hash_value;
	};

	auto equals = [&hash](auto const& lhs_word, auto const& rhs_word){
		return hash(lhs_word) == hash(rhs_word);
	};

	std::unordered_set<std::string, decltype(hash), decltype(equals)> anagrams(begin, end, 0, hash, equals);

	return anagrams;
}

template <class T>
auto count_first_letters(T begin, T end)
{
	std::unordered_map<char,unsigned int> counts;
	std::for_each(begin, end, [&counts](auto const& item)
			{
				counts[tolower(item.front())]++;
			});
	return counts;
}

template <class T>
void display(T begin, T end)
{
	std::for_each(begin, end, [](auto const& item)
			{
				std::cout << item.first << " " << item.second << std::endl;
			});
}

int main(int argc, char *argv[])
{
	auto words = get_words();
	auto anagrams = find_anagrams(std::begin(words), std::end(words));
	auto anagrams_counts = count_first_letters(std::begin(anagrams), std::end(anagrams));
	display(std::begin(anagrams_counts), std::end(anagrams_counts));
	return 0;
}
