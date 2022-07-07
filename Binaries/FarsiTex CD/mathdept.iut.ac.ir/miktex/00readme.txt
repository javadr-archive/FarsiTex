MiKTeX 2.0 Readme File
Copyright (C) 2000 Christian Schenk

MiKTeX Readme File
******************

   This is the MiKTeX 2.0 Readme File.

What is it
**********

   MiKTeX is a free TeX distribution for Windows.

Downloading the MiKTeX distribution
***********************************

   The download folder (i.e. the folder that contains this Readme file)
contains an HTML page named `index.html'.  The page contains links to
all downloadable files.  It is highly recommended that you open this
page with an Internet browser now.

   The MiKTeX distribution consists of the MiKTeX Setup Wizard
(`setupwiz.exe') and accompanying Zip files.  Download the components
(Zip files), that you want to install.  Download all components, if you
intend to redistribute MiKTeX.

`msdll.zip'
     Various dynamic link libraries by Microsoft.  It's highly
     recommended that you download this Zip file.

`lcore.zip'
     MiKTeX core distribution: shared libraries.

`xcore.zip'
     MiKTeX core distribution: executable files.

`core.zip'
     MiKTeX core distribution: non-executable files.

`latex.zip'
     LaTeX core distribution & Babel.  You should download this Zip
     file if you intend to use LaTeX and/or Babel.

`latexpkg.zip'
     Standard LaTeX packages.  You should download this Zip file if you
     intend to use LaTeX.

`urw.zip'
     URW PostScript fonts.  You should download this Zip file if you
     intend to use standard PostScript fonts.

`amslatex.zip'
     This component includes the AMS-LaTeX package and the AMS fonts.
     You should download this Zip file if you intend to typeset
     mathematics.

`cmps.zip'
     Computer Modern fonts in Type1 format.  You should download this
     Zip file if you intend to use pdfTeX and/or Dvipdfm.

`amsps.zip'
     AMS fonts in Type1 format.  You should download this Zip file if
     you intend to use pdfTeX and/or Dvipdfm and if you typeset
     mathematics.

`ecfonts.zip'
     This component includes the European Computer Modern Fonts and Text
     Companion Fonts.  You should download this Zip file if you write
     in an european language.

`dvipdfm.zip'
     This component includes Dvipdfm.  This utility converts DVI files
     into PDF files.  You should download the Zip file if you want to
     create PDF documents.

`metapost.zip'
     This component includes the MetaPost application.  MetaPost is a
     graphics language based on METAFONT, but with PostScript output.

`lhfonts.zip'
     This component includes LH fonts in various encodings.  You should
     download this Zip file if you want to typeset cyrillic texts.

`yandy.zip'
     This component includes support files for Lucida Bright and
     MathTime fonts.  Download this Zip file if you have these fonts.

`psutils.zip'
     Utilities for manipulating PostScript documents.  Some of these
     utilities require Perl.

`pdftex.zip'
     This component includes pdfTeX.  pdfTeX can be used to convert TeX
     documents into PDF documents.

`etex.zip'
     This component includes e-TeX.  e-TeX is a feature-enhanced
     version of TeX.

`pdfetex.zip'
     This component includes pdfeTeX.  pdfeTeX is a pdfTeX/e-TeX merger.

`texinfo.zip'
     This component includes the programs Makeinfo, Makertf and
     Texindex.

`eplain.zip'
     Extended Plain TeX macros.

`xomega.zip'
     Omega executables.  Omega is a unicode-enhanced version of TeX.

`omega.zip'
     Omega input files.

`source2.zip'
     This component includes the source code for the LaTeX2e packages
     included in MiKTeX.

`german.zip'
     This component includes files supporting german-language
     typesetting.

`polish.zip'
     This component includes files supporting polish-language
     typesetting.

   Every Zip file has a correspinding `.lst' file which shows the Zip
file's contents.

Installation Instructions
*************************

  1. You should first remove any previous MiKTeX installation:

        * MiKTeX 1.11 users can use the uninstall program.

        * MiKTeX 1.20 users must remove MiKTeX by hand.  See the Local
          Guide of version 1.20, for more information.

        * MiKTeX 2.0 users can use the uninstall program.

  2. Make sure that you have enough disk space.  A complete MiKTeX
     installation consumes approximately 70MB of disk space.

  3. It is highly recommended that you login as Administrator, if you're
     installing MiKTeX on a Windows NT/2000 computer.

  4. Choose a location for the installation folder (e.g. `C:\Program
     Files\MiKTeX').  This folder receives the files of the MiKTeX
     distribution.

  5. You can cause MiKTeX to deposit newly created files (fonts, format
     files, file name databases) in a separate hierarchy of folders,
     called the _Local TEXMF tree_.  If you decide to use a local TEXMF
     tree, then you must choose a location for its root folder (e.g.
     `C:\Local TeXMF').

     Benefits that a local TEXMF tree provides include the following:

        * You can use it for your own additions (macros, fonts).

        * Easier updates: You don't have to worry about future MiKTeX
          updates, since the local TEXMF tree wont be touched by the
          setup program.

  6. Decide whether you want to incorporate an existing TEXMF tree.  For
     example, if you have a TeXLive CD inserted in your CD-ROM drive
     `E:', then it would be possible to include `E:\texmf' (the root of
     the TeXLive TEXMF tree) in the MiKTeX search procedure.

  7. Start MiKTeX Setup Wizard (`setupwiz.exe').  You will presented
     with the welcome page:

  8. Click `Next>' to go to the next page:

     You have the option to create a shared installation, so that other
     users are able to use MiKTeX.  Under Windows NT/2000, this option
     requires administrator privileges.

  9. Click `Next>' to go to the next page:

     Enter the full path to the desired installation folder (see step
     4).

 10. Click `Next>' to go to the next page:

     Choose the components that you want to install.

 11. Click `Next>' to go to the next page:

     Enter the full path to the desired local TEXMF folder (see step 5).
     Check the button `No local TEXMF tree', if you don't want to use a
     local TEXMF tree.

 12. Click `Next>' to go to the next page:

     You are asked about whether you want to incorporate existing TEXMF
     trees.  If you check the button `Incorporate existing TEXMF
     directory trees', then you must specify the locations of those
     trees on a subsequent page.

 13. Click `Next>' to go to the next page:

     You should now review the installation options.

 14. Click `Next>' to start the installation process.  The selected
     components will be copied to the installation folder chosen in
     step 9.

 15. When the files have been copied to your computer, you have the
     option to register the path to the MiKTeX bin directory:

 16. Click `Next>' to go to the final page:

     Click `Finish' to close Setup Wizard.

   It is possible to run the MiKTeX Setup Wizard in unattended mode.
See the Local Guide for more information.

Configuring dvips
*****************

   Dvips is configured as follows:

   * When generating fonts, Dvips uses METAFONT mode `ljfour' (HP
     Laserjet 4).

   * Horizontal resolution is set to 600 dpi.

   * Paper size is A4.

   * Dvips does not make use of the Computer Modern PostScript fonts.

   If these settings are not suitable for your site, then you have to
edit the Dvips configuration file `config.ps'.  You will find this file
in the directory `dvips\config' relative to the MiKTeX installation
folder (usually `C:\Program Files\MiKTeX').  See the MiKTeX Manual
(http://www.miktex.org/doc/manual/index.html), for more information.

Where are the docs?
*******************

   The MiKTeX Manual is available in a variety of formats:

  1. As a DVI document viewable/printable with Yap:

          C:\Program Files\MiKTeX\doc\miktex\miktex.dvi

  2. As a Windows Help file:

          C:\Program Files\MiKTeX\doc\miktex\miktex.hlp

  3. As an HTML document:

          C:\Program Files\MiKTeX\doc\miktex\miktex.html

  4. As a PDF file viewable with Acrobat Reader:

          C:\Program Files\MiKTeX\doc\miktex\miktex.pdf

   For up-to-date information, visit the MiKTeX Project Page
(http://www.miktex.org) (see below).

Mailing List
************

   There is a discussion list for MiKTeX.  To join the list, send an
email to <miktex-request@dsts.dk> which contains the word `subscribe'
as the first line in the message body.

MiKTeX Project Page
*******************

   Latest news are available on the MiKTeX Project Page:

   `http://www.miktex.org'

Copying
*******

   As far as I know, all components of the MiKTeX distribution are
freely redistributable, i.e. the whole MiKTeX distribution is freely
redistributable.

Disclaimer
**********

   The MiKTeX distribution comes with absolutely no warranty of any
kind.

