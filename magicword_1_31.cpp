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

struct MagicWord{
	string subStr;
	int value;
	int len;
	vector<int> next;

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

struct Output{
	string outWord;
	int outPlace;
	Output(){
		outPlace = -1;
		outWord = "none";
	}
	Output(string w,int p){
		outWord = w;
		outPlace = p;
	}
};

struct Node{
	string nodeStr;
	vector<Output> vecOut;
	int nodeValue;
	Node(){
		nodeStr = "";
		nodeValue = 0;
	}
	Node(string s, vector<Output> v, int total = 0){
		nodeStr = s;
		vecOut = v;
		nodeValue = total;
	}
	Node(string s, int total = 0){
		nodeStr = s;
		nodeValue = total;
	}
};

void calNext(const char *str, int *next,int len){

	next[0] = -1;
	int k = -1;
	for (int q=1;q<=len -1 ;q++){
		while(k > -1 && str[k + 1]!= str[q]){
			k = next[k];
		}
		if(str[k+1]==str[q]){
			k = k+1;
		}
		next[q] = k;
	}
}

int KMP(string str,MagicWord mw){
	int slen = str.size();
	string ptr = mw.subStr;
	int plen = mw.len;
	int k = -1;
	for(int i=0;i<slen;i++){
		while(k>-1 && ptr[k+1]!=str[i]){
			k = mw.next[k];
		}

		if(ptr [k + 1] == str[i]){
			k = k + 1;
		}
		if(k == plen-1){
			return i-plen+1;
		}
	}
	return -1;
}

int removeSubStr(string &s,MagicWord mw, int &totalValue){
	//remove the substring
	string tmps = s;
	int start = KMP(tmps,mw);
	//cout<<"KMP = "<<start<<endl;
	if(start != -1){
		s = s.substr(0,start)+s.substr(start+mw.len,s.size());
		totalValue += mw.value;
	}
	return start;
}

Node dfsFindMax(Node root,vector<MagicWord> vecWord){
	//init the solution maxNode
    Node maxNode = root;

    //cout<<"s now = "<<root.str<<endl;
    //queue<Node> qNode;
    stack<Node> stNode;
    stNode.push(root);
    while(!stNode.empty()){
    	Node tmpN;
    	tmpN = stNode.top();
    	stNode.pop();

    	//update the solution
    	if(tmpN.nodeValue > maxNode.nodeValue){
    		maxNode = tmpN;
    	}

    	for(int i = 0;i < vecWord.size();i++){

	    	//cout<<"substr["<<i<<"] = "<<vecWord[i].subStr<<" len = "<<vecWord[i].len<<endl;
	    	// for (int j=0;j<tmpWord[i].next.size();j++){
	    	// 	cout<<"next["<<j<<"] = "<<tmpWord[i].next[j]<<endl;
	    	// }

	    	string nodeStr = tmpN.nodeStr;
	    	int nodeValue = tmpN.nodeValue;
	    	vector<Output> vecOut = tmpN.vecOut;

	    	int outPlace = removeSubStr(nodeStr,vecWord[i],nodeValue);
	    	if( outPlace != -1){
	    		//find a new neighbor node and put it into stack
	    		Output output(vecWord[i].subStr,outPlace);
	    		vecOut.push_back(output);
	    		Node nghbr(nodeStr,vecOut,nodeValue);
	    		// cout<<"the str now = "<<nghbr.nodeStr<<" value = "<<nghbr.nodeValue<<endl;
	    		// for(int i = 0; i < nghbr.vecOut.size();i++){
			    // 	cout<<"out = "<<nghbr.vecOut[i].outWord<<" "<<nghbr.vecOut[i].outPlace<<endl;
			    // }
	    		stNode.push(nghbr);
	    	}
	    	
	    }
	    // while(!stNode.empty()){
	    // 	Node tmpN;
	    // 	tmpN = stNode.top();
	    // 	stNode.pop();
	    // 	cout<<"nodeStr now = "<<tmpN.nodeStr<<" nodeValue now = "<<tmpN.nodeValue<<endl;
	    // }
    }
    return maxNode;
}

void showAnswer(Node maxNode){
	// for(int i = 0; i < maxNode.vecOut.size();i++){
	// 	cout<<"out = "<<maxNode.vecOut[i].outPlace<<" "<<maxNode.vecOut[i].outWord<<endl;
	// }
	// cout<<"current string is: "<<maxNode.nodeStr<<" the value is: "<<maxNode.nodeValue<<endl;
	for(int i = 0; i < maxNode.vecOut.size();i++){
		cout<<maxNode.vecOut[i].outPlace<<" "<<maxNode.vecOut[i].outWord<<endl;
	}
	cout<<maxNode.nodeValue<<endl;
}

class Process{
	public:
		int n,k;
		string s;

		Process(){

		}
};

int main(int argc,char* argv[]){
    string type;  
    string dbPath;  
    string inFile;  
    string outFile;  
    string sep("\t");  
    int col = -1; 

    if(argc > 1){
        type = string(argv[1]);  
    }  
    int ch;  
    opterr = 0; 

    //get the argv from command line
    while ((ch = getopt(argc, argv, "d:i:o:s:c:")) != -1) {  
        switch (ch) {
        	case 'i': 
				inFile = string(optarg); 
				//cout<<"-i is :"<<inFile<<endl;
				break;  
    //         case 'd': 
				// dbPath = string(optarg); 
				// //cout<<"-d is :"<<dbPath<<endl;
				// break;  
            
    //         case 'o':
				// outFile = string(optarg);
				// //cout<<"-o is :"<<outFile<<endl;
				// break;  
    //         case 's': 
				// sep = string(optarg); 
				// //cout<<"-s is :"<<sep<<endl;
				// break;  
    //         case 'c': 
				// col = atoi(optarg); 
				// //cout<<"-c is :"<<col<<endl;
				// break;  
        }
    }

    if(inFile.empty()){
    	inFile = "in";
    }

    ifstream inputFile(inFile.c_str());
    
    string inputStr;


    int n,k;
    string s;

    inputFile>>n>>k>>s;
    // cout<<n<<endl;
    // cout<<k<<endl;
    // cout<<s<<endl;
    
    vector<MagicWord> vecWord;

    for(int i=0;i<k;i++){
    	string tmps;
    	double tmpd;

    	inputFile>>tmps>>tmpd;
    	MagicWord mw(tmps,tmpd);
    	
    	//calculate the next array
    	int *nxt = new int [mw.len];
    	calNext(mw.subStr.c_str(),nxt,mw.subStr.size());
    	for(int j = 0;j<mw.len;j++){
    		//cout<<"nxt["<<i<<"] = "<<nxt[i]<<endl;
    		mw.next.push_back(nxt[j]);
    	}

    	//push to the vector
    	vecWord.push_back(mw);
    }

    sort(vecWord.begin(), vecWord.end(),less<MagicWord>());



    //init the root node
    Node root(s,0);
    Node maxNode = dfsFindMax(root,vecWord);
    showAnswer(maxNode);
    
	return 0;
}

