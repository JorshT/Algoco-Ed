#include <iostream>
#include <string>

using namespace std;





void test(){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<tabla_costos[i][j]<<endl;
        }
    }
}

int main(){
    string L = "Hola_mundo";
    string B = L.substr(2,L.size()-1);
    cout <<B<<endl;
    cout<<B.size()<<endl;

    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tabla_costos[i][j]=1;
        }
    }
    test();

    
    return 0;
}