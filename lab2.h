

#ifndef COURSEWORK_LAB2_H
#define COURSEWORK_LAB2_H

#include <iostream>
#include <fstream>
#include <chrono>

typedef std :: chrono :: time_point<std :: chrono :: high_resolution_clock> timestamp;

using namespace std;


class lab2 {

public:
    lab2();
    ~lab2();
    int startLab();

private:
    struct Array {
        int * data;
        int size;
        int length;
    };

    struct List {
        int data;
        List *head;
        List *tail;
        int length;
    };


    struct Array *arr;

    int * createRandomArrSize ( struct Array * arr );
    int * createArrayWithoutSize ( struct Array * arr );
    int * createFromFile ( struct Array * arr );

    int * addElementToArray ( struct Array * arr, int element );
    int * deleteElementIndex ( struct Array * arr, int index );
    int * deleteElementValue ( struct Array * arr, int value );
    int getElement ( int * arr, int index );
    int * doubleUpArray ( struct Array * arr );
    int * doubleUpArray ( int * arr, int size );
    int * shrinkArray ( int * arr, int newSize );
    int * shiftArray ( int * arr, int size, int startIndex );
    void printArray ( struct Array * arr );

    void printMenu ();
    void chooseMenu (struct Array * arr, int menuCase );
    void printTime (timestamp, timestamp, string );
};


#endif //COURSEWORK_LAB2_H
