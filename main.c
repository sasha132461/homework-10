// // strchr, strncat

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "hangman.c"

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

int main() {
    srand(time(NULL));
    char secret[21] = {0};
    char alphavit[] = "abcdefghijklmnopqrstuvwxyz";

    if (get_word(secret)) 
    {
        fprintf(stderr, "Could not get a word.\n");
        return 1;
    }

    printf("Let's start guessing the word!\n");
    printf(secret);
    char letters_guessed[27] = {0};
    char guessed_word[21] = {0};
    char available_letters[27] = {0};
    char guess;
    int attempts = 0;

    while (!is_word_guessed(secret, letters_guessed) && attempts < 10) 
    {
        printf(secret);
        printf("Current word: %s\n", guessed_word);
        get_available_letters(letters_guessed, available_letters);
        printf("Available letters: %s\n", available_letters);
        printf("Enter your guess: ");
        scanf(" %c", &guess);

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

        attempts++;
    }

    if (is_word_guessed(secret, letters_guessed)) 
    {
        printf("Congratulations! You guessed the word: %s\n", secret);
    } else {
        printf("Sorry, you didn't guess the word. It was: %s\n", secret);
    }

    return 0;
}