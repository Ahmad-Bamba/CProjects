#include "dynarray.h"

#include <stdlib.h>
#include <string.h>

struct dynarray {
    size_t size;
    size_t capacity;
    unsigned char* buf;
};

struct dynarray* dynarray_create(size_t init)
{
    if (init < 1) {
        init = 1;
    }
    struct dynarray* ret = malloc(sizeof(struct dynarray));
    if (ret == NULL) {
        return NULL;
    }
    ret->buf = malloc(init);
    if (ret->buf == NULL) {
        free(ret);
        return NULL;
    }
    ret->size = 0;
    ret->capacity = init;
    return ret;
}

void dynarray_destroy(struct dynarray* arr)
{
    if (arr == NULL) {
        return;
    }
    if (arr->buf != NULL) {
        free(arr->buf);
        arr->buf = NULL;
    }
    free(arr);
    arr = NULL;
}

bool dynarray_push_back(struct dynarray* this, unsigned char value)
{
    if (this == NULL) {
        return false;
    }
    if (this->size >= this->capacity) {
        this->capacity *= 2;
        unsigned char* new_buf = malloc(this->capacity);
        if (new_buf == NULL) {
            return false;
        }
        memcpy(new_buf, this->buf, this->size);
        unsigned char* temp = this->buf;
        this->buf = new_buf;
        free(temp);
    }
    this->buf[this->size] = value;
    this->size += 1;
    return true;
}

bool dynarray_push_back_all(struct dynarray* this, unsigned char* new_buf, size_t len)
{
    if (len == 0) {
        return true;
    }
    if (this == NULL || new_buf == NULL) {
        return false;
    }

    size_t i;
    for (i = 0; i < len; i++) {
        if (!dynarray_push_back(this, new_buf[i])) {
            return false;
        }
    }
    return true;
}

unsigned char dynarray_get(struct dynarray* this, size_t i)
{
    if (this == NULL) {
        return 0x00;
    }
    return this->buf[i];
}

size_t dynarray_size(struct dynarray* this) {
    if (this == NULL) {
        return 0;
    }
    return this->size;
}
