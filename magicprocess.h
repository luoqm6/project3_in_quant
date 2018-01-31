#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

#ifndef MAGICPROCESS_H_
#define MAGICPROCESS_H_

// structure MagicWord --MagicWord contains the magic word substring,
// the value of the substring and the next array of the substring
struct MagicWord{

	string subStr;
	int value;
	int len;
	vector<int> next;//the next array of the substring used for KMP

	MagicWord(){
		subStr = "";
		value = 0;
		len = 0;
	}

	MagicWord(string w,int v){
		subStr = w;
		value = v;
		len = w.size();
	}

	bool operator < (const MagicWord& right) const {  
	  return value < right.value;  
	}//asscend

	bool operator > (const MagicWord& right) const {  
	  return value > right.value;  
	}//desscend

};

// structure OutWord --OutWord contains the matched magicword substring(the previous removed word)
// and the first index matched in total string
struct OutWord{
	string outWord;
	int outPlace;
	OutWord(){
		outPlace = -1;
		outWord = "none";
	}
	OutWord(string w,int p){
		outWord = w;
		outPlace = p;
	}
};

// structure Node -- the Node is to save some infomation of the tree doing dfs
// It contains the current string (removed some magicwords), the value of the current node
// and the previous removed word and it's index matched in total string
struct Node{
	string nodeStr;
	vector<OutWord> vecOut;
	int nodeValue;
	Node(){
		nodeStr = "";
		nodeValue = 0;
	}
	Node(string s, vector<OutWord> v, int total = 0){
		nodeStr = s;
		vecOut = v;
		nodeValue = total;
	}
	Node(string s, int total = 0){
		nodeStr = s;
		nodeValue = total;
	}
};

// MagicProcess --  maintain the whole process finding the magic word
// including read file, sort, find solution by dfs, print answer
class MagicProcess{
	
	private:
		int n;	// the length of string
		int k;	// the total number of magicwords
		string totalStr;	//the total string to find the magicwords
		vector<MagicWord> vecWord;	// the vector cotains all the magicwords
	
	public:
		
		// Summary: constructed function, initialize some private variable
		MagicProcess();
		
		// Summary: destructor of the class MagicProcess.
		~MagicProcess();
		
		// Summary: calculate the next[]
		// Parameters:
		//      str:point to the string want to calculate next[].*    
		//      next : the int next array to calculate.
		//		len: the size of the string.
		// Return : none.
		void calNext(const char *str, int *next, int len);
		
		// Summary: match the substring by KMP
		// Parameters:
		//      str:the father string to match. 
		//      subStr : the subStr to match.
		//		next: the next array of the subStr.
		// Return : the first index of the matched substring(-1 if unmatched).
		int KMP(string str,string subStr, vector<int> next);
		
		// Summary: match the substring, remove it and add the value
		// Parameters:
		//      totalStr:the reference of the father string to match, may change when return. 
		//      mw : the class contain the subStr, next array of the subStr.
		//		totalValue: the reference of the current value.
		// Return : the first index of the matched substring(-1 if unmatched).
		int removeSubStr(string &totalStr,MagicWord mw, int &totalValue);
		
		// Summary: find the best solution by dfs
		// Parameters:
		//      root:the root Node contains the initial string and value. 
		//      vecWord : the vector contains all the MagicWord.
		// Return : the Node with the max value.
		Node dfsFindMax(Node root,vector<MagicWord> vecWord);
		
		// Summary: read the file
		// Parameters:
		//      inFile:the path string of the file. 
		// Return : none.
		void readFileByStr(string inFile);
		
		// Summary: show the route and value of the Node
		// Parameters:
		//      maxNode:the best node. 
		// Return : none.
		void showAnswer(Node maxNode);
		
		// Summary: sort the word vector by the value of the magic word
		// Parameters:
		//     none. 
		// Return : none.
		void sortVecWordDesc();
		
		// Summary: get the vector contains MagicWords
		// Parameters:
		//     none. 
		// Return : the vector contains MagicWords.
		vector<MagicWord> getVecWord();
		
		// Summary: get the total string
		// Parameters:
		//     none. 
		// Return : the total string.
		string getTotalStr();
		
		
};
#endif /* MAGICPROCESS_H_ */ 
