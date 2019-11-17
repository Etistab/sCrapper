/*
** Filename : main.c
**
** Made by  : Baptiste LEGO
**
** Description  : main file // entry point of the application
*/

#include "include/common.h"

int main(int argc, char **argv) {
    Config config;
    const char *type[1] = {"text/html"};
    int versioning = VERSIONING_ON;
    int i;

    loadConfig(&config, "config.sconf");

    for(i = 0; i < config.numberOfAction; i++) {
        printf("Start scrap %s...\nurl: %s\n\n", config.actions[i].name, config.actions[i].url);
        scrapWebsite(config.actions[i].name, config.actions[i].url, 0, versioning, type, 1);
        printf("\n\n");
    }

    return 0;
}
