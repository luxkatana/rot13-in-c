FILE_TO_DECRYPT = test
default:
	@gcc src/decryptor.c -o bin/decryptor
	@echo "\n\n\n"
	./bin/decryptor $(FILE_TO_DECRYPT)

	@echo "\n\n\n"
	@python3 assertion.py
