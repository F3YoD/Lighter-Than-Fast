# This Makefile should only redirect the job to the Makefile in src/


all clean:
	@cd src/ && $(MAKE) $@
