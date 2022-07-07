changequote([,])changecom(%)
%
% by Behdad Esfahbod, 2002
% Part of faanoos Transcription Schema for Persian Text
%
% This file is not copyrighted -- public domain
%
% Finalize faanoos transcription tranlation process
%
include([faanoos.inc.m4])

input: 2;
output: 2;

expressions:

KASREEZAFEOPT	=> KASREEZAFE;
YEHEZAFEOPT	=> YEHEZAFE;
TASHDIDOPT	=> TASHDID;
ZWNJ ZWNJ	=>		<= ZWNJ;
ZWJ ZWJ		=>		<= ZWJ;
OMEGAPERCENT	=> PERCENT;

.	=> \1;

%
% End of file
