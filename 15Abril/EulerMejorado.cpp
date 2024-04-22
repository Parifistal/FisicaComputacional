#include<iostream>
#include<cmath>

//Definimos la ecuacion diferencual dy/dx=f(x,y)

double f(double x, double y){
    return (x*x)+y;
    
    
}

// Implentando Euler Mejorado

double euler_mejorado(double x0, double y0, double h, double xf){
    
    double x=x0;
    double y=y0;

    while(x<xf){

    double y_asterisco=y+h*f(x,y);
    double y_siguiente=y+0.5*h*(f(x,y)+f(x+h,y_asterisco));

    y=y_siguiente;
    x+=h;
    }
return y;
}

int main(){

    // Definir los parametro iniciales y finales
    // Condiciones iniciales
    double x0=0.0;
    double y0=1.0;
//------------------------------------------------------------------------------------------
    double h=0.1;
    double xf=0;
    
    std::cout<<"Ingrese un valor para x_final: "<<std::endl;
    std::cin>>xf;
    double y_final = euler_mejorado(x0, y0, h, xf);
    std::cout<<"El valor de y en x = "<<xf<<" es: "<<y_final<<std::endl;

}