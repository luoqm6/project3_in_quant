#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct MagicWord{
	string word;
	int value;
	int len;
	int *next;
	MagicWord(){
		word = "";
		value = 0;
		len = 0;
		next = NULL;
	}
	MagicWord(string w,int v){
		word = w;
		value = v;
		len = w.size();
		next = NULL;
	}
	~MagicWord(){
		word = "";
		value = 0;
		delete [] next;
	}
	bool operator < (const MagicWord& right) const {  
	  return value < right.value;  
	}//asscend

	bool operator > (const MagicWord& right) const {  
	  return value > right.value;  
	}//desscend

};

void cal_next(const char *str, int *next,int len){
	
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

int KMP(const char *str, int slen,const char *ptr, int plen, int *next){
	
	int k = -1;

	for(int i=0;i<slen;i++){
		while(k>-1 && ptr[k+1]!=str[i]){
			k = next[k];
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
    while ((ch = getopt(argc, argv, "d:i:o:s:c:")) != -1) {  
        switch (ch) {  
            case 'd': 
				dbPath = string(optarg); 
				cout<<"-d is :"<<dbPath<<endl;
				break;  
            case 'i': 
				inFile = string(optarg); 
				cout<<"-i is :"<<inFile<<endl;
				break;  
            case 'o':
				outFile = string(optarg);
				cout<<"-o is :"<<outFile<<endl;
				break;  
            case 's': 
				sep = string(optarg); 
				cout<<"-s is :"<<sep<<endl;
				break;  
            case 'c': 
				col = atoi(optarg); 
				cout<<"-c is :"<<col<<endl;
				break;  
        }
    }

    string str = "in";

    ifstream inputFile(str.c_str());
    
    string inputStr;


    int n,k;
    string s;

    inputFile>>n>>k>>s;
    cout<<n<<endl;
    cout<<k<<endl;
    cout<<s<<endl;
    
    vector<MagicWord> vecWord;

    for(int i=0;i<k;i++){
    	string tmps;
    	double tmpd;
    	inputFile>>tmps>>tmpd;
    	MagicWord mw(tmps,tmpd);
    	vecWord.push_back(mw);
    	cout<<"word:"<<mw.word<<" "<<mw.value<<endl;
    }

    sort(vecWord.begin(), vecWord.end(),greater<MagicWord>());

    for(int i=0;i<k;i++){
    	MagicWord mw;
    	mw = vecWord[i];
    	int *next = new int [mw.len];
    	cal_next(mw.word.c_str(),next,mw.word.size());
    	mw.next = next;
    	// for(int i=0;i<mw.len;i++){
    	// 	cout<<"next["<<i<<"] = "<<mw.next[i]<<endl;
    	// }
    	cout<<"word:"<<mw.word<<" "<<mw.value<<" len = "<<mw.len<<endl;
    	//cout<<"KMP = "<<KMP(s.c_str(),s.size(),mw.word.c_str(),mw.len,mw.next)<<endl;
    }



	return 0;
}

