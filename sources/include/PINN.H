double normalization(double up, double down)
{
    return up/max(fabs(up)+fabs(down), VSMALL);
}

//-define the cross product for second order tensor
volTensorField MycrossProduct(volTensorField a, volVectorField b)
{
    volTensorField c = a*0;
    forAll(a, celli)
    {
         c[celli].xx() = b[celli].y()*a[celli].zx()+-b[celli].z()*a[celli].yx();
         c[celli].xy() = b[celli].y()*a[celli].zy()-b[celli].z()*a[celli].yy(); 
         c[celli].xz() = b[celli].y()*a[celli].zz()-b[celli].z()*a[celli].yz();
         c[celli].yx() = -b[celli].x()*a[celli].zx()+b[celli].z()*a[celli].xx();
         c[celli].yy() = -b[celli].x()*a[celli].zy()+b[celli].z()*a[celli].xy();
         c[celli].yz() = -b[celli].x()*a[celli].zz()+b[celli].z()*a[celli].xz();
         c[celli].zx() = b[celli].x()*a[celli].yx()-b[celli].y()*a[celli].xx();
         c[celli].zy() = b[celli].x()*a[celli].yy()-b[celli].y()*a[celli].xy();
         c[celli].zz() = b[celli].x()*a[celli].yz()-b[celli].y()*a[celli].xz();
    }
    return c;
}

volTensorField normTensorField(volTensorField a, volTensorField b, volScalarField c)
{
    forAll(a, celli)
    {
        a[celli].xx() =  normalization(b[celli].xx(), c[celli]);
        a[celli].xy() =  normalization(b[celli].xy(), c[celli]);
        a[celli].xz() =  normalization(b[celli].xz(), c[celli]);

        a[celli].yx() =  normalization(b[celli].yx(), c[celli]);
        a[celli].yy() =  normalization(b[celli].yy(), c[celli]);
        a[celli].yz() =  normalization(b[celli].yz(), c[celli]);
        
        a[celli].zx() =  normalization(b[celli].zx(), c[celli]);
        a[celli].zy() =  normalization(b[celli].zy(), c[celli]);
        a[celli].zz() =  normalization(b[celli].zz(), c[celli]);
    }
    return a;
}