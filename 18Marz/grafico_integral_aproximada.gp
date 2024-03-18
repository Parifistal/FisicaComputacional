set term png
set output 'grafico_integral_aproximada.png' 
set xlabel 'N'
set ylabel 'Integral' 
set logscale x
plot 'resultados.dat' u 1:2 w l title 'Integral aproximada' 
