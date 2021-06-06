//
// лабораторная 2
//

#include "lab2.h"



lab2::lab2() {
    arr = new Array();
}

lab2::~lab2() {
    delete[] arr;
}

int lab2::startLab() {
    int menuCase;

    while (true) {

        printMenu();

        cin >> menuCase;

        cout << "\n";

        switch (menuCase) {
            case 7:
                return 0;
                break;
            default:
                chooseMenu(arr, menuCase);
                break;
        }

    }
}

void lab2::printMenu () {

    cout << "---Массив---:\n"
         << "1 - Создать массив автоматически\n"
         << "2 - Создать массив с клавиатуры\n"
         << "3 - Создать массив с файла\n"
         << "4 - Добавить элемеент в массив\n"
         << "5 - Удалить элемент из массива\n"
         << "6 - Получить элемент из массива\n\n"
         // << "===Double Linked List===\n"
         //  << "7 - Create double linked list automaticly\n"
         // << "8 - Create double linked list from input\n"
         //  << "9 - Create double linked list from file\n"
         // << "10 - Add element to list\n"
         // << "11 - Delete element from list\n"
         // << "12 - Get element from list\n"
         << "7 - Выход\n"
         << "Введите пункт: ";
}

void lab2::chooseMenu ( struct Array * arr, int menuCase ) {

    switch (menuCase) {

        case 1: {
            cout << "Введите размер массива: ";
            cin >> arr->size;
            arr->length = arr->size - 1;
            arr->data = createRandomArrSize(arr);
            cout << "Массив создан: ";
            printArray(arr);
            break;
        }
        case 2: {
            std::cout << "Введите элементы массива: \n";
            arr->data = createArrayWithoutSize(arr);
            cout << "Массив создан: ";
            printArray(arr);
            break;
        }
        case 3: {
            arr->data = createFromFile(arr);
            cout << "Массив создан: ";
            printArray(arr);
            break;
        }
        case 4: {
            int newEl;
            cout << "Введите элемент для добавления в массив: ";
            cin >> newEl;
            arr->data = addElementToArray(arr, newEl);
            printArray(arr);
            break;
        }
        case 5: {
            int toDelete, type;
            cout << "Выберите вариант: 1 - по индексу; 2 - по значению\n";
            cin >> type;
            switch (type) {
                case 1:
                    cout << "Введите индекс для удаления: ";
                    cin >> toDelete;
                    arr->data = deleteElementIndex(arr, toDelete);
                    break;
                case 2:
                    cout << "Введите значение для удаления: ";
                    cin >> toDelete;
                    arr->data = deleteElementValue(arr, toDelete);
                    break;
            }
            printArray(arr);
            break;
        }
        case 6: {
            int index;
            cout << "Введите индекс для получения: ";
            cin >> index;
            cout << "Индекс значения: " << getElement(arr->data, index) << "\n";
            break;
        }
    }
}

/*
 * Array
 */
int * lab2::createRandomArrSize ( struct Array * arr ) {

    int * newArr = new int[arr->size];

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    for ( int i = 0; i < arr->size; i++ ) {
        newArr[i] = rand() % 100;
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "Array created: ");

    return newArr;

}

int * lab2::createArrayWithoutSize ( struct Array * arr ) {

    int size = 2;
    int * newArr = new int[size];
    int num, index = 0;
    bool end = false;

    arr->length = size - 1;
    arr->size = size;

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    while ( !end ) {

        cout << "Введите " << index << " элемент ( или -1, чтобы прекратить ввод ): ";

        cin >> num;

        if ( num == -1 ) {
            end = true;
            break;
        } else if ( index < size ) {
            newArr[index] = num;
            index++;
        } else {
            index = size;
            int * temp = newArr;
            newArr = doubleUpArray(temp, size);
            newArr[index] = num;
            size = size * 2;
            index++;
        }

    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "Array created ");

    arr->length = index - 1;

    return newArr;

}

int * lab2::createFromFile ( struct Array * arr ) {

    ifstream file;
    int index = 0, size = 2;
    int * newArr = new int[size];

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    file.open("array.txt");

    if ( file.is_open() ) {

        string line;

        while ( getline(file, line) ) {

            int num = stoi(line);

            if (index < size) {
                newArr[index] = num;
                index++;
            } else {
                index = size;
                int* temp = newArr;
                newArr = doubleUpArray(temp, size);
                newArr[index] = num;
                size = size * 2;
                index++;
            }

        }

    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "Array creation ");

    arr->length = index - 1;

    return newArr;

}


int * lab2::addElementToArray ( struct Array * arr, int element ) {

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    if ( arr->length < arr->size ) {
        arr->length++;
        arr->data[arr->length] = element;

        endTime = std :: chrono :: high_resolution_clock :: now();
        printTime(startTime, endTime, "Добавлен элемент  ");

        return arr->data;
    } else {
        int * newArr = doubleUpArray(arr);
        arr->length++;
        newArr[arr->length] = element;

        endTime = std :: chrono :: high_resolution_clock :: now();
        printTime(startTime, endTime, "Добавлен элемент ");

        return newArr;
    }
}


int * lab2::deleteElementIndex ( struct Array * arr, int index ) {

    if ( arr->length == -1 ) {
        cout << "Массив пустой\n";
        return arr->data;
    }

    if ( index == arr->length ) {
        arr->length--;
        arr->size = arr->length;
        return shrinkArray(arr->data, arr->length);
    } else {
        arr->length--;
        arr->size = arr->length;
        return shiftArray(arr->data, arr->length, index);
    }

}

int * lab2::deleteElementValue ( struct Array * arr, int value ) {

    int index;

    for (int i = 0; i < arr->length; i++) {
        if ( arr->data[i] == value ) {
            return deleteElementIndex(arr, i);
        }
    }

    cout << "Значение удалено\n";

    return arr->data;

}

int lab2::getElement ( int * arr, int index ) {

    cout << "Элемент был получен за 0 ms: ";

    return arr[index];

}


//доп к массивам

int * lab2::doubleUpArray ( struct Array * arr ) {

    int newSize = arr->size * 2;
    int * newArr = new int[newSize];

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    for ( int i = 0; i <= arr->length; i++ ) {
        newArr[i] = arr->data[i];
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "");

    arr->size = newSize;

    return newArr;

}

int * lab2::doubleUpArray ( int * arr, int size ) {

    int newSize = size * 2;
    int * newArr = new int[newSize];

    timestamp startTime, endTime;
    startTime = std :: chrono :: high_resolution_clock :: now();

    for ( int i = 0; i <= size; i++ ) {
        newArr[i] = arr[i];
    }

    endTime = std :: chrono :: high_resolution_clock :: now();
    printTime(startTime, endTime, "");

    return newArr;

}

int * lab2::shrinkArray ( int * arr, int newSize ) {

    int * newArr = new int[newSize + 1];

    for ( int i = 0; i < newSize + 1; i++ ) {
        newArr[i] = arr[i];
    }

    return newArr;

}

int * lab2::shiftArray ( int * arr, int size, int startIndex ) {

    int * newArr = new int[size];

    for ( int i = 0; i < startIndex; i++ ) {
        newArr[i] = arr[i];
    }

    for ( int i = startIndex; i < size + 1; i++ ) {
        newArr[i] = arr[i + 1];
    }

    return newArr;

}

void lab2::printArray ( struct Array * arr ) {

    for ( int i = 0; i <= arr->length; i++ ) {
        cout << arr->data[i] << " ";
    }

    cout << "\n\n";
}

void lab2::printTime ( timestamp startTime, timestamp endTime, string type ) {

    cout << type << "ended in: "
         << std :: chrono :: duration_cast <std :: chrono :: microseconds> (endTime - startTime).count()
         << " microseconds\n";

}


