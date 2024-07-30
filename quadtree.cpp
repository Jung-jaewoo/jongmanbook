#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef struct Node{ 
    char data;
    Node* son[4];
}Node;

string cmpr_paint;
string new_paint;
int new_sequence[4] = { 2, 3, 0, 1};

void solution();
void printNewPaint();
Node* makeTree(int& idx);
void prePrintNewPaint(Node*& tree);
bool checkBlackOrWhite(char first);

int main()
{
    int C;
    cin >> C;
    while(C--){
        cin >> cmpr_paint;
        solution();
    }
    
    return 0;
}

void solution(){
    char first = cmpr_paint[0];
    if(first!='x'){
        if(checkBlackOrWhite(first)){
            cout << first << "\n";
            return;
        }
    }

    Node* root;
    int idx = 0;
    root = makeTree(idx);
    
    prePrintNewPaint(root);
    cout << "\n";
}

Node* makeTree(int& idx){
    Node* root = new Node;
    root->data = cmpr_paint[idx];

    for(int i=0; i<4; i++){
        idx++;
        if(cmpr_paint[idx] == 'x'){
            root->son[i] = makeTree(idx);
        }
        else{
            Node* new_node = new Node;
            new_node->data = cmpr_paint[idx];
            root->son[i] = new_node;
        }
    }

    return root;
}

void prePrintNewPaint(Node*& tree){
    int index;
    cout << tree->data;
    for(int i=0; i<4; i++){
        index = new_sequence[i]; // 2 3 0 1
        if(tree->son[index]->data == 'x')
            prePrintNewPaint(tree->son[index]);
        else
            cout << tree->son[index]->data;
    }
}

bool checkBlackOrWhite(char first){
    for(int i=1; i<cmpr_paint.size(); i++){
        if(cmpr_paint[i]!=first)
            return false;
    }
    return true;
}