#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <cstdio>
#include "magic2_1_n.cpp"
using namespace std;


int main(int argc,char* argv[]){
	string inFile;
    string type;  
    // string dbPath;
    string outFile;  
    // string sep("\t");
    // int col = -1; 

    //inFile = argv[1];

    //outFile = argv[2];

    //cout<<"inFlie = |"<<inFile<<"| outFile = |"<<outFile<<"|"<<endl;

    // //get the argv from command line
    // while ((ch = getopt(argc, argv, "d:i:o:s:c:")) != -1) {  
    //     switch (ch) {
    //     	case 'i': 
				// inFile = string(optarg); 
				// //cout<<"-i is :"<<inFile<<endl;
				// break;  
    // //         case 'd': 
				// // dbPath = string(optarg); 
				// // //cout<<"-d is :"<<dbPath<<endl;
				// // break;  
            
    //          case 'o':
				//  outFile = string(optarg);
				//  //cout<<"-o is :"<<outFile<<endl;
				//  break;  
    // //         case 's': 
				// // sep = string(optarg); 
				// // //cout<<"-s is :"<<sep<<endl;
				// // break;  
    // //         case 'c': 
				// // col = atoi(optarg); 
				// // //cout<<"-c is :"<<col<<endl;
				// // break;  
    //     }
    // }
    
    MagicProcess process;
    
    //read a file to process
    process.readFileByStr(inFile);

    //initialize the root node
    Node root(process.getTotalStr(),0,0,0);
    
    // //sort the vecWord(MagicWords)
    process.sortVecWordDesc();
    
    //find the solution by dfs
	Node maxNode = process.dfsFindMax(root,process.getVecWord());
    
	//sort the vecWord(MagicWords)
   	//process.sortVecWordAsc();
   
   	//find the solution by bfs
	//Node maxNode = process.bfsFindMax(root,process.getVecWord());
   
   	// //find the solution by dfs
	//Node maxNode = process.dfsFindMax2(root,process.getVecWord());
    
    //print the route of the best node
    process.showAnswer(maxNode);
    
    //output to file
    process.outputFile(maxNode,outFile);
    
	return 0;
}

