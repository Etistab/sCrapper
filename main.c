#include <stdio.h>
#include <stdlib.h>
#include "include/common.h"

int main(int argc, char **argv) {
    FILE *file = fopen("res.php", "w");

    int code = httpGet("http://www.google.com", (void *)file, curlCallback);

    return 0;
}
