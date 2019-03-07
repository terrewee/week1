#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cerr;
using std::cin;
using std::endl;
using std::cout;
using std::vector;

string translate(string variabele){
    string result = ""; // implementeer dit
    for(size_t i = 0; i < variabele.size(); i++){
        if(variabele[i] <= 'z' && variabele[i] >= 'a'){
            if(variabele[i]+3 < 'z'){result += (variabele[i]+3);}
            else{result += (variabele[i]+3-26);}
            
        }
        else if(variabele[i] <= 'Z' && variabele[i] >= 'A'){
            if(variabele[i]+3 < 'Z'){result += (variabele[i]+3);}
            else{result += (variabele[i]+3-26);}
            
        }
        else{result += variabele[i];}
    }
    
    return result;
}

int main(int argc, char *argv[])
{string s;

if(argc != 2){
    cerr << "Deze functie heeft exact 1 argument nodig" << endl;
    return -1;
}

while(true){
    getline(cin, s);
    if(cin.eof()){ return 0;}
        cout << translate(s) << endl;
    }
}