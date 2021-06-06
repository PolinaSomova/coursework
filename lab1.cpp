//
// лабораторная 1
//

#include "lab1.h"

lab1::lab1() {}

void lab1::startLab() {
    listSize=0;
    student *List=NULL;
    List=mainMenu (List);
    free(List);
}