#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double v[101][2];

int main( )
{

   FILE *b, *cx, *cy;
   cx = fopen("../0/Cx", "r");
   cy = fopen("../0/Cy", "r");
   b = fopen("../0/omegaDict","w");
   #include "omega.h"
   //  write the file title.
   int cell = 40;
   int cell2 = 0;
   char buffer[81];
   char keyWord;
   double *x=NULL, *y=NULL;
   double vel;
   while( !feof(cx) || !feof(cy))
   {
      fscanf(cx, "%s", buffer);
      fscanf(cy, "%s", buffer);
      if(!(strcmp("IN",buffer)))
      {
          fgets( buffer, 81, cx );
          fgets( buffer, 81, cx );
          fgets( buffer, 81, cx );
          fgets( buffer, 81, cx );
          
          fgets( buffer, 81, cy );
          fgets( buffer, 81, cy );
          fgets( buffer, 81, cy );
          fgets( buffer, 81, cy );

          fscanf( cx, "%d", &cell );
          fscanf( cy, "%d", &cell2 );
          x = new double[cell];
          y = new double[cell];

          fgets( buffer, 81, cx );
          fgets( buffer, 81, cx );
          fgets( buffer, 81, cy );
          fgets( buffer, 81, cy );
          
          for( int i=0; i<cell; i++ )
          {
              fscanf(cx,"%lf",&x[i]);
              fscanf(cy,"%lf",&y[i]);
          }
          break;
      }
   }
   // calculate the velocity in the inlet
   double r ;
   fprintf(b, "IN\n{\n\n");
   fprintf(b, "    type        fixedValue;\n");
   fprintf(b, "    value    nonuniform List<scalar>\n");
   fprintf(b, "(\n");
   for( int i=0; i<cell; i++ )
   {
       r=sqrt(x[i]*x[i]+y[i]*y[i]);       
       for (int k=1; k<101; k++)
       {
	   if (r>v[k-1][0] && r<v[k][0] && k<=101)
	   {
		vel = (v[k][1] - v[k-1][1]) / (v[k][0] - v[k-1][0])*(r - v[k][0]) + v[k][1]; k=105;
	   }
	   else if (fabs(r-0.02)<1e-5) { vel=0; k=105;}
       }
       fprintf(b, "%lf\n", vel );
       printf("%lf %lf %lf  %lf\n", r, x[i], y[i], vel);
   }
   fprintf(b, ");\n");
   fprintf(b, "}\n");
   fclose(cx); fclose(cy); fclose( b );
   if( x!=NULL )  delete x;
   if( y!=NULL )  delete y;
   return 0;
}
