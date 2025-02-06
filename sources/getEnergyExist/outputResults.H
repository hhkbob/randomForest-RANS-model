//output the cell point
FILE *out = fopen("energy.txt", "w");

if(out!=NULL)
{
    forAll(Pk, celli)
    {    
        fprintf(out, "%g\t", Pk[celli]);
        fprintf(out, "%g\t", Dk[celli]);
        fprintf(out, "%g\t", Pw[celli]);
        fprintf(out, "%g\n", Dw[celli]);
    }
   fclose(out);
}


