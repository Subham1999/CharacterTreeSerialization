#include <bits/stdc++.h>
using namespace std;
class Trie {
private:
    /** Initialize your data structure here. */
    class node{
        public:
        char c;
        node * childs[26];
        bool terminate;
        node(char x){
            this->c = x;
            for(short i = 0; i < 26; i++) this->childs[i] = nullptr;
            terminate = false;
        }
    };
    void preOrder(node* root, string& result){
        if(root == nullptr){
            result += string(26, '*');
            return;
        }
        
        result += "<";
        result += root->c;
        result += "<";
        for(short i = 0; i < 26; ++i){
            if(root->childs[i]) result += "1";
            else result += "0";
        }
        result += ">";
        if(root->terminate) result += "1";
        else result += "0";
        result += ">";
        
        for(int i = 0; i < 26; i++){
            if(root->childs[i]){
                preOrder(root->childs[i], result);
            }
        }
    }
public:
    node *root = nullptr;
    Trie() {
        root = new node('`');
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        node *curr = root;
        for(char c : word){
            if(curr->childs[c - 'a']==nullptr){
                curr->childs[c - 'a'] = new node(c);
            }
            curr = curr->childs[c - 'a'];
        }
        curr->terminate = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        node *curr = root;
        for(char c : word){
            if(curr->childs[c - 'a']==nullptr){
                return false;
            }
            curr = curr->childs[c - 'a'];
        }
        return curr->terminate;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        node *curr = root;
        for(char c : prefix){
            if(curr->childs[c - 'a']==nullptr){
                return false;
            }
            curr = curr->childs[c - 'a'];
        }
        return true;
    }
    string serialize() {
       string result = "[";
       preOrder(this->root, result);
       result += ']';
       return result;
    }
    node* preOrderii(vector<string>& alldata, int loc){
        string data = alldata[loc];
        char x = data[1];
        node* ntrie = new node(x);
        int cnt = 0;
        
        // for(int i = 0; i < 26; i++){
        //     cout << data[3 + i];
        // }
        
        // cout << endl; 
    
        for(int i = 0; i < 26; i++){
            if(data[3 + i] == '1'){
                ntrie->childs[i] = preOrderii(alldata, loc + 1);
            }
        }
        
        
        if(data[30] == '1'){
            ntrie->terminate = true;
        } else{
            ntrie->terminate = false; 
        }
        alldata.erase(alldata.begin() + loc);
        return ntrie;
    }
    Trie* deserialize(string text){
        if(text.empty()) return nullptr;
        vector<string> alldata;
        for(int loc = 1; loc < text.length(); loc += 32){
            alldata.push_back(text.substr(loc, 32));
        }
        alldata.pop_back();
        Trie* newTrie = new Trie();
        newTrie->root = preOrderii(alldata, 0);
        return newTrie;
    }
};

string process_line(string line){
	// int n = line.length();
	// if(line[n-1] == '')
	// line.pop_back();cd ..
	return line;
}

int main(int argc, char const *argv[]){
	Trie* trie = new Trie();
	Trie* trie2;
	string code = "";
	string s = argv[1];
	if(s == "load"){
		ifstream infile(argv[2], ios::out | ios::binary);
		string line = "";
		string code2 = "";
		while (getline(infile, line)){
            code2 = line;
        }
        trie2 = trie->deserialize(code);
        infile.close();
	} 
	if(s == "create"){
		ifstream infile(argv[2]);
		ofstream outfile(argv[3], ios::out | ios::binary);

		vector<string> input;
		string line = "";
		while (getline(infile, line)){
            input.push_back(process_line(line));
        }
		for(auto ss : input){
			cout << ss << endl;
			trie->insert(ss);
		}
		code = trie->serialize();

		char buffer[code.length()];
		strcpy(buffer, code.c_str());
		outfile.write(buffer, code.length());
		outfile.close();
		infile.close();
	}
	return 0;
}