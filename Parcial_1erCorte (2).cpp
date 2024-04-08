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


int main(){// Se crean los documentos necesarios para poder guardar los datos generados por los metodos.
    std::ofstream datosSimpsonr_theta("Resultados_Metodo_Simpson_radio_theta.dat");
    std::ofstream datosTrapecior_theta("Resultados_Metodo_Trapecio_radio_theta.dat");
    std::ofstream datosCuadraturar_theta("Resultados_Metodo_Cuadratura_radio_theta.dat");
    std::ofstream datosGaussr_theta("Resultados_Metodo_Gauss_radio_theta.dat");
    std::ofstream datosErrorr_theta("Resultados_Error_radio_theta.dat");

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


// Generamos los valores en modo polar.
        long double x1=r_theta1*cos(theta[i]);
        long double x2=r_theta2*cos(theta[i]);
        long double x3=r_theta3*cos(theta[i]);
        long double x4=r_theta4*cos(theta[i]);

        long double y1=r_theta1*sin(theta[i]);
        long double y2=r_theta2*sin(theta[i]);
        long double y3=r_theta3*sin(theta[i]);
        long double y4=r_theta4*sin(theta[i]);

        datosSimpsonr_theta<<x1<<" "<<y1<<std::endl;
        datosTrapecior_theta<<x2<<" "<<y2<<std::endl;
        datosCuadraturar_theta<<x3<<" "<<y3<<std::endl;
        datosGaussr_theta<<x4<<" "<<y4<<std::endl;
        datosErrorr_theta<<N<<" "<<r_theta1<<" "<<r_theta2<<" "<<r_theta3<<" "<<r_theta4<<std::endl;        
    }       
    }

     
datosSimpsonr_theta.close();
datosTrapecior_theta.close();
datosCuadraturar_theta.close();
datosGaussr_theta.close();
datosErrorr_theta.close();
// Generación de graficas a base de Gnuplot.

// Graficas para Radio vs Theta con los 4 metodos.
std::ofstream Grafico_error("Grafico_error_Radio_theta.gp");
Grafico_error<<"set output 'Grafico_Simpson_Radio_theta.png'\n";
Grafico_error<<"set xlabel 'N'\n";
Grafico_error<<"set ylabel 'Valor de la integral'\n";
Grafico_error<<"set xlogscale x\n";
Grafico_error<<"plot 'Resultados_Error_radio_theta.dat' u 1:2 w l title 'Simpson', '' u 1:3 w l title 'Trapecio', '' u 1:4 w l title 'Rectangular', '' u 1:4 w l title 'Gauss' \n";
Grafico_error.close();

std::ofstream Grafica_Simpson_Radio_Theta("Grafico_Simpson_Radio_theta.gp");
Grafica_Simpson_Radio_Theta<<"set output 'Grafico_Simpson_Radio_theta.png'\n";
Grafica_Simpson_Radio_Theta<<"set xlabel 'Theta'\n";
Grafica_Simpson_Radio_Theta<<"set ylabel 'Radio'\n";
Grafica_Simpson_Radio_Theta<<"plot 'Resultados_Metodo_Simpson_radio_theta.dat' u 1:2 title 'Trayectoria de la Tierra'\n";
Grafica_Simpson_Radio_Theta.close();

std::ofstream Grafica_Analitica("Grafica_Analitica.gp");
Grafica_Analitica<<"set polar\n";
Grafica_Analitica<<"set xlabel 'Theta'\n";
Grafica_Analitica<<"set ylabel 'Radio'\n";
Grafica_Analitica<<"set output 'Grafica_Analitica.png'\n ";
Grafica_Analitica<<"plot 1/(1+0.0163*cos(t)) title 'Trayectoria de la Tierra'\n";
Grafica_Analitica.close();

std::ofstream Grafica_Trapecio_Radio_Theta("Grafico_Trapecio_Radio_theta.gp");
Grafica_Trapecio_Radio_Theta<<"set output 'Grafico_Tapecio_Radio_theta.png'\n";
Grafica_Trapecio_Radio_Theta<<"set xlabel 'Theta'\n";
Grafica_Trapecio_Radio_Theta<<"set ylabel 'Radio'\n";
Grafica_Trapecio_Radio_Theta<<"plot 'Resultados_Metodo_Trapecio_radio_theta.dat' u 1:2 title 'Trayectoria de la Tierra'\n";
Grafica_Trapecio_Radio_Theta.close();

std::ofstream Grafica_Cuadratura_Radio_Theta("Grafico_Cuadratura_Radio_theta.gp");
Grafica_Cuadratura_Radio_Theta<<"set output 'Grafico_Cuadratura_Radio_theta.png'\n";
Grafica_Cuadratura_Radio_Theta<<"set xlabel 'Theta'\n";
Grafica_Cuadratura_Radio_Theta<<"set ylabel 'Radio'\n";
Grafica_Cuadratura_Radio_Theta<<"plot 'Resultados_Metodo_Cuadratura_radio_theta.dat' u 1:2 title 'Trayectoria de la Tierra'\n";
Grafica_Cuadratura_Radio_Theta.close();

std::ofstream Grafica_Gauss_Radio_Theta("Grafico_Gauss_Radio_theta.gp");
Grafica_Gauss_Radio_Theta<<"set output 'Grafico_Gauss_Radio_theta.png'\n";
Grafica_Gauss_Radio_Theta<<"set xlabel 'Theta'\n";
Grafica_Gauss_Radio_Theta<<"set ylabel 'Radio'\n";
Grafica_Gauss_Radio_Theta<<"plot 'Resultados_Metodo_Gauss_radio_theta.dat' u 1:2 title 'Trayectoria de la Tierra'\n";
Grafica_Gauss_Radio_Theta.close();


//Ejecutar todos los archivos generados de Gnuplot.

system("gnuplot Grafico_Simpson_Radio_theta.gp");
system("gnuplot Grafico_Trapecio_Radio_theta.gp");
system("gnuplot Grafico_Cuadratura_Radio_theta.gp");
system("gnuplot Grafico_Gauss_Radio_theta.gp");
system("gnuplot Grafica_Analitica.gp");
system("gnuplot Grafico_error_Radio_theta.gp");
return 0;
}
