#include<iostream>
#include<cmath>
#include<fstream>

// Primero se definen los valores constantes y las igualdades.

const double epsilon=0.0167; // Valor determinado en las diapositivas del parcial.
const double R=1.496e11; 
const double a=R; // El e es una forma de notacion para representar el 10^{x} valor en c++.
const double M_s=1.989e30; // Masa del sol en kg.
const double v_0=30300; // Valor de velocidad de la tierra en m/s.
const double M_t=5.972e24; // Masa de la tierra en kg.
const double G=6.67430e-11;
const double mu=(M_s*M_t)/(M_s+M_t); // El valor de mu se determina gracias a la ecuación proporcionada por el ejercicio.
const double T = sqrt((pow(R,3)/(2*G*mu)));
const double E=(0.5)*v_0*mu+(G*M_s*mu)/R;
const double R_max=1.5214e11;
const double R_min=1.4705e11;
const double L = R * mu * v_0;
const double a_prima = (1-pow(epsilon,2));

// Definimos la función a solucionar con integración númerica para hallar r(\theta).

double dr_theta(double L, double E, double r){
    if(r==0){
        return 0;
    }

    double Dividendo= pow(L,2)/(mu*pow(r,2));
    double Discriminante = (2/mu)*(E-(pow(L,2)/mu*pow(r,2))+(G*M_s*M_t)/r);
    double raiz;
    if(Discriminante < 0){
        return raiz=abs(Discriminante);
    }
    raiz=sqrt(Discriminante);
    return Dividendo/raiz;
}

double simpsonr_theta(double a, double b, int N, double L_prima, double E_prima){
    double h=(b-a)/N; // Se determina el valor del paso, incluyendo los parametros de a y b, obtenidos mediante la integral del ejercicio.
    double suma= dr_theta(a, L_prima, E_prima)+ dr_theta(b, L_prima, E_prima); //Se determina el primer y ultimo valor de la integral númerica.
    for(int i=1;i<N;i++){ //Se determina el valor de los pasos o avance en el que se dividiran los valores de x.
        double xi=a+(i*h);
        if (i % 2 ==0){ //Se determina la diferencia de pares e inpares gracias a la operación de residuo.
            suma+= 2*dr_theta(xi, L_prima, E_prima);
        }
        else{
            suma+=4*dr_theta(xi, L_prima, E_prima);
        }
    }
    return (h/3)*suma;
}
 
// Metodo del Trapecio.

double Trapecior_theta(double a, double b, int N, double L_prima, double E_prima){
    double h=(b-a)/N;
    double suma= dr_theta(a, L_prima, E_prima)+ dr_theta(b, L_prima, E_prima); 
    for(int i=1;i<N;i++){ 
        double xi=a+(i*h);
            suma+= 2*dr_theta(xi, L_prima, E_prima);
    }
    return (h/2)*suma;
}

// Cuadratura rectangular.

double Cuadraturar_theta(double a, double b, int N, double L_prima, double E_prima){
    double h=(b-a)/N;
    double suma=1; // El valor inicial se tomo de las diapositivas del ejercicio.
    for(int i=0;i<N;i++){
        double xi=a+i*h;
        suma+=dr_theta(xi, L_prima, E_prima);
    }
    return h*suma;
}

// Regla de simpson 3/8 compuesta.

double Simpson38r_theta(double a, double b, int N, double L_prima, double E_prima){
    double h=(b-a)/N;
    double suma= dr_theta(a, L_prima, E_prima)+ dr_theta(b, L_prima, E_prima); //Se determina el primer y ultimo valor de la integral númerica.
    for(int i=1;i<N;i++){ //Se determina el valor de los pasos o avance en el que se dividiran los valores de x.
        double xi=a+(i*h);
        if (i % 3 ==0){ //Se determinan los multiplos de 3 y asi se catalogan las multiplicaciones de cada valor de la sumatoria.
            suma+= 2*dr_theta(xi, L_prima, E_prima);
        }
        else{
            suma+=3*dr_theta(xi, L_prima, E_prima);
        }
    }
    return (3*h/8)*suma;
}




int main(){
    std::ofstream datosSimpsonr_theta("Resultados_Metodo_Simpson_radio_theta.dat");
    std::ofstream datosTrapecior_theta("Resultados_Metodo_Trapecio_radio_theta.dat");
    std::ofstream datosCuadraturar_theta("Resultados_Metodo_Cuadratura_radio_theta.dat");
    std::ofstream datosSimpson38r_theta("Resultados_Metodo_Simpson38_radio_theta.dat");
    std::ofstream datosRealesr_theta("Resultado_Solucion_Analitica.dat");
    std::ofstream datosComparacionr_theta("Comparacion_Graficas.dat");
    for (int N = 1; N < 10000; ++N) { 
            
            double r_theta1 = simpsonr_theta(R_min, R_max, N, L, E);
            double r_theta2 = Trapecior_theta(R_min, R_max, N, L, E);
            double r_theta3 = Cuadraturar_theta(R_min, R_max, N, L, E);
            double r_theta4 = Simpson38r_theta(R_min, R_max, N, L, E);
            double r_real = (a_prima)/(1+epsilon*cos(N));
        
        datosSimpsonr_theta<<N<<" "<<r_theta1<<std::endl;
        datosTrapecior_theta<<N<<" "<<r_theta2<<std::endl;
        datosCuadraturar_theta<<N<<" "<<r_theta3<<std::endl;
        datosSimpson38r_theta<<N<<" "<<r_theta4<<std::endl;
        datosRealesr_theta<<N<<" "<<r_real<<std::endl;
        datosComparacionr_theta<<N<<" "<<r_real<<" "<<r_theta1<<" "<<r_theta2<<" "<<r_theta3<<" "<<r_theta4<<std::endl;

}
datosSimpsonr_theta.close();
datosTrapecior_theta.close();
datosCuadraturar_theta.close();
datosSimpson38r_theta.close();
datosRealesr_theta.close();
datosComparacionr_theta.close();


// Generación de graficas a base de Gnuplot.

// Graficas para Radio vs Theta con los 4 metodos.
std::ofstream Resultado_Solucion_Analitica("Resultado_Solucion_Analitica.gp");
Resultado_Solucion_Analitica <<"set output 'Resultado_Solucion_Analitica.png'\n";
Resultado_Solucion_Analitica <<"set title 'Trayectoria de la Tierra'\n";
Resultado_Solucion_Analitica <<"set xlabel 'Índice de los datos'\n";
Resultado_Solucion_Analitica <<"set ylabel 'Radio (m)'\n";
Resultado_Solucion_Analitica <<"set grid \n";
Resultado_Solucion_Analitica <<"plot 'Resultado_Solucion_Analitica.dat' using 1:2 with lines ls 1 title 'Trayectoria de la Tierra'";
Resultado_Solucion_Analitica.close();

std::ofstream Grafica_Simpson_Radio_Theta("Grafico_Simpson_Radio_theta.gp");
Grafica_Simpson_Radio_Theta <<"set output 'Grafico_Simpson_Radio_theta.png'\n";
Grafica_Simpson_Radio_Theta <<"set title 'Trayectoria de la Tierra'\n";
Grafica_Simpson_Radio_Theta <<"set xlabel 'Índice de los datos'\n";
Grafica_Simpson_Radio_Theta <<"set ylabel 'Radio (m)'\n";
Grafica_Simpson_Radio_Theta <<"set grid \n";
Grafica_Simpson_Radio_Theta <<"plot 'Resultados_Metodo_Simpson_radio_theta.dat' using 1:2 with lines ls 1 title 'Trayectoria de la Tierra'";
Grafica_Simpson_Radio_Theta.close();


std::ofstream Grafica_Trapecio_Radio_Theta("Grafico_Trapecio_Radio_theta.gp");
Grafica_Trapecio_Radio_Theta <<"set output 'Grafico_Tapecio_Radio_theta.png'\n";
Grafica_Trapecio_Radio_Theta <<"set title 'Trayectoria de la Tierra'\n";
Grafica_Trapecio_Radio_Theta <<"set xlabel 'Índice de los datos'\n";
Grafica_Trapecio_Radio_Theta <<"set ylabel 'Radio (m)'\n";
Grafica_Trapecio_Radio_Theta <<"set grid \n";
Grafica_Trapecio_Radio_Theta <<"plot 'Resultados_Metodo_Trapecio_radio_theta.dat' using 1:2 with lines ls 1 title 'Trayectoria de la Tierra'";
Grafica_Trapecio_Radio_Theta.close();

std::ofstream Grafica_Cuadratura_Radio_Theta("Grafico_Cuadratura_Radio_theta.gp");
Grafica_Cuadratura_Radio_Theta <<"set output 'Grafico_Cuadratura_Radio_theta.png'\n";
Grafica_Cuadratura_Radio_Theta <<"set title 'Trayectoria de la Tierra'\n";
Grafica_Cuadratura_Radio_Theta <<"set xlabel 'Índice de los datos'\n";
Grafica_Cuadratura_Radio_Theta <<"set ylabel 'Radio (m)'\n";
Grafica_Cuadratura_Radio_Theta <<"set grid \n";
Grafica_Cuadratura_Radio_Theta <<"plot 'Resultados_Metodo_Cuadratura_radio_theta.dat' using 1:2 with lines ls 1 title 'Trayectoria de la Tierra'";
Grafica_Cuadratura_Radio_Theta.close();

std::ofstream Grafica_Simpson38_Radio_Theta("Grafico_Simpson38_Radio_theta.gp");
Grafica_Simpson38_Radio_Theta <<"set output 'Grafico_Simpson38_Radio_theta.png'\n";
Grafica_Simpson38_Radio_Theta <<"set title 'Trayectoria de la Tierra'\n";
Grafica_Simpson38_Radio_Theta <<"set xlabel 'Índice de los datos'\n";
Grafica_Simpson38_Radio_Theta <<"set ylabel 'Radio (m)'\n";
Grafica_Simpson38_Radio_Theta <<"set grid \n";
Grafica_Simpson38_Radio_Theta <<"plot 'Resultados_Metodo_Simpson38_radio_theta.dat' using 1:2 with lines ls 1 title 'Trayectoria de la Tierra'";
Grafica_Simpson38_Radio_Theta.close();


std::ofstream Grafica_Comparativa_Radio_Theta("Grafica_Comparativa_Radio_Theta.gp");
Grafica_Comparativa_Radio_Theta <<"set output 'Grafica_Comparativa_Radio_Theta.png'\n";
Grafica_Comparativa_Radio_Theta <<"set title 'Trayectoria de la Tierra'\n";
Grafica_Comparativa_Radio_Theta <<"set xlabel 'Índice de los datos'\n";
Grafica_Comparativa_Radio_Theta <<"set ylabel 'Radio (m)'\n";
Grafica_Comparativa_Radio_Theta <<"set grid \n";
Grafica_Comparativa_Radio_Theta <<"plot 'Comparacion_Graficas.dat' u 1:2 w l title 'Real', '' u 1:3 w l title 'Simpson', '' u 1:4 w l title 'Trapezoidal', '' u 1:5 w l title 'Cuadraturas', '' u 1:6 w l title 'Simpson 3/8'";
Grafica_Comparativa_Radio_Theta.close();

//Ejecutar todos los archivos generados de Gnuplot.

system("gnuplot Grafico_Simpson_Radio_theta.gp");
system("gnuplot Grafico_Trapecio_Radio_theta.gp");
system("gnuplot Grafico_Cuadratura_Radio_theta.gp");
system("gnuplot Grafico_Simpson38_Radio_theta.gp");
system("gnuplot Resultado_Solucion_Analitica.gp");
system("gnuplot Grafica_Comparativa_Radio_Theta.gp");

return 0;
}