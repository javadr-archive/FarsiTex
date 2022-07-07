changequote([,])changecom(%)
%%% ====================================================================
%%%  @OmegaTranslationProcess-file{
%%%     author          = "Behdad Esfahbod, Alireza Kheirkhahan"
%%%     version         = "1.0",
%%%     date            = "2002-10-10"
%%%     time            = "23:59:59 IRT"
%%%     filename        = "TeXFarsiToUnicode.otp",
%%%     address         = "Computing Center, Sharif Univ. of Tech.,
%%%                        Azadi Ave., Tehran, Iran"
%%%     telephone       = "+98 21 6022372",
%%%     FAX             = "",
%%%     checksum        = "",
%%%     email           = "omega@behdad.org",
%%%     codetable       = "ISO/ASCII",
%%%     keywords        = "",
%%%     supported       = "yes",
%%%     docstring       = "This will be part of the public domain
%%%                        faanoos Omega system.
%%%                        Omega is a TeX extension (C) John Plaice
%%%                        and Yannis Haralambous, 2002"
%%%  }
%%% ====================================================================
define([TASHDID], @"0651)
define([KASRE], @"0650)
define([DAMMA], @"0647)
define([FATHA], @"064E)
define([ALEFMADDAABOVE], @"0622)
define([ALEF], @"0627)
define([WAW], @"0648)
define([HEH], @"0647)
define([YEH], @"06CC)
define([ZWNJ], @"200C)
define([ZWJ], @"200D)
define([KASREEZAFE], KASRE)
define([YEHEZAFE], ZWNJ YEH)
define([ESQ], `=')
% Map optional marks to the actual ones by default.  This may be overrided in
% the included file below.
define([KASREEZAFEOPT], KASREEZAFE)
define([YEHEZAFEOPT], YEHEZAFE)
define([TASHDIDOPT], TASHDID)
sinclude([faanoos.inc.m4])
define([letter], $1	$2 $2	=> $3 TASHDIDOPT ;	$1	$2	=> $3 )
define([map], $1	$2	=> $3 )
define([charnotfounderr], "\errmessage{Invalid char in faanoos input: $1}")


input: 1;
output: 2;

states: IN, OUT, NUM;

aliases:

LETTERS	= (`a'-`z'|`A'-`Z'|`_'|``'|`''|`"'|`@'|`^'|`|'|ESQ);
L	= ({LETTERS});
NL	= ^({LETTERS});

expressions:


% Special ligatures
<IN>	"ALLAH"	=> @"FDF2;
<IN>	"RIAL"	=> @"FDFC ;


% Contextual analysis

<IN>	"-e"{L}		=> ZWNJ		<= \(*+1)	<OUT>;
<IN>	"-e"		=> KASREEZAFEOPT		<OUT>;
<IN>	"-E"{L}		=> ZWNJ		<= \(*+1)	<OUT>;
<IN>	"-E"		=> KASREEZAFE			<OUT>;
<IN>	"-ye"{L}	=> ZWNJ		<= \(*+1)	<OUT>;
<IN>	"-ye"		=> YEHEZAFEOPT			<OUT>;
<IN>	"-yE"{L}	=> ZWNJ		<= \(*+1)	<OUT>;
<IN>	"-yE"		=> YEHEZAFEOPT KASREEZAFE	<OUT>;
<IN>	"-ee"{L}	=> ZWNJ		<= \(*+1)	<OUT>;
<IN>	"-ee"		=> ZWNJ YEH			<OUT>;

<OUT>	"o"{L}	=> ALEF			<= \*		<IN>;
<OUT>	"o"	=> WAW;
<OUT>	"O"{L}	=> ALEF			<= \*		<IN>;
<OUT>	"O"	=> WAW;
<OUT>	"n"(`a'|`A'){L}	=>		<= \*		<IN>;
<OUT>	"n"(`a'|`A')	=>		<= \*"h"	<IN>;

<OUT>	(`a'|`A')(`a'|`A')	=> ALEFMADDAABOVE	<IN>;
<OUT>	(`a'|`e'|`A'|`E'|`i'|`u')	=> ALEF	<= \*	<IN>;

% Escaped BiDi/Joining Marks
map(	<IN>,	"""_",	@"200D);			% ZERO WIDTH JOINER - ZWJ
map(	<IN>,	"""=",	@"200D);			% ZERO WIDTH JOINER - ZWJ
map(	<IN>,	""">",	@"200E);			% LEFT-TO-RIGHT MARK
map(	<IN>,	"""<",	@"200F);			% RIGHT-TO-LEFT MARK

% Punctuation marks
map(	<OUT>,	"<<",	@"00AB);			% LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
map(	<OUT>,	">>",	@"00BB);			% RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
% TODO: use something smarter for above
map(	<OUT>,	"---",	@"2014);			% EM DASH
map(	<OUT>,	"--",	@"2013);			% EN DASH
map(	<OUT>,	"-",	@"200C);			% ZERO WIDTH NON-JOINER - ZWNJ

% TODO: a`  generates two alefs

% Mirroring
map(	<OUT>,	"<",	">");
map(	<OUT>,	">",	"<");

<IN>	.ESQ"-"	=>	<=	\1"-"\2\3"-";		% DASH
<IN>	ESQ"-"	=>	<=	"-"\1\2"-";		% DASH
<OUT>	ESQ"-"	=>	"-"; % @"2010;			% DASH

<IN>	"___"	=>	<= \*	<OUT>;			% ZWNJ TATWEEL TATWEEL TATWEEL ZWNJ
<OUT>	"___"	=> @"200C@"0640@"0640@"0640@"200C;	% ZWNJ TATWEEL TATWEEL TATWEEL ZWNJ
<IN>	"__"	=>	<= "__";			% ZWNJ TATWEEL TATWEEL ZWNJ
<OUT>	"__"	=> @"200C@"0640@"0640@"200C;		% ZWNJ TATWEEL TATWEEL ZWNJ
<IN>	"_"	=> @"0640;				% ARABIC TATWEEL
<IN>	"""|"	=> @"0640;				% ARABIC TATWEEL

<IN>	.ESQ"_"	=>	<=	\1"-"\2\3"-";		% LOW LINE
<IN>	ESQ"_"	=>	<=	"-"\1\2"-";		% LOW LINE
<OUT>	ESQ"_"	=>	@"005F;				% LOW LINE

map(	<OUT>,	[","],	@"060C);			% ARABIC COMMA
map(	<OUT>,	";",	@"061B);			% ARABIC SEMICOLON
map(	<OUT>,	"?", 	@"061F);			% ARABIC QUESTION MARK


% Digits and math symbols
<OUT>	`0'-`9'		=>		<= \*	<NUM>;	% Go in to NUM state
<NUM>	`0'-`9'		=> #(\1+@"06F0-@"0030);		% EXTENDED ARABIC-INDIC NUMS
<NUM>	"."(`0'-`9')	=> @"066B	<= \(*+1);	% ARABIC DECIMAL SEPARATOR
<NUM>	"'"(`0'-`9')	=> @"066C	<= \(*+1);	% ARABIC THOUSANDS SEPARATOR
<NUM>	.		=>		<= \*	<OUT>;	% Get out of NUM state
<OUT>	["%"]		=> @"066A;			% ARABIC PERCENT SIGN


% Semi-common consonants
letter(	<IN>,	"th",	@"062B);		% ARABIC LETTER THEH
letter(	<IN>,	"ch",	@"0686);		% ARABIC LETTER TCHEH
letter(	<IN>,	"kh",	@"062E);		% ARABIC LETTER KHAH
letter(	<IN>,	"Th",	@"0630);		% ARABIC LETTER THAL
letter(	<IN>,	"zh",	@"0698);		% ARABIC LETTER JEH
letter(	<IN>,	"sh",	@"0634);		% ARABIC LETTER SHEEN
letter(	<IN>,	"gh",	@"0642);		% ARABIC LETTER QAF
% Shortcuts
letter(	<IN>,	"dh",	@"0630);		% ARABIC LETTER THAL
letter(	<IN>,	"c",	@"062B);		% ARABIC LETTER THEH
map(	<IN>,	"x",	@"062E WAW);		% KHAH WAW

% Common consonants
letter(	<IN>,	"b",	@"0628);		% ARABIC LETTER BEH
letter(	<IN>,	"p",	@"067E);		% ARABIC LETTER PEH
letter(	<IN>,	"t",	@"062A);		% ARABIC LETTER TEH
letter(	<IN>,	"j",	@"062C);		% ARABIC LETTER JEEM
letter(	<IN>,	"d",	@"062F);		% ARABIC LETTER DAL
letter(	<IN>,	"r",	@"0631);		% ARABIC LETTER REH
letter(	<IN>,	"z",	@"0632);		% ARABIC LETTER ZAIN
letter(	<IN>,	"s",	@"0633);		% ARABIC LETTER SEEN
letter(	<IN>,	"f",	@"0641);		% ARABIC LETTER FEH
letter(	<IN>,	"k",	@"06A9);		% ARABIC LETTER KEHEH
letter(	<IN>,	"g",	@"06AF);		% ARABIC LETTER GAF
letter(	<IN>,	"l",	@"0644);		% ARABIC LETTER LAM
letter(	<IN>,	"m",	@"0645);		% ARABIC LETTER MEEM
letter(	<IN>,	"n",	@"0646);		% ARABIC LETTER NOON

% Other consonants
letter(	<IN>,	"``",	@"0621);		% ARABIC LETTER HAMZA
letter(	<IN>,	"H",	@"062D);		% ARABIC LETTER HAH
letter(	<IN>,	"S",	@"0635);		% ARABIC LETTER SAD
letter(	<IN>,	"D",	@"0636);		% ARABIC LETTER DAD
letter(	<IN>,	"T",	@"0637);		% ARABIC LETTER TAH
letter(	<IN>,	"Z",	@"0638);		% ARABIC LETTER ZAH
letter(	<IN>,	"'",	@"0639);		% ARABIC LETTER AIN
letter(	<IN>,	"q",	@"063A);		% ARABIC LETTER GHAIN
letter(	<IN>,	"h",	@"0647);		% ARABIC LETTER HEH

% Arabic letters
letter(	<IN>,	"K",	@"0643);		% ARABIC LETTER KAF
letter(	<IN>,	"""h",	@"0629);		% ARABIC LETTER TEH MARBUTA
letter(	<IN>,	"Y",	@"064A);		% ARABIC LETTER YEH
letter(	<IN>,	"I",	@"0649);		% ARABIC LETTER ALEF MAKSURA

% Consonant vowels!!!
letter(	<IN>,	`v',	@"0648);		% ARABIC LETTER WAW
letter(	<IN>,	`w',	@"0648);		% ARABIC LETTER WAW
letter(	<IN>,	`y',	@"06CC);		% ARABIC LETTER FARSI YEH

% Vowels
map(	<IN>,	"A"(`A'|`a'),	@"0622);	% ARABIC LETTER ALEF WITH MADDA ABOVE
map(	<IN>,	"aa",	@"0627);		% ARABIC LETTER ALEF
map(	<IN>,	"oo",	@"0648);		% ARABIC LETTER WAW
map(	<IN>,	"eo",	@"0648);		% ARABIC LETTER WAW
map(	<IN>,	"u",	@"0648);		% ARABIC LETTER WAW
map(	<IN>,	"ee",	@"06CC);		% ARABIC LETTER FARSI YEH
map(	<IN>,	"ea",	@"06CC);		% ARABIC LETTER FARSI YEH
map(	<IN>,	"ae",	@"06CC);		% ARABIC LETTER FARSI YEH
map(	<IN>,	"iy",	@"06CC);		% ARABIC LETTER FARSI YEH
map(	<IN>,	"i",	@"06CC);		% ARABIC LETTER FARSI YEH
map(	<IN>,	"""A",	@"0671);		% ARABIC LETTER ALEF WASLA


% Diacritics
map(	<IN>,	"aN",	@"0627 @"064B);		% ALEF FATHATAN
map(	<IN>,	"AN",	@"064B);		% ARABIC FATHATAN
map(	<IN>,	"EN",	@"064D);		% ARABIC KASRATAN
map(	<IN>,	"ON",	@"064C);		% ARABIC DAMMATAN
map(	<IN>,	"A",	@"064E);		% ARABIC FATHA
map(	<IN>,	"E",	@"0650);		% ARABIC KASRA
map(	<IN>,	"O",	@"064F);		% ARABIC DAMMA
map(	<IN>,	"""",	@"0651);		% ARABIC SHADDA
map(	<IN>,	"^",	@"0652);		% ARABIC SUKUN
map(	<IN>,	"@",	@"0653);		% ARABIC MADDAH ABOVE
map(	<IN>,	"`",	@"0654);		% ARABIC HAMZA ABOVE
map(	<IN>,	"`""",	@"0655);		% ARABIC HAMZA BELOW
map(	<IN>,	"|",	@"0670);		% ARABIC LETTER SUPERSCRIPT ALEF
% Help HAMZA ABOVE and HAMZA BELOW
<IN>	(`a'|`e'|`o')"`"	=>	<= \1\*;
<IN>	(`a'|`e'|`o')"`"""	=>	<= \1\*;


% Contextual analysis
<IN>	"e"{L}	=>			<= \$;
<IN>	"e"	=> HEH;
<IN>	"E"{L}	=> KASRE		<= \$;
<IN>	"E"	=> KASRE HEH;
<IN>	"o"{L}	=>			<= \$;
<IN>	"o"	=> WAW;
<IN>	"O"{L}	=> DAMMA		<= \$;
<IN>	"O"	=> DAMMA WAW;
<IN>	"a"	=>;
<IN>	"A"	=> FATHA;


% Handle neutral character
<IN>	ESQ ESQ	=>			<= \$	<OUT>;
<IN>	ESQ	=> ;
<OUT>	ESQ ESQ	=> ESQ;

% Other characters
<IN>	{L}	=> @"FFFD charnotfounderr(\*); 		% Not a character mark
<OUT>	{L}	=>			<= \*	<IN>;	% Go to IN state
<IN>	.	=>			<= \*	<OUT>;	% Go to OUT state
<OUT>	@"00-@"7F	=> \*;				% We are ASCII, map to themselves
<OUT>	.	=>			<= \*	<pop:>;	% Fall back to default process

% Handle other characters
@"00-@"7F	=>			<= \*	<push:OUT>;	% Go to OUT state on ASCII input
% Treat as UTF-8 if possible
sinclude([fanutf8.inc.m4])

%
% End of file
