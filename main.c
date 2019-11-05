#include <stdio.h>
#include <stdlib.h>
#include "include/common.h"

int main(int argc, char **argv) {
    //curl init
    curl_global_init(CURL_GLOBAL_ALL);

    printf("Hello world!\n");
    return 0;
}
