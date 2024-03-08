/* hanoinorec.c 
la quantitat de moviments per a moure n discs és (2**n)-1
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
   int n, i, j, aux;
   char o, f, *ori, *fin;  

   scanf("%d", &n);
   if (n < 1) exit(1);   
   
   aux = pow(2, n);
   ori = (char *)malloc(aux*sizeof(char));
   fin = (char *)malloc(aux*sizeof(char));
   if (ori == NULL || fin == NULL) {
      printf("problemes de memoria \n");
      exit(2);
   }
   /* per comoditat, no s'usen les components 0 */
   
   /* cas d'un sol disc */
   ori[1] = 'A';
   fin[1] = 'C';

   for (i=2; i<=n; i++) {   /* cas de i discs, suposant fel el cas de i-1 discs */
      aux = pow(2, i-1);
      
      /* del cas i-1: intercanviem B <-> C */
      for (j=1; j<aux; j++) {
         switch (ori[j]) {
            case 'A': o = 'A'; break;
            case 'B': o = 'C'; break;
            case 'C': o = 'B'; break;
            default: break;
         }
         switch (fin[j]) {
            case 'A': f = 'A'; break;
            case 'B': f = 'C'; break;
            case 'C': f = 'B'; break;
            default: break;
         }
         ori[j] = o;
         fin[j] = f;
      }

      /* posem el moviment central */
      ori[aux] = 'A';
      fin[aux] = 'C';
      
      /* del cas i-1: fem l'última part */
      for (j=1; j<aux; j++) {
         switch (ori[j]) {
            case 'A': o = 'B'; break;
            case 'B': o = 'C'; break;
            case 'C': o = 'A'; break;
            default: break;
         }
         switch (fin[j]) {
            case 'A': f = 'B'; break;
            case 'B': f = 'C'; break;
            case 'C': f = 'A'; break;
            default: break;
         }
         ori[j+aux] = o;
         fin[j+aux] = f;
      }

   }

   /* escriptura dels resultats */
   aux = pow(2, n);
   for (j=1; j<aux; j++) 
      printf("moure el disc superior de %c cap a %c\n", ori[j], fin[j]);
   
   free(ori);
   free(fin);

   return 0;
}
