#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

using namespace std;

string file_name;
string file_list;
vector<string> matching_list;

bool checkMatching(string file_name, string file_list);

int main()
{
    fastio;   
    int C, N;
    cin >> C;
    while(C--){
        cin >> file_name;
        cin >> N;
        for(int i=0; i<N; i++){
            cin >> file_list;
            if(checkMatching(file_name, file_list))
                matching_list.push_back(file_list);
        }
        sort(matching_list.begin(),matching_list.end());
        for(int i=0; i<matching_list.size(); i++)
            cout << matching_list[i] << "\n";
        matching_list.clear();
    }
}

bool checkMatching(string file_name, string file_list){
    int i;
    for(i=0; i<file_name.size(); i++){
        if(file_name[i] == '?'){
            continue;
        }

        if(file_name[i] == '*'){
            if(i+1 == file_name.size())
                return true;

            for(int j=i; j<file_list.size(); j++){
                for(;i<file_name.size(); i++)
                    if(file_name[i+1]!='*')
                        break;

                if(file_list[j]==file_name[i+1] || file_name[i+1] == '?'){
                    string new_file_list = file_list.substr(j);
                    string new_file_name = file_name.substr(i+1);
                    if(checkMatching(new_file_name, new_file_list)) 
                        return true;
                }      
            }
            return false;
        }


        if(file_name[i] != file_list[i])
            return false;
    }
    if(file_list.size()>i)
        return false;
    return true;
}