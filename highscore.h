#include "game.h"

struct entry { // this struct will be used to define each score made in a gameplay
    char name[50];
    unsigned int score;
};

struct highestscores { // this struct will be used to maintain the top 10 best scores
    struct entry entries[10];
};
