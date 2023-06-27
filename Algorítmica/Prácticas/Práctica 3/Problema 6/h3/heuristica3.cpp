#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
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
* @brief Calcula la ruta óptima según el algoritmo de inserción barata (Cheapest Insertion)
*/
vector<Lugar> calcula_ruta_h3(vector<Lugar> paradas, Lugar punto_partida){
    vector<Lugar> ruta;
    vector<bool> visitados(paradas.size(),false);
    int pos_insercion, pos_cercano, a_insertar;
    double dist, distancia_min;

    ruta.push_back(punto_partida);
    pos_cercano = encuentraCercano(punto_partida, paradas, visitados);
    ruta.push_back(paradas[pos_cercano]);
    visitados[pos_cercano] = true;

    while(ruta.size() <= paradas.size()) {
        distancia_min = INFINITY;
        for (int i = 0; i < ruta.size(); i++) {
            for (int j = 0; j < paradas.size(); j++) {
                if (!visitados[j]) {
                    dist = calcula_distancia(ruta[i],paradas[j]);
                    if (dist < distancia_min) {
                        distancia_min = dist;
                        a_insertar = j;
                    }
                }
            }
        }

        distancia_min = INFINITY;
        for (int i = 0; i < ruta.size()-1; i++) {
            dist = calcula_distancia(paradas[a_insertar], ruta[i])
                 + calcula_distancia(paradas[a_insertar],ruta[i+1])
                 - calcula_distancia(ruta[i],ruta[i+1]);
            if (distancia_min > dist) {
                distancia_min = dist;
                pos_insercion = i;
            }
        }
             
        ruta.push_back(ruta.back());
        for (int i = ruta.size()-1; i > pos_insercion; i--) {
            ruta[i]=ruta[i-1];
        }
        ruta[pos_insercion+1] = paradas[a_insertar];
        visitados[a_insertar] = true;
    }

    ruta.push_back(punto_partida);
    return ruta;
}

int main(int argc, char* argv[]){

    const Lugar PUNTO_PARTIDA(0,0,0);
    const string FICH_DEFAULT="paradas.dat";

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

    cout << "Leidas " << num_paradas << " paradas." << endl << endl;

    vector<Lugar> ruta_h3 = calcula_ruta_h3(paradas, PUNTO_PARTIDA);
    for (int i = 0; i < ruta_h3.size(); i++){
        cout << ruta_h3.at(i).getID() << " "; 
    }
    cout << endl << endl;


    return 0;
}