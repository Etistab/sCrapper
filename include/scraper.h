/*
** Filename : scraper.c
**
** Made by  : Baptiste LEGO
**
** Description  : scrap functions
*/

#ifndef SCRAPER_H

#define SCRAPER_H

void scrapWebsite(char *name, char *url, int maxDepth, int versioning);
char *scrapPage(char *name, char *url, int versioning);
char **findLinks(char *html, int *numberOfLinks);

#endif
