#include<iostream>
#include<cstdlib>

int main (){

int opcion, num1, num2;
float resultado;
system("clear");


std::cout<<"Ingrese el primer numero entero"<<std::endl;
std::cin>>num1;
std::cout<<"Ingrese el segundo número entero"<<std::endl;
std::cin>>num2;
system("clear");

std::cout<<":::::::::::MENU CALCULADORA:::::::::::::"<<std::endl;
std::cout<<" "<<std::endl;
std::cout<<"\t 1. Suma"<<std::endl;
std::cout<<"\t 2. Resta \n\t 3.Producto \n\t 4.División \n\t 5.Modulo"<<std::endl;


std::cin>>opcion;

if(opcion==1) 
{
	system("clear");
	resultado=num1+num2;
	std::cout<<"La suma de "<<num1<<" y "<<num2<<" es igual a: "<<resultado<<std::endl;
}
std::cout<<"La opción elegida es:"<<opcion<<std::endl;

if(opcion==2)
{
        system("clear");
        resultado=num1-num2;
        std::cout<<"La resta de "<<num1<<" y "<<num2<<" es igual a: "<<resultado<<std::endl;
}

if(opcion==3)
{
        system("clear");
        resultado=num1*num2;
        std::cout<<"El producto de "<<num1<<" y "<<num2<<" es igual a: "<<resultado<<std::endl;
}

if(opcion==4)
{
        system("clear");
        resultado=num1/(num2*1.0);
        std::cout<<"La division de "<<num1<<" y "<<num2<<" es igual a: "<<resultado<<std::endl;
}

if(opcion==5)
{
        system("clear");
        resultado=num1%num2;
        std::cout<<"El modulo de "<<num1<<" y "<<num2<<" es igual a: "<<resultado<<std::endl;
}

if(num1%2==0)
	std::cout<<"El primer número elegido es par"<<std::endl;




return 0;
}
