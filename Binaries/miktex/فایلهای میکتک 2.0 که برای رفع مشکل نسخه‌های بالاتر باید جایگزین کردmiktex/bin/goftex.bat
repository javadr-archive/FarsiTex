@echo off
%3
cd %1
ftx2tex %2.ftx %2.tex
etex "&farsitex" %2
