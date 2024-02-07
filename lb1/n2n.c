#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX_TEXT_SIZE 255
#define SEPARATORS " -,/.!?():;\'\""

int main()
{
    char text[MAX_TEXT_SIZE];
    char wordsOfText[MAX_TEXT_SIZE/2][MAX_TEXT_SIZE];
    do{
        printf("\nEnter text: ");
        gets(text);

        char * word = strtok(text, SEPARATORS);
        size_t amountLex = 0;

        while (word != NULL)
        {
            strcpy(wordsOfText[amountLex++], word);
            word = strtok(NULL, SEPARATORS);
        }

        char * _word;
        char repeatedChar[2];
        char lastCharRep;
        char isFindWord = 0;
        size_t lenw, row_len, amountRow;
        for (size_t i = 0; i < amountLex; ++i)
        {
            lenw = strlen(wordsOfText[i]);
            _word = wordsOfText[i];
            lastCharRep = '\0';
            for (size_t j = 0; j < lenw - 1; ++j)
            {
                repeatedChar[0] = _word[j];
                amountRow = strspn(_word + j, repeatedChar);
                if ( (amountRow > 1) && (lastCharRep != repeatedChar[0]) )
                {
                    printf("\nword : %s, ", _word);
                    printf(" reapeted char = %c, - %d times\n", repeatedChar[0], amountRow);
                    isFindWord = 1;
                }
                lastCharRep = repeatedChar[0];
            }
        }
        if (!isFindWord) puts("\nNo words with reapeting chars.");

        puts("\nEnter ESCAPE for exit.");
    } while(_getch() != 27);    
}