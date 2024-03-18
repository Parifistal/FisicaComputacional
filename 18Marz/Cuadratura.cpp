#include<iostream>
#include<cmath>
#include<fstream>

int main(){
    std::ofstream datafile("resultados.dat");

    for(int N=1; N<=10000; ++N){
        double integral=0.0; //Iniciando el valor de la integral.
        double a=0.0;  //Limite inferior.
        double b=1.0;   //Limite superior.
        double h=(b-a)/N;   //Ancho del paso
        for(int i=0;i<N;++i){
            double xi=a+(i+0.5)*h;  //Calculamos el punto medio del sub-intervalo.
            integral+=100*std::pow(xi,2)*std::cos(20*xi);
        }
        integral*=h;    //Multiplicar por el ancho del sub-intervalo.
        double integral_exacta=4.7459;
        datafile<<N<<" "<<integral<<" "<<integral_exacta<<std::endl;
    }
    datafile.close();

    std::ofstream scriptFile("grafico_integral_aproximada.gp");
    scriptFile<<"set term png\n";
    scriptFile<<"set output 'grafico_integral_aproximada.png' \n";
    scriptFile<<"set xlabel 'N'\n";
    scriptFile<<"set ylabel 'Integral' \n";
    scriptFile<<"set logscale x\n";
    scriptFile<<"plot 'resultados.dat' u 1:2 w l title 'Integral aproximada' \n";
    scriptFile.close();

    std::ofstream scriptFile2("grafico_integral_exacta.gp");
    scriptFile2<<"set term png\n";
    scriptFile2<<"set output 'grafico_integral_exacta.png' \n";
    scriptFile2<<"set xlabel 'N'\n";
    scriptFile2<<"set ylabel 'Integral' \n";
    scriptFile2<<"set logscale x\n";
    scriptFile2<<"plot 'resultados.dat' u 1:3 w l title 'Valor exacto de la integral' \n";
    scriptFile2.close();

//Ejecutar Gnuplot
system("gnuplot grafico_integral_aproximada.gp");
system("gnuplot grafico_integral_exacta.gp");

return 0;


}