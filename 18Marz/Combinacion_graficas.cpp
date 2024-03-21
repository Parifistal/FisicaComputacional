#include<iostream>
#include<cmath>
#include<fstream>

// Función para integrar
double funcion(double x){
    return 100*pow(x,2)*cos(20*x);
}

// Calculo de la integral metodo de Simpson
double Simpson(double a, double b, int N){
    double h = (b - a) / N;
    double suma = funcion(a) + funcion(b);
    for(int i = 1; i < N; i++){
        double xi = a + i * h;
        if (i % 2 == 0){
            suma += 2 * funcion(xi);
        }
        else{
            suma += 4 * funcion(xi);
        }
    }
    return (h / 3) * suma;
}

// Calculo de la integral metodo trapezoidal.
double Trapecio(double a, double b, int N){
    double h = (b - a) / N;
    double suma = funcion(a) + funcion(b);
    for(int i = 1; i < N; i++){
        double xi = a + i * h;
        suma += 2 * funcion(xi);
    }
    return (h / 2) * suma;
}

int main(){
    std::ofstream datafile("Comparacion_Metodos_Integracion.dat");

    for(int N = 1; N <= 10000; ++N){
        double integral_simpson = Simpson(0.0, 1.0, N);
        double integral_trapezoidal = Trapecio(0.0, 1.0, N);
        double integra_exacta = 4.7459436532766439;
        datafile << N << " " << integral_simpson << " " << integral_trapezoidal << " " << integra_exacta << std::endl;
    }
    datafile.close();

    std::ofstream scriptFiles("Grafico_Comparacion_Metodos_Integracion.gp");
    scriptFiles << "set term png\n";
    scriptFiles << "set output 'Grafico_Comparacion_Metodos_Integracion.png' \n";
    scriptFiles << "set xlabel 'N' \n";
    scriptFiles << "set ylabel 'Valor de la integral' \n";
    scriptFiles << "set logscale x\n";
    scriptFiles << "plot 'Comparacion_Metodos_Integracion.dat' u 1:2 w l title 'Simpson', '' u 1:3 w l title 'Trapezoidal', '' u 1:4 w l title 'Exacta' \n";
    scriptFiles.close();

    // Ejecutar Gnuplot
    system("gnuplot Grafico_Comparacion_Metodos_Integracion.gp");

    return 0;
}