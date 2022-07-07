@echo off
for %%1 in (*.ftx) do call ftx2tex %%1
etex &farsitex main
dvips main
