/*
Author: Cheng Qian
UCSD CSE100 PA2
*/
#include<malloc.h>
#include "util.h"
#include "DictionaryTrie.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include<string>
#include<stdlib.h>
using namespace std;  

/* Create a new Dictionary that uses a Trie back end */

DictionaryTrie::DictionaryTrie(){
	root = new TrieNode();
}


/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */

TrieNode::TrieNode(){
	frequency = 0;
	end = false;
	for(int i =0; i<27;i++) next[i] = NULL;
	// next(27,NULL);
}

TrieNode::~TrieNode(){}

bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
	if(!root){
		root = new TrieNode();
	}
	TrieNode* node = root;
	bool success;
	char *p = &word[0];//new a pointer to point to the first character of word
	int idx = 0;
	while( *p){
		idx = *p - 'a';
		if(idx == -65) idx = 26; // if p is space, then give the last index to it
		// cout << "inserting letter " << *p << endl;
		// if(node == NULL) {cout<<"node is nullptr"<<endl;} else{cout<<"node is not nullptr"<<endl;}
		if(node->next[idx] == NULL){
			//TrieNode* newNode = new TrieNode();
			//TrieNode newNode; 
			//node->next[idx] = &newNode;
			node->next[idx] = new TrieNode();
			success = true;
		}else{
			success = false;
		}
		node = node->next[idx];
		++p;
	}
	// if(node == NULL) {cout<<"after insert the word, node is nullptr"<<endl;} else{cout<<"after insert the word, node is not nullptr"<<endl;}
	node->frequency = std::max(freq, node->frequency);//update the frequency to be the max value between old one and new one
	if(node->end == false) success = true;// to deal with the harry(harr) bug. If we insert harry first, then insert harr should be true.
	node->end = true;
	return success;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
	TrieNode* node = this->root;
	// cout<<word<<endl;
	char *p = &word[0];
	int idx = 0;

	while( *p ){
		idx = *p - 'a';
		if(idx == -65) idx = 26; // if p is space, then give the last index to it
		//cout<<"idx is "<<idx<<endl;
		//if(node == NULL) {cout<<"node is nullptr"<<endl;} else{cout<<"node is not nullptr"<<endl;}
		node = node->next[idx];
		//cout<<"it is here"<<endl;
		++p;
		if(node == NULL) return false;
	}
	if (node->end == false) return false;
	return true;
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
	std::vector<std::string> words;
	if(root == NULL) return words;
	if((prefix == "") || (num_completions <=0)){
		cout<< "Invalid Input. Do not input null prefix or zero number. Please retry with correct input."<<endl;
		return words;
	}
	
	char *p = &prefix[0];
	int idx = 0;
	
	while(*p){
		idx = *p - 'a';
		// cout<<idx<<endl;
		if((idx == -65) || (idx>=0 && idx<=25)){
			++p;
			continue;
		}else{
			cout<< "Invalid Input. Please retry with correct input."<<endl;
			return words;
		}
		 
	}
	
	
	
	p = &prefix[0];
	TrieNode* node = this->root;
	while(*p){
		idx = *p -'a';
		if(idx == -65) idx = 26; // if p is space, then give the last index to it
		node = node->next[idx];
		++p;
		if(node == NULL) return words;		
	}
	//priority_queue<Type, Container, Functional>
	std::priority_queue<std::pair<TrieNode*, std::string>, std::vector<std::pair<TrieNode*, std::string>>, TrieNodeComparator> PQ;// use for track the most frequent word

	std::queue<std::pair<TrieNode*,std::string>> Q;//use for BFS traversal

	std::pair<TrieNode*, std::string> currPair(node,""); 	

	Q.push(currPair);
	while(!Q.empty()){
		currPair = Q.front();
		Q.pop();
		if(currPair.first->end == true){
			PQ.push(currPair);
			if(PQ.size() > num_completions) PQ.pop();
		}
		for(int i = 0; i<27; i++){
			if(currPair.first->next[i] != NULL){
				char addOnLetter;
				if(i == 26){
					addOnLetter = ' ';
				}else{
					addOnLetter = i + 97;
				}
				std::string addOnWord = currPair.second + addOnLetter;
				std::pair<TrieNode*, std::string> nextPair(currPair.first->next[i], addOnWord);		
				Q.push(nextPair);
			}
		}
	}

	while(!PQ.empty()){
		std::string newWord = prefix + PQ.top().second;
		words.push_back(newWord);
		PQ.pop();		
	}
	reverse(words.begin(), words.end());
	return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
	deleteAll(root);
}

void DictionaryTrie::deleteAll(TrieNode* root){
	if(root == NULL) return;
	for(unsigned int i = 0; i < 27; i++){
		deleteAll(root->next[i]);
	}
	delete root;
}
