# Configuración del gráfico
set terminal pngcairo enhanced font 'arial,10'
set output 'soluciones1.png'
# Títulos y etiquetas de los ejes
set title 'Comparación de Soluciones'
set xlabel 'x'
set ylabel 'y'
# Trazar las soluciones
plot 'resultados.txt' using 1:2 with lines lw 2 title 'Solución Numérica (Runge-Kutta)', \
     'resultados.txt' using 1:3 with lines lw 2 title 'Solución Analítica'
