#include "highscores.h"

/*
    transformToPlay receives player input and his data after a match, transforms it to a struct of type play and returns it;
*/

struct play transformToPlay (char name[21], int timeSpent, int moves, int completeLevels) {
    struct play temporary;
    strcpy(temporary.name, name); // copy string name to temporary.name
    temporary.score = (pow(10, 3) * pow(completeLevels, 3) / (moves + (timeSpent / 2))); // Calculating player score;
    return temporary;
}

/*
    appendPlay receives a struct of type play and append it to the binary highscores file.
*/

void appendPlay (struct play temporary) {
    FILE *binaryFile = fopen("scores.bin", "ab"); // open binary file in append mode
    if (binaryFile == NULL) { // check if had success opening binary file
        printw("Unable to save.");
    }
    fwrite(&temporary, sizeof(struct play), 1, binaryFile); //append received struct play in binary file
    fclose(binaryFile); // close binary file
}

/*
    Simple bubble sort implementation used to sort the scores loaded from the binary file.
*/


void bubbleSort(struct play* array, int i) {
    struct play x;
    for (int j = 0; j < i; j++) {
        for (int k = 0; k < (i - 1); k++) {
            if (array[k].score < array[k + 1].score) {
                x = array[k];
                array[k] = array[k + 1];
                array[k + 1] = x;
            }
        }
    }
}


/*
    showHighscores reads all the data from the binaryfile, sort the data and display it.
*/

void showHighscores() {
    WINDOW * highscore = newwin(20, 76, 2, 2); // highscore window
    char bufferString[80]; // this will be the string variable we'll use to print the highscores, you'll understand it soon.
    FILE *binaryFileRead = fopen("scores.bin", "rb"); //Open scores.bin and assign its address to the pointer binaryFileRead
    if (binaryFileRead == NULL) { //Test if score.bin was loaded.
        printw("Unable to load.");
    }
    fseek(binaryFileRead, 0L, SEEK_END); // goes to the end of the file (required for the following line)
    int i = ftell(binaryFileRead) / sizeof(struct play); // we'll use I as our counter of how many play structs are stored on the bin file, ftell shows current position in bytes and sizeof gives us the size of a struct play, I divide then and get how many struct plays are stored in the file.
    if (!i) { // if there aren't any struct play in the file, displays error message
        printw("there aren't any highscores stored");
    } else {
        rewind(binaryFileRead); // go to the start of the binary file to use it in fread();
        struct play scores[i];
        fread(scores, sizeof(struct play), i, binaryFileRead); // read binary file and store its value in struct play array scores.
        fclose(binaryFileRead); // closes binary file.
        bubbleSort(scores, i); // bubble sort array (with pointers)
        box(highscore, 0, 0); // creates box around window highscore
        mvwprintw(highscore, 2, 33, "Highscore"); // print "Highscore" centralized at the third line of Highscore window.
        for (int x = 0; x < 10; x++) {
            snprintf(bufferString, 80, "nome: %s  score: %f", scores[x].name, scores[x].score);
            wmove(highscore, (4 + x), (76 - strlen(bufferString)) / 2 );
            // let me explain what just happened
            // I needed to centralize the printed string but it's size is variable depending on the name and score of the player
            // so I used snprintf to format a string and save it to the bufferString variable, and with this info the program move the cursor
            // for a position that'll give us sufficient space to print our string with and maintain it centralized
            // also, the program doesn't used newlines for that, it manually moved the string everytime the for loop loops.
            wprintw(highscore, "%s", bufferString);
        }
    }
    wrefresh(highscore); // refresh ncurses window
    getch();
    delwin(highscore);
}
