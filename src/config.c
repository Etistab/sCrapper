#include "../include/common.h"

void loadConfig(Config *config, const char* path) {
    FILE *f = fopen(path, "r");
    verifyPointer(f, "Fichier de config inexistant\n");
    readFile(f, config);
    fclose(f);
}

void readFile(FILE* f, Config *config) {
    char c;
    bool equal = false;
    config->actions = NULL;
    config->tasks = NULL;
    config->numberOfAction = 0;
    config->numberOfTask = 0;

    while(!feof(f)){
        c = fgetc(f);
        if(c == '#'){
            while(c != '\n') {
                c = fgetc(f);
            }
        }
        if(c == '='){
            if(equal == true){
                // Analyze task
                equal = false;
            }else{
                equal = true;
            }
        }
        if(c != '=' && equal == true){
            config->numberOfAction++;
            config->actions = realloc(config->actions, sizeof(Action) * config->numberOfAction);
            config->actions[config->numberOfAction - 1] = readAction(f);
            equal = false;
            fseek(f, -1, SEEK_CUR);
        }
    }
}

Action readAction(FILE* f){
    Action action;
    char buffer[5];
    char c;
    bool options = false;
    int i = 0, j = 0;
    action.name = malloc(sizeof(char) * 100);
    action.url = malloc(sizeof(char) * 100);

    while(c != '=' && !feof(f)){
        c = fgetc(f);
        if(options == false) {
            if(c == 'n'){
                for(i = 0; i < 4 && !feof(f); i++){
                    buffer[i] = c;
                    c = fgetc(f);
                }
                buffer[4] = '\0';

                if(strcmp(buffer, "name") == 0){
                    while(c != '>') {
                        c = fgetc(f);
                    }
                    c = fgetc(f);
                    for(j = 0; c != '}' && !feof(f); j++){
                        c = fgetc(f);
                        action.name[j] = c;
                    }
                    action.name[j - 1] = '\0';
                }
            }
            if(c == 'u'){
                for(i = 0; i < 3 && !feof(f); i++){
                    buffer[i] = c;
                    c = fgetc(f);
                }
                buffer[3] = '\0';

                if(strcmp(buffer, "url") == 0){
                    while(c != '>') {
                        c = fgetc(f);
                    }
                    c = fgetc(f);
                    for(j = 0; c != '}' && !feof(f); j++){
                        c = fgetc(f);
                        action.url[j] = c;
                    }
                    action.url[j - 1] = '\0';
                }
            }
        }
        if(c == '+'){
            //readOptions(f);
            options = true;
        }
    }

    return action;
}

//OPTION

/*Option readOptions(FILE* f) {
    Option options;
    while(c == '+' || !feof(f)){

    }
}*/
