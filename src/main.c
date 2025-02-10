#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/wordle.h"

/*
 * NOTE: Follow this example to use ANSI colours at the terminal:
 * https://www.theurbanpenguin.com/4184-2/
 *
 * In order to get ANSI colors showing in the CLion Run Console,
 * we need to do the following routine:
 *
 * 1. Choose Help -> Edit Custom Properties from CLion menu
 * 2. Add the following line to the idea.properties file:
 *      run.processes.with.pty=false
 * 3. Restart CLion.
 *
 * Reference:
 * https://youtrack.jetbrains.com/issue/CPP-8395/Registry-setting-runprocesseswithpty-not-saved#focus=Comments-27-2499735.0-0
 *
 */

int main(int argc, char* argv[]) {


    //INITIALIZE VARIABLES
    int wordLength;
    int numGuesses;
    int turnNumber;
    char* theWord;
    char** gameBoard;
    char* file1;
    char* file2;
    int** colorMap;
    char* userInput;
    bool flag = false;
    FILE *inFile, *outFile;


    //ERROR HANDLING
    if (argc != 5) {
        fprintf(stderr,"Invalid number of command line arguments.");
        return 1;
    }

    if (strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-o") == 0) {
        file1 = argv[2];
        file2 = argv[4];
    } else if (strcmp(argv[1], "-o") == 0 && strcmp(argv[3], "-i") == 0) {
        file1 = argv[4];
        file2 = argv[2];
    } else {
        fprintf(stderr, "Invalid command line argument usage.\n");
        return 1;
    }

    inFile = fopen(file1, "r");
    if (!inFile) {
        fprintf(stderr,"Cannot open %s for reading.", file1);
        return 1;
    }

    outFile = fopen(file2, "w");
    if (!outFile) {
        fprintf(stderr,"Cannot open %s for writing.", file2);
        fclose(inFile);
        return 1;
    }


    //READ INFILE TO SET VARIABLES
    fscanf(inFile,"%d%d", &wordLength, &numGuesses);

    theWord = malloc((wordLength + 1) * sizeof(char));
    fscanf(inFile,"%s", theWord);
    toUpperCase(theWord);

    userInput = malloc((wordLength + 1) * sizeof(char));


    //SET UP THE BOARD
    gameBoard = malloc(numGuesses * sizeof(char*));
    colorMap = malloc(numGuesses * sizeof(int*));

    for (int i = 0; i < numGuesses; i++) {
        gameBoard[i] = malloc(wordLength * sizeof(char));
        colorMap[i] = malloc((wordLength - 1) * sizeof(int));
    }

    initializeBoard(gameBoard, numGuesses, wordLength);


    //PLAY THE GAME
    printf("\nWelcome to C Wordle!!\n\n");

    for (int i = 0; i < numGuesses; i++) {
        turnNumber = i;

        printBoard(gameBoard, colorMap, numGuesses, wordLength);

        while (true) {
            printf("\nPlease enter a %d-letter word: ", wordLength);
            scanf("%s", userInput);
            if (strlen(userInput) == wordLength && isAllAlphabetical(userInput) == 1) {
                break;
            }

            printf("\nSorry, but you can only enter %d-letter words: ", wordLength);
        }
        toUpperCase(userInput);

        if(updateBoard(gameBoard,colorMap,theWord,userInput,wordLength,turnNumber) == 1) {
            flag = true;
            break;
        }
    }


    //END GAME
    printBoard(gameBoard, colorMap, numGuesses, wordLength);

    gameResult(gameBoard, numGuesses, flag, outFile, argv[4]);


    //CLEANUP
    fclose(inFile);
    fclose(outFile);
    free(theWord);
    free(userInput);

    for (int i = 0; i < numGuesses; i++) {
        free(gameBoard[i]);
        free(colorMap[i]);
    }
    free(gameBoard);
    free(colorMap);

    return 0;
}
