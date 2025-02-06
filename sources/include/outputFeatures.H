
FILE *data = fopen("inputFeatures.txt", "w");
volScalarField q12 = OMEGA/STRAIN;
if(data!=NULL)
{
    forAll(U, celli)
    {
        for(int i = 0; i<inputFeaturesSize; i++)
        {
            fprintf(data, "%g\t", inputFeatures[i][celli]);
        }
        fprintf(data, "%g\t", mut[celli]);
        fprintf(data, "%g", q12[celli]);
        fprintf(data, "\n");
    }
    fclose(data);
}