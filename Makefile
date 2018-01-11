# This Makefile should only redirect the job to the Makefile in src/

all clean cleanobj debug run:
	@$(MAKE) $@ -C src/
