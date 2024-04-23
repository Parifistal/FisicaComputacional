#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

double f(double x, double y) {
    return y*sin(x);
}

double rungeKutta(double x0, double y0, double x, double &h) {
    double k1, k2, k3, k4;
    double y = y0;
    while (x0 < x) {
        if (x0 + h > x)
            h = x - x0;
        k1 = h * f(x0, y);
        k2 = h * f(x0 + 0.5 * h, y + 0.5 * k1);
        k3 = h * f(x0 + 0.5 * h, y + 0.5 * k2);
        k4 = h * f(x0 + h, y + k3);
        y = y + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
        x0 = x0 + h;
    }
    return y;
}

double Solucion_exacta(double x) {
    return -3*exp(1+cos(x));
}

int main() {
    double x0 = 3.141592, y0 = 3, x = 10, h = 0.01; // Paso inicial más pequeño
    std::ofstream outFile("resultados.txt");
    if (!outFile) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return 1;
    }
    outFile << "x" << "\t" << "RungeKutta4" << "\t" << "SoluciónExacta" << "\t" << "Error" << std::endl;

    double xi = x0;
    while (xi <= x) {
        double y_rk4 = rungeKutta(x0, y0, xi, h);
        double y_exact = Solucion_exacta(xi);
        double error = std::abs(y_rk4 - y_exact);
        outFile << xi << "\t" << y_rk4 << "\t" << y_exact << "\t" << error << std::endl;
        xi += h; // Avanzar en x según el paso adaptativo
    }

    outFile.close();


    // Crear archivo .gp para Gnuplot
    std::ofstream gpFile("plot_soluciones.gp");
    if (!gpFile) {
        std::cerr << "Error al abrir el archivo de script de Gnuplot." << std::endl;
        return 1;
    }

    gpFile << "# Configuración del gráfico\n";
    gpFile << "set terminal pngcairo enhanced font 'arial,10'\n";
    gpFile << "set output 'soluciones1.png'\n";
    gpFile << "# Títulos y etiquetas de los ejes\n";
    gpFile << "set title 'Comparación de Soluciones'\n";
    gpFile << "set xlabel 'x'\n";
    gpFile << "set ylabel 'y'\n";
    gpFile << "# Trazar las soluciones\n";
    gpFile << "plot 'resultados.txt' using 1:2 with lines lw 2 title 'Solución Numérica (Runge-Kutta)', \\\n";
    gpFile << "     'resultados.txt' using 1:3 with lines lw 2 title 'Solución Analítica'\n";

    gpFile.close();

    // Ejecutar Gnuplot
    system("gnuplot plot_soluciones.gp");

    return 0;
}
