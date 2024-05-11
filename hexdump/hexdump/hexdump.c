#include "dynarray.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define CHUNK_SIZE 256

void print_args(int argc, char** argv)
{
    int i;
    printf("%d arguments -\r\n\t", argc);
    for (i = 0; i < argc; i++) {
        printf("%d:%s ", i, argv[i]);
    }
    printf("\n");
}

void print_help(FILE* output)
{
    fprintf(output, "--- hexdump ---\r\n");
    fprintf(output, "usage:\r\n\thexdump filename [/W column_width] [/A]\r\n");
    fprintf(output, "\thexdump /h\r\n");
    fprintf(output, "\t/W column width is how many columns the bytes will be displayed (default 2)\r\n");
    fprintf(output, "\t/A should we also print ascii characters? (default no)\r\n");
    fprintf(output, "\t/h prints this help message");
}

bool is_printable_ascii(unsigned char c)
{
    return (c >= 32) && (c <= 127);
}

int dump_file(char const* filename, int col_width, bool ascii)
{
    if (col_width <= 0) {
        print_help(stderr);
        return 1;
    }
    printf("Parsing \"%s\" (cols = %d,", filename, col_width);
    if (ascii) {
        printf(" ascii is enabled)\r\n");
    }
    else {
        printf(" ascii is disabled)\r\n");
    }

    FILE* f;
    if ((f = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "Could not open file \"%s\"", filename);
        return 1;
    }

    struct dynarray* bytes = dynarray_create(100);

    while (true) {
        unsigned char chunk[CHUNK_SIZE];
        size_t const read_size = fread(chunk, sizeof(unsigned char), CHUNK_SIZE, f);
        dynarray_push_back_all(bytes, chunk, read_size);
        if (read_size == CHUNK_SIZE) {
            continue;
        }
        else {
            if (feof(f)) {
                break;
            }
            else if (ferror(f)) {
                fprintf(stderr, "Error reading file \"%s\"!\n", filename);
                dynarray_destroy(bytes);
                return 1;
            }
            fprintf(stderr, "Warning: stopped reading before eof (?)\n");
            break;
        }
    }

    size_t i;
    size_t bytes_size = dynarray_size(bytes);
    int row = 0;
    char* ascii_buf;
    if (ascii) {
        ascii_buf = malloc(4 * 2 * col_width + 1);
    }
    size_t ascii_i;
    for (i = 0; i < bytes_size; i++) {
        if (i % (4 * col_width) == 0) {
            printf("%p: ", (void*)(row * 4 * col_width));
            if (ascii) {
                memset(ascii_buf, (char)0, 4 * 2 * col_width + 1);
                ascii_i = 0;
            }
        }
        if (i % 4 == 0 && i % (4 * col_width) != 0) {
            printf(" ");
        }
        unsigned char c = dynarray_get(bytes, i);
        printf("%02X", c);
        if (ascii) {
            if (is_printable_ascii(c)) {
                ascii_buf[ascii_i] = c;
            }
            else {
                ascii_buf[ascii_i] = '.';
            }
            ascii_i += 1;
        }
        if (i % (4 * col_width) == 4 * col_width - 1) {
            printf(" ");
            if (ascii) {
                printf("%s", ascii_buf);
            }
            printf("\r\n");
            row += 1;
        }
    }

    printf("\r\ndone (printed %d bytes)\r\n", bytes_size);

    if (ascii) {
        free(ascii_buf);
    }
    dynarray_destroy(bytes);
    fclose(f);
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        print_help(stderr);
        return 1;
    }
    // print_args(argc, argv);
    if (strcmp(argv[1], "/h") == 0) {
        print_help(stdout);
        return 0;
    }

    char const* filename = argv[1];
    int col_width = 2;
    bool ascii = false;

    int i;
    for (i = 2; i < argc; i++) {
        if (strcmp(argv[i], "/A") == 0) {
            ascii = true;
            continue;
        }
        if (strcmp(argv[i], "/W") == 0) {
            i++;
            if (i >= argc) {
                print_help(stderr);
                return 1;
            }
            col_width = atoi(argv[i]);
            continue;
        }
    }
    return dump_file(filename, col_width, ascii);
}
