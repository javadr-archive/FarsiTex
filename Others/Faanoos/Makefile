all: fandoc.ps shamlou.ps salinjer.ps

view: fandoc.ps
	gv $< &

.SUFFIXES:

.PHONY: all view

fandoc.dvi: hafez.tex fatiha.tex poem.sty

faanoosotps = faanoos.otp fanfinal.otp noyeh.otp nokasre.otp notashdid.otp smallyeh.otp farsi456.otp
faanoosocps = faanoos.ocp fanfinal.ocp noyeh.ocp nokasre.ocp notashdid.ocp smallyeh.ocp farsi456.ocp
otherocps = farsihack.ocp farsinorm.ocp cuni2ofa.ocp uni2cuni.ocp
ocps = $(faanoosocps) $(otherocps)
faanooslambda = faanoos.sty ot1f456.fd $(ocps)
faanoosodvips = faanoos.map config.faanoos $(ocps)

$(faanoosocps) : faanoos.inc.m4
faanoos.otp : fanutf8.inc.m4

%: %.m4
	m4 $< > $@ || \
	( $(RM) $@; false )

%.ocp: %.otp
	otp2ocp $*

%.dvi: %.tex $(faanooslambda)
	lambda $<
	lambda $<

%.ps: %.dvi $(faanoosodvips)
	odvips -Pfaanoos $< -o $@

%.pdf: %.ps
	ps2pdf $< $@
