#!/bin/sh

# using the gnuplot to plot the discretied data

# plot the velocity

gnuplot <<EOF
set term post enhanced color solid linewidth 2.0 20
set encoding utf8
set termoption dash
set style increment user

name="SST"

time = system("foamListTimes -case .. | tail -1")

# output the velocity at r/D = 0.5
  set terminal png 
  set output "current_result/V0.5.png"
  set key font "Times Roman, 12"
  set xtics 0, 0.1, 0.4 font "Times Roman, 12"
  set ytics 0, 0.2, 1.2 font "Times Roman, 12"
  set xlabel "{/Times-Italic y/D}" font "Times Roman, 14" 
  set ylabel "{/Times-Italic V_{mag} / U_{b}}" font "Times Roman, 14" offset 2.4
  set xtics nomirror
  set ytics nomirror
  unset x2tics
  unset y2tics
  set border 3 linewidth 0.25
  plot [:0.4][:1.2] \
       "exp/expV_0.5.txt" using (\$1):(\$2) title "Cooper et al. 1993" w p pointtype 5 pointsize 0.75, \
       "../postProcessing/sets/".time."/Radial_0.5_U.xy" \
       using (\$1/0.04):(sqrt(\$2*\$2+\$4*\$4)/8.9) title name w l linecolor black
       

# output the velocity at r/D = 1.0
  set terminal png 
  set output "current_result/V1.0.png"
  set key font "Times Roman, 12"
  set xtics 0, 0.1, 0.4 font "Times Roman, 12"
  set ytics 0, 0.2, 1.2 font "Times Roman, 12"
  set xlabel "{/Times-Italic y/D}" font "Times Roman, 14" 
  set ylabel "{/Times-Italic V_{mag} / U_{b}}" font "Times Roman, 14" offset 2.4
  set xtics nomirror
  set ytics nomirror
  unset x2tics
  unset y2tics
  set border 3 linewidth 0.25
  plot [:0.4][:1.2] \
       "exp/expV_1.0.txt" using (\$1):(\$2) title "Cooper et al. 1993" w p pointtype 5 pointsize 0.75, \
       "../postProcessing/sets/".time."/Radial_1.0_U.xy" \
       using (\$1/0.04):(sqrt(\$2*\$2+\$4*\$4)/8.9) title name w l linecolor black
       

# output the velocity at r/D = 1.5
  set terminal png 
  set output "current_result/V1.5.png"
  set key font "Times Roman, 12"
  set xtics 0, 0.1, 0.4 font "Times Roman, 12"
  set ytics 0, 0.2, 1.2 font "Times Roman, 12"
  set xlabel "{/Times-Italic y/D}" font "Times Roman, 14" 
  set ylabel "{/Times-Italic V_{mag} / U_{b}}" font "Times Roman, 14" offset 2.4
  set xtics nomirror
  set ytics nomirror
  unset x2tics
  unset y2tics
  set border 3 linewidth 0.25
  plot [:0.4][:1.2] \
       "exp/expV_1.5.txt" using (\$1):(\$2) title "Cooper et al. 1993" w p pointtype 5 pointsize 0.75, \
       "../postProcessing/sets/".time."/Radial_1.5_U.xy" \
       using (\$1/0.04):(sqrt(\$2*\$2+\$4*\$4)/8.9) title name w l linecolor black
       

# output the velocity at r/D = 2.0
  set terminal png 
  set output "current_result/V2.0.png"
  set key font "Times Roman, 12"
  set xtics 0, 0.1, 0.4 font "Times Roman, 12"
  set ytics 0, 0.2, 1.2 font "Times Roman, 12"
  set xlabel "{/Times-Italic y/D}" font "Times Roman, 14" 
  set ylabel "{/Times-Italic V_{mag} / U_{b}}" font "Times Roman, 14" offset 2.4
  set xtics nomirror
  set ytics nomirror
  unset x2tics
  unset y2tics
  set border 3 linewidth 0.25
  plot [:0.4][:1.2] \
       "exp/expV_2.0.txt" using (\$1):(\$2) title "Cooper et al. 1993" w p pointtype 5 pointsize 0.75, \
       "../postProcessing/sets/".time."/Radial_2.0_U.xy" \
       using (\$1/0.04):(sqrt(\$2*\$2+\$4*\$4)/8.9) title name w l linecolor black

# output the velocity at r/D = 2.5
  set terminal png 
  set output "current_result/V2.5.png"
  set key font "Times Roman, 12"
  set xtics 0, 0.1, 0.4 font "Times Roman, 12"
  set ytics 0, 0.2, 1.2 font "Times Roman, 12"
  set xlabel "{/Times-Italic y/D}" font "Times Roman, 14" 
  set ylabel "{/Times-Italic V_{mag} / U_{b}}" font "Times Roman, 14" offset 2.4
  set xtics nomirror
  set ytics nomirror
  unset x2tics
  unset y2tics
  set border 3 linewidth 0.25
  plot [:0.4][:1.2] \
       "exp/expV_2.5.txt" using (\$1):(\$2) title "Cooper et al. 1993" w p pointtype 5 pointsize 0.75, \
       "../postProcessing/sets/".time."/Radial_2.5_U.xy" \
       using (\$1/0.04):(sqrt(\$2*\$2+\$4*\$4)/8.9) title name w l linecolor black

# output the velocity at r/D = 3.0
  set terminal png 
  set output "current_result/V3.0.png"
  set key font "Times Roman, 12"
  set xtics 0, 0.1, 0.4 font "Times Roman, 12"
  set ytics 0, 0.2, 1.2 font "Times Roman, 12"
  set xlabel "{/Times-Italic y/D}" font "Times Roman, 14" 
  set ylabel "{/Times-Italic V_{mag} / U_{b}}" font "Times Roman, 14" offset 2.4
  set xtics nomirror
  set ytics nomirror
  unset x2tics
  unset y2tics
  set border 3 linewidth 0.25
  plot [:0.4][:1.2] \
       "exp/expV_3.0.txt" using (\$1):(\$2) title "Cooper et al. 1993" w p pointtype 5 pointsize 0.75, \
       "../postProcessing/sets/".time."/Radial_3.0_U.xy" \
       using (\$1/0.04):(sqrt(\$2*\$2+\$4*\$4)/8.9) title name w l linecolor black

