//
// Created by Daryoush Sehatzadeh on 2024-11-21.
//

#ifndef WORDLE_H
#define WORDLE_H
#include <stdbool.h>
#include <stdio.h>

enum  COLORCODES {
    GREY = 0,
    YELLOW = 1,
    GREEN = 2,
};

void initializeBoard(char** gameBoard, int numRows, int numCols);
void printBoard(char** gameBoard, int** colorMap, int numRows, int numCols);
int updateBoard(char** gameBoard, int** colorMap, char* theWord, char* userInput, int wordLength, int turnNumber);
void gameResult(char** gameBoard, int numRows, bool flag, FILE* file, char* path);
void toUpperCase(char* str);
int isAllAlphabetical(const char* str);

#endif //WORDLE_H
