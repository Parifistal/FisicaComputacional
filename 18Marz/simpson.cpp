#include<iostream>
#include<cmath>
#include<fstream>

//Función para integrar
double funcion(double x){
    return 100*pow(x,2)*cos(20*x);
}

// Calculo de la integral bajo la regla de simpson

double Simpson(double a, double b, int N){
    double h=(b-a)/N;
    double suma= funcion(a)+funcion(b);
    for(int i=1;i<N;i++){
        double xi=a+(i*h);
        if (i % 2 == 0){
            suma+= 2* funcion(xi);
        }
        else{
            suma+=4*funcion(xi);
        }
    }
    return (h/3)*suma;

}

// Calculo de la integral bajo la regla trapezoidal.

double Trapecio(double a, double b, int N){
    double h=(b-a)/N;
    double suma = funcion(a)+funcion(b);
    for(int i=0;i<N;i++){
        double xi=a+i+h;
        suma+=2*funcion(xi);
    }
    return (h/2)+suma;
}

int main(){
    std::ofstream datafile("Resultados_Metodo_Simpson.dat");
    std::ofstream errorfile("Error_Metodo_Simpson.dat");
    std::ofstream datafiletrapecio("Resultados_Metodo_Trapezoidal.dat");
    std::ofstream errorfiletrapecio("Error_Metodo_Trapezoidal.dat");

    for(int N=1; N<10000; ++N){
        double integral= Simpson(0.0,1.0,N);
        double integra_exacta=4.7459436532766439;
        double error_porcentual= 100* std::abs(integral - integra_exacta)/integra_exacta;
        double integral2= Trapecio(0.0,1.0,N);
        double error_porcentual_trapecio=100*(integral2-integra_exacta)/integra_exacta;
        datafile<<N<<" "<<integral<<" "<<integra_exacta<<std::endl;
        errorfile<<N<<" "<<error_porcentual<<std::endl;
        datafiletrapecio<<N<<" "<<integral2<<" "<<integra_exacta<<std::endl;
        errorfiletrapecio<<N<<" "<<error_porcentual_trapecio<<std::endl;
    }
    datafile.close();
    errorfile.close();
    datafiletrapecio.close();
    errorfiletrapecio.close();

    std::ofstream scriptFiles("Grafico_integral_VS_Metodo_Simpson.gp");
    scriptFiles<<"set term png\n";
    scriptFiles<<"set output 'Grafico_integral_VS_Metodo_Simpson.png' \n";
    scriptFiles<<"set xlabel 'N' \n";
    scriptFiles<<"set ylabel 'Integral' \n";
    scriptFiles<<"set logscale x\n";
    scriptFiles<<"plot 'Resultados_Metodo_Simpson.dat' u 1:2 w title 'Integral aproximada', '' u 1:3 w l title 'Valor exacto' \n";
    scriptFiles.close();
// Grafico integral contra integral medoto trapezoidal.
    std::ofstream scriptFiles9("Grafico_integral_VS_Metodo_Trapezoidal.gp");
    scriptFiles9<<"set term png\n";
    scriptFiles9<<"set output 'Grafico_integral_VS_Metodo_Trapezoidal.png' \n";
    scriptFiles9<<"set xlabel 'N' \n";
    scriptFiles9<<"set ylabel 'Integral' \n";
    scriptFiles9<<"set logscale x\n";
    scriptFiles9<<"plot 'Resultados_Metodo_Trapezoidal.dat' u 1:2 w title 'Integral aproximada', '' u 1:3 w l title 'Valor exacto' \n";
    scriptFiles9.close();


// Generar los datos para la grafica.
    std::ofstream datafile2("datos.dat");
    int N_plot=10;
    double h_plot=(1.0-0.0)/N_plot;
    for (double x=0.0; x<=1.0; x+=0.01){
        datafile2<<x<<" "<<funcion(x)<<std::endl;
        datafile2<<x<<" "<<0.0<<std::endl;
        datafile2<<std::endl;
    }
    datafile2.close();


    
    std::ofstream scriptFiles2("Grafico_funcion_rectangulos_metodo_simpson.gp");
    scriptFiles2<<"set term png\n";
    scriptFiles2<<"set output 'Grafico_integral_VS_Metodo_Simpson_rectangulos.png' \n";
    scriptFiles2<<"set xlabel 'x' \n";
    scriptFiles2<<"set ylabel 'f(x)' \n";
    scriptFiles2<<"set logscale x\n";
    scriptFiles2<<"plot 'datos.dat' u 1:2 w title 'Funcion', '' w boxes title 'Rectangulos' \n";
    scriptFiles2.close();
//Grafico funcion rectangulos metodo trapezoidal
    std::ofstream scriptFiles4("Grafico_funcion_rectangulos_metodo_trapezoidal.gp");
    scriptFiles4<<"set term png\n";
    scriptFiles4<<"set output 'Grafico_integral_VS_Metodo_Trapezoidal.png' \n";
    scriptFiles4<<"set xlabel 'x' \n";
    scriptFiles4<<"set ylabel 'f(x)' \n";
    scriptFiles4<<"set logscale x\n";
    scriptFiles4<<"plot 'datos.dat' u 1:2 w title 'Funcion', '' w boxes title 'Rectangulos' \n";
    scriptFiles4.close();

    // Grafica para los errores simpson.
    std::ofstream scriptFiles3("Grafico_error_porcentual_metodo_simpson.gp");
    scriptFiles3<<"set term png\n";
    scriptFiles3<<"set output 'Grafico_error_porcentual_metodo_simpson.png' \n";
    scriptFiles3<<"set xlabel 'N' \n";
    scriptFiles3<<"set ylabel 'Error porcentual' \n";
    scriptFiles3<<"set logscale x\n";
    scriptFiles3<<"plot 'Error_Metodo_Simpson.dat' u 1:2 w title 'Error Porcentual' \n";
    scriptFiles3.close();

        // Grafica para los errores Trapezoidal.
    std::ofstream scriptFiles7("Grafico_error_porcentual_metodo_trapezoidal.gp");
    scriptFiles7<<"set term png\n";
    scriptFiles7<<"set output 'Grafico_error_porcentual_metodo_trapezoidal.png' \n";
    scriptFiles7<<"set xlabel 'N' \n";
    scriptFiles7<<"set ylabel 'Error porcentual' \n";
    scriptFiles7<<"set logscale x\n";
    scriptFiles7<<"plot 'Error_Metodo_Trapezoidal.dat' u 1:2 w title 'Error Porcentual' \n";
    scriptFiles7.close();
    // Ejecutar Gnuplot
    system("gnuplot Grafico_integral_VS_Metodo_Simpson.gp");
    system("gnuplot Grafico_funcion_rectangulos_metodo_simpson.gp");
    system("gnuplot Grafico_error_porcentual_metodo_simpson.gp");
    system("gnuplot Grafico_integral_VS_Metodo_Trapezoidal.gp");
    system("gnuplot Grafico_funcion_rectangulos_metodo_trapezoidal.gp");
    system("gnuplot Grafico_error_porcentual_metodo_trapezoidal.gp");
    return 0;
    }