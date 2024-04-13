set term png
set output 'grafico_Velocidad_Tiempo_Analitico.png' 
set xlabel 'Tiempo'
set ylabel 'Velocidad' 
plot 'Datos_Velocidad_vs_Tiempo_Analitico.dat' u 2:1 title 'Solucion Analitica' 
