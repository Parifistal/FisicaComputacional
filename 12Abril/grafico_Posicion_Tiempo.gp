set term png
set output 'grafico_Posicion_Tiempo.png' 
set xlabel 'Tiempo'
set ylabel 'Posicion' 
plot 'Datos_Posicion_vs_Tiempo_Analitico.dat' u 2:1 title 'Posicion vs Tiempo' 
