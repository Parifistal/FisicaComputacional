// German Stevan Rubiano Socha

#include<iostream>

#include<fstream>
#include<cmath>

//Función derivada analitica
double analytic_derivate(double x){
    return cos(x);
}
//Función a derivar númericamente
double function_to_differentiate(double x){
    return sin(x);
}

//Aproximación de derevada númeroca hacia adelante (Foward) con orden de error 0(h)
double foward_difference(double x, double h){
    return (function_to_differentiate(x+h)-function_to_differentiate(x))/h;

}

//Aproximación hacia atras (Backward) con error de 0(h)
double backward_difference(double x, double h){
    return (function_to_differentiate(x)-function_to_differentiate(x-h))/h;
}

//Aproximación centrada con error 0(h)
double central_difference(double x, double h){
    return (function_to_differentiate(x+h)-function_to_differentiate(x-h))/2*h;
}
//Aproximación de derivada númerica hacia adelante con error de 0(h²)
double foward2_difference(double x, double h){
    return (4*function_to_differentiate(x+h)-function_to_differentiate(x+2*h)-3*function_to_differentiate(x))/(2*h);
}
//Aproximación de derivada hacia atras con error de 0(h²)
double backward2_difference(double x, double h){
    return (3*function_to_differentiate(x)-4*function_to_differentiate(x-h)+function_to_differentiate(x-2*h))/(2*h);
}
//Aproximación de derivada centrada con error de 0(h⁵)
double central5_difference(double x, double h){
    return ((-1)*function_to_differentiate(x+2*h)+8*function_to_differentiate(x+h)-8*function_to_differentiate(x-h)+function_to_differentiate(x+2*h))/(12*h);
}

int main() {
    const int num_puntos=100;  //Número de puntos a evaluar
    const double h=0.1;       //Tamaño del pasa para la derivada

    //Archivo para guardar las derivadas.
    std::ofstream data_file("Derivadas.dat");
    for(int i=0; i<num_puntos; ++i){
        double x=static_cast<double>(i)/(num_puntos-1)*10;
        double analytic_result=analytic_derivate(x);
        double foward_result=foward_difference(x,h);
        double backward_result=backward_difference(x,h);
        double central_result= (i>0 && i<num_puntos-1) ?
            central_difference(x,h):0.0; // Fallback para el primer y último punto
        
        double foward2_result=foward2_difference(x,h); // Derivada hacia adelante con error de 0(h²)
        double backward2_result=backward2_difference(x,h); // Derivada hacia atras con error de 0(h²)

        double central5_result= (i>0 && i<num_puntos-1) ?
            central5_difference(x,h):0.0; //Derivada centrada con error de 0(h⁵)

        //Guardar resultado en el archivo
        data_file<<x<<" "<<analytic_result<<" "<<foward_result<<" "<<backward_result<<" "<<central_result<<" "<<foward2_result<<" "<<backward2_result<<" "<<central5_difference<<"\n";
    }

    // Cierre el archvio
    data_file.close();

    //Script Gnuplot
    std::ofstream gnuplot_script("plot_script.gnu");
    gnuplot_script<<"plot 'Derivadas.dat' using 1:2 with line title 'Derivada Analitica', "
                  <<"'' using 1:3 with line title 'Diferencias finitas hacia adelante', "
                  <<"'' using 1:4 with line title 'Diferencias finitas hacia atras', "
                  <<"'' using 1:5 with line title 'Diferencias finitas Centrales', "
                  <<"'' using 1:6 with line title 'Diferencias finitas hacia adelante con 0(h^2)', "
                  <<"'' using 1:7 with line title 'Diferencias finitas hacia atras con 0(h^2)', "
                  <<"'' using 1:8 with line title 'Diferencias finitas centrales con 0(h^5)', \n";
    gnuplot_script.close();
    //Ejecute el script de gnuplot
    system("gnuplot -p plot_script.gnu");
    return 0;  

}