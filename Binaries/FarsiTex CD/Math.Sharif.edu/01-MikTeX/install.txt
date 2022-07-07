==============================================================================
install.txt (FarsiTeX Distribution)
==============================================================================

			    INSTALLATION GUIDE
				   for
			    MiKTeX and FarsiTeX


I. Installation on Windows 95/98/ME/NT/2000
===========================================

1. Get MiKTeX from http://www.miktex.org/ or download a smaller
   version from
      http://download.farsitex.org/farsitex/miktex-small-2.0.zip
   or
      ftp://ftp.sharif.ac.ir/pub/farsitex/miktex-small-2.0.zip
   and install it.

2. Unzip farsitex-1.0-alpha-2.zip to the same directory you installed
   MiKTeX, "c:\Program Files\MiKTeX" for example.

3. Run "mo". Go to the "TeX Formats" tab and press "New...". Fill the
   form with the following information:

      Format Name: FarsiTeX
      Compiler: e-TeX (Extended Mode)
      Input File Name: farsitex.ini
      Output File Name: farsitex.efmt
      Preloaded Format: (empty)
      Description: FarsiTeX

   Press "Ok". Press "Ok" again.

4. At the command line, run the following commands:

      initexmf -p"C:\Program Files\MiKTeX\farsitex\config\miktex.ini"
      initexmf -u

   (Replace "C:\Program Files\MiKTeX" with where you installed MiKTeX).

5. Install the font file at "C:\Program Files\MiKTeX\FarsiTeX.fon" to
   your Windows, by going to "Control Panel | Fonts" and selecting
   "Install New Font" from the "Files" menu.

6. [optional] Get GSview and GhostScript from
      http://www.cs.wisc.edu/~ghost/
   and install them.

7. You can now invoke the editor using the "ftexed" command.

II. Installation on Linux or other UNIX systems
===============================================

[TODO]

III. Installation on DOS and Novell Netware
===========================================
This version of FarsiTeX is not intended for being installed on DOS
or Novell Netware. These two are not supported anymore. You can download
an older version of FarsiTeX for using with DOS or Novell Netware.

Test your installation
======================
- Run the sample file [TODO].

- Read documentation files in <farsitex>\doc\farsitex.

- Print the manual at <farsitex>\doc\farsitex\manual.

- Try some of the sample files in <farsitex>\doc\farsitex\samples.

You are all set now to use FarsiTeX. Enjoy it!


--- Roozbeh Pournader (roozbeh@sharif.edu) -----------------------------
--- Copyright 1996--2001, FarsiTeX Project Team. All rights reserved ---
--- $Date: 2001/03/07 04:29:40 $ -------------------------------------------------------------
