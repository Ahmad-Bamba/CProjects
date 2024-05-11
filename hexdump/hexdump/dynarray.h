#ifndef HEXDUMP_DYNARRAY_H
#define HEXDUMP_DYNARRAY_H

#include <stddef.h>
#include <stdbool.h>

struct dynarray;

struct dynarray* dynarray_create(size_t);
void dynarray_destroy(struct dynarray*);
bool dynarray_push_back(struct dynarray*, unsigned char);
bool dynarray_push_back_all(struct dynarray*, unsigned char*, size_t);
unsigned char dynarray_get(struct dynarray*, size_t);
size_t dynarray_size(struct dynarray*);

#endif
