#!/usr/bin/env python3
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see <http://www.gnu.org/licenses>

##################################################
#  Author:      Mostafa Vahedi                   #
#  Date:        19 August 2011                   #
#  Version:     0-12                             #
#  Application: FarsiTeX to XePersian converter  #
##################################################

import sys
import os

ft_numerical = [
    chr(0xB9),  # Arabic Thoushads Seperator
    chr(0xBC),  # ARABIC DECIMAL SEPARATOR
]


ft_vowels = [
    chr(0xB0),  # ARABIC FATHA
    chr(0xB1),  # ARABIC KASRA
    chr(0xB2),  # ARABIC DAMMA
    chr(0xB3),  # ARABIC FATHATAN
    chr(0xB4),  # ARABIC SHADDA
    chr(0xBA),  # ARABIC LETTER SUPERSCRIPT ALEF
    chr(0xBB),  # ARABIC HAMZA ABOVE
    chr(0xC4),  # ARABIC SUKUN
]

ft_non_joiners = [
    chr(0x8F)  # ARABIC LETTER HAMZA
]

ft_bidi_joiners_initial = [
    chr(0xE4),  # ARABIC LETTER AIN, initial form
    chr(0xE8),  # ARABIC LETTER GHAIN, initial form
    chr(0xFB),  # ARABIC LETTER HEH, initial form
]

ft_bidi_joiners_medial = [
    chr(0xE3),  # ARABIC LETTER AIN, medial form
    chr(0xE7),  # ARABIC LETTER GHAIN, medial form
    chr(0xFA),  # ARABIC LETTER HEH, medial form
]

ft_bidi_joiners_final = [
    chr(0xE2),  # ARABIC LETTER AIN, final form
    chr(0xE6),  # ARABIC LETTER GHAIN, final form
    chr(0xFC),  # ARABIC LETTER FARSI YEH, final form
]

ft_bidi_joiners_isolated = [
    chr(0xE1),  # ARABIC LETTER AIN, isolated form
    chr(0xE5),  # ARABIC LETTER GHAIN, isolated form
    chr(0xFD),  # ARABIC LETTER FARSI YEH, isolated form
]

ft_bidi_joiners_initial_medial = [
    chr(0x8B),  # ARABIC TATWEEL
    chr(0x8E),  # ARABIC LETTER YEH WITH HAMZA ABOVE, initial-medial form
    chr(0x93),  # ARABIC LETTER BEH, initial-medial form
    chr(0x95),  # ARABIC LETTER PEH, initial-medial form
    chr(0x97),  # ARABIC LETTER TEH, initial-medial form
    chr(0x99),  # ARABIC LETTER THEH, initial-medial form
    chr(0x9B),  # ARABIC LETTER JEEM, initial-medial form
    chr(0x9D),  # ARABIC LETTER TCHEH, initial-medial form
    chr(0x9F),  # ARABIC LETTER HAH, initial-medial form
    chr(0xA1),  # ARABIC LETTER KHAH, initial-medial form
    chr(0xA8),  # ARABIC LETTER SEEN, initial-medial form
    chr(0xAA),  # ARABIC LETTER SHEEN, initial-medial form
    chr(0xAC),  # ARABIC LETTER SAD, initial-medial form
    chr(0xAE),  # ARABIC LETTER DAD, initial-medial form
    chr(0xAF),  # ARABIC LETTER TAH, initial-medial form
    chr(0xE0),  # ARABIC LETTER ZAH, initial-medial form
    chr(0xEA),  # ARABIC LETTER FEH, initial-medial form
    chr(0xEC),  # ARABIC LETTER QAF, initial-medial form
    chr(0xEE),  # ARABIC LETTER KEHEH, initial-medial form
    chr(0xF0),  # ARABIC LETTER GAF, initial-medial form
    chr(0xF3),  # ARABIC LETTER LAM, initial-medial form
    chr(0xF5),  # ARABIC LETTER MEEM, initial-medial form
    chr(0xF7),  # ARABIC LETTER NOON, initial-medial form
    chr(0xFE),  # ARABIC LETTER FARSI YEH, initial-medial form
]

ft_bidi_joiners_final_isolated = [
    chr(0x92),  # ARABIC LETTER BEH, final-isolated form
    chr(0x94),  # ARABIC LETTER PEH, final-isolated form
    chr(0x96),  # ARABIC LETTER TEH, final-isolated form
    chr(0x98),  # ARABIC LETTER THEH, final-isolated form
    chr(0x9A),  # ARABIC LETTER JEEM, final-isolated form
    chr(0x9C),  # ARABIC LETTER TCHEH, final-isolated form
    chr(0x9E),  # ARABIC LETTER HAH, final-isolated form
    chr(0xA0),  # ARABIC LETTER KHAH, final-isolated form
    chr(0xA7),  # ARABIC LETTER SEEN, final-isolated form
    chr(0xA9),  # ARABIC LETTER SHEEN, final-isolated form
    chr(0xAB),  # ARABIC LETTER SAD, final-isolated form
    chr(0xAD),  # ARABIC LETTER DAD, final-isolated form
    chr(0xC1),  # ARABIC LETTER TAH, final-isolated form
    chr(0xC2),  # ARABIC LETTER ZAH, final-isolated form
    chr(0xE9),  # ARABIC LETTER FEH, final-isolated form
    chr(0xEB),  # ARABIC LETTER QAF, final-isolated form
    chr(0xED),  # ARABIC LETTER KEHEH, final-isolated form
    chr(0xEF),  # ARABIC LETTER GAF, final-isolated form
    chr(0xF1),  # ARABIC LETTER LAM, final-isolated form
    chr(0xF4),  # ARABIC LETTER MEEM, final-isolated form
    chr(0xF6),  # ARABIC LETTER NOON, final-isolated form
    chr(0xF9),  # ARABIC LETTER HEH, final-isolated form
]

ft_right_joiners_final = [
    chr(0x91)  # ARABIC LETTER ALEF, final form
]

ft_right_joiners_isolated = [
    chr(0x8D),  # ARABIC LETTER ALEF WITH MADDA ABOVE, isolated form
    chr(0x90),  # ARABIC LETTER ALEF, isolated form
]

ft_right_joiners_final_isolated = [
    chr(0xA2),  # ARABIC LETTER DAL
    chr(0xA3),  # ARABIC LETTER THAL
    chr(0xA4),  # ARABIC LETTER REH
    chr(0xA5),  # ARABIC LETTER ZAIN
    chr(0xA6),  # ARABIC LETTER JEH
    chr(0xBF),  # ARABIC LETTER TEH MARBUTAH
    chr(0xF2),  # ARABIC LIGATURE LAM WITH ALEF
    chr(0xF8),  # ARABIC LETTER WAW
]


table_FT_UN = {
    chr(0x80): ["\u06f0"],  # EXTENDED ARABIC-INDIC DIGIT ZERO
    chr(0x81): ["\u06f1"],  # EXTENDED ARABIC-INDIC DIGIT ONE
    chr(0x82): ["\u06f2"],  # EXTENDED ARABIC-INDIC DIGIT TWO
    chr(0x83): ["\u06f3"],  # EXTENDED ARABIC-INDIC DIGIT THREE
    chr(0x84): ["\u06f4"],  # EXTENDED ARABIC-INDIC DIGIT FOUR
    chr(0x85): ["\u06f5"],  # EXTENDED ARABIC-INDIC DIGIT FIVE
    chr(0x86): ["\u06f6"],  # EXTENDED ARABIC-INDIC DIGIT SIX
    chr(0x87): ["\u06f7"],  # EXTENDED ARABIC-INDIC DIGIT SEVEN
    chr(0x88): ["\u06f8"],  # EXTENDED ARABIC-INDIC DIGIT EIGHT
    chr(0x89): ["\u06f9"],  # EXTENDED ARABIC-INDIC DIGIT NINE
    chr(0x8A): ["\u060c"],  # ARABIC COMMA
    chr(0x8B): ["\u0640"],  # ARABIC TATWEEL
    chr(0x8C): ["\u061f"],  # ARABIC QUESTION MARK
    chr(0x8D): ["\u0622"],  # ARABIC LETTER ALEF WITH MADDA ABOVE, isolated form
    chr(0x8E): ["\u0626"],  # ARABIC LETTER YEH WITH HAMZA ABOVE, initial-medial form
    chr(0x8F): ["\u0621"],  # ARABIC LETTER HAMZA
    chr(0x90): ["\u0627"],  # ARABIC LETTER ALEF, isolated form
    chr(0x91): ["\u0627"],  # ARABIC LETTER ALEF, final form
    chr(0x92): ["\u0628"],  # ARABIC LETTER BEH, final-isolated form
    chr(0x93): ["\u0628"],  # ARABIC LETTER BEH, initial-medial form
    chr(0x94): ["\u067e"],  # ARABIC LETTER PEH, final-isolated form
    chr(0x95): ["\u067e"],  # ARABIC LETTER PEH, initial-medial form
    chr(0x96): ["\u062a"],  # ARABIC LETTER TEH, final-isolated form
    chr(0x97): ["\u062a"],  # ARABIC LETTER TEH, initial-medial form
    chr(0x98): ["\u062b"],  # ARABIC LETTER THEH, final-isolated form
    chr(0x99): ["\u062b"],  # ARABIC LETTER THEH, initial-medial form
    chr(0x9A): ["\u062c"],  # ARABIC LETTER JEEM, final-isolated form
    chr(0x9B): ["\u062c"],  # ARABIC LETTER JEEM, initial-medial form
    chr(0x9C): ["\u0686"],  # ARABIC LETTER TCHEH, final-isolated form
    chr(0x9D): ["\u0686"],  # ARABIC LETTER TCHEH, initial-medial form
    chr(0x9E): ["\u062d"],  # ARABIC LETTER HAH, final-isolated form
    chr(0x9F): ["\u062d"],  # ARABIC LETTER HAH, initial-medial form
    chr(0xA0): ["\u062e"],  # ARABIC LETTER KHAH, final-isolated form
    chr(0xA1): ["\u062e"],  # ARABIC LETTER KHAH, initial-medial form
    chr(0xA2): ["\u062f"],  # ARABIC LETTER DAL
    chr(0xA3): ["\u0630"],  # ARABIC LETTER THAL
    chr(0xA4): ["\u0631"],  # ARABIC LETTER REH
    chr(0xA5): ["\u0632"],  # ARABIC LETTER ZAIN
    chr(0xA6): ["\u0698"],  # ARABIC LETTER JEH
    chr(0xA7): ["\u0633"],  # ARABIC LETTER SEEN, final-isolated form
    chr(0xA8): ["\u0633"],  # ARABIC LETTER SEEN, initial-medial form
    chr(0xA9): ["\u0634"],  # ARABIC LETTER SHEEN, final-isolated form
    chr(0xAA): ["\u0634"],  # ARABIC LETTER SHEEN, initial-medial form
    chr(0xAB): ["\u0635"],  # ARABIC LETTER SAD, final-isolated form
    chr(0xAC): ["\u0635"],  # ARABIC LETTER SAD, initial-medial form
    chr(0xAD): ["\u0636"],  # ARABIC LETTER DAD, final-isolated form
    chr(0xAE): ["\u0636"],  # ARABIC LETTER DAD, initial-medial form
    chr(0xAF): ["\u0637"],  # ARABIC LETTER TAH, initial-medial form
    chr(0xB0): ["\u064e"],  # ARABIC FATHA
    chr(0xB1): ["\u0650"],  # ARABIC KASRA
    chr(0xB2): ["\u064f"],  # ARABIC DAMMA
    chr(0xB3): ["\u064b"],  # ARABIC FATHATAN
    chr(0xB4): ["\u0651"],  # ARABIC SHADDA
    chr(0xB5): ["\u0023"],  # * #
    chr(0xB6): ["\u0024"],  # * $
    chr(0xB7): ["\u0025"],  # * %
    chr(0xB8): ["\u0026"],  # * &
    chr(0xB9): ["\u066c"],  # 	Arabic Thoushads Seperator
    chr(0xBA): ["\u0670"],  # ARABIC LETTER SUPERSCRIPT ALEF
    chr(0xBB): ["\u0654"],  # ARABIC HAMZA ABOVE
    chr(0xBC): ["\u066b"],  # ARABIC DECIMAL SEPARATOR
    chr(0xBD): ["\u0029"],  # * RIGHT PARENTHESIS
    chr(0xBE): ["\u0028"],  # * LEFT PARENTHESIS
    chr(0xBF): ["\u0629"],  # ARABIC LETTER TEH MARBUTAH
    chr(0xC0): ["\u00bb"],  # RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
    chr(0xC1): ["\u0637"],  # ARABIC LETTER TAH, final-isolated form
    chr(0xC2): ["\u0638"],  # ARABIC LETTER ZAH, final-isolated form
    chr(0xC3): ["\u00ab"],  # LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
    chr(0xC4): ["\u0652"],  # ARABIC SUKUN
    chr(0xC5): ["\u002d"],  # * -
    chr(0xC6): ["\u002e"],  # * FULL STOP
    chr(0xC7): ["\u002f"],  # * /
    chr(0xC8): ["\u002a"],  # * *
    chr(0xC9): ["\u007e"],  # * ~
    chr(0xCA): ["\u003a"],  # * COLON
    chr(0xCB): ["\u061b"],  # 	ARABIC SEMICOLON
    chr(0xCC): ["\u003e"],  # * GREATER-THAN SIGN
    chr(0xCD): ["\u002b"],  # * +
    chr(0xCE): ["\u003d"],  # * =
    chr(0xCF): ["\u003c"],  # * LESS-THAN SIGN
    # chr(0xD0) : [u'\u0040'],	# * @
    chr(0xD0): [""],  # * @
    chr(0xD1): ["\u005d"],  # * [
    chr(0xD2): ["\u005c"],  # * \
    chr(0xD3): ["\u005b"],  # * ]
    chr(0xD4): ["\u005e"],  # * ^
    chr(0xD5): ["\u005f"],  # * _
    chr(0xD6): ["\u0060"],  # * `
    chr(0xD7): ["\u007d"],  # * {
    chr(0xD8): ["\u007c"],  # * |
    chr(0xDA): ["\u0020"],  # * SPACE
    chr(0xDD): ["\u0021"],  # * EXCLAMATION MARK
    chr(0xDE): ["\u007b"],  # * }
    chr(0xE0): ["\u0638"],  # ARABIC LETTER ZAH, initial-medial form
    chr(0xE1): ["\u0639"],  # ARABIC LETTER AIN, isolated form
    chr(0xE2): ["\u0639"],  # ARABIC LETTER AIN, final form
    chr(0xE3): ["\u0639"],  # ARABIC LETTER AIN, medial form
    chr(0xE4): ["\u0639"],  # ARABIC LETTER AIN, initial form
    chr(0xE5): ["\u063a"],  # ARABIC LETTER GHAIN, isolated form
    chr(0xE6): ["\u063a"],  # ARABIC LETTER GHAIN, final form
    chr(0xE7): ["\u063a"],  # ARABIC LETTER GHAIN, medial form
    chr(0xE8): ["\u063a"],  # ARABIC LETTER GHAIN, initial form
    chr(0xE9): ["\u0641"],  # ARABIC LETTER FEH, final-isolated form
    chr(0xEA): ["\u0641"],  # ARABIC LETTER FEH, initial-medial form
    chr(0xEB): ["\u0642"],  # ARABIC LETTER QAF, final-isolated form
    chr(0xEC): ["\u0642"],  # ARABIC LETTER QAF, initial-medial form
    chr(0xED): ["\u06a9"],  # ARABIC LETTER KEHEH, final-isolated form
    chr(0xEE): ["\u06a9"],  # ARABIC LETTER KEHEH, initial-medial form
    chr(0xEF): ["\u06af"],  # ARABIC LETTER GAF, final-isolated form
    chr(0xF0): ["\u06af"],  # ARABIC LETTER GAF, initial-medial form
    chr(0xF1): ["\u0644"],  # ARABIC LETTER LAM, final-isolated form
    chr(0xF2): ["\u0644\u0627"],  # ARABIC LIGATURE LAM WITH ALEF
    chr(0xF3): ["\u0644"],  # ARABIC LETTER LAM, initial-medial form
    chr(0xF4): ["\u0645"],  # ARABIC LETTER MEEM, final-isolated form
    chr(0xF5): ["\u0645"],  # ARABIC LETTER MEEM, initial-medial form
    chr(0xF6): ["\u0646"],  # ARABIC LETTER NOON, final-isolated form
    chr(0xF7): ["\u0646"],  # ARABIC LETTER NOON, initial-medial form
    chr(0xF8): ["\u0648"],  # ARABIC LETTER WAW
    chr(0xF9): ["\u0647"],  # ARABIC LETTER HEH, final-isolated form
    chr(0xFA): ["\u0647"],  # ARABIC LETTER HEH, medial form
    chr(0xFB): ["\u0647"],  # ARABIC LETTER HEH, initial form
    chr(0xFC): ["\u06cc"],  # ARABIC LETTER FARSI YEH, final form
    chr(0xFD): ["\u06cc"],  # ARABIC LETTER FARSI YEH, isolated form
    chr(0xFE): ["\u06cc"],  # ARABIC LETTER FARSI YEH, initial-medial form
}

F_PERCENT_SIGN = chr(0xB7)
F_AT_SIGN = chr(0xD0)
F_SLASH = chr(0xD2)
F_SPACE = chr(0xDA)
F_PRNT_OPEN = chr(0xDE)
F_PRNT_CLOSE = chr(0xD7)

# latex and farsitex commands whose first parameter does not need \lr{...}
commands = [
    "begin",
    "end",
    "input",
    "include",
    "includeonly",
    "hspace",
    "vspace",
    "hspace*",
    "vspace*",
    "label",
    "ref",
    "cite",
    "bibitem",
    "bibliographystyle",
    "parbox",
    "newenvironment",
    "newtheorem",
    "persianmathdigitsfamily",
    "fontfamily",
    "fontseries",
    "fontshape",
    "rmdefault",
    "sfdefault",
    "ttdefault",
    "bfdefault",
    "itdefault",
    "sldefault",
    "scdefault",
    "pagenumbering",
    "pagestyle",
    "thispagestyle",
    "setcounter",
    "stepcounter",
    "setlength",
    "addtolength",
]


def ft_is_all_persian_space(next_part):
    l = len(next_part)
    i = 0
    while i < l:
        if next_part[i] != F_SPACE:
            return 0
        i += 1
    return 1


def ft_is_numeric(ch):
    if (ch in ft_numerical) or ((ch >= chr(0x80)) and (ch <= chr(0x89))):
        return 1
    return 0


def ft_can_join_left(ch):
    if (
        (ch in ft_bidi_joiners_initial)
        or (ch in ft_bidi_joiners_medial)
        or (ch in ft_bidi_joiners_final)
        or (ch in ft_bidi_joiners_isolated)
        or (ch in ft_bidi_joiners_initial_medial)
        or (ch in ft_bidi_joiners_final_isolated)
    ):
        return 1
    return 0


def ft_can_join_right(ch):
    if (
        ft_can_join_left(ch)
        or (ch in ft_right_joiners_final)
        or (ch in ft_right_joiners_isolated)
        or (ch in ft_right_joiners_final_isolated)
    ):
        return 1
    return 0


def ft_joining_left(ch):
    if (
        (ch in ft_bidi_joiners_initial)
        or (ch in ft_bidi_joiners_medial)
        or (ch in ft_bidi_joiners_initial_medial)
    ):
        return 1
    return 0


def ft_joining_right(ch):
    if (
        (ch in ft_right_joiners_final)
        or (ch in ft_bidi_joiners_medial)
        or (ch in ft_bidi_joiners_final)
    ):
        return 1
    return 0


def ft_not_right_joined(ch):
    if (
        (ch in ft_bidi_joiners_initial)
        or (ch in ft_right_joiners_isolated)
        or (ch in ft_bidi_joiners_isolated)
    ):
        return 1
    return 0


def ft_adjust_shaping(text, i):
    current = text[i]
    u = ""
    try:
        u = table_FT_UN[current][0]
    except KeyError:
        return ""

    # if you don't want shaping remove the following comment
    # return u

    if (current in ft_vowels) or (ft_is_numeric(current)):
        return u

    # find next non-vowel character on the left
    text_len = len(text)
    next_index = i + 1
    while (next_index < text_len) and (text[next_index] in ft_vowels):
        next_index += 1

    if next_index == text_len:
        next = ""
    else:
        next = text[next_index]

    # if current letter is joining from left but next letter is or can not joining
    if ft_joining_left(current):
        if not ft_can_join_right(next):
            u += "\u200d"  # ZWJ
        elif ft_not_right_joined(next):
            u += "\u200d\u200c"  # ZWJ+ZWNJ
    # if current letter can join but next letter is joining from right
    elif ft_can_join_left(current):
        if ft_joining_right(next):
            u += "\u200c\u200d"  # ZWNJ+ZWJ
        elif ft_can_join_right(next):
            u += "\u200c"  # ZWNJ
    return u


def ft_adjust_number(text):
    result = ""
    i = len(text) - 1
    while i >= 0:
        result += ft_adjust_shaping(text, i)
        i -= 1
    return result


def map_ft_unicode(text):
    mapped_text = ""

    i = 0
    while i < len(text):
        if ft_is_numeric(text[i]):
            next_index = i
            while (next_index + 1 < len(text)) and (ft_is_numeric(text[next_index + 1])):
                next_index += 1
            mapped_text += ft_adjust_number(text[i : next_index + 1])
            i = next_index + 1
            continue

        mapped_text += ft_adjust_shaping(text, i)
        i += 1
    return mapped_text


# Finds next token all of the same language
def ft_next_part(line, i, line_len):
    global global_state
    global recursive
    global filenames

    j = i
    language_flag = line[j] < chr(0x80)
    while (j < line_len) and ((line[j] < chr(0x80)) == language_flag):
        if (
            (global_state == 0)
            and ((line[j] == "%") or (line[j] == F_PERCENT_SIGN))
            and (line[j - 1] != "\\")
            and (line[j - 1] != F_SLASH)
        ):
            global_state = 1
        elif (global_state == 0) and (
            (line[j : j + 16] == "\\begin{verbatim}") or (line[j : j + 17] == "\\begin{verbatim*}")
        ):
            global_state = 2
        elif (global_state == 2) and (
            (line[j : j + 14] == "\\end{verbatim}") or (line[j : j + 15] == "\\end{verbatim*}")
        ):
            global_state = 0
        elif (global_state == 0) and (line[j : j + 6] == "\\verb*"):
            next_index = line.find(line[j + 6], j + 7)
            j = next_index
        elif (global_state == 0) and (line[j : j + 5] == "\\verb"):
            next_index = line.find(line[j + 5], j + 6)
            j = next_index
        elif recursive == 1:
            if (global_state == 0) and (line[j : j + 9] == "\\include{"):
                next_index = line.find("}", j + 9)
                filename = line[j + 10 : next_index - 1] + ".ftx"
                if os.path.exists(filename) and not filename in filenames:
                    filenames.append(filename)
            elif (global_state == 0) and (line[j : j + 7] == "\\input{"):
                next_index = line.find("}", j + 7)
                filename = line[j + 8 : next_index - 1] + ".ftx"
                if os.path.exists(filename) and not filename in filenames:
                    filenames.append(filename)
            elif (global_state == 0) and (line[j : j + 9] == F_SLASH + "include" + F_PRNT_OPEN):
                next_index = line.find(F_PRNT_CLOSE, j + 9)
                if line[j + 9] != F_AT_SIGN:
                    filename = line[j + 9 : next_index] + ".ftx"
                else:
                    filename = line[j + 10 : next_index - 1] + ".ftx"
                if os.path.exists(filename) and not filename in filenames:
                    filenames.append(filename)
            elif (global_state == 0) and (line[j : j + 7] == F_SLASH + "input" + F_PRNT_OPEN):
                next_index = line.find(F_PRNT_CLOSE, j + 7)
                if line[j + 7] != F_AT_SIGN:
                    filename = line[j + 7 : next_index] + ".ftx"
                else:
                    filename = line[j + 8 : next_index - 1] + ".ftx"
                if os.path.exists(filename) and not filename in filenames:
                    filenames.append(filename)
        j += 1
    return j


###############################################
# from here all functions are used to translate
# farsitex commands to xepersian commands
###############################################


def read_size(input, index, last_index):
    dim_index = -1
    inch_index = input.find("in", index)
    if inch_index != -1:
        dim_index = inch_index
    mm_index = input.find("mm", index)
    if mm_index != -1:
        if dim_index == -1 or mm_index < index:
            dim_index = mm_index
    cm_index = input.find("cm", index)
    if cm_index != -1:
        if dim_index == -1 or cm_index < dim_index:
            dim_index = cm_index
    pt_index = input.find("pt", index)
    if pt_index != -1:
        if dim_index == -1 or pt_index < dim_index:
            dim_index = pt_index
    next_cmd = input.find("\\", index)
    if next_cmd == -1 and dim_index == -1:
        print("Error in parsing \epsfxsize command at " + str(line_number) + "\n")
        return -1
    elif next_cmd == -1 or (dim_index != -1 and next_cmd > dim_index):
        epsfxsize = input[index : dim_index + 2]
        return dim_index + 2
    elif next_cmd != -1:
        end_cmd = next_cmd + 1
        while end_cmd < last_index and input[end_cmd].isalpha():
            end_cmd += 1
        return end_cmd
    else:
        print("Error in parsing \epsfxsize command at " + str(line_number) + "\n")
        return -1


latex_options = [
    "a4paper",
    "a5paper",
    "b5paper",
    "letterpaper",
    "legalpaper",
    "executivepaper",
    "landscape",
    "10pt",
    "11pt",
    "12pt",
    "oneside",
    "twoside",
    "draft",
    "final",
    "titlepage",
    "notitlepage",
    "onecolumn",
    "twocolumn",
    "leqno",
    "fleqn",
]

table_eq_packages = {
    "poem": "persianpoem",
    "fmakeidx": "makeidx",
    "ffancyhe": "fancyhdr",
    "fmultico": "multicol",
}

farsitex_ignore_options = ["persian", "farsi", "epsf", "fgraphix", "lotusfont"]

xepersian_packages = "\n\\usepackage{url}\n%\\usepackage{fancyvrb}\n\\usepackage{setspace}\\doublespacing\n\\usepackage{graphicx} \n\\usepackage{amssymb}\n"

xepersian_preamble = "\\settextfont[Scale=1.2]{XB Zar}\n\\setlatintextfont[Scale=1.1]{Times New Roman}\n\\setdigitfont{XB Zar}\n\\setpookfont{XB Kayhan Pook}\n\\setsayehfont{XB Kayhan Sayeh}\n\\defpersianfont\\lotoos[Scale=1.2]{XB Roya}\n\\defpersianfont\\elmi[Scale=1.2]{XB Roya} \n\\def\\nazok{\\normalfont\\normalsize}\n\\let\\iranic\\it\n\\let\\siah\\bf\n\\let\\khabide\\sl\n\\def\\siahir{\\siah\\iranic} \n\\def\\siahkh{\\siah\\khabide}\n\\let\\tookhali\\pookfamily\n\\let\\sayedar\\sayehfamily\n\\def\\farsi{\\end{latin}}\n\\def\\english{\\begin{latin}}\n\\let\\farmbox\\mbox\n\\newcommand{\\ftxepmatrix}[1]{\\begin{pmatrix}#1\\end{pmatrix}}\n\\newcommand{\\ftxematrix}[1]{\\begin{matrix}#1\\end{matrix}} \n\\def\\FarsiTeX{\\lr{FarsiTeX}}\n\\def\\فارسی‌تک{\\rl{فارسی‌‌تک}}\n\\def\\InE{\\begingroup\\beginL\\latinfont}\n\\def\\EnE{\\endL\\endgroup} \n\\def\\InF{\\begingroup\\beginR\\persianfont}\n\\def\\EnF{\\endR\\endgroup}\n\\newcommand{\\IE}[1]{\\lr{#1}}\n\\newcommand{\\IP}[1]{\\rl{#1}} \n\\newcommand{\\IF}[1]{\\rl{#1}}\n\\def\\persiandash{\\rl{-}} \n\\def\\DeclareRobustBiCommand#1#2#3#4{\\DeclareRobustCommand#1{\\if@rl{}#4\\else{}#3\\fi}\\let#2=#1} \n\\catcode`\\﷼=3\n\\catcode`‌=11\n\\newcommand\\dotsectionseparator{\\SepMark{.}}\n\\newcommand\\dashsectionseparator{\\SepMark{-}}\n"

thesis_preamble = "\\university{\\lr{UniversityName}}\n\\city{\\lr{CityName}}\n\\latinuniversity{UniversityName}\n\\latincity{CityName} \n\\let\\englishtitle\\latintitle\n\\let\\englishauthor\\latinauthor\n\\let\\englishdegree\\latindegree\n\\let\\englishthesisdate\\latinthesisdate \n\\let\\englishsupervisor\\latinsupervisor\n\\let\\englishdepartment\\latindepartment\n\\let\\makeenglishtitle\\makelatintitle \n\\let\\englishkeywords\\latinkeywords\n\\newenvironment{englishabstract}{\\begin{latinabstract}}{\\end{latinabstract}}\n"


def is_alpha_numeric_space(input):
    input_len = len(input)
    i = 0
    while i < input_len:
        if not (input[i].isalpha() or input[i].isdigit() or input[i] == "." or input[i] == " "):
            return 0
        i += 1
    return 1


def is_alpha_numeric(input):
    input_len = len(input)
    i = 0
    while i < input_len:
        if not (input[i].isalpha() or input[i].isdigit() or input[i] == "."):
            return 0
        i += 1
    return 1


def find_eq_cmd(keyword):
    try:
        eq_cmd = table_eq_packages[keyword]
    except KeyError:
        eq_cmd = ""
    return eq_cmd


def convert_persian_to_english(num):
    result = ""
    num_len = len(num)
    index = 0
    while index < num_len:
        if ord(num[index]) >= ord("۰") and ord(num[index]) <= ord("۹"):
            result += chr(ord(num[index]) - ord("۰") + ord("0"))
        else:
            result += num[index]
        index += 1
    return result


def generate_farsitex_cmds_file(helper_filename, preamble):
    try:
        of = open(helper_filename, encoding="utf-8", mode="w")
    except IOError:
        print("Can not open the output file: " + helper_filename)
        exit(0)
    of.write(preamble)
    of.close


# \verb|| -> \item[\verb||] or \section{\verb||}
# \kasre{} \alef{} ...
def translate_cmds(output_line):
    global last_epsfxsize
    global last_epsfxsize_line
    global last_epsfysize
    global last_epsfysize_line
    global state
    global filename

    result = ""
    line_len = len(output_line)
    index = 0
    if state == 1:  # \begin{verbatim}
        end_verbatim = output_line.find("\\end{verbatim}")
        if end_verbatim == -1:
            return output_line
        result += output_line[0 : end_verbatim + 14]
        index = end_verbatim + 14
        state = 0
    elif state == 2:  # \begin{verbatim*}
        end_verbatim = output_line.find("\\end{verbatim*}")
        if end_verbatim == -1:
            return output_line
        result += output_line[0 : end_verbatim + 15]
        index = end_verbatim + 15
        state = 0
    elif output_line[0:14] == "\\documentstyle":
        result += "\\documentclass"
        # process options
        last_index = output_line.find("]")
        index = 15
        first_option = 1
        preamble = xepersian_preamble
        packages = xepersian_packages
        xe_document_class = ""
        while index < last_index:
            next_comma = output_line.find(",", index, last_index)
            if next_comma == -1:
                next_comma = last_index
            first_of_option = index
            while output_line[first_of_option] == " ":
                first_of_option += 1
            end_of_option = next_comma
            while output_line[end_of_option - 1] == " ":
                end_of_option -= 1
            option = output_line[first_of_option:end_of_option]
            index = next_comma + 1
            eq_cmd = find_eq_cmd(option)
            if eq_cmd != "":
                packages += "\\usepackage{" + eq_cmd + "}\n"
                continue
            elif option in farsitex_ignore_options:
                continue
            elif option == "sharifth":
                xe_document_class = "xepersian-thesis"
                preamble += thesis_preamble
                continue
            elif not option in latex_options:
                packages += "\\usepackage{" + option + "}\n"
                continue

            if first_option:
                result += "["
            else:
                result += ","
            result += option
            first_option = 0
        # end while
        if not first_option:
            result += "]"
        # process document style into document class
        index = output_line.find("}", last_index)
        document_class = output_line[last_index + 2 : index]
        if xe_document_class != "":
            result += "{" + xe_document_class + "}"
        elif document_class == "oldarticle":
            result += "{article}"
        elif document_class == "oldbook":
            result += "{book}"
        elif document_class == "oldreport":
            result += "{report}"
        else:
            result += "{" + document_class + "}"
        # I assume that nothing important is after
        # \documentstyle[...]{...}, otherwise it may conflict
        # with our preamble
        if index != -1:
            result += output_line[index + 1 :]
        result += packages + "\\usepackage{xepersian}\n"
        helper_filename = filename + "_farsitex_cmds_xepersian.tex"
        generate_farsitex_cmds_file(helper_filename, preamble)
        result += "\\input{" + helper_filename + "}\n"
        return result
    # end elif "documentstyle"

    while index < line_len:
        next_index = output_line.find("\\", index)
        comment_index = output_line.find("%", index)
        if next_index == -1:
            result += output_line[index:]
            break
        elif state == 1:
            if output_line[next_index : next_index + 14] == "\\end{verbatim}":
                result += output_line[index : next_index + 14]
                index = next_index + 14
                state = 0
            else:
                result += output_line[index : next_index + 1]
                index = next_index + 1
        elif state == 2:
            if output_line[next_index : next_index + 15] == "\\end{verbatim*}":
                result += output_line[index : next_index + 15]
                index = next_index + 15
                state = 0
            else:
                result += output_line[index : next_index + 1]
                index = next_index + 1
        elif comment_index != -1 and comment_index < next_index:
            result += output_line[index:]
            break
        elif output_line[next_index : next_index + 14] == "\\input{amssym}":
            result += "\\usepackage{amssymb}"
            index = next_index + 14
        elif output_line[next_index : next_index + 12] == "\\input{epsf}":
            index = next_index + 12
        elif output_line[next_index : next_index + 15] == "\\includeepspdf{":
            result += "\\includegraphics{"
            index = next_index + 15
        elif output_line[next_index : next_index + 16] == "\\begin{verbatim}":
            result += output_line[index : next_index + 16]
            index = next_index + 16
            state = 1
        elif output_line[next_index : next_index + 17] == "\\begin{verbatim*}":
            result += output_line[index : next_index + 17]
            index = next_index + 17
            state = 2
        elif output_line[next_index : next_index + 26] == "\\setlength{\\headrulewidth}":
            end_cmd = output_line.find("}", next_index + 26)
            result += "\\renewcommand{\\headrulewidth}" + output_line[next_index + 26 : end_cmd + 1]
            index = end_cmd + 1
        elif output_line[next_index : next_index + 26] == "\\setlength{\\footrulewidth}":
            end_cmd = output_line.find("}", next_index + 26)
            result += "\\renewcommand{\\footrulewidth}" + output_line[next_index + 26 : end_cmd + 1]
            index = end_cmd + 1
        elif output_line[next_index : next_index + 10] == "\\epsffile{":
            result += output_line[index:next_index]
            result += "\\includegraphics"
            size_options = ""
            if line_number - last_epsfxsize_line <= 3:
                size_options = "width=" + last_epsfxsize
            if line_number - last_epsfysize_line <= 3:
                if size_options != "":
                    size_options += ","
                size_options += "height=" + last_epsfysize
            if size_options != "":
                result += "[" + size_options + "]"
            end_prn = output_line.find(".eps}", next_index + 9)

            if end_prn != -1:
                result += output_line[next_index + 9 : end_prn] + "}"
                index = end_prn + 5
            else:
                end_prn = output_line.find(".ps}", next_index + 9)
                if end_prn != -1:
                    result += output_line[next_index + 9 : end_prn] + "}"
                    index = end_prn + 4
                else:
                    end_prn = output_line.find("}", next_index + 9)
                    result += output_line[next_index + 9 : end_prn + 1]
                    index = end_prn + 1
        # I assume all the parameter of \epsfxsize comes in one line
        elif output_line[next_index : next_index + 11] == "\\epsfxsize=":
            end_size = read_size(output_line, next_index + 11, line_len)
            if end_size != -1:
                last_epsfxsize = output_line[next_index + 11 : end_size]
                index = end_size
            else:
                index = next_index + 11
            last_epsfxsize_line = line_number
        # I assume all the parameter of \epsfysize comes in one line
        elif output_line[next_index : next_index + 11] == "\\epsfysize=":
            end_size = read_size(output_line, next_index + 11, line_len)
            if end_size != -1:
                last_epsfysize = output_line[next_index + 11 : end_size]
                index = end_size
            else:
                index = next_index + 11
            last_epsfysize_line = line_number
        elif output_line[next_index : next_index + 10] == "\\LR{\\verb*":
            end_verb = output_line.find(output_line[next_index + 10], next_index + 11)
            verb_param = output_line[next_index + 11 : end_verb]
            if is_alpha_numeric(verb_param):
                result += output_line[index:next_index]
                result += "\\lr{\\tt{}" + verb_param
            else:
                result += output_line[index : end_verb + 1]
            index = end_verb + 1
        elif output_line[next_index : next_index + 9] == "\\LR{\\verb":
            end_verb = output_line.find(output_line[next_index + 9], next_index + 10)
            verb_param = output_line[next_index + 10 : end_verb]
            if is_alpha_numeric_space(verb_param):
                result += output_line[index:next_index]
                result += "\\lr{\\tt{}" + verb_param
            else:
                result += output_line[index : end_verb + 1]
            index = end_verb + 1
        elif output_line[next_index : next_index + 6] == "\\verb*":
            end_verb = output_line.find(output_line[next_index + 6], next_index + 7)
            result += output_line[index : end_verb + 1]
            index = end_verb + 1
        elif output_line[next_index : next_index + 5] == "\\verb":
            end_verb = output_line.find(output_line[next_index + 5], next_index + 6)
            result += output_line[index : end_verb + 1]
            index = end_verb + 1
        elif output_line[next_index : next_index + 9] == "\\pmatrix{":
            result += "\\ftxepmatrix{"
            index = next_index + 9
        elif output_line[next_index : next_index + 8] == "\\matrix{":
            result += "\\ftxematrix{"
            index = next_index + 8
        elif output_line[next_index : next_index + 16] == "\\begin{document}":
            result += "\\begin{document}\n%\\VerbatimFootnotes"
            index = next_index + 16
        elif output_line[next_index : next_index + 8] == "\\label {":
            begin_param = next_index + 8
            end_param = output_line.find("}", begin_param)
            param = convert_persian_to_english(output_line[begin_param:end_param])
            result += output_line[index : begin_param - 2]
            result += "{" + param + "}"
            index = end_param + 1
        elif output_line[next_index : next_index + 6] == "\\ref {":
            begin_param = next_index + 6
            end_param = output_line.find("}", begin_param)
            param = convert_persian_to_english(output_line[begin_param:end_param])
            result += output_line[index : begin_param - 2]
            result += "{" + param + "}"
            index = end_param + 1
        elif output_line[next_index : next_index + 7] == "\\label{":
            begin_param = next_index + 7
            end_param = output_line.find("}", begin_param)
            param = convert_persian_to_english(output_line[begin_param:end_param])
            result += output_line[index:begin_param]
            result += param + "}"
            index = end_param + 1
        elif output_line[next_index : next_index + 5] == "\\ref{":
            begin_param = next_index + 5
            end_param = output_line.find("}", begin_param)
            param = convert_persian_to_english(output_line[begin_param:end_param])
            result += output_line[index:begin_param]
            result += param + "}"
            index = end_param + 1
        elif output_line[next_index : next_index + 13] == "\\multicolumn{":
            begin_param = next_index + 13
            end_param = output_line.find("}", begin_param)
            param = convert_persian_to_english(output_line[begin_param:end_param])
            result += output_line[index:begin_param]
            result += param + "}"
            index = end_param + 1
        elif output_line[next_index : next_index + 12] == "\\setcounter{":
            begin_num = output_line.find("{", next_index + 12)
            end_num = output_line.find("}", begin_num)
            num = convert_persian_to_english(output_line[begin_num + 1 : end_num])
            result += output_line[index : begin_num + 1]
            result += num + "}"
            index = end_num + 1
        elif output_line[next_index : next_index + 14] == "\\addtocounter{":
            begin_num = output_line.find("{", next_index + 14)
            end_num = output_line.find("}", begin_num)
            num = convert_persian_to_english(output_line[begin_num + 1 : end_num])
            result += output_line[index : begin_num + 1]
            result += num + "}"
            index = end_num + 1
        else:
            result += output_line[index : next_index + 2]
            index = next_index + 2
    # end while
    return result


###############################################
# from here all functions are mainly used to
# convert farsitex format to unicode
###############################################


def convert_file(f, of, convert_cmds):
    global state
    global line_number
    global last_epsfysize_line
    global last_epsfxsize_line
    global last_epsfxsize
    global last_epsfysize
    global global_state

    state = 0
    line_number = 0
    last_epsfysize_line = 0
    last_epsfxsize_line = 0
    last_epsfxsize = ""
    last_epsfysize = ""

    for line in f:
        line_number += 1
        print(line_number, end=" ")
        output_line = ""
        line_len = len(line)

        # remove new-line characters from end of line
        if line_len > 1 and line[line_len - 1] == "\n":
            line_len -= 1
        if line_len > 1 and line[line_len - 1] == "\r":
            line_len -= 1

        # check line-direction character
        line_direction_rtl = line[0] == "<"
        if (line[0] != ">") and (line[0] != "<"):
            print("FORMAT ERROR AT LINE: " + str(line_number))
            exit(0)

        i = 1

        while i < line_len:
            next_part_index = ft_next_part(line, i, line_len)
            next_part = line[i:next_part_index]
            next_part_latin = line[i] < chr(0x80)

            # see if we should put \lr{...} for the current english expression
            if global_state == 0:
                if line_direction_rtl and next_part_latin:
                    is_command_rtl = next_part_latin and (i > 1) and (line[i - 1] == F_SLASH)
                    is_parameter_rtl = (
                        next_part_latin
                        and (i > 1)
                        and (next_part_index < line_len)
                        and (line[i - 1] == F_AT_SIGN)
                        and (line[next_part_index] == F_AT_SIGN)
                    )
                    is_math_rtl = (
                        next_part_latin and (line[i] == "$") and (line[next_part_index - 1] == "$")
                    )
                    is_verb_parameter = (line[i - 6 : i] == F_SLASH + "verb") and not line[
                        i
                    ].isalpha()
                    is_verb = next_part_latin and (
                        line[i : i + 5] == "\\verb" or line[i : i + 6] == " \\verb"
                    )
                    is_english = next_part_latin and (line[i : i + 8] == "\\english")

                    cmd_index = 0
                    while cmd_index < len(commands):
                        len_cmd = len(commands[cmd_index]) + 2
                        if (i > len_cmd) and (
                            line[i - len_cmd : i] == F_SLASH + commands[cmd_index] + F_PRNT_OPEN
                        ):
                            break
                        elif (i > len_cmd + 1) and (
                            line[i - len_cmd - 1 : i]
                            == F_SLASH + commands[cmd_index] + F_SPACE + F_PRNT_OPEN
                        ):
                            break
                        cmd_index += 1
                    is_commands_group = cmd_index < len(commands)
                    is_documentstyle_cmd = (line_len > 15) and (
                        line[1:15] == F_SLASH + "documentstyle"
                    )

            if next_part_latin:
                if global_state == 0:
                    # whether we should put a \lr{ command
                    if line_direction_rtl and not (
                        is_command_rtl
                        or is_parameter_rtl
                        or is_math_rtl
                        or is_commands_group
                        or is_documentstyle_cmd
                        or is_verb_parameter
                        or is_verb
                        or is_english
                    ):
                        output_line += "\\lr{"
                    if line_direction_rtl and is_verb:
                        output_line += "\\LR{"

                # here is the main place that converting happens
                output_line += next_part  # .encode("utf-8")

                if global_state == 0:
                    # check whether we already used a \lr command: then end it
                    if line_direction_rtl and not (
                        is_command_rtl
                        or is_parameter_rtl
                        or is_math_rtl
                        or is_commands_group
                        or is_documentstyle_cmd
                        or is_verb_parameter
                        or is_verb
                        or is_english
                    ):
                        output_line += "}"
                    if line_direction_rtl and is_verb:
                        output_line += "}"
            else:
                if global_state == 0:
                    # whether we should put a \rl{} command
                    if not line_direction_rtl and not ft_is_all_persian_space(next_part):
                        output_line += "\\rl{"

                # here is the main place that converting happens
                output_line += map_ft_unicode(next_part)

                if global_state == 0:
                    # check whether we already used a \rl command: then end it
                    if not line_direction_rtl and not ft_is_all_persian_space(next_part):
                        output_line += "}"

            i = next_part_index
        # end of while

        # if there was a % commenting then we can return to normal situation
        if global_state == 1:
            global_state = 0

        # convert some of the FarsiTeX commands to XePersian commands
        # only if it is requested
        if convert_cmds:
            result = translate_cmds(output_line)
        else:
            result = output_line
        output_line = result + "\n"
        # write the processed line
        of.write(output_line)
        # end of line processing
    # end of file processing


def print_usage():
    print("usage: python ftxe-0-11 [-r] [-s] [-x] [-u] in_filename1 in_filename2")
    print("-r: (DEFAULT) recursively consider files included in the given files")
    print("-s: do not recursively consider files")
    print("-x: (DEFAULT) insert xepersian related commands")
    print("-u: only convert to unicode")


###################################
# Begin of main body of the program
###################################

# global variables
line_number = 0
last_epsfxsize = ""
last_epsfxsize_line = 0
last_epsfysize = ""
last_epsfysize_line = 0
state = 0
global_state = 0
recursive = 1
convert_xepersian = 1
filename = ""

if len(sys.argv) <= 1:
    print_usage()
    exit(0)

# find options
options_index = 1
while options_index < len(sys.argv) and sys.argv[options_index][0] == "-":
    if sys.argv[options_index] == "-s":
        recursive = 0
    elif sys.argv[options_index] == "-u":
        convert_xepersian = 0
    options_index += 1

filenames = []
while options_index < len(sys.argv):
    filenames.append(sys.argv[options_index])
    options_index += 1

if len(filenames) == 0:
    print("error: no input filename is specified!")
    print_usage()
    exit(0)

index = 0
while index < len(filenames):
    filename = filenames[index]
    index += 1

    outfile = ""
    if filename[-4:] != ".tex":
        outfile = filename[0:-3] + "tex"
    else:
        outfile = filename + ".tex"

    print('\n\nConverting "' + filename + '" into "' + outfile + '"')
    try:
        f = open(filename, "r", encoding="Latin-1")
    except IOError:
        print("Can not open the input file: " + filename)
        exit(0)

    try:
        of = open(outfile, encoding="utf-8", mode="w")
    except IOError:
        print("Can not open the output file: " + outfile)
        exit(0)

    convert_file(f, of, convert_xepersian)

    of.close()
    f.close()
