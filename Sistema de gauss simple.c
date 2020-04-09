

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

//Declaracion de protipos de la funcion 
void analisis_de_datos( double **M, int fila, int columna, double B[] );
void eliminacion_por_metodo_de_gauss( double **M, int fila, int columna, double v[] );
void intercambiarfilaas( double **M, int columna, int k, int max );
void imprimirMatriz1( double **M, int fila, int columna, double v[] );
void imprimirMatriz2( double **M, int fila, int columna, double v[] );
void impresion_de_resultados( double v[], int fila );
void comprobar();

int main()
{
    int fila, columna;
    char op;

    cout << "\n Ingresa el numero de ecuaciones... "<<endl;
    cin >> fila;
    columna = fila;

    double** A = new double*[fila];
    for( int i = 0; i < fila; i++ )
        A[i] = new double[columna];

    double B[fila];

    analisis_de_datos( A, fila, columna, B );

    imprimirMatriz1( A, fila, columna, B );
      cout << "\nTu sistema de ecuaciones es correcto (s/n)? ...\n"<<endl;
      cin >> op;
      if (op=='s')
      {
    imprimirMatriz2( A, fila, columna, B );
    eliminacion_por_metodo_de_gauss( A, fila, columna, B );
    cout << "\nComprobando resultados ...\n"<<endl;
    imprimirMatriz1( A, fila, columna, B );

      }
      else
      {
          cout << "\nError vuelva a intentarlo \n"<<endl;
          return 0;
      }

    return 0;
}

void analisis_de_datos( double **A, int fila, int columna, double B[] )
{
    //cout << "\nIntroduzca coeficientes de la ecuacion:\n";

    for( int i = 0; i < fila; i++ ){
        //cout << "\nfilaa " << i + 1 << ":\n";
        for( int j = 0; j < columna; j++ ) {
            cout<<" "<<"Ingresa a["<<i<<"]["<<j<<"] = ";
            cin >> A[i][j];

        }
    }
    cout << "\nIgualdad de ecuacion\n";
    for(int i = 0; i < fila; i++ ){
        cout<<" "<<"Ingresa b["<<i<<"] = ";
        cin >> B[i];
    }
     cout << "\n";
      cout << "\n";
    //cout << "\nPaso 2\n";
   /* for( int i = 0; i < fila; i++){
        for( int j = 0; j < columna; j++){
            cout << M[i][j] << "x" <<i<< "   ";
        }
        cout << "    " << v[i] << "\n";
    }*/

}

void eliminacion_por_metodo_de_gauss( double **A, int fila, int columna, double B[] )
{
    int max;
    int N = fila;
    double factor, temp;

    for( int k = 0; k < N; k++ ){
        max = k;
        for( int i = k + 1; i < N; i++ )
            if( abs( A[i][k] ) > abs( A[max][k] ) )
                max = i;

        intercambiarfilaas( A, columna, k, max );
        temp = B[k];
        B[k] = B[max];
        B[max] = temp;

        for( int i = k + 1; i < N; i++ ) {
            factor = A[i][k] / A[k][k];
            B[i] -= factor * B[k];

            for( int j = k; j < N; j++ )
                A[i][j] -= factor * A[k][j];

        }
    }
    imprimirMatriz2( A, fila, columna, B );

    double solucion[fila] = { 0.0 };
    double suma;

    for (int i = N - 1; i >= 0; i-- ){

        suma = 0.0;

        for( int j = i + 1; j < N; j++ )
            suma += A[i][j] * solucion[j];

        solucion[i] = (B[i] - suma) / A[i][i];

    }
    impresion_de_resultados( solucion, fila );
}

void intercambiarfilaas( double **M, int columna, int k, int max )
{
    double temp[columna];

    for( int i = k; i < columna; i++ ) {
            temp[i] = M[k][i];
            M[k][i] = M[max][i];
            M[max][i] = temp[i];
    }
}

void imprimirMatriz1(double **M, int fila, int columna, double v[] )
{

    for( int k = 0; k < fila; k++){
        for( int l = 0; l < columna; l++){
            cout << M[k][l] <<"x"<<l+1<< " + ";
        }
        cout << " = " << v[k] << "\n";
    }
    cout << "\n";

}

void imprimirMatriz2( double **M, int fila, int columna, double v[] )
{

    cout << setprecision(3) << fixed;
    cout << "\nPaso 2\n";
    for( int i = 0; i < fila; i++){
        for( int j = 0; j < columna; j++){
            cout << M[i][j] << "    ";
        }
        cout << "    " << v[i] << "\n";
    }
    cout << "\n";
}

void impresion_de_resultados( double v[], int fila )
{
    cout << "\nPaso 3 ";
    for(int i=fila-1;i>-1;i--)
     // for (int k=0;k<fila;k++)
        cout << "\nx[" << i << "]= " << v[i];

    cout << endl;
}
