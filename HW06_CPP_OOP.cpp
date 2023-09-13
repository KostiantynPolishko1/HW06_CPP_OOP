#include <iostream>

using std::cout;
using std::cin;
using std::string;

const short	MIN_SIZE = 2;
const short	MAX_SIZE = 10;

enum Rotation {
    ROTATE0,
    ROTATE90,
    ROTATE180,
    ROTATE270,
    ROTATE360,
    EXIT
};

enum Direction {
    CLOCKWISE,
    COUNTERCLOCKWISE,
    OUT
};

int inputValue(int a);
short inputSize(std::string text);

void printMenu(string* const arr, const short& indMenu, const short& size);
short indexMenu(short& indMenu, const short& size);

int** createMatrix(const short& row, const short& col);
void fillMatrix(int** const arr, const short& row, const short& col);
void printMatrix(int** const arr, const short& row, const short& col, const std::string rotation);
void clearMatrix(int** arr, const short& row);

void rotateMatrix(int** const arr, short row, short col, const Rotation& Rotate);

void matrixRotation(Rotation Rotate, const Direction& Direct, int** const arr, const short &row, const short &col);

int main(void)
{
    cout << "\nStart!\n";

    short indMenu = 0;
    short indDirect = 0;
    short exit = 0;
    short sizeRow = 0, sizeCol = 0;

    string arrMenu[] { "ROTATE 0", "ROTATE 90" , "ROTATE 180" , "ROTATE 270" , "ROTATE 360", "EXIT" };
    string arrDirect[]{ "CLOCKWISE", "COUNTERCLOCKWISE", "EXIT" };

    sizeRow = inputSize("rows");
    sizeCol = inputSize("columns");

    int** arrMatrix = createMatrix(sizeRow, sizeCol);
    fillMatrix(arrMatrix, sizeRow, sizeCol);

    //menu of rotation (0, 90, 180, 270, 360)
    do {
        printMatrix(arrMatrix, sizeRow, sizeCol, " ");
        printMenu(arrMenu, indMenu, EXIT);

        exit = indexMenu(indMenu, EXIT);

    } while (static_cast<char>(exit) != '\n');

    printMatrix(arrMatrix, sizeRow, sizeCol, " ");

    Rotation rotation = static_cast<Rotation>(indMenu);

    switch (rotation)
    {
    case ROTATE0:
    case ROTATE360:
        printMatrix(arrMatrix, sizeRow, sizeCol, " ");
        return 0;
    case ROTATE90:
    case ROTATE270:
        //menu of direction (clockwise or counterclockwise)
        do {
            printMatrix(arrMatrix, sizeRow, sizeCol, " ");
            printMenu(arrDirect, indDirect, OUT);

            exit = indexMenu(indDirect, OUT);

        } while (static_cast<char>(exit) != '\n');

        printMatrix(arrMatrix, sizeRow, sizeCol, " ");
    }

    Direction direct = static_cast<Direction>(indDirect);

    matrixRotation(rotation, direct, arrMatrix, sizeRow, sizeCol);
    clearMatrix(arrMatrix, sizeRow);

    return 0;
}
;

//======================functions======================

int inputValue(int a)
{
    while (true)
    {
        cout << "\tenter -> ";
        cin >> a;
        if (cin.peek() != '\n')
        {
            cout << "\t\tINPUT ERROR!\n";
            cin.clear();
            cin.ignore(32767, '\n');
            continue;
        }

        cin.ignore(32767, '\n');
        system("CLS");

        return abs(a);
    }
}
;
short inputSize(std::string text) {

    while (true)
    {
        short size = 0;

        cout << "\n\tnumber of " + text + " (" << MIN_SIZE << "..." << MAX_SIZE << ")\n";
        size = inputValue(size);
        if (size <= MAX_SIZE && size >= MIN_SIZE)
            return size;

        system("CLS");
        cout << "\tOUT of RANGE. ERROR!\n";
    };
}
;
int** createMatrix(const short& row, const short& col) {

    int** arr = new int* [row];
    for (short i = 0; i < row; i++)
        *(arr + i) = new int[col];

    return arr;
}
;
void fillMatrix(int** const arr, const short& row, const short& col) {

    int count = 0;
    for (int** iter = arr; iter != arr + row; iter++)
        for (int* jter = *iter; jter != *iter + col; jter++)
            *jter = ++count;
}
;
void printMatrix(int** const arr, const short& row, const short& col, const std::string rotation) {

    cout << "\n\tmatrix " << row << " x " << col << "\n\n";

    for (int** iter = arr; iter != arr + row; iter++) {
        cout << "\t";
        for (int* jter = *iter; jter != *iter + col; jter++)
            cout << *jter << ( *jter < 10 ? "  " : " ");
        cout << "\n";
    }
}
;
void clearMatrix(int** arr, const short& row) {

    for (int** iter = arr; iter != arr + row; iter++) {
        delete[] * iter;
        *iter = nullptr;
    }
    delete[] arr;
    arr = nullptr;
}
;
void rotateMatrix(int** const arr, short row, short col, const Rotation& Rotate) {

    switch (Rotate) 
    {
    case ROTATE90:
    case ROTATE270:
        std::swap(row, col);
        break;
    }

    int** matrixR = createMatrix(row, col);

    for (int** iterR = matrixR, **iter0 = arr, i = 0; iterR != matrixR + row; iterR++, i++)
    {
        for (int* jterR = *iterR, *jter0 = *iter0, j = 0; jterR != *iterR + col; jterR++, j++) {
            switch (Rotate) {
            case ROTATE90:
                *jterR = *(*(arr + ((col - 1) - j)) + i);
                break;
            case ROTATE180:
                *jterR = *(*(arr + ((row - 1) - i)) + ((col - 1) - j));
                break;
             case ROTATE270:
                 *jterR = *(*(arr + j) + ((row - 1) - i));
                break;
             }
        }
    }

    printMatrix(matrixR, row, col, " ");
    clearMatrix(matrixR, row);
}
;
short indexMenu(short& indMenu, const short& size) {

    short indMin = 0;
    char direct = ' ';

    cout << " w|s ";
    direct = cin.get();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    system("CLS");

    while (true) {

        if (direct == '\n')
            return static_cast<int>(direct);
        else if (direct == 'w' || direct == 'W')
            indMenu++;
        else if (direct == 's' || direct == 'S')
            indMenu--;
        else
        {
            cout << "\n\tERROR!";
            cout << "\n\t\"w\" - Down, \"s\" - Up: -> ";
        }

        //reload index menu
        if (indMenu < indMin)
            indMenu = size;
        else if (indMenu > size)
            indMenu = indMin;

        return indMenu;
    }
}
;
void printMenu(string* const arr, const short& indMenu, const short& size) {

    cout << "\n Menu:\n";
    for (short i = 0; i <= size; i++) {
        if (indMenu == i) {
            cout << " -> " << *(arr + i) << "\n";
            continue;
        }
        cout << "    " << *(arr + i) << "\n";
    }
}
;
void matrixRotation(Rotation Rotate, const Direction &Direct, int** const arr, const short &row, const short &col) {
    
    if (static_cast<int>(Direct) == 1) {
        int x = static_cast<int>(Rotate);
        int y = ROTATE270;

        if (x < y)
            std::swap(x, y);
        else {
            y = ROTATE90;
            std::swap(x, y);
        }

        Rotate = static_cast<Rotation>(x);
    }
   
    switch (Rotate)
    {
    case ROTATE0:
    case ROTATE360:
        rotateMatrix(arr, row, col, ROTATE0);
        break;
    case ROTATE90:
        rotateMatrix(arr, row, col, ROTATE90);
        break;
    case ROTATE180:
        rotateMatrix(arr, row, col, ROTATE180);
        break;
    case ROTATE270:
        rotateMatrix(arr, row, col, ROTATE270);
        break;
    case EXIT:
        cout << "\nEXIT!\n";
        break;
    }
}
;