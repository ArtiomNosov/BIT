//пример использования функции strtok
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int isHave(char ch, const char* str)
{
        for (size_t i = 0; ch != '\0'; i++)
                if (str[i] == ch)
                        return 1;
        return 0;
}
size_t strlen(const char* str)
{
        if (str == NULL)
                return 0;
        size_t res = 0;
        for (size_t i = 0; str[i] != '\0'; i++)
                res++;
        return res;  
}
void fill(char* string, const char* dest, char* source)
{
        size_t len = strlen(string);
        // printf("Hello2!\n");
        // printf("%d\n", len);
        for (size_t i = 0; i < len; i++) {
                // printf("Hello2!\n");
                if (isHave(string[i], dest)) {
                        // printf("%d\n", len);
                        string[i] = '\0';
                }
        }
}
char* strtok(char* _String, const char* _Delimeter)
{
        static size_t len;
        static char* string;
        static size_t position;
        if (_String) {
                len = strlen(_String);
                position = 0;
                fill(_String, _Delimeter, '\0');
                string = _String;
                // printf("%s", string);
                return string;
        }
        while(string[0] != '\0' && position < len) {
                position++;
                string++;
        }
        while (string[0] == '\0' && position < len) {
                position++;
                string++;
        }
        if (position == len)
                return NULL;
        else 
                return string;
}
int main ()
{
  char* str = calloc(10, 1);
  str[0] = 'a';
  str[1] = 'a';
  str[2] = 'a';
  str[3] = ' ';
  str[4] = 'a';
  str[5] = 'a';
  str[6] = 'a';
  str[7] = 'a';
  str[8] = 'a';
  char* str2 = calloc(10, 1);
  str2[0] = 'b';
  str2[1] = 'b';
  str2[2] = 'b';
  str2[3] = ' ';
  str2[4] = 'b';
  str2[5] = 'b';
  str2[6] = 'b';
  str2[7] = 'b';
  str2[8] = 'b';
 

  char * pch = strtok (str," \ta"); // во втором параметре указаны разделитель (пробел, запятая, точка, тире)
 
  while (pch != NULL) {
      printf("%s\n", pch);
      pch = strtok (NULL, " \ta");
  }

  pch = strtok (str2," "); // во втором параметре указаны разделитель (пробел, запятая, точка, тире)
 
  while (pch != NULL) {
      printf("%s\n", pch);
      pch = strtok (NULL, " ");
  }
  return 0;
}

public class UserValidator {
  private Cryptographer cryptographer;
  public boolean checkPassword(String userName, String password) 
{
    User user = UserGateway.findByName(userName); 
    if (user != User.NULL) {
      String codedPhrase = user.getPhraseEncodedByPassword(); 
      String phrase = cryptographer.decrypt(codedPhrase, password); 
      if ("Valid Password".equals(phrase)) {
        Session.initialize(); 
        return true;
      } 
    }
    return false; 
  }
}