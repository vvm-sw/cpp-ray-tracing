#include <iostream>
#include "src/ObjReader.cpp"

/*

Divirtam-se :)

*/

int main(){

    objReader obj("inputs/cubo.obj");

    obj.print_faces();
   
    return 0;
}