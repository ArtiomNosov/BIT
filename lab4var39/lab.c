#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int isHave(const char* string, int ch)
{
        if (string == NULL)
                return 0;
        size_t lenght = strlen(string);
        for (size_t i = 0; i < lenght; i++)
                if (string[i] == ch)
                        return 1;
        return 0;
}
size_t getCountSentenceSeparator(const char* string, const char* sentenceSeparator[], size_t NsentenceSeparator)
{
        if (string == NULL || sentenceSeparator == NULL || NsentenceSeparator == 0)
                return 0;
        size_t result = 0;
        size_t intermediateResult = 0;
        unsigned char isEqual = 1;
        for (size_t i = 0; i < NsentenceSeparator; i++) {
                size_t separatorLenght = strlen(sentenceSeparator[i]);
                size_t stringLenght = strlen(string);
                intermediateResult = 0;
                for (size_t j = 0; j < stringLenght - separatorLenght + 1; j++) {
                        isEqual = 1;
                        for (size_t k = 0; k < separatorLenght; k++) {
                                isEqual &= string[j + k] == sentenceSeparator[i][k];
                        }
                        intermediateResult += isEqual;
                }
                if (i == 1) {
                        result += intermediateResult - result * 3;
                } else {
                        result += intermediateResult;
                }
        }
        return result;
}
char* getResult(const char* string, const char* sentenceSeparator[], size_t NsentenceSeparator)
{
        if (string == NULL || sentenceSeparator == NULL || NsentenceSeparator == 0)
                return NULL;
        size_t countSentenceSeparator = getCountSentenceSeparator(string, sentenceSeparator, NsentenceSeparator);
        size_t stringLenght = strlen(string);
        char* result = calloc(stringLenght + countSentenceSeparator, sizeof(char));
        // 0 - начало предложения 
        // 1 - внутри 
        // 2 - на разделителе 
        // 3 - сразу после разделителя
        unsigned char state = 0; 
        for (size_t u = 0, i = 0; i < stringLenght; i++, u++) {
                if (isHave(".!?", string[i])) {
                        state = 1;
                } else if (state == 1) {
                        result[u] = '\n';
                        u++;
                        state = 0;
                        i++;
                        result[u] = toupper(string[i]);
                        continue;
                }
                result[u] = string[i];
        }
        return result;
}
int main()
{
        const char* sentenceSeparator[] = {"...", ".", "!", "?"};
        const char* data = "It is well I drew the curtain. thought I and I wished fervently he might not discover! my hiding-place: nor would John Reed have found it out himself!!! he was not quick either of vision or conception? but Eliza just put her head in at the door, and said at once She is in the window-seat, to be sure, Jack!";
        printf("data:\n%s", data); 
        char* result = getResult(data, sentenceSeparator, 4);
        printf("\nresult:\n%s", result);
        free(result);
        return 0;
}