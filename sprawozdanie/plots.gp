# Quality vs Size mean
set term qt 0 persist

set yrange [0:1.2]
set xrange [10:52]

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
# Quality vs Size mean META
set term qt 1 persist

set format x "$%g$"
set format y "\\num{%.1f}"

set xlabel "rozmiar problemu"
set ylabel "śr. jakość"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

plot "/tmp/simulatedData" using 1:3:4 title "simulated ann." with yerrorbars linecolor rgb "black" pointtype 7 linetype 1, \
     "/tmp/simulatedData" using 1:3 title "" smooth unique with lines linecolor rgb "black" linetype 1, \
     "/tmp/tabuData" using 1:3:4 title "tabu" smooth unique with yerrorbars linecolor rgb "blue" pointtype 7 linetype 1, \
     "/tmp/tabuData" using 1:3 title "" smooth unique with lines linecolor rgb "blue" linetype 1, \
     "/tmp/greedyData" using 1:3:4 title "greedy" with yerrorbars linecolor rgb "red" pointtype 7 linetype 1, \
     "/tmp/greedyData" using 1:3 title "" smooth unique with lines linecolor rgb "red" linetype 1, \
     "/tmp/steepestData" using 1:3:4 title "steepest" with yerrorbars linecolor rgb "green" pointtype 7 linetype 1, \
     "/tmp/steepestData" using 1:3 title "" smooth unique with lines linecolor rgb "green" linetype 1

set term epslatex color size 15cm, 10cm
set output "./plotQualitySizeMeanMETA.tex"
replot


#------------------------------
# Quality vs Size max

set term qt 2 persist

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
# Quality vs Size max META

set term qt 3 persist

set ylabel "maks. jakość"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

plot "/tmp/simulatedData" using 1:2 title "simulated ann." smooth unique with linespoints linecolor rgb "black" pointtype 7 linetype 1, \
     "/tmp/tabuData" using 1:2 title "tabu" smooth unique with linespoints linecolor rgb "blue" pointtype 7 linetype 1, \
     "/tmp/greedyData" using 1:2 title "greedy" smooth unique with linespoints linecolor rgb "red" pointtype 7 linetype 1, \
     "/tmp/steepestData" using 1:2 title "steepest" smooth unique with linespoints linecolor rgb "green" pointtype 7 linetype 1

set term epslatex color size 15cm, 10cm
set output "./plotQualitySizeMaxMETA.tex"
replot

#------------------------------
# Time vs Size
set term qt 4 persist

set key inside top left

set yrange [0:0.02]
set ytics 2e-3
set mytics 2

set ylabel "$t$ [s]"
set format y "\\num{%g}"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

frandom(x) = ar*x**2+br*x+cr
ar=1e-15; br=1e-10; cr=1e-10;
fit frandom(x) "<(sed -n -e '1,9p' -e '11,18p' /tmp/randomData)" using 1:5 via ar, br, cr

fgreedy(x) = ag*x**2+bg*x+cg
ag = 2.4e-6; bg=1e-10; cg=1e-10;
fit fgreedy(x) "<(sed -n -e '1,9p' -e '11,18p' /tmp/greedyData)" using 1:5 via ag, bg, cg

fsteepest(x) = as*x**2+bs*x+cs
as = 2.4e-6; bs=1e-10; cs=1e-10;
fit fsteepest(x) "<(sed -n -e '1,9p' -e '11,18p' /tmp/steepestData)" using 1:5 via as, bs, cs

fheuristic(x) = ah*x**2+bh*x+ch
ah=1e-15; bh=1e-10; ch=1e-10;
fit fheuristic(x) "<(sed -n -e '1,9p' -e '11,18p' /tmp/heuristicData)" using 1:3 via ah, bh, ch

fsimulated(x) = asim*x**2+bsim*x+csim
asim=2.4e-6; bsim=1e-10; csim=1e-10;
fit fsimulated(x) "<(sed -n -e '1,9p' -e '11,18p' /tmp/simulatedData)" using 1:5 via asim, bsim, csim

plot "/tmp/randomData" using 1:5:6 title "random" with yerrorbars linecolor rgb "black" pointtype 7 linetype 1, \
     frandom(x) title "" with lines linecolor rgb "black" linetype 2, \
     "/tmp/greedyData" using 1:5:6 title "greedy" with yerrorbars linecolor rgb "red" pointtype 7 linetype 1, \
     fgreedy(x) title "" with lines linecolor rgb "red" linetype 2, \
     "/tmp/steepestData" using 1:5:6 title "steepest" with yerrorbars linecolor rgb "green" pointtype 7 linetype 1, \
     fsteepest(x) title "" with lines linecolor rgb "green" linetype 2, \
     "/tmp/heuristicData" using 1:3 title "heuristic" with points linecolor rgb "blue" pointtype 7, \
     fheuristic(x) title "" with lines linecolor rgb "blue" linetype 2, \
     "/tmp/simulatedData" using 1:5:6 title "simulated ann." with yerrorbars linecolor rgb "magenta" pointtype 7 linetype 1, \
     fsimulated(x) title "" with lines linecolor rgb "magenta" linetype 2, \


set term epslatex color size 15cm, 10cm
set output "./plotTimeSize.tex"
replot

#------------------------------
# Time vs Size META
set term qt 5 persist

set key inside bottom

set yrange [0:50]
set ytics 10
set mytics 5

set ylabel "$t$ [s]"
set format y "\\num{%g}"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

ftabu(x) = atabu*x**2+btabu*x+ctabu
atabu = 2.4e-6; btabu=1e-10; ctabu=1e-10;
fit ftabu(x) "<(sed -n -e '1,9p' -e '11,18p' /tmp/tabuData)" using 1:5 via atabu, btabu, ctabu

plot "/tmp/tabuData" using 1:5:6 title "tabu" with yerrorbars linecolor rgb "blue" pointtype 7 linetype 1, \
     ftabu(x) title "" with lines linecolor rgb "blue" linetype 2

set term epslatex color size 15cm, 10cm
set output "./plotTimeSizeMETA.tex"
replot

#------------------------------
# SAME FOR HEURISTIC ONLY
set term qt 6 persist

set yrange [0:2.2e-4]
set ytics 2e-5
set mytics 2

unset key

set ylabel "$t$ [s]"
set format y "\\num{%g}"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

plot "/tmp/heuristicData" using 1:3 title "" with points linecolor rgb "blue" pointtype 7, \
     fheuristic(x) title "" with lines linecolor rgb "blue" linetype 2

set term epslatex color size 15cm, 10cm
set output "./plotTimeSizeHeuristic.tex"
replot

#------------------------------
# QUALITY vs TIME chosen only
set term qt 7 persist

set key inside bottom right

set yrange [0:1]
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
set term qt 8 persist

set key below

set yrange [0:1]
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
     "<(sed -n '14,14p' /tmp/heuristicData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 14

set term epslatex color size 16.5cm, 13cm
set output "./plotQualityTimeFull.tex"
replot

unset pointsize
unset logscale x

#------------------------------
# QUALITY vs TIME META !!!ALL!!!
set term qt 9 persist

set key below

set yrange [0:1]
set ytics 0.2
set mytics 2

set ylabel "$\\underrightarrow{\\textrm{jakość}}$"
set format y "\\num{%g}"

set xlabel "$\\underleftarrow{t\\textrm{ [s]}}$"
set xrange [1e-5:1]
set format x "\\num{%g}"
set xtics 10
set mxtics 10

set logscale x 10

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

set pointsize 2

plot "<(sed -n '1,1p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 1, \
     "<(sed -n '1,1p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 1, \
     "<(sed -n '1,1p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 1, \
     "<(sed -n '1,1p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 1, \
     \
     "<(sed -n '2,2p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 2, \
     "<(sed -n '2,2p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 2, \
     "<(sed -n '2,2p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 2, \
     "<(sed -n '2,2p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 2, \
     \
     "<(sed -n '3,3p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 3, \
     "<(sed -n '3,3p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 3, \
     "<(sed -n '3,3p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 3, \
     "<(sed -n '3,3p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 3, \
     \
     "<(sed -n '4,4p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 4, \
     "<(sed -n '4,4p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 4, \
     "<(sed -n '4,4p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 4, \
     "<(sed -n '4,4p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 4, \
     \
     "<(sed -n '5,5p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 5, \
     "<(sed -n '5,5p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 5, \
     "<(sed -n '5,5p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 5, \
     "<(sed -n '5,5p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 5, \
     \
     "<(sed -n '6,6p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 6, \
     "<(sed -n '6,6p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 6, \
     "<(sed -n '6,6p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 6, \
     "<(sed -n '6,6p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 6, \
     \
     "<(sed -n '7,7p' /tmp/simulatedData)" using 5:3 title "simulated ann." linecolor rgb "black" pointtype 7, \
     "<(sed -n '7,7p' /tmp/greedyData)" using 5:3 title "greedy" linecolor rgb "red" pointtype 7, \
     "<(sed -n '7,7p' /tmp/steepestData)" using 5:3 title "steepest" linecolor rgb "green" pointtype 7, \
     "<(sed -n '7,7p' /tmp/tabuData)" using 3:2 title "tabu" with points linecolor rgb "blue" pointtype 7, \
     \
     "<(sed -n '8,8p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 8, \
     "<(sed -n '8,8p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 8, \
     "<(sed -n '8,8p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 8, \
     "<(sed -n '8,8p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 8, \
     \
     "<(sed -n '9,9p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 9, \
     "<(sed -n '9,9p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 9, \
     "<(sed -n '9,9p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 9, \
     "<(sed -n '9,9p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 9, \
     \
     "<(sed -n '10,10p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 10, \
     "<(sed -n '10,10p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 10, \
     "<(sed -n '10,10p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 10, \
     "<(sed -n '10,10p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 10, \
     \
     "<(sed -n '11,11p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 11, \
     "<(sed -n '11,11p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 11, \
     "<(sed -n '11,11p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 11, \
     "<(sed -n '11,11p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 11, \
     \
     "<(sed -n '12,12p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 12, \
     "<(sed -n '12,12p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 12, \
     "<(sed -n '12,12p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 12, \
     "<(sed -n '12,12p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 12, \
     \
     "<(sed -n '13,13p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 13, \
     "<(sed -n '13,13p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 13, \
     "<(sed -n '13,13p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 13, \
     "<(sed -n '13,13p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 13, \
     \
     "<(sed -n '14,14p' /tmp/simulatedData)" using 5:3 title "" linecolor rgb "black" pointtype 14, \
     "<(sed -n '14,14p' /tmp/greedyData)" using 5:3 title "" linecolor rgb "red" pointtype 14, \
     "<(sed -n '14,14p' /tmp/steepestData)" using 5:3 title "" linecolor rgb "green" pointtype 14, \
     "<(sed -n '14,14p' /tmp/tabuData)" using 3:2 title "" with points linecolor rgb "blue" pointtype 14

set term epslatex color size 16.5cm, 13cm
set output "./plotQualityTimeFullMETA.tex"
replot

unset pointsize
unset logscale x

#------------------------------
#Number of steps vs instance size
set term qt 10 persist

set key inside top left
set yrange [0:120]
set ytics 10
set mytics 2

set ylabel "śr. liczba kroków"
set format y "\\num{%g}"

set xrange[10:52]
set xlabel "rozmiar problemu"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

plot "/tmp/greedyData" using 1:7 title "greedy" linecolor rgb "red" pointtype 7, \
     "/tmp/steepestData" using 1:7 title "steepest" linecolor rgb "green" pointtype 7

set term epslatex color size 15cm, 10cm
set output "./plotStepsSize.tex"
replot

#------------------------------
#Number of steps vs instance size META
set term qt 11 persist

set key below
set yrange [0:5000]
set ytics 1000
set mytics 5

set ylabel "śr. liczba kroków"
set format y "\\num{%g}"

set xrange[10:52]
set xlabel "rozmiar problemu"

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

plot "/tmp/greedyData" using 1:7 title "greedy" linecolor rgb "red" pointtype 7, \
     "/tmp/steepestData" using 1:7 title "steepest" linecolor rgb "green" pointtype 7, \
     "/tmp/simulatedData" using 1:7 title "simulated ann." linecolor rgb "black" pointtype 7, \
     "/tmp/tabuData" using 1:7 title "tabu" linecolor rgb "blue" pointtype 7

set term epslatex color size 15cm, 10cm
set output "./plotStepsSizeMETA.tex"
replot

#------------------------------
# END QUALITY vs INIT QUALITY 1 INSTANCE
# !!! problems' sizes: 12 and 16 !!!
set term qt 12 persist

set key inside bottom right

set yrange [0:1.01]
set ytics 0.2
set mytics 2

set ylabel "jakość końcowa"
set format y "\\num{%g}"

set xlabel "jakość początkowa"
set xrange [0:1.01]
set format x "\\num{%g}"
set xtics 0.2
set mxtics 5

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

set pointsize 1

# problems' sizes: 12 and 16
plot "<(sed -n -e '/^12/p' /tmp/initCostsData)" using 2:3 title "steepest" linecolor rgb "green" pointtype 1, \
     "<(sed -n -e '/^12/p' /tmp/initCostsData)" using 4:5 title "greedy" linecolor rgb "red" pointtype 1, \
     "<(sed -n -e '/^16/p' /tmp/initCostsData)" using 2:3 title "" linecolor rgb "green" pointtype 15, \
     "<(sed -n -e '/^16/p' /tmp/initCostsData)" using 4:5 title "" linecolor rgb "red" pointtype 15

set term epslatex color size 16.5cm, 13cm
set output "./plotInitEndQuality.tex"
replot

#------------------------------
# END QUALITY vs INIT QUALITY 1 INSTANCE
# !!! problems' sizes: many !!!
set term qt 13 persist

set key inside bottom right

set yrange [0:1.01]
set ytics 0.2
set mytics 2

set ylabel "jakość końcowa"
set format y "\\num{%g}"

set xlabel "jakość początkowa"
set xrange [0:1.01]
set format x "\\num{%g}"
set xtics 0.2
set mxtics 5

set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"

set pointsize 1


plot "<(sed -n -e '/^12/p' /tmp/initCostsData)" using 2:3 title "steepest" linecolor rgb "green" pointtype 1, \
     "<(sed -n -e '/^12/p' /tmp/initCostsData)" using 4:5 title "greedy" linecolor rgb "red" pointtype 1, \
     "<(sed -n -e '/^14/p' /tmp/initCostsData)" using 2:3 title "" linecolor rgb "green" pointtype 4, \
     "<(sed -n -e '/^14/p' /tmp/initCostsData)" using 4:5 title "" linecolor rgb "red" pointtype 4, \
     "<(sed -n -e '/^16/p' /tmp/initCostsData)" using 2:3 title "" linecolor rgb "green" pointtype 10, \
     "<(sed -n -e '/^16/p' /tmp/initCostsData)" using 4:5 title "" linecolor rgb "red" pointtype 10, \
     "<(sed -n -e '/^17/p' /tmp/initCostsData)" using 2:3 title "" linecolor rgb "green" pointtype 19, \
     "<(sed -n -e '/^17/p' /tmp/initCostsData)" using 4:5 title "" linecolor rgb "red" pointtype 19, \
     "<(sed -n -e '/^18/p' /tmp/initCostsData)" using 2:3 title "" linecolor rgb "green" pointtype 2, \
     "<(sed -n -e '/^18/p' /tmp/initCostsData)" using 4:5 title "" linecolor rgb "red" pointtype 2, \
     "<(sed -n -e '/^19/p' /tmp/initCostsData)" using 2:3 title "" linecolor rgb "green" pointtype 15, \
     "<(sed -n -e '/^19/p' /tmp/initCostsData)" using 4:5 title "" linecolor rgb "red" pointtype 15, \
     "<(sed -n -e '/^20/p' /tmp/initCostsData)" using 2:3 title "" linecolor rgb "green" pointtype 15, \
     "<(sed -n -e '/^20/p' /tmp/initCostsData)" using 4:5 title "" linecolor rgb "red" pointtype 15, \
     "<(sed -n -e '/^30/p' /tmp/initCostsData)" using 2:3 title "" linecolor rgb "green" pointtype 15, \
     "<(sed -n -e '/^30/p' /tmp/initCostsData)" using 4:5 title "" linecolor rgb "red" pointtype 15, \
     "<(sed -n -e '/^50/p' /tmp/initCostsData)" using 2:3 title "" linecolor rgb "green" pointtype 15, \
     "<(sed -n -e '/^50/p' /tmp/initCostsData)" using 4:5 title "" linecolor rgb "red" pointtype 15

set term epslatex color size 16.5cm, 13cm
set output "./plotInitEndQualityAll.tex"
replot

unset pointsize

#------------------------------
# max quality vs run no
# problem ste36

set term qt 14 persist
set pointsize 1
set key bottom right
set xlabel "liczba uruchomień"
set ylabel "maks.~jakość"
set format y "\\num{%g}"

set ytics 0.02
set xtics 20
unset mxtics
unset mytics

set xrange [0:30]
set yrange [0.9:1]

plot "/tmp/steepSte36.dat" title "Steepest" with linespoints linetype 1 linecolor rgb "green", \
     "/tmp/greedySte36.dat" title "Greedy" with linespoints linetype 1 linecolor rgb "red"

set term epslatex color size 16.5cm, 13cm
set output "./plotQualityRunNo.tex"
replot
