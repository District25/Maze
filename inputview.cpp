#include "inputview.h"
#include <iostream>

using namespace std;

InputView::InputView() {}

char InputView::readInput()
{
    char car;
    cout << "Type 's' to start and 'q'";
    cin >> car;
    return car;
}
