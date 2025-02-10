//
// Created by Daryoush Sehatzadeh on 2024-11-21.
//

#include "../inc/wordle.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


//yellow = "\033[0;33m"
//green = "\033[0;32m"
//reset = "\033[0m"


void initializeBoard(char** gameBoard, int numRows, int numCols) {

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            gameBoard[i][j] = '_';
        }
        gameBoard[i][numCols] = '\0';
    }
}

void printBoard(char** gameBoard, int** colorMap, int numRows, int numCols) {
    printf("Current game state: \n");
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (colorMap[i][j] == GREEN) {
                printf("\033[0;32m");
            } else if (colorMap[i][j] == YELLOW) {
                printf("\033[0;33m");
            }
            printf("%c\t", gameBoard[i][j]);
            printf("\033[0m");
        }
        printf("\n");
    }
}

int updateBoard(char** gameBoard, int** colorMap, char* theWord, char* userInput, int wordLength, int turnNumber) {
    if(strcmp(theWord, userInput) == 0) {
        for (int i = 0; i < wordLength; i++) {
            colorMap[turnNumber][i] = GREEN;
            strcpy(gameBoard[turnNumber], userInput);
        }
        return 1;
    }

    for (int i = 0; i < wordLength; i++) {
        if (userInput[i] == theWord[i]) {
            colorMap[turnNumber][i] = GREEN;
        } else if (strchr(theWord, userInput[i])) {
            colorMap[turnNumber][i] = YELLOW;
        } else {
            colorMap[turnNumber][i] = GREY;
        }
    }

    strcpy(gameBoard[turnNumber], userInput);

    return 0;
}

void gameResult(char** gameBoard, int numRows, bool flag, FILE* file, char* path) {
    if (flag) {
        printf("\nYOU WIN!!!\n");
        fprintf(file, "The solution was found.\n");
    } else {
        printf("\nYOU LOSE!!!\n");
        fprintf(file, "The solution was not found.\n");
    }

    for (int i = 0; i < numRows; i++) {
        fprintf(file, "%s\n", gameBoard[i]);
    }
    printf("The game result was written to the %s file", path);

}

void toUpperCase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

int isAllAlphabetical(const char* str) {
    while (*str) {
        if (!isalpha((unsigned char)*str)) {
            return 0; // Not an alphabetical character
        }
        str++;
    }
    return 1; // All characters are alphabetical
}