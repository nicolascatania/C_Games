#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAXWORDS 50
#define MAXWORDLEN 100
#define INITIAL_WORD_COUNT 10
#define FILE_WORDS "WORDS.txt"


void hangmanGame();
char* randWord(const char**,int);
char validateCharEntry();
void printWord(const char*,const int*, int);
char** getWords(const char* file_name, int* wordCount);

int main()
{
    srand(time(NULL));
    hangmanGame();
    return 0;

}

void hangmanGame()
{
    char c, option;
    char* randW, *guess;
    char** wordPool;
    int i, lifes, win =0, lettersCorrect, wordLen, wordsCount;
    int* guessWord;
    wordPool = getWords(FILE_WORDS,&wordsCount);
    if(!wordPool){
        puts("Error: Unable to allocate memory for words");
        return;
    }
    puts("Welcome to HangmanGame");
    while(1)
    {
        lettersCorrect=0;
        randW = randWord((const char**)wordPool, wordsCount);
        if (!randW) {
            puts("Error: Unable to allocate memory for random word.");
            return;
        }
        wordLen = strlen(randW);
        guessWord = (int*)malloc(wordLen*sizeof(int));
        if(!guessWord){
            puts("Error: Unable to allocate memory for the result manager buffer");
            return;
        }
        memset(guessWord, 0, wordLen*sizeof(int));
        printWord(randW,guessWord,wordLen);
        lifes = 3;
        win =0;

        while(lifes>0 && !win)
        {
            puts("Type your guess");
            c= toupper(validateCharEntry());
            guess = strchr(randW, (int)c);

            if(!guess){
                lifes--;
                puts("INCORRECT");
            }
            else
            {
                for(i=0;i<wordLen;i++){
                    if(c == randW[i])
                    {
                        lettersCorrect++;
                        guessWord[i]= 1;
                    }
                    if(guessWord[i]==1)
                    {
                        printf("%c ",randW[i]);
                    }
                    else
                    {
                        printf("_ ");
                    }
                }
                puts("");
            }
            if(lettersCorrect==wordLen)
            {
                win=1;
                system("cls");
                printWord(randW,guessWord,wordLen);
                puts("\nYOU WIN");
            }
        }
        if(lifes<1){
            system("cls");
            printf("The word was %s.\n", randW);
            puts("You loose");
        }
        puts("Do you want to play again? [any key/n]");
        option = toupper(validateCharEntry());
        if(option=='N'){
            break;
        }
        system("cls");
    }
    free(randW);
    free(guessWord);
}

char* randWord(const char** wordPool, int wordsCount)
{
    int randN = rand()%(wordsCount);
    char* w = (char*)malloc(strlen(wordPool[randN]));
    strcpy(w, wordPool[randN]);
    return w;
}


char validateCharEntry() {
    char c;
    while (1) {
        scanf(" %c", &c);
        fflush(stdin);
        if (isalpha(c)) {
            return c;
        }
        puts("Invalid input. Please enter a single alphabetic character.");
    }
}

void printWord(const char* w,const int* result, int len){
    int i;
    for(i=0;i<len;i++){
        if(result[i])
        {
            printf("%c ", w[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    puts("");
}



char** getWords(const char* file_name, int* wordCount) {
    int capacity = INITIAL_WORD_COUNT, len;
    char** wordPool = (char**)malloc(capacity * sizeof(char*));
    char buffer[MAXWORDLEN];
    FILE* pf = fopen(file_name, "rt");
    if (!pf) {
        printf("There was a problem trying to open %s.\n", file_name);
        return NULL;
    }

    *wordCount = 0;

    while (fscanf(pf, "%s", buffer) == 1) {
        if (*wordCount >= capacity) {
            capacity *= 2;
            wordPool = (char**)realloc(wordPool, capacity * sizeof(char*));
        }
        if(!wordPool)
        {
            puts("Error: Unable to allocate more memory to store more words");
        }
        len = strlen(buffer);
        wordPool[*wordCount] = (char*)malloc((len + 1) * sizeof(char));
        strcpy(wordPool[*wordCount], buffer);
        (*wordCount)++;
    }

    fclose(pf);
    return wordPool;
}

