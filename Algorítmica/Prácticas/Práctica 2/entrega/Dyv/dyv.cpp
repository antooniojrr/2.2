// Ejecución: ./dyv <fich_datos.dat>
/*
    @name especifico.cpp
    @author Antonio Rodríguez, David Kessler, Santiago López

*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;

// Número máximo de vacas sobre el que aplicar el algoritmo cuadrático
const double UMBRAL = 50;

/*
    @brief Aplica la técnica Divide y Vencerás para encontrar la pareja de vacas más cercanas.
    @param vacas Array de coordenadas de las vacas
    @param init primera posición del array a comprobar
    @param end última posición del array a comprobar
    @return pareja de vacas más amigas
*/
pair<pair<double,double>,pair<double,double>> vacas_amigas_DyV(const pair<double,double> *vacas, int n);

/*
    @brief Obtiene las vacas más amigas cercanas a la frontera a partir de esta y un margen
    @param vacas Vacas estudiadas
    @param n Número de vacas
    @param frontera Frontera a comprobar
    @param margen Distancia de margen en la frontera
    @pre La frontera tiene que ser dos puntos alineados vertical u horizontalmente
*/

pair<pair<double,double>,pair<double,double>> vacas_amigas_frontera(const pair<double,double> *vacas, int n, pair<pair<double,double>,pair<double,double>> frontera, double margen);

/*
    @brief Busca las vacas más amigas dentro de un array de coordenadas de distintas vacas, es decir, las más cercanas entre sí
    @param vacas array dinámico de coordenadas (x,y) de las vacas a estudiar
    @param n número de vacas en el array
    @return índices en el array de las vacas más cercanas
*/
pair<int,int> vacas_amigas_lims(const pair<double,double> *vacas, int n);



/*
    @brief Función para calcular la distancia entre dos punto del plano euclideo
    @param coord1 Punto 1 del plano
    @param coord2 Punto 2 del plano
    @return Distancia entre los dos puntos
*/
double distancia(pair<double,double> coord1, pair<double,double> coord2) {             

    double dist = (coord1.first-coord2.first)*(coord1.first-coord2.first)
                    +(coord1.second-coord2.second)*(coord1.second-coord2.second);  
    return sqrt(dist);                                                                  

}

/*
    @brief Encuentra las coordenadas de las esquinas contrarias de un cuadrante que comprende todas las vacas del array
    @param vacas Vacas estudiadas
    @param n Número de vacas
    @return Extremos
*/
pair<pair<double,double>,pair<double,double>> extremos(const pair<double,double> *vacas, int n) {

    pair<pair<double,double>,pair<double,double>> extremos(pair<double,double>(MAXFLOAT,MAXFLOAT),pair<double,double>(-MAXFLOAT,-MAXFLOAT));
    for(int i=0; i < n; i++) {
        if(vacas[i].first < extremos.first.first)
            extremos.first.first = vacas[i].first;
        else if(vacas[i].first > extremos.second.first)
            extremos.second.first = vacas[i].first;

        if(vacas[i].second < extremos.first.second)
            extremos.first.second = vacas[i].second;
        else if(vacas[i].second > extremos.second.second)
            extremos.second.second = vacas[i].second;
    }

    return extremos;

}

/*
    @brief Separa las vacas de un array dependiendo de sus coordenadas en el plano en dos cuadrantes
    @param vacas array a separar
    @param n número de vacas
    @param vac1 array con las vacas en el cuadrante 1
    @param n1 número de vacas en vac1
    @param vac2 array con las vacas sobrantes
    @param n2 número de vacas en vac2
    @return Dos puntos que marcan la frontera entre los cuadrantes
*/

pair<pair<double,double>,pair<double,double>> separar(const pair<double,double> *vacas, int n, pair<double,double> *vac1, int &n1, pair<double,double> *vac2, int &n2) {
    n1=n2=0;
    pair<pair<double,double>,pair<double,double>> extrem=extremos(vacas,n),frontera;
    
    if (extrem.second.first-extrem.first.first > extrem.second.second-extrem.first.second) {
        // Dividimos horizontalmente

        double x_med=((extrem.second.first-extrem.first.first)/2)+ extrem.first.first;

        frontera.first.first=frontera.second.first=x_med;
        frontera.first.second=extrem.first.second;
        frontera.second.second=extrem.second.second;

        for(int i=0; i<n; i++) {
            if(vacas[i].first<x_med) {
                vac1[n1]=vacas[i];
                n1++;
            }
            else {
                vac2[n2]=vacas[i];
                n2++;
            }
        }

    }

    else {
        // Dividimos verticalmente

        double y_med=((extrem.second.second-extrem.first.second)/2) + extrem.first.second;

        frontera.first.second=frontera.second.second=y_med;
        frontera.first.first=extrem.first.first;
        frontera.second.first=extrem.second.first;

        for(int i=0; i<n; i++) {
            if(vacas[i].second<y_med) {
                vac1[n1]=vacas[i];
                n1++;
            }
            else {
                vac2[n2]=vacas[i];
                n2++;
            }
        }
    }
    return frontera;
}




pair<pair<double,double>,pair<double,double>> vacas_amigas_frontera(const pair<double,double> *vacas, int n, pair<pair<double,double>,pair<double,double>> frontera, double margen) {
    pair<double,double> *vac=new pair<double,double>[n];
    int n1=0;

    if (frontera.first.first == frontera.second.first) {
        // Frontera = línea vertical
        for(int i = 0; i<n; i++) {
            if (abs(vacas[i].first-frontera.first.first)<margen) {
                vac[n1]=vacas[i];
                n1++;
            }
        }
    }
    else {
        // Frontera = línea horizontal
        for(int i = 0; i<n; i++) {
            if (abs(vacas[i].second-frontera.first.second)<margen) {
                vac[n1]=vacas[i];
                n1++;
            }
        }
    }
    if (n1>1) {
        pair<int,int>am=vacas_amigas_lims(vac,n1);
        delete [] vac;
        return pair<pair<double,double>,pair<double,double>>(vacas[am.first],vacas[am.second]);
    }
    else return pair<pair<double,double>,pair<double,double>>(pair<double,double>(-1,-1),pair<double,double>(-1,-1));
}

pair<int,int> vacas_amigas_lims(const pair<double,double> *vacas, int n) { // O(n²)

    pair<int,int> amigas(0,1);                                  // O(1)
    double dist = distancia(vacas[0],vacas[1]);                 // O(1)             
    for (int i = 0; i < n-1; i++) {                             // O(n²)
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

pair<pair<double,double>,pair<double,double>> vacas_amigas_DyV(const pair<double,double> *vacas, int n) {
    
    if ( n < UMBRAL ) {
        pair <int,int> am=vacas_amigas_lims(vacas,n);
        return pair<pair<double,double>,pair<double,double>>(vacas[am.first],vacas[am.second]);
    }
    else {

        pair<pair<double,double>,pair<double,double>> extrem=extremos(vacas,n);
        pair<double,double> *vac1, *vac2;
        vac1 = new pair<double,double>[n];
        vac2 = new pair<double,double>[n];
        int n1,n2;

        pair<pair<double,double>,pair<double,double>> frontera = separar(vacas,n,vac1,n1,vac2,n2);
        pair<pair<double,double>,pair<double,double>> am1,am2,am3;
        float dist1,dist2;
        if (n1 > 1) {
            am1 = vacas_amigas_DyV(vac1,n1);
            dist1 = distancia(am1.first,am1.second);
        }
        else dist1 = MAXFLOAT;

        if (n2 > 1) {
            am2 = vacas_amigas_DyV(vac2,n2);
            dist2 = distancia(am2.first,am2.second);
        }
        else dist2 = MAXFLOAT;
        
        float dist3, dist = (dist1 < dist2) ? dist1 : dist2;
        am3=vacas_amigas_frontera(vacas,n,frontera,dist);
        if (am3.first.first == -1 && am3.first.second == -1 && am3.second.first == -1 && am3.second.second == -1)
            dist3=MAXFLOAT;
        else dist3 = distancia(am3.first,am3.second);

        delete [] vac1;
        delete [] vac2;
        if (dist3 <= dist1 && dist3 <= dist2 )
            return am3;
        else
            return (dist1 < dist2) ? am1 : am2;
    }
    
}



int main(int argc, char *argv[]) {
    const int MAX_INICIAL=10000000;
    pair<double,double> *vacas=new pair<double,double>[MAX_INICIAL];
    const int VECES=10;
    const string FICH_DEFAULT="vacas.dat";
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

    double data;
    int num=0;

    while (datos >> data) {
        vacas[num].first=data;
        datos >> data;
        vacas[num].second=data;
        num++;
    }
    datos.close();

    cout << "Leidas " << num << " vacas." << endl;
    pair<pair<double,double>,pair<double,double>> amigas=vacas_amigas_DyV(vacas,num);

    cout << "Las vacas más amigas son (Indice en el array):" << endl;
    cout << "\tVaca ( " << amigas.first.first << " , " <<  amigas.first.second << " )" << endl;
    cout << "\tVaca ( " << amigas.second.first << " , " <<  amigas.second.second << " )" << endl;
    cout << "Distancia entre ellas = " << distancia(amigas.first, amigas.second) << endl;

    delete [] vacas;
    return 0;

}
