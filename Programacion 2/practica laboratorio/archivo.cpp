#include <iostream>
#include <vector>
using namespace std;
int main(){
    string name, mCadena;
    char a;
    int num, acum =0;
    
    while(cin >> num){
        
        acum += num;
        cin.get(a);
        if(a == '\n') {
            cout << acum << endl;
            acum = 0;
            }
    }
    cout << acum;
    
    
    /*
    cin >> name;
    cout << name;
    cin.get(a);
    cin >> name;
    cout << name;
    */
    
    return 0;
}
