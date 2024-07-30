#include <iostream>
#include <vector>
#include <string>
using namespace std;

string cmpr_paint;

string reverse1(string::iterator& it);

int main()
{
    int C;
    cin >> C;
    while(C--){
        cin >> cmpr_paint;
        string::iterator it = cmpr_paint.begin();
        cout << reverse1(it) <<"\n";
    }
    
    return 0;
}

string reverse1(string::iterator& it){
    char head = *it;
    ++it;
    if(head == 'b' || head =='w')
        return string(1,head);
    string upperLeft = reverse1(it);
    string upperRight = reverse1(it);
    string lowerLeft = reverse1(it);
    string lowerRight = reverse1(it);

    return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}