FILE_TO_ENCRYPT = test
default:
	@gcc src/encryptor.c -o bin/encryptor
	@echo "\n\n\n"

	./bin/encryptor $(FILE_TO_ENCRYPT)
	@echo "\n\n\n"
	@python3 assertion.py
