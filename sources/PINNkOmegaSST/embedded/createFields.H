const fvMesh& mesh = this->mesh_;
const volScalarField& p = mesh.lookupObject<const volScalarField>("p");
volTensorField gradTU=T(fvc::grad(U));
volTensorField R = nut*gradTU;
const surfaceScalarField& phi = mesh.lookupObject<const surfaceScalarField>("phi");

