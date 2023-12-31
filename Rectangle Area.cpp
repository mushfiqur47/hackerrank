#include <iostream>

using namespace std;
/*
 * Create classes Rectangle and RectangleArea
 */
 class Rectangle {
public:
    virtual void display() const {
        cout << width << ' ' << height << endl;
    }