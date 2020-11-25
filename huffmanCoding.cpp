#include<iostream>
#include<string>
#include<queue>
#include<unordered_map>
#include<cmath>
using namespace std;

///Node class for making a tree
class Node{
    public:
    char c;
    int freq;
    Node *left, *right;
};

///Function to make a new tree node
Node* getNode(char c, int freq, Node* left, Node* right){
    Node* t = new Node();
    t->c = c;
    t->freq = freq;
    t->left = left;
    t->right = right;
    return t;
}

///Comparison object so as to order the heap
class comp{
    public:
    bool operator()(Node* left, Node* right){
        ///Highest priority or top most item in pq must have highest freq
        return left->freq > right->freq;
    }
};

///Traverse huffman and store strings in the map for huffman codes
void encode(Node* root, string str, unordered_map<char,string> &huffmanCode){
    ///If root is NULL nothing can be done!
    if(!root)
        return;

    ///Found a leaf
    if(!root->left && !root->right)
        huffmanCode[root->c] = str;

    encode(root->left, str+"0", huffmanCode);
    encode(root->right, str+"1", huffmanCode);
}

///Traverse huffman and decode the string given
string decode(Node* root, string s){
	string ans = "";
	Node* temp = root;
	for (int i=0;i<s.size();i++){
		if (s[i] == '0')
            temp = temp->left;
		else
            temp = temp->right;

		// reached leaf node
		if (!temp->left && !temp->right){
			ans += temp->c;
			temp = root;
		}

	}

	return ans+'\0';
}

///Building huffman and finally, decoding it!
void buildHuffman(string text){

    ///Counts and stores frequency of every occuring character
    unordered_map<char, int> freq;

    for(auto c:text){
        ///Updating frequency
        freq[c]++;
    }

    ///Creating priority queue for storing leaves of the huffman tree
    priority_queue<Node*, vector<Node*>, comp> tree;

    ///Creating leaf node of each character stored in the map and insert in root;
    cout<<"\nFrequency of each character in input string:\n";
    for(auto p: freq){
        cout<<p.first<<" : "<<p.second<<endl;
        tree.push(getNode(p.first, p.second, NULL, NULL));
    }

    ///Creating tree
    while(tree.size()!=1){
        ///Remove two nodes with highest priority ie lowest frequency from tree
        Node* left = tree.top(); tree.pop();
        Node* right = tree.top(); tree.pop();

        ///Create new node with these two as its children and push a new node with freq = sum of both children
        int sum = left->freq + right->freq;
        tree.push(getNode(NULL, sum, left, right));
    }

    ///Root stores pointer to root of huffman tree
    Node* root = tree.top();

    ///CREATED!

    ///Traverse the whole huffman tree and store huffman codes in map
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout<<"\nHUFFMAN CODES ARE:\n"<<endl;

    ///Printing codes for each character
    for(auto p: huffmanCode)
        cout<<p.first<<" : "<<p.second<<endl;

    cout<<endl;

    cout<<"\nOriginal string was: \n"<<text<<endl;
    cout<<endl;

    ///Appending code
    string res = "";
    for(char c:text)
        res += huffmanCode[c];

    ///Printing huffman coded string for the given text;
    cout<<"\nEncoded string is: \n"<<res<<endl;

    ///Traversing the huffman tree again so as to decode the string res
    cout<<"\nDecoded string is: \n";
    string decodedStr = decode(root, res);
    cout<<decodedStr<<endl;
    cout<<endl<<endl;

    ///Finding compression ratio
    int org = 8*text.length();
    int conv = ceil(res.length()/8);
    double compressionRate = (double)conv/org;
    cout<<"String is compressed to "<<compressionRate*100<<"% of the total size."<<endl;

}

///Huffman coding begins
int main()
{
    string str;
    getline(cin, str);

    buildHuffman(str);

    return 0;
}
