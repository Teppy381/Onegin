#include "functions.h"

int main()
{
    int sort_mode = 0;
    printf("\nEnter sort mode (0 = forward, 1 = reverse): ");
    scanf("%i", &sort_mode);

    FILE* text_input = fopen("hamlet.txt", "r");
    int simbol_amount = 0;


    char* buffer = ReadFile(text_input, &simbol_amount);


    char** indexPtr = (char**) calloc(simbol_amount, sizeof(char*));
    indexPtr[0] = &(buffer[0]);

    int line_amount = SplitToLines(indexPtr, buffer, simbol_amount);


    if (sort_mode == 0)
    {
    qsort(&indexPtr[0], line_amount, sizeof(char**), &CompareForward);
    printf("\nSort mode = forward");
    }
    else
    {
    qsort(&indexPtr[0], line_amount, sizeof(char**), &CompareReverse);
    printf("\nSort mode = reverse");
    }

    OutputResult("Result.txt", indexPtr, line_amount);


    free(buffer);
    free(indexPtr);
    fclose(text_input);

    return 0;
}
