#include<iostream>
#include<fstream>
#include<cmath>

//Función derivada analitica
double analytic_derivate(double x){
    return 2*x;
}
//Función a derivar númericamente
double function_to_differentiate(double x){
    return x+x;
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

        //Guardar resultado en el archivo
        data_file<<x<<" "<<analytic_result<<" "<<foward_result<<" "<<backward_result<<" "<<central_result<<"\n";
    }

    // Cierre el archvio
    data_file.close();

    //Script Gnuplot
    std::ofstream gnuplot_script("plot_script.gnu");
    gnuplot_script<<"plot 'Derivadas.dat' using 1:2 with line title 'Derivada Analitica', "
                  <<"'' using 1:3 with line title 'Diferencias finitas hacia adelante', "
                  <<"'' using 1:4 with line title 'Diferencias finitas hacia atras', "
                  <<"'' using 1:5 with line title 'Diferencias finitas Centrales', \n";
    gnuplot_script.close();
    //Ejecute el script de gnuplot
    system("gnuplot -p plot_script.gnu");
    return 0;  

}