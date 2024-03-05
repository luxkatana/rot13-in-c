#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#define MAX_LENGTH_OF_LINE 2000
int contains_char(char character, char *collection);
char *encrypt_rot32(char *input, unsigned int input_length);
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "SYNTAX: %s <FILE_TO_ENCRYPT>\n", *argv);
        return 1;
    }
    char *FILE_TO_ENCRYPT = argv[1];
    FILE *to_read_file = fopen(FILE_TO_ENCRYPT, "r");
    if (to_read_file == NULL)
    {
        fprintf(stderr, "Could not open file\n");
        exit(1);
    }

    FILE *result_file = fopen("./result.txt", "w");
    if (result_file == NULL)
    {
        fprintf(stderr, "Could not open result.txt\n");
        exit(1);
    }
    char buffer[MAX_LENGTH_OF_LINE];
    while (fgets(buffer, MAX_LENGTH_OF_LINE, to_read_file))
    {
        if (buffer[strlen(buffer) - 1] == '\n') // trimming the \n if necessary
            buffer[strlen(buffer) - 1] = '\0';

        char *encrypted_data = encrypt_rot32(buffer, strlen(buffer));

        fprintf(result_file, "%s\n", encrypted_data);
        free(encrypted_data);
    }

    fclose(to_read_file);
    fclose(result_file);
    printf("Encrypted version of %s has been written to ./result.txt\n", FILE_TO_ENCRYPT);

    return 0;
}

char *encrypt_rot32(char *input, unsigned int input_length)
{
    char current_char = *input;
    char *rot13_charset = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
    char *alphabet_charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char *symbols = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ \t\n0123456789";
    char *encrypted_data = (char *)malloc(sizeof(char) * input_length);
    if (encrypted_data == NULL)
        return NULL;
    for (int i = 0; i < input_length; i++, current_char = *(input + i))
    {
        int index = contains_char(current_char, alphabet_charset);

        if (index != -1)
        {
            *(encrypted_data + i) = rot13_charset[index];
        }
        else if (contains_char(current_char, symbols) != -1)
        {
            if (current_char != '\n')
                *(encrypted_data + i) = current_char;
        }
    }
    encrypted_data[input_length] = '\0'; // ending the 'encrypted_data' with \0
    return encrypted_data;
}

int contains_char(char character, char *collection)
{
    char current_char = *collection;
    for (int i = 0; current_char != '\0'; i++, current_char = collection[i])
    {
        if (current_char == character)
            return i;
    }
    return -1;
}