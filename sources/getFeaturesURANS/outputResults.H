//output the cell point
Info<<"Output region is:"<<endl;
Info<<"("<<Xmin<<" "<<Ymin<<" "<<Zmin<<")"<<endl;
Info<<"("<<Xmax<<" "<<Ymax<<" "<<Zmax<<")"<<endl;
FILE *out = fopen("energy.txt", "w");
pointField points = mesh.C();
if(out!=NULL)
{
    forAll(Dw, celli)
    {    
        double x = points[celli][0];
        double y = points[celli][1];
        double z = points[celli][2];
        if( x>Xmin.value() && x<Xmax.value())
        {
            if( y>Ymin.value() && y<Ymax.value())
            {
                if( z>Zmin.value() && z<Zmax.value())
                {
                    fprintf(out, "%g\t", Pk[celli]);
                    fprintf(out, "%g\t", Dk[celli]);
                    fprintf(out, "%g\t", Pw[celli]);
                    fprintf(out, "%g\n", Dw[celli]);
                }
            }
        }
    }
   fclose(out);
}


