#include<iostream>
#include<cstdlib>
#include<cmath>

int menu(){
int opc;
std::cout<<"Welcome to the vectorial calculator"<<std::endl;
std::cout<<"1. Product x escalar\n 2. Vectorial Sum\n 3. Diferentiation\n 4. Dot Product\n 5. Vectorial Product\n 6. Norm\n 7. Exterior\n 8. Geometric  "<<std::endl;
std::cin>>opc;
return opc;
}
double readnum(){
    double num;
    std::cout<<"Type a number"<<std::endl;
    std::cin>>num;
    return(num);
}

double proescal(double num1, double num2){
    return(num1*num2);}
double sum(double num1, double num2){
    return(num1+num2);}
double resta(double num1, double num2){
    return(num1-num2);}
double dotp(double num1, double num2){
    return(num1*num2);}
double vectorp(double num1, double num2, double num3, double num4){
    return(num1*num2-num3*num4);}
double normv(double num1, double num2, double num3){
    return(sqrt(pow(num1, 2)+pow(num2, 2)+pow(num3, 2)));}
double outerp(double num1, double num2, double num3, double num4){
    return(num1*num2-num3*num4);}    

int main(){
    double x, y, z, a, b, c;
    switch(menu()){
    case 1:
       system("clear");
       std::cout<<"The escalar number is the first one and the others are the vector components (x,y,z)"<<std::endl;
       x = readnum() , y = readnum(), z = readnum(), a = readnum();
       std::cout<<"The multiplication of the vector ("<<y<<","<<z<<","<<a<<") by "<<x<<" equals to ("<<proescal(x,y)<<","<<proescal(x,z)<<","<<proescal(x,a)<<")"<<std::endl;
       break;
    case 2:
       system("clear");
       std::cout<<"The first 3 numbers are the first vector components, and the other 3 are the second one"<<std::endl;
       x = readnum() , y = readnum(), z = readnum(), a = readnum(), b = readnum(), c = readnum();
       std::cout<<"The sum of the vector ("<<x<<","<<y<<","<<z<<") and the vector ("<<a<<","<<b<<","<<c<<") equals to ("<<sum(x,a)<<","<<sum(y,b)<<","<<sum(z,c)<<")"<<std::endl;
       break;
    case 3:
       system("clear");
       std::cout<<"The first 3 numbers are the first vector components, and the other 3 are the second one"<<std::endl;
       x = readnum() , y = readnum(), z = readnum(), a = readnum(), b = readnum(), c = readnum();
       std::cout<<"The difference between the vectors ("<<x<<","<<y<<","<<z<<") and ("<<a<<","<<b<<","<<c<<") equals to ("<<resta(x,a)<<","<<resta(y,b)<<","<<resta(z,c)<<")"<<std::endl;
       break;   
    case 4:
       system("clear");
       std::cout<<"The first 3 numbers are the first vector components, and the other 3 are the second one"<<std::endl;
       x = readnum() , y = readnum(), z = readnum(), a = readnum(), b = readnum(), c = readnum();
       std::cout<<"The dot product between the vectors ("<<x<<","<<y<<","<<z<<") and ("<<a<<","<<b<<","<<c<<") equals to ("<<dotp(x,a)<<","<<dotp(y,b)<<","<<dotp(z,c)<<")"<<std::endl;
       break;   
    case 5:
       system("clear");
       std::cout<<"The first 3 numbers are the first vector components, and the other 3 are the second one"<<std::endl;
       x = readnum() , y = readnum(), z = readnum(), a = readnum(), b = readnum(), c = readnum();
       std::cout<<"The vectorial product between the vectors ("<<x<<","<<y<<","<<z<<") and ("<<a<<","<<b<<","<<c<<") equals to ("<<vectorp(y,c,b,z)<<","<<-vectorp(x,c,a,z)<<","<<vectorp(x,b,a,y)<<")"<<std::endl;
       break;     
    case 6:
       system("clear");
       std::cout<<"Type 3 values for the vector in order to compute the norm"<<std::endl;
       x = readnum() , y = readnum(), z = readnum();
       std::cout<<"The norm of the vector ("<<x<<","<<y<<","<<z<<") equals to "<<normv(x,y,z)<<")"<<std::endl;
       break; 
    case 7:
       system("clear");
       std::cout<<"The first 3 numbers are the first vector, and the other 3 are the second one"<<std::endl;
       x = readnum() , y = readnum(), z = readnum(), a = readnum(), b = readnum(), c = readnum();
       std::cout<<"The outer product between the vectors ("<<x<<","<<y<<","<<z<<") and ("<<a<<","<<b<<","<<c<<") equals to ("<<outerp(x,b,y,a)<<"(e1^e2),"<<outerp(y,c,b,z)<<"(e2^e3),"<<outerp(a,z,x,c)<<"(e3^e1))"<<std::endl;
       break; 
    case 8:
       system("clear");
       std::cout<<"The first 3 numbers are the first vector, and the other 3 are the second one"<<std::endl;
       x = readnum() , y = readnum(), z = readnum(), a = readnum(), b = readnum(), c = readnum();
       std::cout<<"The geometric product between the vectors ("<<x<<","<<y<<","<<z<<") and ("<<a<<","<<b<<","<<c<<") equals to ("<<dotp(x,a)+outerp(x,b,y,a)<<","<<dotp(y,b)+outerp(y,c,b,z)<<","<<dotp(z,c)+outerp(a,z,x,c)<<")"<<std::endl;
       break;                 
  default:
  std::cout<<"Invalid option - aprenda a escribir mas bien"<<std::endl;
  return 0;
  }
return 0;
}