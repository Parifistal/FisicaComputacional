#include<iostream>
#include<cmath>
#include<fstream>

// Primero se definen los valores constantes y las igualdades.

const double epsilon=0.0167; // Valor determinado en las diapositivas del parcial.
const double R=1; 
const double a=R; // El e es una forma de notacion para representar el 10^{x} valor en c++.
const double M_s=1.989e30; // Masa del sol en kg.
const double v_0=30300; // Valor de velocidad de la tierra en m/s.
const double M_t=5.972e24; // Masa de la tierra en kg.
const double G=6.67430e-11;
const double mu=(M_s*M_t)/(M_s+M_t); // El valor de mu se determina gracias a la ecuación proporcionada por el ejercicio.
const double T = sqrt((pow(R,3)/(2*G*mu)));
const double E=(0.5)*v_0*mu+(G*M_s*mu)/R;
const double R_max=1.017;
const double R_min=0.983;
const double L = R * mu * v_0;
const double a_prima = (1-pow(epsilon,2));

// Definimos la función a solucionar con integración númerica para hallar r(\theta).

double dr_theta(double L, double E, double r){
    if(r==0){
        return 0; // Se formula un if para evitar errores de división sobre 0.
    }

    long double Multiplicador = (mu*pow(r,2))/L;
    long double Discriminante = (2/mu)*(E-(pow(L,2)/(2*mu*pow(r,2)))+(G*M_s*M_t)/r);
    double raiz;
    if(Discriminante < 0){
        return raiz=sqrt(abs(Discriminante)); //Nuevamente con un if se determina una forma para evitar errores,
    // de raices negativas.
    }
    else{
        raiz = sqrt(Discriminante);
    }
    
    return Multiplicador*raiz;
}

// Metodo de Simpson
long double simpsonr_theta(double a, double b, int N, double L, double E){
    long double h=(b-a)/N; // Se determina el valor del paso, incluyendo los parametros de a y b, obtenidos mediante la integral del ejercicio.
    double suma= dr_theta(a, L, E)+ dr_theta(b, L, E); //Se determina el primer y ultimo valor de la integral númerica.
    for(int i=1;i<N;i++){ //Se determina el valor de los pasos o avance en el que se dividiran los valores de x.
        double xi=a+(i*h);
        if (i % 2 ==0){ //Se determina la diferencia de pares e inpares gracias a la operación de residuo.
            suma+= 2*dr_theta(xi, L, E);
        }
        else{
            suma+=4*dr_theta(xi, L, E);
        }
    }
    return (h/3)*suma;
}
 
// Metodo del Trapecio.

double Trapecior_theta(double a, double b, int N, double L, double E){
    double h=(b-a)/N;
    long double suma= dr_theta(a, L, E)+ dr_theta(b, L, E); 
    for(int i=1;i<N;i++){ 
        double xi=a+(i*h);
            suma+= 2*dr_theta(xi, L, E);
    }
    return (h/2)*suma;
}

// Cuadratura rectangular.

double Cuadraturar_theta(double a, double b, int N, double L, double E){
    long double h=(b-a)/N;
    double suma=0.983; 
    for(int i=0;i<N;i++){
        double xi=a+i*h;
        suma+=dr_theta(xi, L, E);
    }
    return h*suma;
}

// Regla de Gauss.

double Gaussr_theta(double a, double b, double r, double L, double E){
    
    long double x[6]={-0.93246951, -0.66120938, -0.23861918, 0.23861918, 0.66120938, 0.93246951};
    long double w[6]={0.17132449, 0.36076157, 0.46791393, 0.46791393, 0.36076157, 0.17132449};
// Se determinan los valores de xi y los valores de peso w como vectores, para asi llamarlos posteriormente.
    long double suma;
    for(int i=0; i<6; ++i){
        long double xi=0.017*x[i]+1; //Se determina el cambio de la integral donde los valores son el resultado de 
//Aplicar la division y restas correspondientes tal y como induca la formula general de Gauss.
        suma=dr_theta(xi, L, E)*w[i];
    } // Tanto el x[i], como el w[i], se usan dentro del bucle for para asi obtener que se multipliquen 
// Todos los componentes que los conforman en la suma.
    return ((b-a)/2)*suma;
}

double r_real(double L, double E, double theta){
    long double C=G*M_s*M_t; //Se determina la siguiente igualdad para reducir escritura.
    long double arriba=(pow(L,2))/(mu*C);
    long double Determinante1 = 1+((2*E*pow(L,2))/(mu*pow(C,2))*sin(theta));
    long double raiz;
    if(Determinante1<0){
        raiz=sqrt(abs(Determinante1));
    }//Al igual que en anteriores casos se determina por medio de un if una forma de evitar valores de 
// Raices negativas.
    else{
        raiz=sqrt(Determinante1);
    }
    long double r= arriba/(1-raiz);
    return r;
}






int main(){// Se crean los documentos necesarios para poder guardar los datos generados por los metodos.
    std::ofstream datosSimpsonr_theta("Resultados_Metodo_Simpson_radio_theta.dat");
    std::ofstream datosTrapecior_theta("Resultados_Metodo_Trapecio_radio_theta.dat");
    std::ofstream datosCuadraturar_theta("Resultados_Metodo_Cuadratura_radio_theta.dat");
    std::ofstream datosGaussr_theta("Resultados_Metodo_Gauss_radio_theta.dat");
    std::ofstream datosRealesr_theta("Resultado_Solucion_Analitica.dat");
//Se determina una forma para obtener datos de Theta, conociendo que estos datos pueden variar de 0 a 360
    const int num_puntos_theta = 1000;

    // Rango de theta
    const double theta_min = 0.0;
    const double theta_max = 360.0;

    // Calcula el paso angular
    const double deltaTheta = (theta_max - theta_min) / (num_puntos_theta - 1);

    // Genera los valores de theta
    double theta[num_puntos_theta];
    for (int i = 0; i < num_puntos_theta; ++i) {
        theta[i] = i * deltaTheta;
    }

    for (int N = 1; N < 1000; ++N) { for (int i = 0; i < num_puntos_theta; ++i) { 
            
            long double r_theta1 = simpsonr_theta(R_min, R_max, N, L, E);
            long double r_theta2 = Trapecior_theta(R_min, R_max, N, L, E);
            long double r_theta3 = Cuadraturar_theta(R_min, R_max, N, L, E);
            long double r_theta4 = Gaussr_theta(R_min, R_max, N, L, E);
            long double r_realtheta = r_real(L, E, theta[i]);


// Generamos los valores en modo polar.
        long double x1=r_theta1*cos(theta[i]);
        long double x2=r_theta2*cos(theta[i]);
        long double x3=r_theta3*cos(theta[i]);
        long double x4=r_theta4*cos(theta[i]);
        long double x5=r_realtheta*cos(theta[i]);

        long double y1=r_theta1*sin(theta[i]);
        long double y2=r_theta2*sin(theta[i]);
        long double y3=r_theta3*sin(theta[i]);
        long double y4=r_theta4*sin(theta[i]);
        long double y5=r_realtheta*sin(theta[i]);
        



        datosSimpsonr_theta<<x1<<" "<<y1<<std::endl;
        datosTrapecior_theta<<x2<<" "<<y2<<std::endl;
        datosCuadraturar_theta<<x3<<" "<<y3<<std::endl;
        datosGaussr_theta<<x4<<" "<<y4<<std::endl;
        datosRealesr_theta<<x5<<" "<<y5<<std::endl;
        

                
    }       
    }

     
datosSimpsonr_theta.close();
datosTrapecior_theta.close();
datosCuadraturar_theta.close();
datosGaussr_theta.close();
datosRealesr_theta.close();




// Generación de graficas a base de Gnuplot.

// Graficas para Radio vs Theta con los 4 metodos.
std::ofstream Resultado_Solucion_Analitica("Resultado_Solucion_Analitica.gp");
Resultado_Solucion_Analitica<<"set term png\n";
Resultado_Solucion_Analitica<<"set output 'Resultado_Solucion_Analitica.png'\n";
Resultado_Solucion_Analitica<<"set xlabel 'Theta'\n";
Resultado_Solucion_Analitica<<"set ylabel 'Radio'\n";
Resultado_Solucion_Analitica<<"set logscale x\n";
Resultado_Solucion_Analitica<<"plot 'Resultado_Solucion_Analitica.dat' u 1:2 w l title 'Trayectoria de la Tierra'\n";
Resultado_Solucion_Analitica.close();

std::ofstream Grafica_Simpson_Radio_Theta("Grafico_Simpson_Radio_theta.gp");
Grafica_Simpson_Radio_Theta<<"set term png\n";
Grafica_Simpson_Radio_Theta<<"set output 'Grafico_Simpson_Radio_theta.png'\n";
Grafica_Simpson_Radio_Theta<<"set xlabel 'Theta'\n";
Grafica_Simpson_Radio_Theta<<"set ylabel 'Radio'\n";
Grafica_Simpson_Radio_Theta<<"set logscale x\n";
Grafica_Simpson_Radio_Theta<<"plot 'Resultados_Metodo_Simpson_radio_theta.dat' u 1:2 w l title 'Trayectoria de la Tierra'\n";
Grafica_Simpson_Radio_Theta.close();


std::ofstream Grafica_Trapecio_Radio_Theta("Grafico_Trapecio_Radio_theta.gp");
Grafica_Trapecio_Radio_Theta<<"set term png\n";
Grafica_Trapecio_Radio_Theta<<"set output 'Grafico_Tapecio_Radio_theta.png'\n";
Grafica_Trapecio_Radio_Theta<<"set xlabel 'Theta'\n";
Grafica_Trapecio_Radio_Theta<<"set ylabel 'Radio'\n";
Grafica_Trapecio_Radio_Theta<<"set logscale x\n";
Grafica_Trapecio_Radio_Theta<<"plot 'Resultados_Metodo_Trapecio_radio_theta.dat' u 1:2 w l title 'Trayectoria de la Tierra'\n";
Grafica_Trapecio_Radio_Theta.close();

std::ofstream Grafica_Cuadratura_Radio_Theta("Grafico_Cuadratura_Radio_theta.gp");
Grafica_Cuadratura_Radio_Theta<<"set term png\n";
Grafica_Cuadratura_Radio_Theta<<"set output 'Grafico_Cuadratura_Radio_theta.png'\n";
Grafica_Cuadratura_Radio_Theta<<"set xlabel 'Theta'\n";
Grafica_Cuadratura_Radio_Theta<<"set ylabel 'Radio (m)'\n";
Grafica_Cuadratura_Radio_Theta<<"set logscale x\n";
Grafica_Cuadratura_Radio_Theta<<"plot 'Resultados_Metodo_Cuadratura_radio_theta.dat' u 1:2 w l title 'Trayectoria de la Tierra'\n";
Grafica_Cuadratura_Radio_Theta.close();

std::ofstream Grafica_Gauss_Radio_Theta("Grafico_Gauss_Radio_theta.gp");
Grafica_Gauss_Radio_Theta<<"set term png\n";
Grafica_Gauss_Radio_Theta<<"set output 'Grafico_Gauss_Radio_theta.png'\n";
Grafica_Gauss_Radio_Theta<<"set xlabel 'Theta'\n";
Grafica_Gauss_Radio_Theta<<"set ylabel 'Radio (m)'\n";
Grafica_Gauss_Radio_Theta<<"set logscale x\n";
Grafica_Gauss_Radio_Theta<<"plot 'Resultados_Metodo_Gauss_radio_theta.dat' u 1:2 w l title 'Trayectoria de la Tierra'\n";
Grafica_Gauss_Radio_Theta.close();


//Ejecutar todos los archivos generados de Gnuplot.

system("gnuplot Grafico_Simpson_Radio_theta.gp");
system("gnuplot Grafico_Trapecio_Radio_theta.gp");
system("gnuplot Grafico_Cuadratura_Radio_theta.gp");
system("gnuplot Grafico_Gauss_Radio_theta.gp");
system("gnuplot Resultado_Solucion_Analitica.gp");


return 0;
}