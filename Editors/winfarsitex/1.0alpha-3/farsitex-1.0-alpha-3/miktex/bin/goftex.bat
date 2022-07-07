@echo off
cd %1
ftx2tex %2
etex "&farsitex" %2
