#include <iostream>
#include "src/ObjReader.cpp"
#include "src/Vector.cpp"
#include "src/Point.cpp"

/*

Divirtam-se :)

*/

int main(){

    //objReader obj("inputs/cubo.obj");

    //obj.print_faces();

    // Teste Basico classe vetor
    vetor v(1,1,1);
    v.multByScalarV2(2);
    v.print();

    return 0;
}
