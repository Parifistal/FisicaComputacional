#include<iostream>
#include<cmath>
#include<fstream>

// Valores:
double v_inicial=0;
double m=70;
double g=9.7;
double rho=1;
double A=0.6;
double delta=0.8;
double b=(rho*A*delta)/2;
double v_limite=sqrt((m*g)/b);
double v_negativo=(v_inicial-v_limite);
double v_positivo=(v_inicial+v_limite);
double t_inicial=0;
double posicion_inicial=0;
double posicion_final=100;
// Solución funcion Analitica:

double Velocidad_Analitica(double v_limite, double v_inicial, double t, double t_i){
    
    double Division;
    double potencia = (g/v_limite)*( t -t_i);
    double Dividendo= v_negativo*exp(potencia)+v_positivo*exp(-potencia);
    double Divisor = v_negativo*exp(potencia)-v_positivo*exp(-potencia);
    if(Divisor == 0){
        return Divisor=0;

    }
    else{
        Division= Dividendo/Divisor;
    }
    return -v_limite*(Division);

}

// Solucion Númerica:

double Derivada(double h, double v_inicial, int N){
    double ve;
    double suma;
    for(int i=0; i<N; i++){
    ve=v_inicial+(i*h);

    suma= (ve-v_inicial)/h;
}
return suma;
}



// Integración de la solución Analitico por medios númericos:

long double simpsonr_Posicion(double a, double b, int N, double v_limite, double v_inicial, double t_i){
    long double h=(b-a)/N; // Se determina el valor del paso, incluyendo los parametros de a y b, obtenidos mediante la integral del ejercicio.
    double suma= Velocidad_Analitica(a, v_limite, v_inicial, t_i)+ Velocidad_Analitica(b, v_limite, v_inicial, t_i); //Se determina el primer y ultimo valor de la integral númerica.
    for(int i=1;i<N;i++){ //Se determina el valor de los pasos o avance en el que se dividiran los valores de x.
        double xi=a+(i*h);
        if (i % 2 ==0){ //Se determina la diferencia de pares e inpares gracias a la operación de residuo.
            suma+= 2*Velocidad_Analitica(xi, v_limite, v_inicial, t_i);
        }
        else{
            suma+=4*Velocidad_Analitica(xi, v_limite, v_inicial, t_i);
        }
    }
    return (h/3)*suma;
}

int main(){

    std::ofstream datosVelocidadvsTiempo_Analitico("Datos_Velocidad_vs_Tiempo_Analitico.dat");
    std::ofstream datosVelocidadvsTiempo_Numerico("Datos_Velocidad_vs_Tiempo_Numerico.dat");
    std::ofstream datosErrorVelocidadvsTiempo("Datos_Error_Velocidad_vs_Tiempo_Numerico_vs_Analitico.dat");
    std::ofstream datosPosicionvsTiempo_Analitico("Datos_Posicion_vs_Tiempo_Analitico.dat");
    



    
    double h=0.1;
    const int num_puntos_t = 1000;
    // Genera los valores de t
    double t[num_puntos_t];
    for (int i = 0; i < num_puntos_t; ++i) {
        t[i] = i * h;
    }
    
    for (int N = 1; N < 1000; ++N){for (int i = 0; i < num_puntos_t; ++i) { 
        long double TiempoActual=t[i];
        long double VelocidadNumerica=v_inicial+(h*Derivada(h, v_inicial, N));
        long double VelocidadAnalitica = Velocidad_Analitica(v_limite, v_inicial, TiempoActual, t_inicial);
        long double Posicion=simpsonr_Posicion(posicion_inicial, posicion_final, N, v_limite, v_inicial, t_inicial);

        datosVelocidadvsTiempo_Analitico<<VelocidadAnalitica<<" "<<TiempoActual<<std::endl;
        datosVelocidadvsTiempo_Numerico<<VelocidadNumerica<<" "<<TiempoActual<<std::endl;
        datosErrorVelocidadvsTiempo<<N<<" "<<VelocidadAnalitica<<" "<<VelocidadNumerica<<std::endl;
        datosPosicionvsTiempo_Analitico<<Posicion<<" "<<TiempoActual<<std::endl;

    }
    }



    datosVelocidadvsTiempo_Analitico.close();
    datosVelocidadvsTiempo_Numerico.close();
    datosErrorVelocidadvsTiempo.close();
    datosPosicionvsTiempo_Analitico.close();

    std::ofstream scriptFile("grafico_Velocidad_Tiempo_Analitico.gp");
    scriptFile<<"set term png\n";
    scriptFile<<"set output 'grafico_Velocidad_Tiempo_Analitico.png' \n";
    scriptFile<<"set xlabel 'Tiempo'\n";
    scriptFile<<"set ylabel 'Velocidad' \n";
    scriptFile<<"plot 'Datos_Velocidad_vs_Tiempo_Analitico.dat' u 1:2 title 'Solucion Analitica' \n";
    scriptFile.close();

    std::ofstream scriptFile2("grafico_Velocidad_Tiempo_Numerico.gp");
    scriptFile2<<"set term png\n";
    scriptFile2<<"set output 'grafico_Velocidad_Tiempo_Numerico.png' \n";
    scriptFile2<<"set xlabel 'Tiempo'\n";
    scriptFile2<<"set ylabel 'Velocidad' \n";
    scriptFile2<<"plot 'Datos_Velocidad_vs_Tiempo_Numerico.dat' u 1:2 title 'Solucion Numerica' \n";
    scriptFile2.close();

    std::ofstream scriptFile3("grafico_Velocidad_Tiempo_Error.gp");
    scriptFile3<<"set term png\n";
    scriptFile3<<"set output 'grafico_Velocidad_Tiempo_Error.png' \n";
    scriptFile3<<"set xlabel 'N'\n";
    scriptFile3<<"set ylabel 'Velocidad Analitica y NUmerica' \n";
    scriptFile3<<"plot 'Datos_Error_Velocidad_vs_Tiempo_Numerico_vs_Analitico.dat' u 1:2 w l title 'Analitica', '' u 1:3 w l title 'Numerica' \n";
    scriptFile3.close();

    std::ofstream scriptFile4("grafico_Posicion_Tiempo.gp");
    scriptFile4<<"set term png\n";
    scriptFile4<<"set output 'grafico_Posicion_Tiempo.png' \n";
    scriptFile4<<"set xlabel 'Tiempo'\n";
    scriptFile4<<"set ylabel 'Posicion' \n";
    scriptFile4<<"plot 'Datos_Posicion_vs_Tiempo_Analitico.dat' u 1:2 title 'Posicion vs Tiempo' \n";
    scriptFile4.close();

    system("gnuplot grafico_Velocidad_Tiempo_Analitico.gp");
    system("gnuplot grafico_Velocidad_Tiempo_Numerico.gp");
    system("gnuplot grafico_Velocidad_Tiempo_Error.gp");
    system("gnuplot grafico_Posicion_Tiempo.gp");

    return 0;

}