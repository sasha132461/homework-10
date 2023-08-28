#include <stdio.h>
#include <stdlib.h>
#include "hangman.h"


int is_word_guessed(const char secret[], const char letters_guessed[])
{
    int w;
    for (int i = 0; secret[i] != '\0'; i++) 
    {
        for(int j = 0; letters_guessed[j] != '\0'; j++) 
        {
            if (secret[j] == letters_guessed[j])
            {
                w = 1;
                break;
            }
        }
        if (!letters_guessed) 
        {
            return 1;
        }
    }
    
    return 0;
};

int main() {
    char secret[255];
    char letter_guessed[255];
    get_word(secret);
    printf("\n%s",secret);

    return 0;
}
