#include <iostream>
#include <string>
#include <cmath>  
#include <algorithm>
#include <fstream>
#include <chrono> 
using namespace std;


#define INF 2000000000

/*
# Definicion de matrices para costos y booleanos en caso de utilizar matrices o costos constantes

La idea es utilizar los booleanos globales, de forma que si son verdaderos, las funciones utilicen la data
de las matrices que tambien son globales, y si son falsos, que calculen la funcion en función de lo caracteres


Se definirá N y M los tamaños máximos de las matrices, los cuales podrán ser modificados dependiendo del dataset,
tambien si se tiene un dataset con valores de N y M mayores, que el programa los pueda guardar, de forma que no haya
problemas con el tamaño de los arreglos en memoria

*/

const int N = 400;

bool exist_cost_matrix = false;


int insert_cost[N];
int delete_cost[N];
int replace_cost[N][N];
int transpose_cost[N][N];


/*
Debido a que existe la posibilidad de utilizar matriz de costos, tambien se trabajarán las funciones con posiciones
para acceder a las matrices, 


*/


//Funciones para operaciones
//- a: Caracter original
//- b: caracter con el que se sustituye
// Return: Costo de sustituir de 'a' por 'b'
int costo_sub(char a, char b, int i, int j){
    if(exist_cost_matrix){
        return replace_cost[i][j];
    }
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

int costo_ins(char b,int i){
    if(exist_cost_matrix){
        return insert_cost[i];
    }
    int costo=1;
    return costo;
}

// Calcula el costo de eliminar el carácter ’a ’.
// Parámetros:
//−a: carácter a eliminar
// Return: costo de eliminar ’a’

int costo_del(char a, int i){
    if(exist_cost_matrix){
        return delete_cost[i];
    }
    int costo=1;
    // Implementación
    return costo;
}

// Calcula el costo de transponer los caracteres ’a’ y ’b’.
// Parámetros:
//−a: primer carácter a transponer
//−b: segundo carácter a transponer
// Return: costo de transponer ’a’ y ’b’

int costo_trans(char a, char b, int i, int j) {
    if(exist_cost_matrix){
        return transpose_cost[i][j];
    }
    int costo=1;
    // Implementación
    return costo;
}






//Funcion distancia de edicion por fuerza bruta



int edfb2(string S, string T, int i, int j){
    
    if(i==((int)S.size())){
        //cout<<S.size()<<endl;
        int cost = 0;
        for(int c=j;c<(int)T.size();c++){
            cost+= costo_ins(T[c],j);
            j++;
        }
        return cost;
    }

    if(j==((int)T.size())){
        int cost=0;
        for(int c=i;c<(int)S.size();c++){
            cost+=costo_del(S[c],i);
            i++;
        }
        return cost;
    }
    
    if(S[i]==T[j]){
        return edfb2(S,T,i+1,j+1);
    }

    
    int cost_insert = costo_ins(T[j],j) + edfb2(S,T,i,j+1);
    int cost_delete = costo_del(S[i],i) + edfb2(S,T,i+1,j);
    int cost_sustituir = costo_sub(S[i],T[j],i,j) + edfb2(S,T,i+1,j+1);
    int cost_transponer = INF;

    if((i < ((int)S.size())-1) && j<((int)T.size())-1 && S[i]==T[j+1] && S[i+1] == T[j]){
        cost_transponer = costo_trans(S[i],S[i+1],i,j) + edfb2(S,T,i+2,j+2);
    }
    //cout<<"###############"<<endl;
    //cout<<cost_insert<<endl;
    //cout<<cost_delete<<endl;
    //cout<<cost_sustituir<<endl;
    //cout<<"i,j:"<<i<<" "<<j<<endl;
    //cout<<cost_transponer<<endl;
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
        d[i][0] = d[i-1][0] + costo_del(S[i-1],i);
    }

    for(int j=1;j<=m;j++){
        d[0][j] = d[0][j-1] + costo_ins(T[j-1],j);
    }

    //Parte de rellenaar la matriz:
    
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(S[i-1]==T[j-1]){
                d[i][j] = d[i-1][j-1];
            }
            else{
                int cost_eliminar =  d[i-1][j] + costo_del(S[i-1],i-1);
                int cost_insertar = d[i][j-1] + costo_ins(T[j-1],j-1);
                int cost_sustituir = d[i-1][j-1] + costo_sub(S[i-1],T[j-1],i-1,j-1);
                
                d[i][j] = min(cost_eliminar,min(cost_insertar,cost_sustituir));
                
                if( i >1 && S[i-2] == T[j-1] && S[i-1] == T[j-2]){
                    d[i][j] = min(d[i][j],d[i-2][j-2]+costo_trans(S[i-2],S[i-1],i-2,j-1));
                }

            }
        }
    }

    return d[n][m];




}


int rellenar_matrix(){
    int n;
    ifstream fp("test_cases/cost_delete.txt");
    if(!fp.is_open()){
        cerr<<"No se pudo abrir el archivo.\n";
        return -1;
    }
    fp>>n;
    if(n>N){
        cout<<"AQUII"<<endl;
        return -2;
    };
    for(int i=0;i<n;i++){
        fp>>delete_cost[i];
    }
    fp.close();

    ifstream fp1("test_cases/cost_insert.txt");
    if(!fp1.is_open()){
        cerr<<"No se pudo abrir el archivo.\n";
        return -1;
    }

    fp1>>n;
    if(n>N){
        return -2;
    }
    for(int i=0;i<n;i++){
        fp1>>insert_cost[i];
    }
    fp1.close();

    ifstream fp2("test_cases/cost_replace.txt");
    if(!fp2.is_open()){
        cerr<<"No se pudo abrir el archivo.\n";
        return -1;
    }
    fp2>>n;
    if(n>N){
        return -2;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fp2>>replace_cost[i][j];
        }
    }
    fp2.close();

    ifstream fp3("test_cases/cost_transpose.txt");
    if(!fp3.is_open()){
        cerr<<"No se pudo abrir el archivo.\n";
        return -2;
    }

    fp3>>n;
    if(n>N){
        return -2;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            fp3>>transpose_cost[i][j];
        }
    }
    fp3.close();

    return n;


}



int main(){
    string s;
    string t;
    cin>>s;
    cin>>t;
    if(s.size()>N || t.size()>N){
        return 1;
    }
    exist_cost_matrix=false;
    if(exist_cost_matrix){
        //Leer archivos y rellenar matrices
        cout<<"Leyendo valores"<<endl;
        int x= rellenar_matrix();
        if(x<0){
            cout<<x<<endl;
            return 1;
        }
    }

    cout<<"Calculando..."<<endl;
    auto start_edfb = chrono::high_resolution_clock::now();
    cout<<edfb2(s,t,0,0)<<endl;
    auto end_edfb = std::chrono::high_resolution_clock::now();
    auto start_edpd = chrono::high_resolution_clock::now();
    cout<<edpd(s,t)<<endl;
    auto end_edpd = std::chrono::high_resolution_clock::now();

    auto duration_edfb= std::chrono::duration_cast<std::chrono::milliseconds>(end_edfb - start_edfb); 
    auto duration_edpd= std::chrono::duration_cast<std::chrono::milliseconds>(end_edpd - start_edpd);

    cout<<"Tiempo de ejecucion algoritmo fuerza bruta: "<<duration_edfb.count()<<" ms"<<endl;
    cout<<"Tiempo de ejecucion algoritmo programacion dinamica: "<<duration_edpd.count()<<" ms"<<endl;
    return 0;
}