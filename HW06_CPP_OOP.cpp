#include <iostream>
#include <ctime>

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

int inputValue(int a);
short inputSize(std::string text);

void printMenu(string* const arr, const short& indMenu, const short& size);
short indexMenu(short& indMenu, const short& size);

void matrixRotation(const Rotation &Rotate);


int** createMatrix(const short& row, const short& col) {

    int** arr = new int* [row];
    for (short i = 0; i < row; i++)
        *(arr + i) = new int[col];

    return arr;
}

int main(void)
{
    cout << "\nStart!\n";

    short indMenu = 0;
    short exit = 0;
    string arrMenu[]{ "ROTATE 0", "ROTATE 90" , "ROTATE 180" , "ROTATE 270" , "ROTATE 360", "EXIT" };

    short sizeRow = 0, sizeCol = 0;

    sizeRow = inputSize("rows");
    sizeCol = inputSize("columns");

    int** matrixR0 = createMatrix(sizeRow, sizeCol);

    do {
        printMenu(arrMenu, indMenu, EXIT);
        exit = indexMenu(indMenu, EXIT);

    } while (static_cast<char>(exit) != '\n');

    Rotation rotation = static_cast<Rotation>(indMenu);

    matrixRotation(rotation);

    return 0;
}

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
};

void printMenu(string* const arr, const short& indMenu, const short& size) {

    cout << "\n Menu:\n";
    for (short i = 0; i <= size; i++) {
        if (indMenu == i) {
            cout << " -> " << *(arr + i) << "\n";
            continue;
        }
        cout << "    " << *(arr + i) << "\n";
    }
};

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
};

void matrixRotation(const Rotation &Rotate) {
    
    switch (Rotate)
    {
    case ROTATE0:
        cout << "\nrotation 0\n";
        break;
    case ROTATE90:
        cout << "\nrotation 90\n";
        break;
    case ROTATE180:
        cout << "\nrotation 180\n";
        break;
    case ROTATE270:
        cout << "\nrotation 270\n";
        break;
    case ROTATE360:
        cout << "\nrotation 360\n";
        break;
    case EXIT:
        cout << "\nexit\n";
        break;
    }
};