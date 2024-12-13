#include <iostream>
#include "src/ObjReader.cpp"

/*

Divirtam-se :)

*/

int main(){

    colormap cmap("inputs/cubo.mtl");
    objReader obj("inputs/cubo.obj", cmap);

    obj.print_faces();
   
    return 0;
}