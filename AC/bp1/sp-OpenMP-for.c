#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
  #include <omp.h>
#else
  #define omp_get_thread_num() 0
#endif

/**
 * 
 Código para suma secuencial de 2 vectores SumaVectores.c
 * 
 */

#include <stdlib.h>	// biblioteca con funciones atoi(), malloc() y free()
#include <stdio.h>	// biblioteca donde se encuentra la función printf()
#include <time.h>	// biblioteca donde se encuentra la función clock_gettime() 

//Sólo puede estar definida una de las tres constantes VECTOR_ (sólo uno de los ... 
//tres defines siguientes puede estar descomentado):
//#define VECTOR_LOCAL	// descomentar para que los vectores sean variables ...
			// locales (si se supera el tamaño de la pila se ...
			// generará el error "Violación de Segmento")
#define VECTOR_GLOBAL // descomentar para que los vectores sean variables ...
			// globales (su longitud no estará limitada por el ...
			// tamaño de la pila del programa)
//#define VECTOR_DYNAMIC	// descomentar para que los vectores sean variables ...
			// dinámicas (memoria reutilizable durante la ejecución)

#ifdef VECTOR_GLOBAL
#define MAX 33554432	//=2^25
   
double v1[MAX], v2[MAX], v3[MAX]; 
#endif
/**
 * @file  SumaVectores.c  
 * @brief _Suma secuencial de dos vectores: v3 = v1 + v2_
 * 
 * @param int n=atoi(argv[1])  número de componentes a sumar
 * @return 0 upon exit success (print tiempo de cálculo de la suma de vectores, longitud vectores y resultados (primer y último componente del resultado para longitudes mayores que 9))
 *
 * **Compilación**
 * @code
	gcc  -fopenmp -O2  sp-OpenMP-for.c -o sp-OpenMP-for -lrt
    (-lrt: real time library, es posible que no sea necesario usar -lrt)
 * @endcode
*/
int main(int argc, char** argv){ 
  
  int i; 

  double cgt1,cgt2; double ncgt; //para tiempo de ejecución

  //Leer argumento de entrada (nº de componentes del vector)
  if (argc<2){	
    printf("Faltan nº componentes del vector\n");
    exit(-1);
  }
  
  unsigned int N = atoi(argv[1]);	// Máximo N =2^32-1=4294967295 (sizeof(unsigned int) = 4 B)
  #ifdef VECTOR_LOCAL
  double v1[N], v2[N], v3[N];   // Tamaño variable local en tiempo de ejecución ...
				// disponible en C a partir de C99 
  #endif
  #ifdef VECTOR_GLOBAL
  if (N>MAX) N=MAX;
  #endif
  #ifdef VECTOR_DYNAMIC
  double *v1, *v2, *v3;
  v1 = (double*) malloc(N*sizeof(double));// malloc necesita el tamaño en bytes
  v2 = (double*) malloc(N*sizeof(double));
  v3 = (double*) malloc(N*sizeof(double));
  if ((v1 == NULL) || (v2 == NULL) || (v2 == NULL)) {	
    printf("No hay suficiente espacio para los vectores \n");
    exit(-2);
  }
  #endif
 
  //Inicializar vectores
  #pragma omp parallel
  {
          #pragma omp for
	  for(i=0; i<N; i++){ 
	    v1[i] = N*0.1+i*0.1; v2[i] = N*0.1-i*0.1; 
	  }
  }
 
  int num_threads;
  cgt1 = omp_get_wtime();

  //Calcular suma de vectores e imprimir la suma de cada componente si N es pequeño
  #pragma omp parallel 
  {
          num_threads = omp_get_num_threads();
          #pragma omp for
	  for(i=0; i<N; i++) {
	    v3[i] = v1[i] + v2[i];
        if(N<20)
            printf ("\tv3[%i] = v1[%i] + v2[%i] = %f + %f = %f\n",i,i,i,v1[i],v2[i],v3[i]);
      }
  }
 
  cgt2 = omp_get_wtime();
  ncgt = cgt2 - cgt1;

  //Imprimir el tiempo de ejecución
  printf("%u %11.9f\t\n",N,ncgt);
 

  #ifdef VECTOR_DYNAMIC
  free(v1); // libera el espacio reservado para v1
  free(v2); // libera el espacio reservado para v2
  free(v3); // libera el espacio reservado para v3
  #endif
  return 0; 
}