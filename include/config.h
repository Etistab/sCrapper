#ifndef CONFIG_H

#define CONFIG_H

struct Option {
    char *key;
    void *value;
} typedef Option;

struct Action {
    char *name;
    char *url;
    Option *options;
} typedef Action;

struct Task {
    short hour, minute, second;
    char * name;
    Action *action;
} typedef Task;

struct Config {
    Action *actions;
    int numberOfAction;
    Task *tasks;
    int numberOfTask;
} typedef Config;

void loadConfig(Config *config, const char* path);
void readFile(FILE* f, Config *config);
Action readAction(FILE* f);

#endif
