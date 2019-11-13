void scrapWebsite(char *name, char *url, int maxDepth);
char *scrapPage(char *name, char *url);
char **findLinks(char *html, int *numberOfLinks);
