#include<iostream>

float z;

void otrafuncion(){
    std::cout<<"La variable z es: "<<z<<std::endl;
    z=z+1;
    std::cout<<"Cambio el valor a: "<<z<<std::endl;
}
int main()
{
    
    z=0;
    std::cout<<"El valor de z es: "<<z<<std::endl;
    std::cin>>z;
    otrafuncion();

    return 0;


}