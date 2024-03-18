set term png
set output 'grafico_integral_vs_cuadratura_rectangular.png' 
set xlabel 'x'
set ylabel 'f(x)' 
set logscale x
plot 'datos_cuadratura_rectangular.dat' u 1:2 w l title 'Funcion', '' w boxes title 'Rectangulos' 
