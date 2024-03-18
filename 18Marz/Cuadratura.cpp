#include<iostream>
#include<cmath>
#include<fstream>

//Funcion para integrar
double funcion(double x){
    return 100*pow(x,2)*cos(20*x);

}

// Calculo de la integral aproximada bajo cuadratura rectangular

double cuadraturaRectangular(double a, double b, int N){
    double h=(b-a)/N;
    double suma=0.0;
    for(int i=0;i<N;i++){
        double xi=a+i*h;
        suma+=funcion(xi);
    }
    return h*suma;
}


int main(){
    std::ofstream datafile("resultados_cuadratura_rectangular.dat");

    for(int N=1; N<=10000; ++N){
        double integral= cuadraturaRectangular(0.0,1.0,N);
        double integral_exacta=4.7459;
        datafile<<N<<" "<<integral<<" "<<integral_exacta<<std::endl;
        }
    
    
    datafile.close();

    std::ofstream scriptFile("grafico_integral_vs_cuadratura_rectangular.gp");
    scriptFile<<"set term png\n";
    scriptFile<<"set output 'grafico_integral_vs_cuadratura_rectangular.png' \n";
    scriptFile<<"set xlabel 'N'\n";
    scriptFile<<"set ylabel 'Integral' \n";
    scriptFile<<"set logscale x\n";
    scriptFile<<"plot 'resultados_cuadratura_rectangular.dat' u 1:2 w l title 'Integral aproximada', '' u 1:3 w l title 'Valor exacto' \n";
    scriptFile.close();



//Ejecutar Gnuplot
system("gnuplot grafico_integral_vs_cuadratura_rectangular.gp");
system("gnuplot grafico_integral_vs_cuadratura_rectangular.gp");

return 0;


}