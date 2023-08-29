#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include "hangman.h"


int get_word(char secret[]){
    // check if file exists first and is readable
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    // get the filesize first
    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        // generate random number between 0 and filesize
        long int random = (rand() % size) + 1;
        // seek to the random position of file
        fseek(fp, random, SEEK_SET);
        // get next word in row ;)
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]) 
{
    for (int i = 0; secret[i] != '\0'; i++) 
    {
        bool letter_found = false;
        for (int j = 0; letters_guessed[j] != '\0'; j++) 
        {
            if (secret[i] == letters_guessed[j]) 
            {
                letter_found = true;
                break;
            }
        }
        if (!letter_found) 
        {
            return 0;
        }
    }
    return 1;
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) 
{
    int i, j;
    bool letter_found;

    for (i = 0; secret[i] != '\0'; i++) 
    {
        letter_found = false;

        for (j = 0; letters_guessed[j] != '\0'; j++) 
        {
            if (secret[i] == letters_guessed[j]) 
            {
                letter_found = true;
                break;
            }
        }

        if (letter_found) 
        {
            guessed_word[i] = secret[i];
        } else {
            guessed_word[i] = '_';
        }
    }

    guessed_word[i] = '\0'; 
}

void get_available_letters(const char letters_guessed[], char available_letters[]) 
{
    char alphavit[] = "abcdefghijklmnopqrstuvwxyz";
    int j = 0; 

    for (int i = 0; alphavit[i] != '\0'; i++) 
    {
        bool found = false;

        for (int k = 0; letters_guessed[k] != '\0'; k++) 
        {
            if (alphavit[i] == letters_guessed[k]) 
            {
                found = true;
                break;
            }
        }

        if (!found) 
        {
            available_letters[j] = alphavit[i];
            j++;
        }
    }
    available_letters[j] = '\0';
}

void hangman() 
{
    srand(time(NULL));
    char secret[21] = {0};
    char alphavit[] = "abcdefghijklmnopqrstuvwxyz";

    if (get_word(secret)) 
    {
        fprintf(stderr, "Could not get a word.\n");
        return;
    }

    printf("Welcome to the game, Hangman!\n");
    printf("Secret: %s\n", secret);
    char letters_guessed[27] = {0};
    char guessed_word[21] = {0};
    char available_letters[27] = {0};
    char guess;
    int attempts = 8;

    while (!is_word_guessed(secret, letters_guessed) && attempts >= 0) 
    {
        get_available_letters(letters_guessed, available_letters);
        printf("Current word: %s\n", guessed_word);
        printf("Available letters: %s\n", available_letters);
        printf("You have guesses: %d\n", attempts);
        printf("Please guess a letter: ");
        scanf(" %c", &guess);

        bool guess_is_correct = false;
        for (int i = 0; secret[i] != '\0'; i++) 
        {
            if (secret[i] == guess) 
            {
                guess_is_correct = true;
                break;
            }
        }

        if (guess_is_correct) 
        {
            if (attempts < 8) 
            {
                continue;
            }
        }
        else
        {
            printf("Oops! That letter is not in my word\n");
            attempts--;
        }

        if (guess >= 'A' && guess <= 'Z') 
        {
            printf("You write big word.\n");
            attempts++;
        } else if (guess >= '0' && guess <= '9') {
            printf("You write number.\n");
            attempts++;
        }

        bool already_guessed = false;
        for (int i = 0; letters_guessed[i] != '\0'; i++) 
        {
            if (letters_guessed[i] == guess) 
            {
                already_guessed = true;
                break;
            }
        }

        if (!already_guessed) 
        {
            int len = 0;
            while (letters_guessed[len] != '\0') 
            {
                len++;
            }
            letters_guessed[len] = guess;
            letters_guessed[len + 1] = '\0';
            
            get_guessed_word(secret, letters_guessed, guessed_word);
        } else {
            printf("You've already guessed that letter.\n");
        }
    }

    if (is_word_guessed(secret, letters_guessed)) 
    {
        printf("Congratulations! You guessed the word: %s\n", secret);
    } else {
        printf("Sorry, you didn't guess the word. It was: %s\n", secret);
    }

}