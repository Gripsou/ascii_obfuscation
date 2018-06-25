@echo *** Call ubuntu subsystem ***
@ubuntu run doxygen ascii_obfuscation.doxygen.cnfg
@cd latex
@ubuntu run make all
@rename refman.pdf ascii_obfuscation_api_documentation.pdf