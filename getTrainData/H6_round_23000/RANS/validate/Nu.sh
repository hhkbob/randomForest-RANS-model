#!/bin/sh

  gnuplot << EOF


  set term post enhanced color solid linewidth 2.0 20
  set encoding utf8
  set termoption dash
  set style increment user
  time = system("foamListTimes -case .. | tail -1")
# output the Nusselt number
  set terminal png
  set output "current_result/Nu.png"
  set key font "Times Roman, 12"
  set xtics 0, 1, 8 font "Times Roman, 12"
  set ytics 0, 40, 240 font "Times Roman, 12"
  set xlabel "{/Times-Italic r/D}" font "Times Roman, 14" 
  set ylabel "{/Times-Italic Nu}" font "Times Roman, 14" offset 2.4
  set xtics nomirror
  set ytics nomirror
  unset x2tics
  unset y2tics
  set border 3 linewidth 0.25
  plot [0:8][0:240] \
       "exp/expNu.txt" using (\$1):(\$2) title "Exp" w p pointtype 5 pointsize 0.75, \
       "../postProcessing/Nu/".time."/line_grad(T).xy" \
       using (\$1/0.04):(\$4*-0.04/20.) title "SST" w p pointtype 4 pointsize 0.75
      
