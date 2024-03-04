#include<iostream>
#include<cstdlib>
#include<math.h>
#include<cmath>
int main()
{
    int x;
    float e, nuevo, nuevo1;

        system("clear");
        std::cout<<"::::::::::BIENVENIDO:::::: \n\n "<<std::endl;
        std::cout<<"\t Seleccione el valor inicial de x"<<std::endl;
        std::cin>>x;
        e=2.71828182845904525356;
        while(x!=0.135){
        x=x-(((pow(e, 2*x))+log(2*x))/(2*pow(e,2*x)+(1/x)));
        }
        std::cout<<"La raiz es: "<<x<<std::endl;
        



return 0;


}