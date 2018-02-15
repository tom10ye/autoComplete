#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){
	
}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
	return s.insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
	std::set<std::string>::iterator it;
        it=s.find(word);    
        if(it!=s.end())    
            return true;
        else            
            return false;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
