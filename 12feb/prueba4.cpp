#include<iostream>
int main()
{
    int opc;
    while (opc!=3)
    {
        system("clear");
        std::cout<<"::::::::::BIENVENIDO:::::: \n\n "<<std::endl;
        std::cout<<"\t 1. Suma"<<std::endl;
        std::cout<<"\t 2. Resta"<<std::endl;
        std::cout<<"\t 3. Salir"<<std::endl;
        std::cout<<"Eleja la opción que desea"<<std::endl;
        std::cin>>opc;
        if(opc==1)
        {
        system("clear");
        std::cout<<"Usted eligio la Suma"<<std::endl;   
        }
        else if(opc==2){
        system("clear");
        std::cout<<"Usted eligio la opción Resta"<<std::endl;
        }
        else if(opc==3){
        system("clear");
        std::cout<<"CHAO...CHAO"<<std::endl;
        exit(5);
        }
        else{
        system("clear");
        std::cout<<"Usted eligio la opcion incorrecta"<<std::endl;
        }
    }
    return 0;


}