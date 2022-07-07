@echo off
%3
cd %1
ftx2tex %2.ftx
etex "&farsitex" %2.tex
