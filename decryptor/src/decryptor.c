#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH_OF_LINE 256

char *decrypt_rot32(char *input, int input_length);
int contains_char(char character, char *collection);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "SYNTAX: %s <FILE_TO_DECRYPT>\n");
        return 1;
    }
    char *FILE_TO_DECRYPT = argv[1];
    FILE *file_to_read = fopen(FILE_TO_DECRYPT, "r");
    if (file_to_read == NULL)
    {
        fprintf(stderr, "%s: no such file or directory\n", FILE_TO_DECRYPT);
        return 1;
    }
    FILE *result_file = fopen("./result.txt", "w");
    if (result_file == NULL)
    {
        fprintf(stderr, "Could not open result file\n");
        exit(1);
    }
    char buffer[MAX_LENGTH_OF_LINE];
    while (fgets(buffer, MAX_LENGTH_OF_LINE, file_to_read))
    {
        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';
        char *decrypted_data = decrypt_rot32(buffer, strlen(buffer));
        if (decrypted_data == NULL)
        {
            fprintf(stderr, "Possible data loss (could not allocate data for decrypting)\n");
            exit(1);
        }
        fprintf(result_file, "%s\n", decrypted_data);
        free(decrypted_data);
    }
    fclose(file_to_read);
    fclose(result_file);
    return 0;
}

char *decrypt_rot32(char *input, int input_length)
{
    char *rot13_charset = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
    char *alphabet_charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char *symbols = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~ \t0123456789";
    char current_character = *input;
    char *result = (char *)malloc(sizeof(char) * input_length);
    if (result == NULL)
        return NULL;
    for (int i = 0; i < input_length; i++, current_character = input[i])
    {
        int index = contains_char(current_character, rot13_charset);
        if (index != -1)
            result[i] = alphabet_charset[index];
        else if (contains_char(current_character, symbols) != -1)
            result[i] = current_character;
    }
    result[input_length] = '\0';
    return result;
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