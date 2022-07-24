TEXFILE := Informe

.PHONY: all clean

all:
	pdflatex -synctex=1 $(TEXFILE)
	pdflatex -synctex=1 $(TEXFILE)

clean:
	-$(RM) -r *.idx *.ind *.glo *.brf *.ilg *.ist *.nlo *.nls *.acn *.gls *.glg *.glg
	-$(RM) -r *.log *.aux *.bbl *.blg *.dvi *.bak *.toc *.ps *.synctex.gz *.pdfsync *.out *.lof *.lot
	-$(RM) -r *.alg *.acr *.loa *.lol *.nav *.snm
	-$(RM) -r *~
