@echo off
%3
cd "%1"
ftx2tex "%2"
etex "&farsitex" "%2"
ftx2tex "%2"
etex "&farsitex" "%2"
fmakeidx "%2.idx"
ftx2tex "%2"
etex "&farsitex" "%2"
dvips "%2"
ps2pdf -sPAPERSIZE#a4 "%2.ps" %2.pdf
erase "%2.tex"
erase "%2.aux"
erase "%2.ps"
erase "%2.dvi"
erase "%2.log"
erase "%2.bak"
erase "%2.idx"
erase "%2.ind"
erase "%2.toc"
erase "%2.lot"
erase "%2.lof"
