/*
** Filename : main.c
**
** Made by  : Baptiste LEGO
**
** Description  : main file // entry point of the application
*/

#include "include/common.h"

int main(int argc, char **argv) {
    scrapWebsite("google", "https://www.google.com", 0, VERSIONING_ON);

    return 0;
}
