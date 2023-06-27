/*
    @name especifico.cpp
    @author Antonio Rodríguez, David Kessler, Santiago López

*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>

using namespace std;

/*
    @brief Función para calcular la distancia entre dos punto del plano euclideo
    @param coord1 Punto 1 del plano
    @param coord2 Punto 2 del plano
    @return Distancia entre los dos puntos
*/

double distancia(pair<double,double> coord1, pair<double,double> coord2) {              // O(1)

    double dist = pow(coord1.first-coord2.first,2)+pow(coord1.second-coord2.second,2);  // O(1)
    return sqrt(dist);                                                                  // O(1)

}

/*
    @brief Busca las vacas más amigas dentro de un array de coordenadas de distintas vacas, es decir, las más cercanas entre sí
    @param vacas array dinámico de coordenadas (x,y) de las vacas a estudiar
    @param n número de vacas en el array
    @return índice en el array de las vacas más cercanas
    @post Si n <=1 se devolverá la pareja (-1,-1) como valor de error
*/
pair<int,int> vacas_amigas(pair<double,double> *vacas, int n) { // O(n²)

    if (n > 1) {                                                    // O(n²)

        pair<int,int> amigas(0,1);                                      // O(1)
        double dist = distancia(vacas[0],vacas[1]);                     // O(1)             
        for (int i = 0; i < n; i++) {                                   // O(n²)
            for (int j = i+1; j < n; j++) {                                 // O(n)
                if (i!=j) {                                                     // O(1)
                    if (distancia(vacas[i],vacas[j])<dist) {                        // O(1)
                        amigas.first=i;                                                 // O(1)
                        amigas.second=j;                                                // O(1)
                        dist=distancia(vacas[i],vacas[j]);                              // O(1)
                    }
                }
            }
        }

        return amigas;
    }

    else return pair<int,int>(-1,-1);                               // O(1)

}

int main(int argc, char *argv[]) {
    
    const int MAX_INICIAL=100000;
    const string FICH_DEFAULT="vacas.dat";
    string fich;
    if (argc < 2) {
        cout << "Ningun parametro introducido. Tomado fichero por defecto: " << FICH_DEFAULT <<endl <<endl;
        fich=FICH_DEFAULT;
    }
    else fich=argv[1];

    ifstream datos;
    datos.open(fich);

    if (!datos) {
        cerr << "ERROR: no se pudo abrir el archivo especificado" <<endl;
        exit(-1);
    }

    double data;
    int num=0;
    pair<double,double> *vacas = new pair<double,double>[MAX_INICIAL];

    while (datos >> data) {
        vacas[num].first=data;
        datos >> data;
        vacas[num].second=data;
        num++;
    }
    datos.close();

    cout << "Leidas " << num << " vacas." << endl;
    pair<int,int> amigas=vacas_amigas(vacas,num);

    cout << "Las vacas más amigas son (Indice en el array):" << endl;
    cout << "\tVaca " << amigas.first << "( " << vacas[amigas.first].first << " , " <<  vacas[amigas.first].second << " )" << endl;
    cout << "\tVaca " << amigas.second << "( " << vacas[amigas.second].first << " , " <<  vacas[amigas.second].second << " )" << endl;
    cout << "Distancia entre ellas = " << distancia(vacas[amigas.first], vacas[amigas.second]) << endl;

    delete [] vacas;
    return 0;

}