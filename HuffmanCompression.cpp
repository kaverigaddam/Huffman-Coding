#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Huffman tree node class
class HuffmanNode {
public:
    char data;
    int frequency;
    HuffmanNode *left, *right;
    
    HuffmanNode(char d, int f) : data(d), frequency(f), left(nullptr), right(nullptr) {}
};

// Function to build Huffman tree using a vector-based approach
HuffmanNode* buildHuffmanTree(string S, vector<int>& f) {
    vector<HuffmanNode*> nodes;
    
    //initial nodes for each character
    for (int i = 0; i < S.length(); i++) {
        nodes.push_back(new HuffmanNode(S[i], f[i]));
    }
    
    // Build the tree bottom-up
    while (nodes.size() > 1) {
        // Sort nodes based on frequency
        sort(nodes.begin(), nodes.end(), [](HuffmanNode* a, HuffmanNode* b) {
            return a->frequency < b->frequency;
        });
        
        // Take two nodes with lowest frequencies
        HuffmanNode *left = nodes[0];
        HuffmanNode *right = nodes[1];
        
        // Create a new internal node
        HuffmanNode *parent = new HuffmanNode('$', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        
        // Remove the two nodes and add the new parent node
        nodes.erase(nodes.begin(), nodes.begin() + 2);
        nodes.push_back(parent);
    }
    
    return nodes[0];
}

//preorder traversal printing
void printCodesPreorder(HuffmanNode* root, string code, vector<pair<char, string>>& result) {
    if (!root) return;
    
    if (root->data != '$') {
        result.push_back({root->data, code});
    }
    
    printCodesPreorder(root->left, code + "0", result);
    printCodesPreorder(root->right, code + "1", result);
}

int main() {
    string S = "abcdef";
    vector<int> f = {5, 9, 12, 13, 16, 45};
    
    cout << "Input Data:\n";
    cout << "String: " << S << "\n";
    cout << "Frequencies: ";
    for (int freq : f) {
        cout << freq << " ";
    }
    cout << "\n\n";

    HuffmanNode* root = buildHuffmanTree(S, f);
    
    vector<pair<char, string>> huffmanCodes;
    printCodesPreorder(root, "", huffmanCodes);
    
    cout << "Huffman Codes (Preorder):\n";
    for (const auto& code : huffmanCodes) {
        cout << "'" << code.first << "' -> " << code.second << "\n";
    }
    
    return 0;
}
