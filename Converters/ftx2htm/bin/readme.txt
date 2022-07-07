The program BMP2GIF converts windows bitmap files into gif files, and
optionally makes one colour transparent.

Usage:
BMP2GIF infile [outfile] [-options]

infile is the name of the bitmap file to be converted. If no extension
is provided, .bmp will be assumed. This filename may contain wildcards,
so that several files can be converted in one run.
Windows bitmap files can have 1, 4, 8 or 24 bit colour. Gif files
cannot encode 24 bit colour, so these bitmaps cannot be converted.
In addition, this program cannot process compressed bitmaps.

outfile is an optional output file or path name. If it is omitted, the
output file name will be the same as the input file, with an extension
of .gif. The output file name cannot contain wildcards. If the input
name does contain wildcards, the output name should be at most a disk
and directory, specifying where the output files should be placed.

Only one option is available at present, that of assigning a
transparent colour. The options argument may take one of the following
forms:

Option      Transp. colour                   rgb
-tk            black                     0,   0,   0
-tw            white                   255, 255, 255
-tg            grey                    192, 192, 192
-tr            red                     255,   0,   0
-tb            blue                      0,   0, 255
-ty            yellow                  255, 255,   0
-t#         User-specified             n'th colour in palette

The options -tk to -ty make the corresponding colour transparent. The
colour is defined as the first entry in the bmp palette that has the
r,g,b colour components given in the table above. If you want to
specify some other colour as transparent, you have to know its location
in the bmp palette. -t# where # is a decimal number between 0 and 255
will set the transparent colour to the corresponding palette entry. e.g
-t123 will set the transparent colour to whatever colour is defined by
entry number 123 in the bitmap palette.

This program is copyright (C) Ian D. Gay, 1999. Everyone is hereby 
given permission to use this program for non-commercial purposes. No
support of any kind is provided. The author assumes no liability for any
damages arising in any way from use or attempted use of this program.
Use at your own risk.

Ian Gay
gay@sfu.ca
