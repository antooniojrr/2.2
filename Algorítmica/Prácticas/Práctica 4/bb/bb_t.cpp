
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <queue>
#include <vector>

using namespace std;

struct Trabajo {
    int duracion=0;
    int plazo=0;
    int penalizacion=0;
    bool terminado=false;
};

bool cmpTrabajos(Trabajo t1, Trabajo t2) {
    return (t1.penalizacion*1.0/t1.duracion) <= (t2.penalizacion*1.0/t2.duracion);
}

class Solucion {

private:

    vector<Trabajo> trabajos;
    vector<int> orden;
    int num_hechos;
    int penalizacion;
    int duracion;
    int total;
    
    int est = 0;

    double estimador0() const { return 0.0; }

    double estimador1() const {
        double estimacion = 0;
        for ( int i = 0; i < total; i++) {
            if (!trabajos[i].terminado && trabajos[i].plazo < duracion + trabajos[i].duracion)
                estimacion += trabajos[i].penalizacion;
        }

        return estimacion;
    }

    /*double estimador2() const {
        int pen_max1 = 0, pen_max2 = 0;
        for (int i = 0; i < total; i++) {
            if (trabajos[i].terminado)
                pen_max1 += trabajos[i].penalizacion;
            else pen_max2 += trabajos[i].penalizacion;
        }

        return pen_max2 * (penalizacion * 1.0 / pen_max1);
    }*/

public:

    Solucion(const int tam_max) {
        total = tam_max;
        trabajos = vector<Trabajo>(tam_max);
        orden = vector<int>(tam_max);
        num_hechos = 0;
        penalizacion = 0;
        duracion = 0;
    }

    Solucion(vector<Trabajo> trab) {
        trabajos = trab;
        total = trab.size();
        orden = vector<int>(total);
        num_hechos = 0;
        penalizacion = 0;
        duracion = 0;

    }

    int getNumHechos() { return num_hechos;}

    int getTotal() { return total;}

    void inicializar(int k) {
        if ( orden.empty()) {
            orden[0]=k;
            trabajos[k].terminado = true;
            num_hechos++;
            duracion += trabajos[k].duracion;
            if ( duracion > trabajos[k].plazo)
                penalizacion += trabajos[k].penalizacion;
        }
    }

    Trabajo& operator[](int i) {
        return trabajos[i];
    }

    void planificar( int k ) {
        if (k < total) {
            orden[num_hechos] = k;
            num_hechos++;
            trabajos[k].terminado = true;
            duracion += trabajos[k].duracion;
            if ( duracion > trabajos[k].plazo)
                penalizacion += trabajos[k].penalizacion;
        }
    }

    bool todosHechos() {
        return num_hechos == total;
    }

    void procesaSolucion() {
        cout << "Orden de realizacion de los trabajos:" << endl;
        for (int i = 0; i < num_hechos; i++)
            cout << orden[i] <<  " ";
        cout << endl;
        cout << "Penalizacion total = " << penalizacion << endl;
    }

    int getPenalizacion() const { return penalizacion;}

    // Primera solución obtenida por algoritmo Greedy
    Solucion solucionGreedy() {
        Solucion primera_sol(trabajos);
        while( primera_sol.getNumHechos() < primera_sol.getTotal()) {
            int pos_mejor = 0;
            double min_pen = INFINITY;
            for(int i = 0; i < total; i++) {
                if (!primera_sol[i].terminado && primera_sol[i].penalizacion < min_pen) {
                    min_pen = primera_sol[i].penalizacion;
                    pos_mejor=i;
                } 
            }
            primera_sol.planificar(pos_mejor);
        }

        return primera_sol;
    }

    double estimador() const {
        double estimacion;
        switch(est) {
            case 1:
                estimacion = estimador1();
                break;
            /*case 2:
                estimacion = estimador2();
                break;*/
            default:
                estimacion = estimador0();
                break;
        }

        return estimacion;

    }

    void setEstimador(int estimador) { est = estimador; }

    bool operator<( const Solucion &sol2) const {
        return (getPenalizacion() + estimador() < sol2.getPenalizacion()  + sol2.estimador());
    }


};



Solucion algoritmoBB( vector<Trabajo> trabajos, int estimador) {
    priority_queue<Solucion> Q;
    Solucion enodo(trabajos),mejor_solucion(trabajos);
    enodo.setEstimador(estimador);
    mejor_solucion.setEstimador(estimador);
    mejor_solucion=mejor_solucion.solucionGreedy();
    int mejor_penalizacion = mejor_solucion.getPenalizacion();
    Q.push(enodo);
    while(!Q.empty()) {
        enodo = Q.top();
        Q.pop();

        if(enodo.todosHechos()) {
            // Es solucion completa
            if ( mejor_penalizacion > enodo.getPenalizacion()) {
                mejor_solucion = enodo;
                mejor_penalizacion = mejor_solucion.getPenalizacion();
            }
        }
        else {
            Solucion aux=enodo;
            aux.setEstimador(estimador);
            for (int i = 0; i < enodo.getTotal(); i++) {
                if (!enodo[i].terminado && enodo.getPenalizacion()
                    + enodo.estimador() <= mejor_penalizacion) {
                    aux = enodo;
                    aux.planificar(i);
                    Q.push(aux);
                }
            }
        }
    }

    return mejor_solucion;
}


int main(int argc, char* argv[]) {

    const string FICH_DEF="datos.dat";
    string fich = FICH_DEF;
    int VECES=5;
    int estimador = 0;
    if ( argc > 1) {
        estimador = atoi(argv[1]);

        if (argc > 2)
            fich = argv[2];

    }
	
    ifstream entrada;
    entrada.open(fich);

    if (!entrada) {
        cerr << "ERROR: no se pudo abrir el archivo" << endl;
        exit(-1);
    }

    int num;
    
    Trabajo aux;

    entrada >> num;
    vector<Trabajo> trabajos(num);
    for (int i = 0; i<num; i++) {
        entrada >> aux.duracion;
        entrada >> aux.plazo;
        entrada >> aux.penalizacion;
        trabajos[i]=aux;
    }


clock_t t_antes = clock();

for (int i = 0; i < VECES; i++)
    Solucion optima = algoritmoBB(trabajos,estimador);

 clock_t t_despues = clock();

    cout << "\t" << (double)(t_despues-t_antes) / (CLOCKS_PER_SEC*VECES)<<endl;
    
    return 0;
}
