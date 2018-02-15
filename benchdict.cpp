/*
Author: Cheng Qian
UCSD CSE100 PA2 benchmark different datastructure
*/


#include<iostream>
#include <fstream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
using namespace std;


int main(int argc, char* argv[]){ //argc is the number of input, argv is the array of input(need from argv[1])	
    	
	int min_size = std::stoi(argv[1]); // convert from string to integer
    int step_size = std::stoi(argv[2]);
	int num_iterations = std::stoi(argv[3]);
    std::string dictfile = argv[4];

	int times = 2000;
	
	
	std::cout<<"BST is benchmarking"<<std::endl;
	for(int i=0; i<num_iterations; i++){
		//int times = 5;		
		
		
		DictionaryBST d_bst;
		std::ifstream infile;
		infile.open(dictfile);
		Utils::load_dict(d_bst,infile,min_size + i * step_size);

		vector<string> the100phrase; //initialize a vector to store the 100 phrases to find

		string line = "";
		for (unsigned int i = 0; i < 100; i++){
			getline(infile, line);
			//cout <<"get the line complete"<<endl;
			if (infile.eof()) {
			    std::cout << "Warning!  Only " << i << " words read from file." << endl;
			    break;
			}

			//erase frequency
			int count = 0;
		    string::iterator last = line.end();
		    for (string::iterator it = line.begin(); it != last; ++it) {
		        count++;
		        if (*it == ' ') {
		            break;
		        }
		    }
		    //unsigned int freq = std::stoi(line.substr(0, count));
		    line.erase(0, count);
		    the100phrase.push_back(line);
			//cout <<"find line operation complete"<<endl;
		}
			//cout<<"load complete"<<endl;
		long total = 0;
		for(int j=0; j<times; j++){
			Timer T;
			long time_duration;
			T.begin_timer();
			//cout <<"Timer begin"<<endl;
			vector<string>::iterator vit = the100phrase.begin();
			vector<string>::iterator ven = the100phrase.end();
			for(; vit != ven; ++vit) d_bst.find(*vit);
			time_duration = T.end_timer();
			total = total + time_duration;
		}
		long average_time = total/times;
		cout<< min_size + i * step_size << "\t" << average_time <<endl;
	}

	std::cout<<"HashTable is benchmarking"<<std::endl;
	for(int i=0; i<num_iterations; i++){
		//int times = 5;		
		long total = 0;
		
		DictionaryHashtable d_ht;
		std::ifstream infile;
		infile.open(dictfile);
		Utils::load_dict(d_ht,infile,min_size + i * step_size);

		vector<string> the100phrase; //initialize a vector to store the 100 phrases to find

		string line = "";
		for (unsigned int i = 0; i < 100; i++){
			getline(infile, line);
			//cout <<"get the line complete"<<endl;
			if (infile.eof()) {
			    std::cout << "Warning!  Only " << i << " words read from file." << endl;
			    break;
			}

			//erase frequency
			int count = 0;
		    string::iterator last = line.end();
		    for (string::iterator it = line.begin(); it != last; ++it) {
		        count++;
		        if (*it == ' ') {
		            break;
		        }
		    }
		    //unsigned int freq = std::stoi(line.substr(0, count));
		    line.erase(0, count);
		    the100phrase.push_back(line);
			//cout <<"find line operation complete"<<endl;
		}
			//cout<<"load complete"<<endl;
		for(int j=0; j<times; j++){
			Timer T;
			long time_duration;
			T.begin_timer();
			//cout <<"Timer begin"<<endl;
			vector<string>::iterator vit = the100phrase.begin();
			vector<string>::iterator ven = the100phrase.end();
			for(; vit != ven; ++vit) d_ht.find(*vit);
			time_duration = T.end_timer();
			total = total + time_duration;
		}
		long average_time = total/times;
		cout<< min_size + i * step_size << "\t" << average_time <<endl;
	}

	std::cout<<"MWT is benchmarking"<<std::endl;
	for(int i=0; i<num_iterations; i++){
		//int times = 5;		
		long total = 0;
		
		DictionaryTrie d_t;
		std::ifstream infile;
		infile.open(dictfile);
		Utils::load_dict(d_t,infile,min_size + i * step_size);

		vector<string> the100phrase; //initialize a vector to store the 100 phrases to find

		string line = "";
		for (unsigned int i = 0; i < 100; i++){
			getline(infile, line);
			//cout <<"get the line complete"<<endl;
			if (infile.eof()) {
			    std::cout << "Warning!  Only " << i << " words read from file." << endl;
			    break;
			}

			//erase frequency
			int count = 0;
		    string::iterator last = line.end();
		    for (string::iterator it = line.begin(); it != last; ++it) {
		        count++;
		        if (*it == ' ') {
		            break;
		        }
		    }
		    //unsigned int freq = std::stoi(line.substr(0, count));
		    line.erase(0, count);
		    the100phrase.push_back(line);
			//cout <<"find line operation complete"<<endl;
		}
			//cout<<"load complete"<<endl;
		for(int j=0; j<times; j++){
			Timer T;
			long time_duration;
			T.begin_timer();
			//cout <<"Timer begin"<<endl;
			vector<string>::iterator vit = the100phrase.begin();
			vector<string>::iterator ven = the100phrase.end();
			for(; vit != ven; ++vit) d_t.find(*vit);
			time_duration = T.end_timer();
			total = total + time_duration;
		}
		long average_time = total/times;
		cout<< min_size + i * step_size << "\t" << average_time <<endl;
	}
}
