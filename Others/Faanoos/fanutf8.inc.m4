%
% by Behdad Esfahbod, 2002
% Part of faanoos Transcription Schema for Persian Text
%
% This file is not copyrighted -- public domain
%
define([badutferr], "\errmessage{Malformed UTF-8 sequence in faanoos input: $1}")

% Handle single octet characters
@"00-@"7F
	=> \1;

% Handle two octet characters
(@"C2-@"DF)(@"80-@"BF)
	=> #(((\1-@"C0)*@"40) + (\2-@"80));

% Handle three octet characters
(@"E0-@"EF)(@"80-@"BF)<2,2>
	=> #(((\1-@"E0)*@"1000) + ((\2-@"80)*@"40) + (\3-@"80));

% Handle four octet characters
% Generate surrogate pairs while Omega is 16bit
% It has bad side-effects, so should be changed as soon as Omega becomes 32bit
(@"F0-@"F7)(@"80-@"BF)<3,3>
	=> #(((\1-@"F0)*@"100) + ((\2-@"80)*@"4) + ((\3-@"80)div:@"10) - @"40 + @"D800)
	   #((((\3-@"80)mod:@"10)*@"40) + (\4-@"80) + @"DC00);

% Others pass through
(@"0100-@"FFFC)
	=> \*;

.	=> @"FFFD badutferr(\*);
