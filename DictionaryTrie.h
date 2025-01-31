/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */
#include<malloc.h>
#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */

class TrieNode{
public:
	TrieNode();

	~TrieNode();

//private:
	unsigned int frequency;
	//std::vector<TrieNode*> next(27,NULL);// the space is also a char, whose ascii code is 32
  TrieNode* next[27];
	bool end;
};


class TrieNodeComparator{
public:
	bool operator()(std::pair<TrieNode*, std::string>& A, std::pair<TrieNode*, std::string>& B) const {
        return A.first->frequency > B.first->frequency;
    }
};

class DictionaryTrie{
public:

  /* Create a new Dictionary that uses a Trie back end */

  // DictionaryTrie():root(nullptr){};
     DictionaryTrie();
  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();
  void deleteAll(TrieNode* root);
private:
  // Add your own data members and methods here
	TrieNode* root;
};

#endif // DICTIONARY_TRIE_H


//class TrieNode;

