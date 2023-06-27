#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

/*
* @brief Clase Lugar, va a representar cada uno de los lugares que tiene que visitar el vendedor. Tiene como atributos privados un identificador, 
*        una coordenada x y una coordenada y que indican donde se encuentra esta parada en el plano. Tiene los getters y setters básicos, además de
*        un constructor que recibe como parámetros el valor de los tres nuevos atributos privados. 
*/
class Lugar{
    private: 
        int id;
        double x; 
        double y; 
    public: 
        Lugar (int id, double x, double y){this->id = id; this->x = x; this->y = y;}
        int getID(){return id;}
        double getX(){return x;}
        double getY(){return y;}

        void setID(int id){this->id = id;}        
        void setX(double x){this->x = x;}
        void setY(double y){this->y = y;}
};

/*
* @brief Calcula la distancia entre dos lugares (simplificada por cuestiones de eficiencia)
*
*/
double calcula_distancia(Lugar p1, Lugar p2){
    return pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2);
}

/*
* @brief Devuelve la posición del Lugar más cercano entre las distintas opciones al Lugar pasado como parámetro, teniendo en cuenta
*        cuales puede considerar según el vector visitados.  
*
*/
int encuentraCercano(Lugar lugar, vector<Lugar> paradas, vector<bool> visitados) {
    double distancia,distancia_min = INFINITY;
    int pos_cercano;

    for (int i = 0; i < paradas.size(); i++){
        if (!visitados[i]){
            distancia = calcula_distancia(lugar, paradas[i]);
            if (distancia < distancia_min){
                pos_cercano = i;
                distancia_min = distancia;
            }
        }
    }
    return pos_cercano;
}

/*
* @brief Calcula la ruta óptima según el algoritmo de encontrar la distancia mínima con el último punto visitado (Nearest Neighbour)
*
*/
vector<Lugar> calcula_ruta_h2(vector<Lugar> paradas, Lugar punto_partida){
    vector<Lugar> ruta; 
    vector<bool> visitados(paradas.size(), false);
    int pos_cercano;

    ruta.push_back(punto_partida);

    pos_cercano = encuentraCercano(punto_partida, paradas, visitados);
    visitados[pos_cercano] = true;
    ruta.push_back(paradas[pos_cercano]);

    while (ruta.size() <= paradas.size()){
        
        pos_cercano = encuentraCercano(paradas[pos_cercano],paradas,visitados);
        visitados[pos_cercano] = true;
        ruta.push_back(paradas[pos_cercano]);
    }
    
    ruta.push_back(punto_partida);    

    return ruta; 
} 

int main(int argc, char* argv[]){

    const Lugar PUNTO_PARTIDA(0,0,0);
    const string FICH_DEFAULT="paradas.dat";
    const int VECES = 5;

    vector<Lugar> paradas;
    int num_paradas;
    string fich;

    if (argc < 2) 
        fich=FICH_DEFAULT;
    else fich=argv[1];

    ifstream datos;
    datos.open(fich);

    if (!datos) {
        cerr << "ERROR: no se pudo abrir el archivo especificado" <<endl;
        exit(-1);
    }

    datos >> num_paradas;
    int id;
    double x;
    double y;

    for (int i = 0; i < num_paradas; i++){
        datos >> id;
        datos >> x;
        datos >> y;

        paradas.push_back(Lugar(id, x, y));  
    }
    datos.close();

    clock_t t_antes,t_despues;

    t_antes = clock();
    for (int i = 0; i < VECES; i++)
        vector<Lugar> ruta_h2 = calcula_ruta_h2(paradas, PUNTO_PARTIDA);

    t_despues = clock();
   
    cout <<(double)(t_despues-t_antes)/(CLOCKS_PER_SEC*VECES);

    return 0;
}