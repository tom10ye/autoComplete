/*
Author: Cheng Qian
UCSD CSE100 PA2 benchmark different hashfunction
*/


#include<iostream>
#include <fstream>
#include<string>
#include<algorithm>
#include<set>
#include<math.h>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
using namespace std;

class myClass{
public:
	unsigned int hashfunction_java(string s, unsigned int tablesize);
	unsigned int hashfunction_c(string s, unsigned int tablesize);
};

unsigned int myClass::hashfunction_java(string s, unsigned int tablesize){//http://stackoverflow.com/questions/299304/why-does-javas-hashcode-in-string-use-31-as-a-multiplier
	int n = s.size();
	unsigned int res = 0;
	for(int i=0 ; i<n; i++){
		res = res + s[i]*pow(31,(n-i-1));//s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
	}
	return res%tablesize;
}

unsigned int myClass::hashfunction_c(string s, unsigned int tablesize){//http://stackoverflow.com/questions/7666509/hash-function-for-string
	char* str = &s[0];
	unsigned int hash = 5381;
    int c;

    while (*str){
    	c = *str;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        str++;
    }
	return hash%tablesize;
}

int main(int argc, char* argv[]){
	string dictfile = argv[1];
	unsigned int num_words = std::stoi(argv[2]);
	unsigned int tablesize = 2*num_words;
    vector<unsigned int> v1(tablesize,0);
    vector<unsigned int> v2(tablesize,0);
    myClass sol;

    std::ifstream infile;
	infile.open(dictfile);

	string line = "";
	for(unsigned int i = 0; i < num_words; i++){
		getline(infile, line);
		unsigned int idx1 = sol.hashfunction_java(line,tablesize);
		unsigned int idx2 = sol.hashfunction_c(line,tablesize);
		v1[idx1] = v1[idx1] + 1;
		v2[idx2] = v2[idx2] + 1;

	}

	unsigned int max1 = 0;
	unsigned int max2 = 0;
	for(unsigned int i=0; i<tablesize;i++){
		max1 = std::max(max1,v1[i]);
		max2 = std::max(max2,v1[i]);
	}
	// cout<<max1<<" "<<max2<<endl;
	vector<unsigned int> hit_slot1(max1+1,0);
	vector<unsigned int> hit_slot2(max2+1,0);
	// unsigned int hit_slot1[max1+1];
	// unsigned int hit_slot2[max2+1];

	for(unsigned int i=0 ;i<tablesize;i++){
		hit_slot1[v1[i]] = hit_slot1[v1[i]] + 1;
		hit_slot2[v2[i]] = hit_slot2[v2[i]] + 1;
	}

	//average
	unsigned int total1 = 0;
	for(unsigned int i=1; i<hit_slot1.size();i++){
		unsigned int temp1 = 0;
		for(unsigned int j =i; j<hit_slot1.size();j++) temp1 = temp1 + hit_slot1[j];
		total1 = total1 + i*temp1;
	}
	double av1 = total1/double(num_words);

	unsigned int total2 = 0;
	for(unsigned int i=1; i<hit_slot2.size();i++){
		unsigned int temp2 = 0;
		for(unsigned int j =i; j<hit_slot2.size();j++) temp2 = temp2 + hit_slot2[j];
		total2 = total2 + i*temp2;
	}
	double av2 = total2/double(num_words);


	cout<<"Printing the statistics for hashFunction1 with hash table size "<<tablesize<<endl;
	cout<<"#hits\t"<<"#slots receiving the #hits"<<endl;
	for(unsigned int i =0; i<= max1; i++) cout<<i<<"\t"<<hit_slot1[i]<<endl;


	cout<<"The average number of steps for a successful search for hashfunction 1 would be "<<av1<<endl;
	cout<<"The worst case steps that would be needed to find a word is "<<max1<<endl;

	cout<<endl;

	cout<<"Printing the statistics for hashFunction2 with hash table size "<<tablesize<<endl;
	cout<<"#hits\t"<<"slots receiving the #hits"<<endl;
	for(unsigned int i =0; i<= max2; i++) cout<<i<<"\t"<<hit_slot2[i]<<endl;

	cout<<"The average number of steps for a successful search for hashfunction 2 would be "<<av2<<endl;
	cout<<"The worst case steps that would be needed to find a word is "<<max2<<endl;

	// string test_string = "final report";
	// unsigned int test_tablesize = 1000;
	// cout<< "hashfunction 1 "<<sol.hashfunction_java(test_string,test_tablesize) << endl;
	// cout<< "hashfunction 2 " << sol.hashfunction_c(test_string,test_tablesize) << endl;
}

