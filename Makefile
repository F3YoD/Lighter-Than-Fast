# This Makefile should only redirect the job to the Makefile in src/
GOTOSUB=cd src/

all:
	$(GOTOSUB) && make all

clean:
	$(GOTOSUB) && make clean
