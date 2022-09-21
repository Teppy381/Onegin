#include "functions.h"


char* ReadFile(FILE* text_input, int* p_simbol_amount)
{
    fseek(text_input, 0, SEEK_END);
    *p_simbol_amount = ftell(text_input);
    int simbol_amount = *p_simbol_amount;
    fseek(text_input, 0, SEEK_SET);

    char* buffer = (char*) calloc(simbol_amount + 1, sizeof(*buffer));
    assert (buffer != NULL);

    fread(buffer, sizeof(*buffer), simbol_amount, text_input);
    buffer[simbol_amount - 1] == '\0';

    return buffer;
}


int SplitToLines(char** indexPtr, char* buffer, int simbol_amount)
{
    int simbol_num = 0;
    int line_num = 1;

    while(simbol_num <= simbol_amount)
    {
        if (buffer[simbol_num] == '\n')
        {
            buffer[simbol_num] = '\0';
            simbol_num++;
            while (buffer[simbol_num] == ' ' || buffer[simbol_num] == '\n')
            {
                simbol_num++;
            }
            indexPtr[line_num] = &(buffer[simbol_num]);
            line_num++;
        }
        simbol_num++;
    }
    return line_num;
}


void OutputResult(const char* file_name, char** indexPtr, int line_amount)
{
    FILE* result_file = fopen(file_name, "w");

    for (int i = 0; i < line_amount; i++)
    {
        fprintf(result_file,"%s\n", indexPtr[i]);
    }

    printf("\nResults are recorded in a file \"%s\"\n\n", file_name);
}


int CompareForward(const void* aPtr, const void* bPtr)
{
    const char* a = *(const char**) aPtr;
    const char* b = *(const char**) bPtr;
    return StrokeComparator(a, b, 0);
}


int CompareReverse(const void* aPtr, const void* bPtr)
{
    const char* a = *(const char**) aPtr;
    const char* b = *(const char**) bPtr;
    return StrokeComparator(a, b, 1);
}


int StrokeComparator(const char* str1, const char* str2, int mode)
{
    if (str1 == NULL || str2 == NULL)
    {
        return 0;
    }
    int i1 = 0;
    int i2 = 0;

    if (mode)
    {
        i1 = strlen(str1) - 1;
        i2 = strlen(str2) - 1;
    }

    while (!((str1[i1] == '\0') && (str2[i2] == '\0')))
    {
        while (ispunct(str1[i1]))
        {
            if (mode)
                i1--;
            else
                i1++;
        }

        while (ispunct(str2[i2]))
        {
            if (mode)
                i2--;
            else
                i2++;
        }

        if (str1[i1] != str2[i2])
        {
            return(((int) str1[i1]) - ((int) str2[i2]));
        }

        if (mode)
        {
            i1--;
            i2--;
        }
        else
        {
            i1++;
            i2++;
        }
    }
    return 0;
}
