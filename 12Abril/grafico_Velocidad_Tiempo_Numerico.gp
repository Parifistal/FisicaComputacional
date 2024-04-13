set term png
set output 'grafico_Velocidad_Tiempo_Numerico.png' 
set xlabel 'Tiempo'
set ylabel 'Velocidad' 
plot 'Datos_Velocidad_vs_Tiempo_Numerico.dat' u 2:1 title 'Solucion Numerica' 
