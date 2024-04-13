set term png
set output 'grafico_Velocidad_Tiempo_Error.png' 
set xlabel 'N'
set ylabel 'Velocidad Analitica y Numérica' 
plot 'Datos_Error_Velocidad_vs_Tiempo_Numerico_vs_Analitico.dat' u 1:2 w l title 'Analitica', '' u 1:3 w l title 'Numerica' 
