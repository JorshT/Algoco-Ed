#include <iostream>
#include <string>
#include <cmath>  
#include <algorithm>
using namespace std;


#define INF 2000000000

//Funciones para operaciones

//- a: Caracter original
//- b: caracter con el que se sustituye
// Return: Costo de sustituir de 'a' por 'b'
int costo_sub(char a, char b){
    int costo=0;
    if(a!=b){
        costo=2;
    }
    return costo;
}

// Calcula el costo de insertar el carácter ‘b’.
// Parámetros:
//−b: carácter a insertar
// Return: costo de insertar ’b’

int costo_ins(char b){
    int costo=1;
    return costo;
}

// Calcula el costo de eliminar el carácter ’a ’.
// Parámetros:
//−a: carácter a eliminar
// Return: costo de eliminar ’a’

int costo_del(char a){
    int costo=1;
    // Implementación
    return costo;
}

// Calcula el costo de transponer los caracteres ’a’ y ’b’.
// Parámetros:
//−a: primer carácter a transponer
//−b: segundo carácter a transponer
// Return: costo de transponer ’a’ y ’b’

int costo_trans(char a, char b) {
    int costo=1;
    // Implementación
    return costo;
}



//Funcion distancia de edicion por fuerza bruta
int edfb(string S,string T){
    //Caso Base 
    if(S.size()==0){
        int cost = 0;
        for(size_t i=0;i<T.size();i++){
            cost+= costo_ins(T[i]);
        }
        return cost;
    }
    //Caso base
    if(T.size()==0){
        int cost = 0;
        for(size_t i=0;i<S.size();i++){
            cost+= costo_del(S[i]);
        }
        return cost;
    }

    if(S[0]==T[0]){
        return edfb(S.substr(1,S.size()-1),T.substr(1,T.size()-1));
    }

    int cost_insert = costo_ins(T[0]) + edfb(S,T.substr(1,T.size()-1));
    int cost_delete = costo_del(T[0]) + edfb(S.substr(1,S.size()-1),T);
    int cost_sustituir = costo_sub(S[0],T[0]) + edfb(S.substr(1,S.size()-1),T.substr(1,T.size()-1));
    int cost_transponer = INF;
    if(S.size()>1 && T.size()>1 && S[0] == T[1] && S[1]== T[0] ){
        cost_transponer = costo_trans(S[0],S[1]) +  edfb(S.substr(2,S.size()-1),T.substr(2,T.size()-1));
    }
    
    return min(min(cost_insert,cost_delete),min(cost_sustituir,cost_transponer));


}


//Funcion de distancia de edicion usando paradigma de programacion dinamica


int edpd(string S, string T){
    int n,m;
    n = (int)S.size();
    m = (int)T.size();

    //Definir la matriz
    int d[n+1][m+1];

    //Rellenar la matriz con 0
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            d[i][j] = 0;
        }
    }

    //inicializar la matriz con costos de insercion y eliminacion para los casos base.

    for(int i=1;i<=n;i++){
        d[i][0] = d[i-1][0] + costo_del(S[i-1]);
    }

    for(int j=1;j<=m;j++){
        d[0][j] = d[0][j-1] + costo_ins(T[j-1]);
    }

    //Parte de rellenaar la matriz:
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(S[i-1]==T[j-1]){
                d[i][j] = d[i-1][j-1];
            }
            else{
                int cost_eliminar =  d[i-1][j] + costo_del(S[i-1]);
                int cost_insertar = d[i][j-1] + costo_ins(T[j-1]);
                int cost_sustituir = d[i-1][j-1] + costo_sub(S[i-1],T[j-1]);
                
                d[i][j] = min(cost_eliminar,min(cost_insertar,cost_sustituir));
                
                if( i >1 && S[i-2] == T[j-1] && S[i-1] == T[j-2]){
                    d[i][j] = min(d[i][j],d[i-2][j-2]+costo_trans(S[i-2],S[i-1]));
                }

            }
        }
    }

    return d[n][m];




}





int main(){
    string s;
    string t;
    cin>>s;
    cin>>t;
    cout<<edfb(s,t)<<endl;
    cout<<edpd(s,t)<<endl;
    return 0;
}