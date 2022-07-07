#!/bin/python
# ***** BEGIN GPL LICENSE BLOCK *****
#
# Copyright (C) 2008: Hamed Zaghaghi,
#       I Used Roozbeh Pournader Farsi to Unicode table, thanks to him and FarsiTeX team.
#       You can find the table here, that contains most of FarsiTeX(IRAN SYSTEM) character codes .
#       http://ce.sharif.edu/~ghodsi/archive/My%20Usefull%20Documents/TeX%20%20Good%20Utitities/FTX2HTM/INPUT/UNICODE/FARSITEX.TXT
# 
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
# ***** END GPL LICENCE BLOCK *****

__author__ = "Hamed Zaghaghi"
__version__ = 0.01 # 20081029
__email__ = 'hamed.zaghaghi@gmail.com; zaghaghi@ut.ac.ir'

import sys
import codecs

def usage():
    print "FarsiTeX to Unicode v0.01 2008\n\
    Usage:\n\
    \tpython ftx2uni.py INPUT [OPTIONS]\n\
    \n\
    OPTIONS:\n\
    \t-x\t\t Converts INPUT file into a XeTex file.[EXPRIMENTAL]"
    quit()
    
def convert(ch):
    if ord(ch)==0x80:
        return u'\u06F0'    #    EXTENDED ARABIC-INDIC DIGIT ZERO
    elif ord(ch)==0x81:
        return u'\u06F1'    #    EXTENDED ARABIC-INDIC DIGIT ONE
    elif ord(ch)==0x82:
        return u'\u06F2'    #    EXTENDED ARABIC-INDIC DIGIT TWO
    elif ord(ch)==0x83:
        return u'\u06F3'    #    EXTENDED ARABIC-INDIC DIGIT THREE
    elif ord(ch)==0x84:
        return u'\u06F4'    #    EXTENDED ARABIC-INDIC DIGIT FOUR
    elif ord(ch)==0x85:
        return u'\u06F5'    #    EXTENDED ARABIC-INDIC DIGIT FIVE
    elif ord(ch)==0x86:
        return u'\u06F6'    #    EXTENDED ARABIC-INDIC DIGIT SIX
    elif ord(ch)==0x87:
        return u'\u06F7'    #    EXTENDED ARABIC-INDIC DIGIT SEVEN
    elif ord(ch)==0x88:
        return u'\u06F8'    #    EXTENDED ARABIC-INDIC DIGIT EIGHT
    elif ord(ch)==0x89:
        return u'\u06F9'    #    EXTENDED ARABIC-INDIC DIGIT NINE
    elif ord(ch)==0x8A:
        return u'\u060C'    #    ARABIC COMMA
    elif ord(ch)==0x8B:
        return u'\u0640'    #    ARABIC TATWEEL
    elif ord(ch)==0x8C:
        return u'\u061F'    #    ARABIC QUESTION MARK
    elif ord(ch)==0x8D:
        return    u'\u200c'+''u'\u0622'    #    ARABIC LETTER ALEF WITH MADDA ABOVE, isolated form
    elif ord(ch)==0x8E:
        return u'\u0626'+u'\u200d'    #    ARABIC LETTER YEH WITH HAMZA ABOVE, initial-medial form
    elif ord(ch)==0x8F:
        return u'\u0621'    #    ARABIC LETTER HAMZA
    elif ord(ch)==0x90:
        return u'\u200c'+u'\u0627'    #    ARABIC LETTER ALEF, isolated form
    elif ord(ch)==0x91:
        return u'\u200d'+u'\u0627'    #    ARABIC LETTER ALEF, final form
    elif ord(ch)==0x92:
        return u'\u0628'+u'\u200c'    #    ARABIC LETTER BEH, final-isolated form
    elif ord(ch)==0x93:
        return u'\u0628'+u'\u200d'    #    ARABIC LETTER BEH, initial-medial form
    elif ord(ch)==0x94:
        return u'\u067E'+u'\u200c'    #    ARABIC LETTER PEH, final-isolated form
    elif ord(ch)==0x95:
        return u'\u067E'+u'\u200d'    #    ARABIC LETTER PEH, initial-medial form
    elif ord(ch)==0x96:
        return u'\u062A'+u'\u200c'    #    ARABIC LETTER TEH, final-isolated form
    elif ord(ch)==0x97:
        return u'\u062A'+u'\u200d'    #    ARABIC LETTER TEH, initial-medial form
    elif ord(ch)==0x98:
        return u'\u062B'+u'\u200c'   #    ARABIC LETTER THEH, final-isolated form
    elif ord(ch)==0x99:
        return u'\u062B'+u'\u200d'    #    ARABIC LETTER THEH, initial-medial form
    elif ord(ch)==0x9A:
        return u'\u062C'+u'\u200c'    #    ARABIC LETTER JEEM, final-isolated form
    elif ord(ch)==0x9B:
        return u'\u062C'+u'\u200d'    #    ARABIC LETTER JEEM, initial-medial form
    elif ord(ch)==0x9C:
        return u'\u0686'+u'\u200c'    #    ARABIC LETTER TCHEH, final-isolated form
    elif ord(ch)==0x9D:
        return u'\u0686'+u'\u200d'    #    ARABIC LETTER TCHEH, initial-medial form
    elif ord(ch)==0x9E:
        return u'\u062D'+u'\u200c'    #    ARABIC LETTER HAH, final-isolated form
    elif ord(ch)==0x9F:
        return u'\u062D'+u'\u200d'    #    ARABIC LETTER HAH, initial-medial form
    elif ord(ch)==0xA0:
        return u'\u062E'+u'\u200c'    #    ARABIC LETTER KHAH, final-isolated form
    elif ord(ch)==0xA1:
        return u'\u062E'+u'\u200d'    #    ARABIC LETTER KHAH, initial-medial form
    elif ord(ch)==0xA2:
        return u'\u062F'    #    ARABIC LETTER DAL
    elif ord(ch)==0xA3:
        return u'\u0630'    #    ARABIC LETTER THAL
    elif ord(ch)==0xA4:
        return u'\u0631'    #    ARABIC LETTER REH
    elif ord(ch)==0xA5:
        return u'\u0632'    #    ARABIC LETTER ZAIN
    elif ord(ch)==0xA6:
        return u'\u0698'    #    ARABIC LETTER JEH
    elif ord(ch)==0xA7:
        return u'\u0633'+u'\u200c'    #    ARABIC LETTER SEEN, final-isolated form
    elif ord(ch)==0xA8:
        return u'\u0633'+u'\u200d'    #    ARABIC LETTER SEEN, initial-medial form
    elif ord(ch)==0xA9:
        return u'\u0634'+u'\u200c'    #    ARABIC LETTER SHEEN, final-isolated form
    elif ord(ch)==0xAA:
        return u'\u0634'+u'\u200d'    #    ARABIC LETTER SHEEN, initial-medial form
    elif ord(ch)==0xAB:
        return u'\u0635'+u'\u200c'    #    ARABIC LETTER SAD, final-isolated form
    elif ord(ch)==0xAC:
        return u'\u0635'+u'\u200d'    #    ARABIC LETTER SAD, initial-medial form
    elif ord(ch)==0xAD:
        return u'\u0636'+u'\u200c'    #    ARABIC LETTER DAD, final-isolated form
    elif ord(ch)==0xAE:
        return u'\u0636'+u'\u200d'     #    ARABIC LETTER DAD, initial-medial form
    elif ord(ch)==0xAF:
        return u'\u0637'+u'\u200d'    #    ARABIC LETTER TAH, initial-medial form
    elif ord(ch)==0xB1:
        return u'\u0650'    #    ARABIC KASRA
    elif ord(ch)==0xB3:
        return u'\u064B'    #    ARABIC FATHATAN
    elif ord(ch)==0xBD:
        return u'\u0029'    #    RIGHT PARENTHESIS
    elif ord(ch)==0xBE:
        return u'\u0028'    #    LEFT PARENTHESIS
    elif ord(ch)==0xBF:
        return u'\u0629'    #    ARABIC LETTER TEH MARBUTAH
    elif ord(ch)==0xC0:
        return u'\u00BB'    #    RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
    elif ord(ch)==0xC1:
        return u'\u0637'+u'\u200c'     #    ARABIC LETTER TAH, final-isolated form
    elif ord(ch)==0xC2:
        return u'\u0638'+u'\u200c'     #    ARABIC LETTER ZAH, final-isolated form
    elif ord(ch)==0xC3:
        return u'\u00AB'    #    LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
    elif ord(ch)==0xC6:
        return u'\u002E'    #    FULL STOP
    elif ord(ch)==0xCA:
        return u'\u003A'    #    COLON
    elif ord(ch)==0xCC:
        return u'\u003E'    #    GREATER-THAN SIGN
    elif ord(ch)==0xCF:
        return u'\u003C'#    LESS-THAN SIGN
    elif ord(ch)==0xDA:
        return u'\u0020'    #    SPACE
    elif ord(ch)==0xDD:
        return u'\u0021'    #    EXCLAMATION MARK
    elif ord(ch)==0xE0:
        return u'\u0638'+u'\u200d'     #    ARABIC LETTER ZAH, initial-medial form
    elif ord(ch)==0xE1:
        return u'\u200c'+u'\u0639'+u'\u200c'     #    ARABIC LETTER AIN, isolated form
    elif ord(ch)==0xE2:
        return u'\u200d'+u'\u0639'+u'\u200c'     #    ARABIC LETTER AIN, final form
    elif ord(ch)==0xE3:
        return u'\u200d'+u'\u0639'+u'\u200d'     #    ARABIC LETTER AIN, medial form
    elif ord(ch)==0xE4:
        return    u'\u200c'+u'\u0639'+u'\u200d'     #    ARABIC LETTER AIN, initial form
    elif ord(ch)==0xE5:
        return    u'\u200c'+u'\u063A'+u'\u200c'     #    ARABIC LETTER GHAIN, isolated form
    elif ord(ch)==0xE6:
        return    u'\u200d'+u'\u063A'+u'\u200c'     #    ARABIC LETTER GHAIN, final form
    elif ord(ch)==0xE7:
        return    u'\u200d'+u'\u063A'+u'\u200d'     #    ARABIC LETTER GHAIN, medial form
    elif ord(ch)==0xE8:
        return     u'\u200c'+u'\u063A'+u'\u200d'     #    ARABIC LETTER GHAIN, initial form
    elif ord(ch)==0xE9:
        return u'\u0641'+u'\u200c'     #    ARABIC LETTER FEH, final-isolated form
    elif ord(ch)==0xEA:
        return u'\u0641'+u'\u200d'     #    ARABIC LETTER FEH, initial-medial form
    elif ord(ch)==0xEB:
        return u'\u0642'+u'\u200c'     #    ARABIC LETTER QAF, final-isolated form
    elif ord(ch)==0xEC:
        return u'\u0642'+u'\u200d'     #    ARABIC LETTER QAF, initial-medial form
    elif ord(ch)==0xED:
        return u'\u06A9'+u'\u200c'     #    ARABIC LETTER KEHEH, final-isolated form
    elif ord(ch)==0xEE:
        return u'\u06A9'+u'\u200d'     #    ARABIC LETTER KEHEH, initial-medial form
    elif ord(ch)==0xEF:
        return u'\u06AF'+u'\u200c'     #    ARABIC LETTER GAF, final-isolated form
    elif ord(ch)==0xF0:
        return u'\u06AF'+u'\u200d'     #    ARABIC LETTER GAF, initial-medial form
    elif ord(ch)==0xF1:
        return u'\u0644'+u'\u200c'     #    ARABIC LETTER LAM, final-isolated form
    elif ord(ch)==0xF2:
        return u'\u0644'+u'\u0627'    #    ARABIC LIGATURE LAM WITH ALEF
    elif ord(ch)==0xF3:
        return u'\u0644'+u'\u200d'     #    ARABIC LETTER LAM, initial-medial form
    elif ord(ch)==0xF4:
        return u'\u0645'+u'\u200c'     #    ARABIC LETTER MEEM, final-isolated form
    elif ord(ch)==0xF5:
        return u'\u0645'+u'\u200d'     #    ARABIC LETTER MEEM, initial-medial form
    elif ord(ch)==0xF6:
        return u'\u0646'+u'\u200c'     #    ARABIC LETTER NOON, final-isolated form
    elif ord(ch)==0xF7:
        return u'\u0646'+u'\u200d'     #    ARABIC LETTER NOON, initial-medial form
    elif ord(ch)==0xF8:
        return u'\u0648'    #    ARABIC LETTER WAW
    elif ord(ch)==0xF9:
        return u'\u0647'+u'\u200c'     #    ARABIC LETTER HEH, final-isolated form
    elif ord(ch)==0xFA:
        return u'\u200d'+u'\u0647'+u'\u200d'     #    ARABIC LETTER HEH, medial form
    elif ord(ch)==0xFB:
        return u'\u200c'+u'\u0647'+u'\u200d'     #    ARABIC LETTER HEH, initial form
    elif ord(ch)==0xFC:
        return u'\u200d'+u'\u0649'+u'\u200c'     #    ARABIC LETTER FARSI YEH, final form
    elif ord(ch)==0xFD:
        return u'\u200c'+u'\u0649'+u'\u200c'     #    ARABIC LETTER FARSI YEH, isolated form
    elif ord(ch)==0xFE:
        return u'\u064A'+u'\u200d'     #    ARABIC LETTER FARSI YEH, initial-medial form
    elif ord(ch)==0xCB:
        return u'\u061B'    #    ARABIC SEMICOLON
    elif ord(ch)==0xBC:
        return u'\u066B'    #    ARABIC DECIMAL SEPARATOR
    elif ord(ch)==0xB0:
        return u'\u064E'    #    ARABIC FATHA
    elif ord(ch)==0xB2:
        return u'\u064F'    #    ARABIC DAMMA
    elif ord(ch)==0xB4:
        return u'\u0651'    #    ARABIC SHADDA
    elif ord(ch)==0xC4:
        return u'\u0652'    #    ARABIC SUKUN
    elif ord(ch)==0xBA:     # ARABIC LETTER SUPERSCRIPT ALEF
        return u'\u0656'
    elif ord(ch)==0xB9:     # SANIH MARK I don't know what is this. i use space
        return u'\u0020'
    elif ord(ch)==0xB7:     #%
        return u'\u0025'     #or u'\u066a'
    elif ord(ch)==0xDA:     #SPACE
        return u'\u0020'
    elif ord(ch)==0xbb:     # HIGH HAMZAH
        return u'\u0674'     # or '\ufe80' 
    elif ord(ch)==0xD1:     # ]
        return u'\u005d'
    elif ord(ch)==0xD2:     # \
        return u'\u005c'
    elif ord(ch)==0xD3:     # [
        return u'\u005b'
    elif ord(ch)==0xD7:     # }
        return u'\u007d'
    elif ord(ch)==0xDE:     # {
        return u'\u007b'
    else:
        if ord(ch)<128:
            return unicode(ch, 'utf-8')
        else:
            return ' ' #Not in the list above and also not in the range(128)

if len(sys.argv)<2:
    usage()

input_filename = sys.argv[1]

toxetex = False
if sys.argv.count('-x')!=0:
    toxetex = True

f = open(input_filename,"rb")
buf = f.read()
unibuf = ""
buggy_chars = ""
first_char = True
for ch in buf:
    if first_char and (ch=='<' or ch=='>'):
        first_char = False
    elif ord(ch)<=255:
        unibuf += convert(ch)
    else:
        buggy_chars+=ch
    if ch=='\n':
        first_char = True
print buggy_chars

if toxetex:
    unibuf = unibuf.replace(unicode("\\FarsiTeX", "utf-8"),  unicode("FarsiTeX", "utf-8"))
    if unibuf.find(unicode("\\documentstyle[farsi]", "utf-8"))!=-1:
        unibuf = unibuf.replace(unicode("\\documentstyle[farsi]", "utf-8"), unicode("\documentclass", "utf-8"))
        index = unibuf.find(unicode("\documentclass", "utf-8"))
        index = unibuf.find(unicode("\n", "utf-8"),  index+1)
        if index!=-1:
            unibuf = unibuf[:index+1] +\
                        "\\usepackage{fontspec}\n\\usepackage{bidi}\\setmainfont[Script=Arabic, Scale=1]{Nazli}" + \
                        unibuf[index+1:]
        else:
            unibuf += "\\usepackage{fontspec}\n\\usepackage{bidi}\\setmainfont[Script=Arabic, Scale=1]{Nazli}"
    index = unibuf.find(unicode("\\begin{document}"))
    if index!=-1:
        index = unibuf.find(unicode("\n", "utf-8"),  index+1)
        if index!=-1:
            unibuf = unibuf[:index+1] +\
                        "\\setRL" + \
                        unibuf[index+1:]
        else:
            unibuf += "\\setRL"

output_filename = ""
for part in input_filename.split('.')[:-1]:
    output_filename += part + '.'
output_filename += 'tex'
f2 = codecs.open(output_filename, 'w', 'utf_8')
f2.write(unibuf)

 	  	 
