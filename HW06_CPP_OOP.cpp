#include <iostream>
#include <ctime>

using std::cout;
using std::cin;
using std::string;

void printMenu(string* const arr, const short& indMenu, const short& size);

short indexMenu(short& indMenu, const short& size);

enum Rotation {
    ROTATE0,
    ROTATE90,
    ROTATE180,
    ROTATE270,
    ROTATE360,
    EXIT
};

int main(void)
{
    cout << "\nStart!\n";

    short indMenu = 0;
    short exit = 0;
    string arrMenu[]{ "ROTATE 0", "ROTATE 90" , "ROTATE 180" , "ROTATE 270" , "ROTATE 360", "EXIT" };

    do {
        printMenu(arrMenu, indMenu, EXIT);
        exit = indexMenu(indMenu, EXIT);

    } while (static_cast<char>(exit) != '\n');

    Rotation rotation = static_cast<Rotation>(indMenu);

    switch (rotation)
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

    return 0;
}

void printMenu(string* const arr, const short& indMenu, const short& size) {

    cout << "\n Menu:\n";
    for (short i = 0; i <= size; i++) {
        if (indMenu == i) {
            cout << " w|s" << *(arr + i) << "\n";
            continue;
        }
        cout << "    " << *(arr + i) << "\n";
    }
};

short indexMenu(short& indMenu, const short& size) {

    short indMin = 0;
    char direct = ' ';

    cout << " -> ";
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