#include <stdio.h>                                                                                                                                                                                                                            
#include <stdlib.h>                                                                                                                                                                                                                           
#include <string.h>                                                                                                                                                                                                                           

//#include "mylib.h"                                                                                                                                                                                                                          

char** strtok_multi(char* src, char* delimiter, int* num_strings)
{
  register int i = 0;
  register int j = 0;
  int len = 0;
  int num_str = 0;
  char** str_array = NULL;
  char* ptr = NULL;
  char* buf = NULL;

  len = strlen(src);

  // make a copy of the src string                                                                                                                                                                                                          
  buf = strdup(src);
  if (!buf) return NULL;

  // count occurences of delimiter, plus the final string if necessary                                                                                                                                                                      
  for (i = 0; i < len; i++) {
    if (strchr(delimiter, buf[i])) {
      num_str++;
    }
    if (i + 1 == len) {
      num_str++;
    }
  }
  //    num_str++;                                                                                                                                                                                                                              

      // make an array of strings                                                                                                                                                                                                               
  str_array = (char**)malloc((num_str + 1) * (sizeof(char*)));
  if (!str_array) { free(buf); return NULL; }

  // null terminate the str_array for good measure                                                                                                                                                                                          
  str_array[num_str] = NULL;

  if (num_str == 0) {

    // for an empty string, there will be no entries in the array,                                                                                                                                                                        
    // so when we go to clean up in mie_strtok_free, there will                                                                                                                                                                           
    // be no reference to buf (which was malloced), so we need to                                                                                                                                                                         
    // free it here.                                                                                                                                                                                                                      
    free(buf);

  }
  else {
    ptr = buf;
    for (i = 0; i < len; i++) {
      if (strchr(delimiter, buf[i])) {
        buf[i] = 0; // null terminate every string                                                                                                                                                                                    
        str_array[j] = ptr;
        j++;
        ptr = buf + i + 1;
      }

      if (i + 1 == len) {
        str_array[j++] = ptr;
      }
    }
  }

  if (num_strings) *num_strings = num_str;

  return str_array;
}

int main(int argc, char* argv[])
{
  char* withoutDelim = "HelloThereWorld";
  char* withDelim = "Hello,There,World";
  char** tmp = NULL;
  int num = 0, x = 0;

  tmp = strtok_multi(withoutDelim, ",:", &num);
  printf("\nFound %d str sections\n", num);
  for (x = 0; x < num; x++) {
    printf("Section %d: %s\n", num, tmp[x]);
  }
  free(tmp);
  tmp = strtok_multi(withDelim, ",:", &num);
  printf("\nFound %d str sections\n", num);
  for (x = 0; x < num; x++) {
    printf("Section %d: %s\n", num, tmp[x]);
  }
  free(tmp);
}

