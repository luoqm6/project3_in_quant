#include "magicprocess.h"

// Summary: initialize some private variable
MagicProcess::MagicProcess(){
	n = 0;
	k = 0;
	totalStr = "";
}

// Summary: destructor of the class MagicProcess.
MagicProcess::~MagicProcess(){
}

// Summary: calculate the next[]
// Parameters:
//      str:point to the string want to calculate next[].*    
//      next : the int next array to calculate.
//		len: the size of the string.
// Return : none.
void MagicProcess::calNext(const char *str, int *next, int len){
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
int MagicProcess::KMP(string str,string subStr, vector<int> next){
	int slen = str.size();
	int subLen = subStr.size();
	int k = -1;
	for(int i=0;i<slen;i++){

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
int MagicProcess::removeSubStr(string &totalStr,MagicWord mw, int &totalValue){
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
Node MagicProcess::dfsFindMax(Node root,vector<MagicWord> vecWord){
	//initialize the solution maxNode
    Node maxNode = root;

    //cout<<"totalStr now = "<<root.str<<endl;
    //queue<Node> qNode;

    //stack to cotain the nodes when doing dfs
    stack<Node> stNode;

    //initialize the stack
    stNode.push(root);
    while(!stNode.empty()){

    	//current node
    	Node tmpN;
    	tmpN = stNode.top();
    	stNode.pop();

    	//update the solution maxNode
    	if(tmpN.nodeValue > maxNode.nodeValue){
    		maxNode = tmpN;
    	}
    	
    	
    	if(tmpN.nodeStr.empty()) continue;

    	//get all the possible child neighbor node of current node
    	for(int i = 0;i < vecWord.size();i++){

	    	//cout<<"substr["<<i<<"] = "<<vecWord[i].subStr<<" len = "<<vecWord[i].len<<endl;
	    	// for (int j=0;j<tmpWord[i].next.size();j++){
	    	// 	cout<<"next["<<j<<"] = "<<tmpWord[i].next[j]<<endl;
	    	// }

	    	//temp variables
	    	string nodeStr = tmpN.nodeStr;
	    	int nodeValue = tmpN.nodeValue;
	    	vector<OutWord> vecOut = tmpN.vecOut;

	    	//the string of current node contains the substring
	    	int outPlace = removeSubStr(nodeStr,vecWord[i],nodeValue);
	    	if( outPlace != -1){
	    		//find a new child neighbor node and put it into stack
	    		OutWord output(vecWord[i].subStr,outPlace);
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

    //as it means
    return maxNode;
}

// Summary: read the file
// Parameters:
//      inFile:the path string of the file. 
// Return : none.
void MagicProcess::readFileByStr(string inFile){
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
void MagicProcess::showAnswer(Node maxNode){
	// for(int i = 0; i < maxNode.vecOut.size();i++){
	// 	cout<<"out = "<<maxNode.vecOut[i].outPlace<<" "<<maxNode.vecOut[i].outWord<<endl;
	// }
	// cout<<"current string is: "<<maxNode.nodeStr<<" the value is: "<<maxNode.nodeValue<<endl;
	for(int i = 0; i < maxNode.vecOut.size();i++){
		cout<<maxNode.vecOut[i].outPlace<<" "<<maxNode.vecOut[i].outWord<<endl;
	}
	cout<<maxNode.nodeValue<<endl;
}

// Summary: sort the word vector by the value of the magic word
// Parameters:
//     none. 
// Return : none.
void MagicProcess::sortVecWordDesc(){
	sort(vecWord.begin(), vecWord.end(),less<MagicWord>());
}

// Summary: get the vector contains MagicWords
// Parameters:
//     none. 
// Return : the vector contains MagicWords.
vector<MagicWord> MagicProcess::getVecWord(){
	return vecWord;
}

// Summary: get the total string
// Parameters:
//     none. 
// Return : the total string.
string MagicProcess::getTotalStr(){
	return totalStr;
}

