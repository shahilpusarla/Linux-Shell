.PHONY: pwd
install_pwd:
	gcc pwd.c -o pawd
install_cs:
	gcc CS33.c -o CS33
mkdir:
	mkdir mydir
mv:
	mv pawd ./mydir
install:install_pwd install_cs mkdir mv

test:
	./CS33 batch
clean:
	rm mydir/*
	rmdir mydir
	rm CS33
	rm file.txt
doc:
	pdflatex latexdoc
	  
	
