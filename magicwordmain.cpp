#include <iostream>
#include <string>
#include "magicprocess.h"

//#include <unistd.h>
//#include <cstdlib>
//#include <cstring>
//#include <vector>
//#include <fstream>
//#include <algorithm>
//#include <queue>
//#include <stack>
//#include <cstdio>

using namespace std;

int main(int argc,char* argv[]){
	string inFile;
    string type;  
    // string dbPath;
    // string outFile;  
    // string sep("\t");
    // int col = -1; 

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
    
    MagicProcess process;
    
    //read a file to process
    process.readFileByStr(inFile);

    //initialize the root node
    Node root(process.getTotalStr(),0);
    
    //sort the vecWord(MagicWords)
    process.sortVecWordDesc();
    
    //find the solution by dfs
    Node maxNode = process.dfsFindMax(root,process.getVecWord());
    
    //print the route of the best node
    process.showAnswer(maxNode);
    
	return 0;
}

