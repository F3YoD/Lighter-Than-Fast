# This Makefile should only redirect the job to the Makefile in src/

all debug clean cleanobj:
	@$(MAKE) $@ -C src/
