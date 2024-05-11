// Matrix library
#include "randstr.h"

// standard library
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

// windows api
#include <Windows.h>

enum column_type {
    RainDrop = 0,
    Spacer = 1,
};

struct column {
    enum column_type type;
    const char* data;
    size_t sparkler_index;
    struct column* next;
};

static volatile bool alive = true;

static void kill_handler(int arg)
{
    alive = false;
}

int main()
{

}