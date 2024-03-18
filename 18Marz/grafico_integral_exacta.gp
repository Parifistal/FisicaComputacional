set term png
set output 'grafico_integral_exacta.png' 
set xlabel 'N'
set ylabel 'Integral' 
set logscale x
plot 'resultados.dat' u 1:3 w l title 'Valor exacto de la integral' 
