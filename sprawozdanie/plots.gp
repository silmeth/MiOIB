# Quality vs Size mean
set term qt 0 persist

set yrange [0:1.2]
set xrange [10:34]

set xtics 4
set ytics 0.2

set mxtics 4
set mytics 2

set key below
set format x "$%g$"
set format y "\\num{%.1f}"

set xlabel "rozmiar problemu"
set ylabel "śr. jakość"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

plot "/tmp/randomData" using 1:3:4 title "random" with yerrorbars linecolor rgb "black" pointtype 7 linetype 1, \
     "/tmp/randomData" using 1:3 title "" smooth unique with lines linecolor rgb "black" linetype 1, \
     "/tmp/greedyData" using 1:3:4 title "greedy" with yerrorbars linecolor rgb "red" pointtype 7 linetype 1, \
     "/tmp/greedyData" using 1:3 title "" smooth unique with lines linecolor rgb "red" linetype 1, \
     "/tmp/steepestData" using 1:3:4 title "steepest" with yerrorbars linecolor rgb "green" pointtype 7 linetype 1, \
     "/tmp/steepestData" using 1:3 title "" smooth unique with lines linecolor rgb "green" linetype 1, \
     "/tmp/heuristicData" using 1:2 title "heuristic" smooth unique with linespoints linecolor rgb "blue" pointtype 7 linetype 1

set term epslatex color size 15cm, 10cm
set output "./plotQualitySizeMean.tex"
replot

#------------------------------
# Quality vs Size max

set term qt 1 persist

set ylabel "maks. jakość"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

plot "/tmp/randomData" using 1:2 title "random" smooth unique with linespoints linecolor rgb "black" pointtype 7 linetype 1, \
     "/tmp/greedyData" using 1:2 title "greedy" smooth unique with linespoints linecolor rgb "red" pointtype 7 linetype 1, \
     "/tmp/steepestData" using 1:2 title "steepest" smooth unique with linespoints linecolor rgb "green" pointtype 7 linetype 1, \
     "/tmp/heuristicData" using 1:2 title "heuristic" smooth unique with linespoints linecolor rgb "blue" pointtype 7 linetype 1

set term epslatex color size 15cm, 10cm
set output "./plotQualitySizeMax.tex"
replot

#------------------------------
# Time vs Size
set term qt 2 persist

set key inside top left

set yrange [0:0.004]
set ytics 1e-3
set mytics 2

set ylabel "$t$ [s]"
set format y "\\num{%g}"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

frandom(x) = ar*x**2+br*x+cr
ar=1e-15; br=1e-10; cr=1e-10;
fit frandom(x) "<(sed -n -e '1,9p' -e '11,14p' /tmp/randomData)" using 1:5 via ar, br, cr

fgreedy(x) = ag*x**2+bg*x+cg
ag = 2.4e-6; bg=1e-10; cg=1e-10;
fit fgreedy(x) "<(sed -n -e '1,9p' -e '11,14p' /tmp/greedyData)" using 1:5 via ag, bg, cg

fsteepest(x) = as*x**2+bs*x+cs
as = 2.4e-6; bs=1e-10; cs=1e-10;
fit fsteepest(x) "<(sed -n -e '1,9p' -e '11,14p' /tmp/steepestData)" using 1:5 via as, bs, cs

fheuristic(x) = ah*x**2+bh*x+ch
ah=1e-15; bh=1e-10; ch=1e-10;
fit fheuristic(x) "<(sed -n -e '1,9p' -e '11,14p' /tmp/heuristicData)" using 1:3 via ah, bh, ch

plot "/tmp/randomData" using 1:5:6 title "random" with yerrorbars linecolor rgb "black" pointtype 7 linetype 1, \
     frandom(x) title "" with lines linecolor rgb "black" linetype 2, \
     "/tmp/greedyData" using 1:5:6 title "greedy" with yerrorbars linecolor rgb "red" pointtype 7 linetype 1, \
     fgreedy(x) title "" with lines linecolor rgb "red" linetype 2, \
     "/tmp/steepestData" using 1:5:6 title "steepest" with yerrorbars linecolor rgb "green" pointtype 7 linetype 1, \
     fsteepest(x) title "" with lines linecolor rgb "green" linetype 2, \
     "/tmp/heuristicData" using 1:3 title "heuristic" with points linecolor rgb "blue" pointtype 7, \
     fheuristic(x) title "" with lines linecolor rgb "blue" linetype 2

set term epslatex color size 15cm, 10cm
set output "./plotTimeSize.tex"
replot

#------------------------------
# SAME FOR HEURISTIC AND RANDOM
set term qt 3 persist

set yrange [0:1.2e-4]
set ytics 2e-5
set mytics 2

set ylabel "$t$ [s]"
set format y "\\num{%g}"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

plot "/tmp/heuristicData" using 1:3 title "heuristic" with points linecolor rgb "blue" pointtype 7, \
     fheuristic(x) title "" with lines linecolor rgb "blue" linetype 2

set term epslatex color size 15cm, 10cm
set output "./plotTimeSizeHeuristic.tex"
replot

#------------------------------
# SAME FOR !!!ONLY!!! RANDOM
set term qt 4 persist

set yrange [0:6e-7]
set ytics 1e-7
set mytics 2

set ylabel "$t$ [s]"
set format y "\\num{%g}"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

plot "/tmp/randomData" using 1:5:6 title "random" with yerrorbars linecolor rgb "black" pointtype 7 linetype 1, \
     frandom(x) title "" with lines linecolor rgb "black" linetype 2

set term epslatex color size 15cm, 10cm
set output "./plotTimeSizeRandom.tex"
replot

#------------------------------
# QUALITY vs TIME chosen only
set term qt 5 persist

set key inside bottom right

set yrange [0:1.2]
set ytics 0.2
set mytics 2

set ylabel "$\\underrightarrow{\\textrm{jakość}}$"
set format y "\\num{%g}"

set xlabel "$\\underleftarrow{t\\textrm{ [s]}}$"
set xrange [1e-5:0.01]
set format x "\\num{%g}"
set xtics 10
set mxtics 10

set logscale x 10

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

set pointsize 1.5

plot "<(sed -n '5,5p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 5, \
     "<(sed -n '5,5p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 5, \
     "<(sed -n '5,5p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 5, \
     "<(sed -n '5,5p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 5, \
     \
     "<(sed -n '6,6p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 6, \
     "<(sed -n '6,6p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 6, \
     "<(sed -n '6,6p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 6, \
     "<(sed -n '6,6p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 6, \
     \
     "<(sed -n '7,7p' /tmp/randomData)" using 5:3 title "random" linecolor rgb "black" pointtype 7, \
     "<(sed -n '7,7p' /tmp/greedyData)" using 5:3 title "greedy" linecolor rgb "red" pointtype 7, \
     "<(sed -n '7,7p' /tmp/steepestData)" using 5:3 title "steepest" linecolor rgb "green" pointtype 7, \
     "<(sed -n '7,7p' /tmp/heuristicData)" using 3:2 title "heuristic" with points linecolor rgb "blue" pointtype 7, \
     \
     "<(sed -n '8,8p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 8, \
     "<(sed -n '8,8p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 8, \
     "<(sed -n '8,8p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 8, \
     "<(sed -n '8,8p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 8

set term epslatex color size 15cm, 10cm
set output "./plotQualityTime.tex"
replot

unset pointsize
unset logscale x

#------------------------------
# QUALITY vs TIME !!!ALL!!!
set term qt 6 persist

set key below

set yrange [0:1.2]
set ytics 0.2
set mytics 2

set ylabel "$\\underrightarrow{\\textrm{jakość}}$"
set format y "\\num{%g}"

set xlabel "$\\underleftarrow{t\\textrm{ [s]}}$"
set xrange [1e-5:0.01]
set format x "\\num{%g}"
set xtics 10
set mxtics 10

set logscale x 10

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

set pointsize 2

plot "<(sed -n '1,1p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 1, \
     "<(sed -n '1,1p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 1, \
     "<(sed -n '1,1p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 1, \
     "<(sed -n '1,1p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 1, \
     \
     "<(sed -n '2,2p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 2, \
     "<(sed -n '2,2p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 2, \
     "<(sed -n '2,2p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 2, \
     "<(sed -n '2,2p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 2, \
     \
     "<(sed -n '3,3p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 3, \
     "<(sed -n '3,3p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 3, \
     "<(sed -n '3,3p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 3, \
     "<(sed -n '3,3p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 3, \
     \
     "<(sed -n '4,4p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 4, \
     "<(sed -n '4,4p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 4, \
     "<(sed -n '4,4p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 4, \
     "<(sed -n '4,4p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 4, \
     \
     "<(sed -n '5,5p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 5, \
     "<(sed -n '5,5p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 5, \
     "<(sed -n '5,5p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 5, \
     "<(sed -n '5,5p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 5, \
     \
     "<(sed -n '6,6p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 6, \
     "<(sed -n '6,6p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 6, \
     "<(sed -n '6,6p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 6, \
     "<(sed -n '6,6p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 6, \
     \
     "<(sed -n '7,7p' /tmp/randomData)" using 5:3 title "random" linecolor rgb "black" pointtype 7, \
     "<(sed -n '7,7p' /tmp/greedyData)" using 5:3 title "greedy" linecolor rgb "red" pointtype 7, \
     "<(sed -n '7,7p' /tmp/steepestData)" using 5:3 title "steepest" linecolor rgb "green" pointtype 7, \
     "<(sed -n '7,7p' /tmp/heuristicData)" using 3:2 title "heuristic" with points linecolor rgb "blue" pointtype 7, \
     \
     "<(sed -n '8,8p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 8, \
     "<(sed -n '8,8p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 8, \
     "<(sed -n '8,8p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 8, \
     "<(sed -n '8,8p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 8, \
     \
     "<(sed -n '9,9p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 9, \
     "<(sed -n '9,9p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 9, \
     "<(sed -n '9,9p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 9, \
     "<(sed -n '9,9p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 9, \
     \
     "<(sed -n '10,10p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 10, \
     "<(sed -n '10,10p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 10, \
     "<(sed -n '10,10p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 10, \
     "<(sed -n '10,10p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 10, \
     \
     "<(sed -n '11,11p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 11, \
     "<(sed -n '11,11p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 11, \
     "<(sed -n '11,11p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 11, \
     "<(sed -n '11,11p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 11, \
     \
     "<(sed -n '12,12p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 12, \
     "<(sed -n '12,12p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 12, \
     "<(sed -n '12,12p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 12, \
     "<(sed -n '12,12p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 12, \
     \
     "<(sed -n '13,13p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 13, \
     "<(sed -n '13,13p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 13, \
     "<(sed -n '13,13p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 13, \
     "<(sed -n '13,13p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 13, \
     \
     "<(sed -n '14,14p' /tmp/randomData)" using 5:3 title "" linecolor rgb "black" pointtype 14, \
     "<(sed -n '14,14p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 14, \
     "<(sed -n '14,14p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 14, \
     "<(sed -n '14,14p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 14, \

set term epslatex color size 16.5cm, 13cm
set output "./plotQualityTimeFull.tex"
replot

unset pointsize
unset logscale x

#------------------------------
#Number of steps vs instance size
set term qt 7 persist

set key inside top left
set yrange [0:100]
set ytics 10
set mytics 2

set ylabel "śr. liczba kroków"
set format y "\\num{%g}"

set xrange[10:34]
set xlabel "rozmiar problemu"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

plot "/tmp/greedyData" using 1:7 title "greedy" linecolor rgb "red" pointtype 7, \
     "/tmp/steepestData" using 1:7 title "steepest" linecolor rgb "green" pointtype 7

set term epslatex color size 15cm, 10cm
set output "./plotStepsSize.tex"
replot

