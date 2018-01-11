# This Makefile should only redirect the job to the Makefile in src/

all %:
	@$(MAKE) $@ -C src/
