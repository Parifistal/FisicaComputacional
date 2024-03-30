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
const double T = sqrt((pow(R,3)/2*G*mu));
const double E=(0.5)*v_0*mu+(G*M_s*mu)/R;
//Función para determinar r.

double dr_dt(double r, double L, double E, double t){
    if (r == 0.0) {
        // Manejar el caso cuando r es cero para evitar la división por cero
        return 0.0; // O cualquier otro valor adecuado
    }
    double discriminante = (2/mu) * (E - (pow(L,2) / (2 * mu * pow(r,2))) + (G * M_s * M_t / r));
    if (discriminante < 0.0) {
        // Manejar el caso cuando el discriminante es negativo para evitar la raíz cuadrada de un número negativo
        return 0.0; // O cualquier otro valor adecuado
    }
    return sqrt(discriminante);
}
// Función para determinar el cambio en theta.

double Delta_theta(double L_prima, double theta, double E_prima ){
    double r_prima=a/(1.0+epsilon*cos(theta));
    double dividendo=pow(L_prima,2)/pow(r_prima,2);
    double divisor=sqrt(2*E_prima-(pow(L_prima,2)/pow(r_prima,2))+(M_s*M_t/r_prima));
    return dividendo/divisor;
}

// Función para determinar el cambio de Delta t.

double Delta_t(double L_prima, double theta, double E_prima) {
    double r_prima = a / (1.0 + epsilon * cos(theta));

    // Se realizan estas entradas para evitar que los resultados que son 0, generen problemas con los calculos.
    if (r_prima == 0.0) {
        return 0.0; // O cualquier otro valor adecuado
    }

    double discriminante = 2 * E_prima - pow(L_prima, 2) / pow(r_prima, 2) + (M_s * M_t) / r_prima;

    // Se evita la raíz cuadrada de un número negativo
    if (discriminante < 0.0) {
        return 0.0; // O cualquier otro valor adecuado
    }

    double divisor_Dt = sqrt(discriminante);

    // Se diferencia los valores cero para poder dividir de forma correcta en el calculo.
    if (divisor_Dt == 0.0) {
        return 0.0; // O cualquier otro valor adecuado
    }

    return 1.0 / divisor_Dt;
}
// Para poder resolver la ecuación diferencial de r se resuelve por medio del metodo de Runge Kutta del 
// cuarto orden 

// Metodo Runge Kutta de Cuarto Orden.

// Se define un valor h que sera el paso del metodo.
double Runge_Kutta(double r, double t, double E_prima, double L_prima, double h){
    double k1 = h * dr_dt(r, L_prima, E_prima, t);
    double k2 = h * dr_dt(r + (h / 2) * k1, L_prima, E_prima, t + (h / 2));
    double k3 = h * dr_dt(r + (h / 2) * k2, L_prima, E_prima, t + (h / 2));
    double k4 = h * dr_dt(r + h * k3, L_prima, E_prima, t + h);
    return r + ((k1 + 2 * k2 + 2 * k3 + k4) / 6);
}
// Calculo de la integral para hallar el cambio de theta.

// Metodo de Simpson.

double simpsontheta(double a, double b, int N, double L_prima, double E_prima){
    double h=(b-a)/N; // Se determina el valor del paso, incluyendo los parametros de a y b, obtenidos mediante la integral del ejercicio.
    double suma= Delta_theta(a, L_prima, E_prima)+ Delta_theta(b, L_prima, E_prima); //Se determina el primer y ultimo valor de la integral númerica.
    for(int i=1;i<N;i++){ //Se determina el valor de los pasos o avance en el que se dividiran los valores de x.
        double xi=a+(i*h);
        if (i % 2 ==0){ //Se determina la diferencia de pares e inpares gracias a la operación de residuo.
            suma+= 2*Delta_theta(xi, L_prima, E_prima);
        }
        else{
            suma+=4*Delta_theta(xi, L_prima, E_prima);
        }
    }
    return (h/3)*suma;
}
 
// Metodo del Trapecio.

double Trapeciotheta(double a, double b, int N, double L_prima, double E_prima){
    double h=(b-a)/N;
    double suma= Delta_theta(a, L_prima, E_prima)+ Delta_theta(b, L_prima, E_prima); 
    for(int i=1;i<N;i++){ 
        double xi=a+(i*h);
            suma+= 2*Delta_theta(xi, L_prima, E_prima);
    }
    return (h/2)*suma;
}

// Cuadratura rectangular.

double Cuadraturatheta(double a, double b, int N, double L_prima, double E_prima){
    double h=(b-a)/N;
    double suma=1; // El valor inicial se tomo de las diapositivas del ejercicio.
    for(int i=0;i<N;i++){
        double xi=a+i*h;
        suma+=Delta_theta(xi, L_prima, E_prima);
    }
    return h*suma;
}

// Regla de simpson 3/8 compuesta.

double Simpson38theta(double a, double b, int N, double L_prima, double E_prima){
    double h=(b-a)/N;
    double suma= Delta_theta(a, L_prima, E_prima)+ Delta_theta(b, L_prima, E_prima); //Se determina el primer y ultimo valor de la integral númerica.
    for(int i=1;i<N;i++){ //Se determina el valor de los pasos o avance en el que se dividiran los valores de x.
        double xi=a+(i*h);
        if (i % 3 ==0){ //Se determinan los multiplos de 3 y asi se catalogan las ultiplicaciones de cada valor de la sumatoria.
            suma+= 2*Delta_theta(xi, L_prima, E_prima);
        }
        else{
            suma+=3*Delta_theta(xi, L_prima, E_prima);
        }
    }
    return (3*h/8)*suma;
}

// Calculo de la integral para hallar el cambio de t'.

// Metodo de Simpson.

double simpsont(double a, double b, int N, double L_prima, double E_prima){
    double h=(b-a)/N; // Se determina el valor del paso, incluyendo los parametros de a y b, obtenidos mediante la integral del ejercicio.
    double suma= Delta_t(a, L_prima, E_prima)+ Delta_t(b, L_prima, E_prima); //Se determina el primer y ultimo valor de la integral númerica.
    for(int i=1;i<N;i++){ //Se determina el valor de los pasos o avance en el que se dividiran los valores de x.
        double xi=a+(i*h);
        if (i % 2 ==0){ //Se determina la diferencia de pares e inpares gracias a la operación de residuo.
            suma+= 2*Delta_t(xi, L_prima, E_prima);
        }
        else{
            suma+=4*Delta_t(xi, L_prima, E_prima);
        }
    }
    return (h/3)*suma;
}
 



// Metodo del Trapecio.

double Trapeciot(double a, double b, int N, double L_prima, double E_prima){
    double h=(b-a)/N;
    double suma= Delta_t(E_prima, L_prima, a)+ Delta_t(E_prima, L_prima, b); 
    for(int i=1;i<N;i++){ 
        double xi=a+(i*h);
            suma+= 2*Delta_t(E_prima, L_prima, xi);
    }
    return (h/2)*suma;
}

// Cuadratura rectangular.

double Cuadraturat(double a, double b, int N, double L_prima, double E_prima){
    double h=(b-a)/N;
    double suma=1; // El valor inicial se tomo de las diapositivas del ejercicio.
    for(int i=0;i<N;i++){
        double xi=a+i*h;
        suma+=Delta_t(E_prima, L_prima, xi);
    }
    return h*suma;
}

// Regla de simpson 3/8 compuesta.

double Simpson38t(double a, double b, int N, double L_prima, double E_prima){
    double h=(b-a)/N;
    double suma= Delta_t(E_prima, L_prima, a)+ Delta_t(E_prima, L_prima, b); //Se determina el primer y ultimo valor de la integral númerica.
    for(int i=1;i<N;i++){ //Se determina el valor de los pasos o avance en el que se dividiran los valores de x.
        double xi=a+(i*h);
        if (i % 3 ==0){ //Se determinan los multiplos de 3 y asi se catalogan las ultiplicaciones de cada valor de la sumatoria.
            suma+= 2*Delta_t(E_prima, L_prima, xi);
        }
        else{
            suma+=3*Delta_t(E_prima, L_prima, xi);
        }
    }
    return (3*h/8)*suma;
}

// Ahora se inicia el proceso para realizar las graficas de el cambio de theta con respecto a el radio.

int main(){
    std::ofstream datosSimpsontheta("Resultados_Metodo_Simpson_radio_vs_theta.dat");
    std::ofstream datosTrapeciotheta("Resultados_Metodo_Trapecio_radio_vs_theta.dat");
    std::ofstream datosCuadraturatheta("Resultados_Metodo_Cuadratura_radio_vs_theta.dat");
    std::ofstream datosSimpson38theta("Resultados_Metodo_Simpson38_radio_vs_theta.dat");
    std::ofstream datosSimpsont("Resultados_Metodo_Simpson_radio_vs_tiempo.dat");
    std::ofstream datosTrapeciot("Resultados_Metodo_Trapecio_radio_vs_tiempo.dat");
    std::ofstream datosCuadraturat("Resultaods_Metodo_Cuadratura_radio_vs_tiempo.dat");
    std::ofstream datosSimpson38t("Resultados_Metodo_Simpson38_radio_vs_tiempo.dat");

    for (int t = 1, N = 1; t < 10000 || N < 10000; ++t, ++N) { //Los simbolos || funcionan como un o logico, logrando asi que el codigo se ejecute de forma seguida siempre y cuando uno de los dos valores determinados sea verdadero, cuando los dos sean falsos entonces el bucle terminara.
        double r = R;
        double theta1 = 0.0;
        double theta2 = 0.0;
        double theta3 = 0.0;
        double theta4 = 0.0;
        double t1 = 0.0;
        double t2 = 0.0;
        double t3 = 0.0;
        double t4 = 0.0;
        double E_prima;
        double L_prima;
        double h = 1000;
        

        if (t < 100000) {
            L_prima = R * mu * v_0;
            E_prima = (E * pow(T, 2)) / (mu * pow(R, 2));
            r = Runge_Kutta(r, t, E_prima, L_prima, h);
        }
        
        if (N < 10000) {
            double r_prima1 = r / R;
            E_prima = (E * pow(T, 2)) / (mu * pow(R, 2));
            L_prima = R * mu * v_0;
            theta1 = simpsontheta(1.0, r_prima1, N, L_prima, E_prima);
            theta2 = Trapeciotheta(1.0, r_prima1, N, L_prima, E_prima);
            theta3 = Cuadraturatheta(1.0, r_prima1, N, L_prima, E_prima);
            theta4 = Simpson38theta(1.0, r_prima1, N, L_prima, E_prima);
            t1 = simpsont(1.0, r_prima1, N, L_prima, E_prima);
            t2 = Trapeciot(1.0, r_prima1, N, L_prima, E_prima);
            t3 = Cuadraturat(1.0, r_prima1, N, L_prima, E_prima);
            t4 = Simpson38t(1.0, r_prima1, N, L_prima, E_prima);
        }
        datosSimpsontheta<<r<<" "<<theta1<<std::endl;
        datosTrapeciotheta<<r<<" "<<theta2<<std::endl;
        datosCuadraturatheta<<r<<" "<<theta3<<std::endl;
        datosSimpson38theta<<r<<" "<<theta4<<std::endl;
        datosSimpsont<<r<<" "<<t1<<std::endl;
        datosTrapeciot<<r<<" "<<t2<<std::endl;
        datosCuadraturat<<r<<" "<<t3<<std::endl;
        datosSimpson38t<<r<<" "<<t4<<std::endl;

}
datosSimpsontheta.close();
datosTrapeciotheta.close();
datosCuadraturatheta.close();
datosSimpson38theta.close();
datosSimpsont.close();
datosTrapeciot.close();
datosCuadraturat.close();
datosSimpson38t.close();
//eeebdudb



// Generación de graficas a base de Gnuplot.

// Graficas para Radio vs Theta con los 4 metodos.

std::ofstream Grafica_Simpson_Radio_vs_Theta("Grafico_Simpson_Radio_vs_theta.gp");
Grafica_Simpson_Radio_vs_Theta <<"set polar\n"; //Se establece el modo polar.
Grafica_Simpson_Radio_vs_Theta<<"plot 'Resultados_Metodo_Simpson_radio_vs_theta.dat' u 2:1 w pt 7 ps 1 lc rgb 'blue' title 'Datos'\n";
Grafica_Simpson_Radio_vs_Theta<<"set grid\n";
Grafica_Simpson_Radio_vs_Theta<<"set term png\n";
Grafica_Simpson_Radio_vs_Theta<<"set output 'Grafico_Simpson_Radio_vs_theta.png'\n";
Grafica_Simpson_Radio_vs_Theta<<"set xlabel 'Theta'\n";
Grafica_Simpson_Radio_vs_Theta<<"set ylabel 'Radio'\n";
Grafica_Simpson_Radio_vs_Theta<<"set title 'Grafica de Theta vs Radio Simpson' \n";
Grafica_Simpson_Radio_vs_Theta.close();

std::ofstream Grafica_Trapecio_Radio_vs_Theta("Grafico_Trapecio_Radio_vs_theta.gp");
Grafica_Trapecio_Radio_vs_Theta <<"set polar\n"; //Se establece el modo polar.
Grafica_Trapecio_Radio_vs_Theta<<"plot 'Resultados_Metodo_Trapecio_radio_vs_theta.dat' u 2:1 w pt 7 ps 1 lc rgb 'blue' title 'Datos'\n";
Grafica_Trapecio_Radio_vs_Theta<<"set grid\n";
Grafica_Trapecio_Radio_vs_Theta<<"set term png\n";
Grafica_Trapecio_Radio_vs_Theta<<"set output 'Grafico_Trapecio_Radio_vs_theta.png'\n";
Grafica_Trapecio_Radio_vs_Theta<<"set xlabel 'Theta'\n";
Grafica_Trapecio_Radio_vs_Theta<<"set ylabel 'Radio'\n";
Grafica_Trapecio_Radio_vs_Theta<<"set title 'Grafica de Theta vs Radio Trapecio' \n";
Grafica_Trapecio_Radio_vs_Theta.close();

std::ofstream Grafica_Cuadratura_Radio_vs_Theta("Grafico_Cuadratura_Radio_vs_theta.gp");
Grafica_Cuadratura_Radio_vs_Theta <<"set polar\n"; //Se establece el modo polar.
Grafica_Cuadratura_Radio_vs_Theta<<"plot 'Resultados_Metodo_Cuadratura_radio_vs_theta.dat' u 2:1 w pt 7 ps 1 lc rgb 'blue' title 'Datos'\n";
Grafica_Cuadratura_Radio_vs_Theta<<"set grid\n";
Grafica_Cuadratura_Radio_vs_Theta<<"set term png\n";
Grafica_Cuadratura_Radio_vs_Theta<<"set output 'Grafico_Cuadratura_Radio_vs_theta.png'\n";
Grafica_Cuadratura_Radio_vs_Theta<<"set xlabel 'Theta'\n";
Grafica_Cuadratura_Radio_vs_Theta<<"set ylabel 'Radio'\n";
Grafica_Cuadratura_Radio_vs_Theta<<"set title 'Grafica de Theta vs Radio Trapecio' \n";
Grafica_Cuadratura_Radio_vs_Theta.close();

std::ofstream Grafica_Simpson38_Radio_vs_Theta("Grafico_Simpson38_Radio_vs_theta.gp");
Grafica_Simpson38_Radio_vs_Theta <<"set polar\n"; //Se establece el modo polar.
Grafica_Simpson38_Radio_vs_Theta<<"plot 'Resultados_Metodo_Simpson38_radio_vs_theta.dat' u 2:1 w pt 7 ps 1 lc rgb 'blue' title 'Datos'\n";
Grafica_Simpson38_Radio_vs_Theta<<"set grid\n";
Grafica_Simpson38_Radio_vs_Theta<<"set term png\n";
Grafica_Simpson38_Radio_vs_Theta<<"set output 'Grafico_Simpson38_Radio_vs_theta.png'\n";
Grafica_Simpson38_Radio_vs_Theta<<"set xlabel 'Theta'\n";
Grafica_Simpson38_Radio_vs_Theta<<"set ylabel 'Radio'\n";
Grafica_Simpson38_Radio_vs_Theta<<"set title 'Grafica de Theta vs Radio Trapecio' \n";
Grafica_Simpson38_Radio_vs_Theta.close();


// Grafica para Radio vs Tiempo.

std::ofstream Grafica_Simpson_Radio_vs_Tiempo("Grafica_Simpson_Radio_vs_Tiempo.gp");
Grafica_Simpson_Radio_vs_Tiempo<<"set term png\n";
Grafica_Simpson_Radio_vs_Tiempo<<"set output 'Grafica_Simpson_Radio_vs_Tiempo.png' \n";
Grafica_Simpson_Radio_vs_Tiempo<<"set xlabel 'N'\n";
Grafica_Simpson_Radio_vs_Tiempo<<"set ylabel '' \n";
Grafica_Simpson_Radio_vs_Tiempo<<"set logscale x\n";
Grafica_Simpson_Radio_vs_Tiempo<<"plot 'Resultados_Metodo_Simpson_radio_vs_tiempo.dat' u 2:1 w l title 'Radio vs Tiempo Simpson' \n";
Grafica_Simpson_Radio_vs_Tiempo.close();

std::ofstream Grafica_Trapecio_Radio_vs_Tiempo("Grafica_Trapecio_Radio_vs_Tiempo.gp");
Grafica_Trapecio_Radio_vs_Tiempo<<"set term png\n";
Grafica_Trapecio_Radio_vs_Tiempo<<"set output 'Grafica_Trapecio_Radio_vs_Tiempo.png' \n";
Grafica_Trapecio_Radio_vs_Tiempo<<"set xlabel 'N'\n";
Grafica_Trapecio_Radio_vs_Tiempo<<"set ylabel '' \n";
Grafica_Trapecio_Radio_vs_Tiempo<<"set logscale x\n";
Grafica_Trapecio_Radio_vs_Tiempo<<"plot 'Resultados_Metodo_Trapecio_radio_vs_tiempo.dat' u 2:1 w l title 'Radio vs Tiempo Trapecio' \n";
Grafica_Trapecio_Radio_vs_Tiempo.close();

std::ofstream Grafica_Cuadratura_Radio_vs_Tiempo("Grafica_Cuadratura_Radio_vs_Tiempo.gp");
Grafica_Cuadratura_Radio_vs_Tiempo<<"set term png\n";
Grafica_Cuadratura_Radio_vs_Tiempo<<"set output 'Grafica_Cuadratura_Radio_vs_Tiempo.png' \n";
Grafica_Cuadratura_Radio_vs_Tiempo<<"set xlabel 'N'\n";
Grafica_Cuadratura_Radio_vs_Tiempo<<"set ylabel '' \n";
Grafica_Cuadratura_Radio_vs_Tiempo<<"set logscale x\n";
Grafica_Cuadratura_Radio_vs_Tiempo<<"plot 'Resultaods_Metodo_Cuadratura_radio_vs_tiempo.dat' u 2:1 w l title 'Radio vs Tiempo Trapecio' \n";
Grafica_Cuadratura_Radio_vs_Tiempo.close();

std::ofstream Grafica_Simpson38_Radio_vs_Tiempo("Grafica_Simpson38_Radio_vs_Tiempo.gp");
Grafica_Simpson38_Radio_vs_Tiempo<<"set term png\n";
Grafica_Simpson38_Radio_vs_Tiempo<<"set output 'Grafica_Simpson38_Radio_vs_Tiempo.png' \n";
Grafica_Simpson38_Radio_vs_Tiempo<<"set xlabel 'N'\n";
Grafica_Simpson38_Radio_vs_Tiempo<<"set ylabel '' \n";
Grafica_Simpson38_Radio_vs_Tiempo<<"set logscale x\n";
Grafica_Simpson38_Radio_vs_Tiempo<<"plot 'Resultados_Metodo_Simpson38_radio_vs_tiempo.dat' u 2:1 w l title 'Radio vs Tiempo Trapecio' \n";
Grafica_Simpson38_Radio_vs_Tiempo.close();

//Ejecutar todos los archivos generados de Gnuplot.

system("gnuplot Grafico_Simpson_Radio_vs_theta.gp");
system("gnuplot Grafico_Trapecio_Radio_vs_theta.gp");
system("gnuplot Grafico_Cuadratura_Radio_vs_theta.gp");
system("gnuplot Grafico_Simpson38_Radio_vs_theta.gp");
system("gnuplot Grafica_Simpson_Radio_vs_Tiempo.gp");
system("gnuplot Grafica_Trapecio_Radio_vs_Tiempo.gp");
system("gnuplot Grafica_Cuadratura_Radio_vs_Tiempo.gp");
system("gnuplot Grafica_Simpson38_Radio_vs_Tiempo.gp");

return 0;
}