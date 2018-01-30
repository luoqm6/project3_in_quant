#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>

using namespace std;

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

    ifstream inputFile("in");
    
    string inputStr;


    int n,k;
    string s;

    inputFile>>n>>k>>s;
    cout<<n<<endl;
    cout<<k<<endl;
    cout<<s<<endl;
    
    vector<string> vecWord;
    vector<double> vecValue;

    for(int i=0;i<k;i++){
    	string tmps;
    	double tmpd;
    	inputFile>>tmps>>tmpd;
    	vecWord.push_back(tmps);
    	vecValue.push_back(tmpd);
    	//cout<<"word:"<<tmps<<" "<<tmpd<<endl;
    }

    


	return 0;
}

