#include <stdio.h>
#include <string.h>
int main(void) {
   char *a[] = {"Florida", "Oregon", "Califoria", "Georgia"};

   for (int i = 0; i < 4; i++) {
      for (int j = i+1; j < 4; j++)
         if (strcmp(a[i], a[j]) > 0) {
            char* temp = a[i]; 
            a[i] = a[j]; 
            a[j] = temp; 
         }
       printf("%s ", a[i]);
     }
   getchar();
   return 0;  
}