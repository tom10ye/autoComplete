#include<iostream>
#include<malloc.h>
#include <fstream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;


int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");
  words.push_back("harr");
  words.push_back("i am a hero");
  words.push_back("i am a");

  //
  vector<std::string> words2;
  words2.push_back("ha");
  words2.push_back("auto");
  words2.push_back("i am a hero titan");
  words2.push_back("cse is interesting");
  words2.push_back("autocompleted");
  words2.push_back("srira");

  
  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 5);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  
/*You are supposed to add more test cases in this file */
  cout << endl << "Finding elements that were in Dictionaries..." << endl;
  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Finding: \"" << *wit << "\"... ";
      t_bst = d_bst.find(*wit);
      t_ht = d_ht.find(*wit);
      tt = dt.find(*wit);
      if(!t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(!t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(!tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(t_bst && t_ht && tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;
//
  cout << endl << "Finding elements that were not in Dictionaries..." << endl;
  
  wit = words2.begin();
  wen = words2.end();
  for(; wit != wen; ++wit)
    {
      cout << "Finding: \"" << *wit << "\"... ";
      t_bst = d_bst.find(*wit);
      t_ht = d_ht.find(*wit);
      tt = dt.find(*wit);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

// myself test case for autocompletion
	dt.insert("harrymost",100);
	dt.insert("harrythird", 50);
	dt.insert("harry second", 80);
	dt.insert("ha",200);
  // dt.insert("message appears", 25);
  // dt.insert("month or two ago", 16);
  // dt.insert("and wait for them", 42);
	cout << "return the autocompletion result"<<endl;
	std::vector<std::string> res = dt.predictCompletions("ha",3);
	for(unsigned int i =0; i<res.size(); i++){
		cout<<res[i]<<endl;
	}
  cout << endl;


//use the file stream to test the autocompletion
	DictionaryTrie* fileDT = new DictionaryTrie();
	ifstream infile;
  // infile.open("smalldictionary.txt");
	infile.open("shuffled_unique_freq_dict.txt");
	if(infile.is_open()) cout<< "infile open successfully!"<<endl; 
  Utils::load_dict(*fileDT, infile);
	infile.close();
  cout << "insertion completed" <<endl;
  cout << "return the autocompletion result"<<endl;
	/*
	cout<<dict.find("and")<<endl;
	cout<<dict.find("dog")<<endl;
	cout<<dict.find("hel")<<endl;
	cout<<dict.find("g")<<endl;
	cout<<dict.valid_node_count<<endl;
	*/
  // cout<<fileDT->find("a aaa")<<endl;
	std::vector<std::string> word = fileDT->predictCompletions("a", 10);
	for(unsigned int i = 0; i < word.size(); i++)
		cout<<word[i]<<endl;
  
  delete fileDT;
//
  cout<<"All passed!"<<endl;
  return 0;
}
