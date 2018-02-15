#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
	return us.insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
	//std::unordered_set<std::string>::iterator it;
        //it=;    
        if(us.find(word)!=us.end())    
            return true;
        else            
            return false;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
