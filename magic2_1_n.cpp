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

using namespace std;

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
	int nodeLevel;
	bool nodeVis;
	
	
	Node(){
		nodeStr = "";
		nodeValue = 0;
		nodeVis = 0;
		nodeLevel = 0;
	}
	Node(string s, vector<OutWord> v, int total = 0, int level = 0, bool vis = 0){
		nodeStr = s;
		vecOut = v;
		nodeValue = total;
		nodeVis = vis;
		nodeLevel = level;
	}
	Node(string s, int total = 0, int level = 0, bool vis = 0){
		nodeStr = s;
		nodeValue = total;
		nodeVis = vis;
		nodeLevel = level;
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
		vector<Node> vecNodes;
	
	public:
		
		// Summary: constructed function, initialize some private variable
		MagicProcess(){
			n = 0;
			k = 0;
			totalStr = "";
		}
		
		// Summary: destructor of the class MagicProcess.
		~MagicProcess(){
		}
		
		// Summary: calculate the next[]
		// Parameters:
		//      str:point to the string want to calculate next[].*    
		//      next : the int next array to calculate.
		//		len: the size of the string.
		// Return : none.
		void calNext(const char *str, int *next, int len){
			// initialize next[0]
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
		
		// Summary: match the substring by KMP
		// Parameters:
		//      str:the father string to match. 
		//      subStr : the subStr to match.
		//		next: the next array of the subStr.
		// Return : the first index of the matched substring(-1 if unmatched).
		int KMP(string str,string subStr, vector<int> next){
			int sLen = str.size();
			int subLen = subStr.size();
			int k = -1;
			if(sLen < subLen) return -1;
			for(int i=0;i<sLen;i++){
		
				// unmatched and move to next[k]
				while(k>-1 && subStr[k+1]!=str[i]){
					k = next[k];
				}
				// matched a char and move
				if(subStr [k + 1] == str[i]){
					k = k + 1;
				}
				// matched all
				if(k == subLen-1){
					return i-subLen+1;
				}
			}
			return -1;
		}
		
		// Summary: match the substring, remove it and add the value
		// Parameters:
		//      totalStr:the reference of the father string to match, may change when return. 
		//      mw : the class contain the subStr, next array of the subStr.
		//		totalValue: the reference of the current value.
		// Return : the first index of the matched substring(-1 if unmatched).
		int removeSubStr(string &totalStr,MagicWord mw, int &totalValue){
			//remove the substring
			string tmps = totalStr;
			int start = KMP(tmps,mw.subStr,mw.next);
			//cout<<"KMP = "<<start<<endl;
			if(start != -1){
				totalStr = totalStr.substr(0,start)+totalStr.substr(start+mw.len,totalStr.size());
				totalValue += mw.value;
			}
			return start;
		}
		
		// Summary: find the best solution by dfs
		// Parameters:
		//      root:the root Node contains the initial string and value. 
		//      vecWord : the vector contains all the MagicWord.
		// Return : the Node with the max value.
		Node dfsFindMax(Node root,vector<MagicWord> vecWord){
			//initialize the solution maxNode
		    Node maxNode = root;
		    
		    vecNodes.clear();
		
		    //cout<<"totalStr now = "<<root.str<<endl;
		    //queue<Node> qNode;
		
		    //stack to cotain the nodes when doing dfs
		    stack<Node> stNode;
		    
		    int curLevel = 0;
		    
		    int curMaxVal = 0;
		
		    //initialize the stack
		    stNode.push(root);
		    while(!stNode.empty()){
		
		    	//current node
		    	Node tmpN;
		    	tmpN = stNode.top();
		    	stNode.pop();
		    	//
		    	if(tmpN.nodeVis==0){
		    		tmpN.nodeVis = 1;
		    		stNode.push(tmpN);
				}
				else{//visited
					if(tmpN.nodeLevel < curLevel){
						
					}
				}
	
		    	//update the solution maxNode
		    	if(tmpN.nodeValue > maxNode.nodeValue){
		    		maxNode = tmpN;
		    	}
		    	
		    	//temp variables
		    	string tmpStr = tmpN.nodeStr;
		    	int tmpValue = tmpN.nodeValue;
		    	
		    	//cut?
				// bool cut =0;
				// for (int i = 0;i<vecNodes.size();i++){
		  //   		if(tmpN.nodeStr == vecNodes[i].nodeStr&&tmpN.nodeValue < vecNodes[i].nodeValue){
		  //   			//cout<<"str ="<<tmpN.nodeStr<<" value = "<<tmpN.nodeValue<<" < "<<vecNodes[i].nodeValue<<endl;
		  //   			cut = 1;
		  //   			break;
				// 	}
				// }
				// if(cut == 1){
				// 	//cout<<"cut some\n";
				// 	continue;
				// } 
		    	
		    	
		    	//if(tmpN.nodeStr.empty()) continue;
		
		    	//get all the possible child neighbor node of current node
		    	for(int i = 0;i < vecWord.size();i++){
		
		
			    	//temp variables
			    	string nodeStr = tmpN.nodeStr;
			    	int nodeValue = tmpN.nodeValue;
			    	vector<OutWord> vecOut = tmpN.vecOut;
			    	
			    	if(nodeStr.size()<vecWord[i].subStr.size()){
			    		continue;
					}

		
			    	//the string of current node contains the substring
			    	int outPlace = removeSubStr(nodeStr,vecWord[i],nodeValue);
			    	if( outPlace != -1){
			    		//find a new child neighbor node and put it into stack
			    		OutWord output(vecWord[i].subStr,outPlace);
			    		vecOut.push_back(output);
			    		Node nghbr(nodeStr,vecOut,nodeValue,tmpN.nodeLevel+1,0);
			    		
						
						///////////////////////
						//if(!nghbr.nodeStr.empty())vecNodes.push_back(nghbr);
						///////////////////////
						
			    		stNode.push(nghbr);
			    		curLevel = nghbr.nodeValue;
			    	}
			    	
			    }
		

		    }
		
		    //as it means
		    return maxNode;
		}
		
		
		
		
		// Summary: find the best solution by bfs
		// Parameters:
		//      root:the root Node contains the initial string and value. 
		//      vecWord : the vector contains all the MagicWord.
		// Return : the Node with the max value.
		Node bfsFindMax(Node root,vector<MagicWord> vecWord){
			//initialize the solution maxNode
		    Node maxNode = root;
		
		    vecNodes.clear();
		
		    //stack to cotain the nodes when doing dfs
		    queue<Node> qNode;
		
		    //initialize the stack
		    qNode.push(root);
		    while(!qNode.empty()){
		
		    	//current node
		    	Node tmpN;
		    	tmpN = qNode.front();
		    	qNode.pop();
	
		    	//update the solution maxNode
		    	if(tmpN.nodeValue > maxNode.nodeValue){
		    		maxNode = tmpN;
		    	}
		    	
		    	
		    	if(tmpN.nodeStr.empty()) continue;
		    	
		  //   	//cut?
				// bool cut =0;
				// for (int i = 0;i<vecNodes.size();i++){
		  //   		if(tmpN.nodeStr == vecNodes[i].nodeStr&&tmpN.nodeValue < vecNodes[i].nodeValue){
		  //   			//cout<<"str ="<<tmpN.nodeStr<<" value = "<<tmpN.nodeValue<<endl;
		  //   			cut = 1;
		  //   			break;
				// 	}
				// }
				// if(cut == 1) {
				// 	//cout<<"cut some\n";
				// 	continue;
				// }
		
		    	//get all the possible child neighbor node of current node
		    	for(int i = 0;i < vecWord.size();i++){
		
			    	//temp variables
			    	string nodeStr = tmpN.nodeStr;
			    	int nodeValue = tmpN.nodeValue;
			    	vector<OutWord> vecOut = tmpN.vecOut;
			    	
			    	if(nodeStr.size()<vecWord[i].subStr.size()){
			    		continue;
					}
		
			    	//the string of current node contains the substring
			    	int outPlace = removeSubStr(nodeStr,vecWord[i],nodeValue);
			    	if( outPlace != -1){
			    		//find a new child neighbor node and put it into stack
			    		OutWord output(vecWord[i].subStr,outPlace);
			    		vecOut.push_back(output);
			    		Node nghbr(nodeStr,vecOut,nodeValue);

						
						///////////////////////
						//Node node(nghbr.nodeStr,nghbr.vecOut,nghbr.nodeValue);
						//if(!nghbr.nodeStr.empty())vecNodes.push_back(nghbr);
						///////////////////////
			    		qNode.push(nghbr);
			    	}
			    	
			    }
		    }
		
		    //as it means
		    return maxNode;
		}
		
		// Summary: read the file
		// Parameters:
		//      inFile:the path string of the file. 
		// Return : none.
		void readFileByStr(string inFile){
			if(inFile.empty()){
		    	inFile = "in";
		    }
		
		    ifstream inputFile(inFile.c_str());
		
		
		    inputFile>>n>>k>>totalStr;
		    // cout<<n<<endl;
		    // cout<<k<<endl;
		    // cout<<totalStr<<endl;
		    
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
		}
		
		// Summary: show the route and value of the Node
		// Parameters:
		//      maxNode:the best node. 
		// Return : none.
		void showAnswer(Node maxNode){
			
			for(int i = 0; i < maxNode.vecOut.size();i++){
				cout<<maxNode.vecOut[i].outPlace<<" "<<maxNode.vecOut[i].outWord<<endl;
			}
			
			cout<<maxNode.nodeValue<<endl;
		}
		

		
		// Summary: output to the file
		// Parameters:
		//      maxNode:the best node. 
		//		outFile:the output path
		// Return : none.
		void outputFile(Node maxNode,string outFile){
			if(outFile.empty()){
		    	outFile = "out";
		    }
			ofstream outputFile(outFile.c_str());
			for(int i = 0; i < maxNode.vecOut.size();i++){
				outputFile<<maxNode.vecOut[i].outPlace<<" "<<maxNode.vecOut[i].outWord<<endl;
			}
			outputFile<<maxNode.nodeValue<<endl;
		}
		
		// Summary: sort the word vector by the value of the magic word
		// Parameters:
		//     none. 
		// Return : none.
		void sortVecWordDesc(){
			sort(vecWord.begin(), vecWord.end(),less<MagicWord>());
		}
		
		// Summary: sort the word vector by the value of the magic word
		// Parameters:
		//     none. 
		// Return : none.
		void sortVecWordAsc(){
			sort(vecWord.begin(), vecWord.end(),greater<MagicWord>());
		}
		
		// Summary: get the vector contains MagicWords
		// Parameters:
		//     none. 
		// Return : the vector contains MagicWords.
		vector<MagicWord> getVecWord(){
			return vecWord;
		}
		
		// Summary: get the total string
		// Parameters:
		//     none. 
		// Return : the total string.
		string getTotalStr(){
			return totalStr;
		}
		
		// Summary: find the best solution by dfs digui
		// Parameters:
		//      root:the root Node contains the initial string and value. 
		//      vecWord : the vector contains all the MagicWord.
		// Return : the Node with the max value.
		Node dfsFindMax2(Node root,vector<MagicWord> vecWord){
			
		    
		    vector<Node> vecNodes;
	    	
	    	Node maxNode = dfs_recur(root,vecWord,vecNodes);
		    
		    //as it means
		    return maxNode;
		}
		
		// Summary: find the best solution by dfs digui
		// Parameters:
		//      root:the root Node contains the initial string and value. 
		//      vecWord : the vector contains all the MagicWord.
		// Return : the Node with the max value.
		Node dfs_recur(Node root,vector<MagicWord> vecWord,vector<Node> &vecNodes){
			//initialize the solution maxNode
		    Node curNode = root;
		    
		    
			//temp variables
	    	string nodeStr = root.nodeStr;
	    	int nodeValue = root.nodeValue;
	    	vector<OutWord> vecOut = root.vecOut;
	    	
	    	
	    	if(root.nodeStr.empty()){
		    	return root;
			}
			else{
				for(int i=0;i<vecWord.size();i++){
					//the string of current node contains the substring
			    	int outPlace = removeSubStr(nodeStr,vecWord[i],nodeValue);
			    	if( outPlace != -1){
			    		//find a new child neighbor node and put it into stack
			    		OutWord output(vecWord[i].subStr,outPlace);
			    		vecOut.push_back(output);
			    		Node back(nodeStr,vecOut,nodeValue);
			    		back = dfs_recur(back,vecWord,vecNodes);
			    		if(back.nodeValue>root.nodeValue){
			    			vecOut.insert(vecOut.end(),back.vecOut.begin(),back.vecOut.end());
				    		Node ret(root.nodeStr,vecOut,back.nodeValue);
				    		return ret;
						}
			    		else {
			    			return root;
						}
			    	}
				}
			}
		    
		    //as it means
		    return curNode;
		}
		
};
