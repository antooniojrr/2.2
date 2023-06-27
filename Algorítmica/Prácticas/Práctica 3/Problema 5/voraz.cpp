

#include<iostream>
#include<fstream>
#include<cmath>
#include<set>


using namespace std;

/*
*   @brief Clase para representar un grafo no direccionado, conexo y ponderado, consistente en distintos nodos con aristas determinadas entre ellos
*   con un peso también establecido, ya sea positivo o negativo
*/
class Grafo {

    private:
    int nodos;
    double **M;
    const double PESOMAX=MAXFLOAT;

    public:
    
    Grafo() {nodos=0; M=nullptr;}

    Grafo(int n) {
        nodos=n;
        M=new double*[n];
        // Solo trabajamos con la triangular inferior
        for (int i = 0; i < n; i++) {
            M[i]=new double[i];
            for(int j = 0; j < i; j++)
                    M[i][j]=PESOMAX;
        }
    }

    Grafo(string data) {
        ifstream entrada;
        entrada.open(data);
        if(!entrada) {
            cerr << "Error: no se ha podido abrir " << data << endl;
            nodos=0;
            M=nullptr;
        }

        else {
            entrada >> nodos;
            M=new double*[nodos];
            // Solo trabajamos con la triangular inferior
            for (int i = 0; i < nodos; i++) {
                M[i]=new double[i];
                for(int j = 0; j < i; j++)
                    M[i][j]=PESOMAX;
            }
            int i,j;
            double value;
            while(entrada >> i) {
                entrada >> j;
                entrada >> value;
                setWeight(i,j,value);
            }
            entrada.close();
        }
    }

    double getWeight(int i, int j) {
        double value=-1;
        if ( j < i)
            value=M[i][j];
        else if (i < j)
            value=M[j][i];
        return value;
    }

    void setWeight(int i, int j, double value) {
        if ( j < i)
            M[i][j]=value;
        else if (i < j)
           M[j][i]=value;
    }

    void useEdge(int i, int j) {
        setWeight(i,j,PESOMAX);
    }

    int getNodes() { return nodos;}

    double getTotalWeight() {
        double suma=0;
        for (int i = 0; i < nodos; i++) {
            for (int j = 0; j < i; j++) {
                if (getWeight(i,j) != PESOMAX)
                    suma += getWeight(i,j);
            }
        }
        return suma;
    }

    const double getPesoMax() { return PESOMAX;}

    Grafo operator=(Grafo g) {
        nodos=g.getNodes();
        free(M);
        M=new double*[nodos];
        // Solo trabajamos con la triangular inferior
        for (int i = 0; i < nodos; i++) {
            M[i]=new double[i];
            for(int j = 0; j < i; j++)
                setWeight(i,j,g.getWeight(i,j));     
        }
        return (*this);
    }

    string toString() {
        string grafo="Nodos = ";
        int num=getNodes();
        int aristas=0;
        grafo += to_string(num);
        grafo += "\n";
        for (int i = 0; i < num+1; i++) {
            for (int j = i+1; j < num; j++) {
                if (getWeight(i,j)!=PESOMAX) {
                    grafo += "\tArista(";
                    grafo += to_string(i);
                    grafo += ",";
                    grafo += to_string(j);
                    grafo += "):\tPeso = ";
                    grafo += to_string(getWeight(i,j));
                    grafo += "\n";
                    aristas++;
                }
            }
        }
        grafo += "Aristas = " + to_string(aristas) + "\n";
        grafo += "Peso Total = " + to_string(getTotalWeight()) + "\n";

        return grafo;
    }

};


Grafo getParcialRoot(Grafo G, int node0) {
    int nodos=G.getNodes();
    Grafo result(nodos);

    set<int> no_usados;
    for(int i=0; i<nodos; i++)
        no_usados.insert(i);
    no_usados.erase(node0);

    set<int> usados;
    usados.insert(node0);

    pair<int,int> arista_fav(-1,-1);
    double min_value;
    while(!no_usados.empty()) {
        min_value=G.getPesoMax();
        for(auto it=usados.begin(); it!=usados.end(); it++) {
            for(auto it2=no_usados.begin(); it2!=no_usados.end(); it2++) {
                if (G.getWeight(*it,*it2) < min_value) {
                    arista_fav.first=*it;
                    arista_fav.second=*it2;
                    min_value = G.getWeight(*it,*it2);
                }
            }
        }
        result.setWeight(arista_fav.first,arista_fav.second,min_value);
        no_usados.erase(arista_fav.second);
        usados.insert(arista_fav.second);
    }

    double peso;
    for (int i=0; i<nodos-1; i++ ) {
        for (int j=i+1; j<nodos; j++) {
            peso=G.getWeight(i,j);
            if (peso<0 && result.getWeight(i,j)!=peso)
                result.setWeight(i,j,peso);
        }
    }

    return result;
}

Grafo getParcial(Grafo G) {
    int nodos = G.getNodes();
    Grafo result=getParcialRoot(G,0),aux(nodos);
    
    for (int i = 1; i<nodos; i++) {
        aux=getParcialRoot(G,i);
        if (aux.getTotalWeight() < result.getTotalWeight())
            result=aux;

    }

    return result;

}


int main(int argc, char* argv[]) {
    const string FICH_DEFAULT="nodos.dat";
    string fich;
    if (argc < 2) {
        cout << "Tomando fichero por defecto: \"" << FICH_DEFAULT << "\"" << endl;
        fich = FICH_DEFAULT;
    }
    else fich = argv[1];

    Grafo G(fich);

    cout << "Grafo leido:\n" << G.toString();

    Grafo result=getParcial(G);

    cout << "Parcial con menos peso obtenida:\n" << result.toString();

    return 0;

}
