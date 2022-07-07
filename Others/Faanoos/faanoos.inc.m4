divert(-1)dnl
%
% by Behdad Esfahbod, 2002
% Part of faanoos Transcription Schema for Persian Text
%
% This file is not copyrighted -- public domain
%
define([TASHDID], @"0651)
define([KASRE], @"0650)
define([KASREEZAFE], KASRE)
define([YEH], @"06CC)
define([YEHEZAFE], ZWNJ YEH)
define([HAMZAABOVE], @"0654)
define([ZWNJ], @"200C)
define([ZWJ], @"200D)
define([PERCENT], @"066A)
% Omega specific
define([OMEGAPERCENT], @"F025)
% Assign non-unicode code-points to these, to recover later:
define([KASREEZAFEOPT], @"F650)
define([YEHEZAFEOPT], @"F6CC)
define([TASHDIDOPT], @"F651)
divert[]dnl
