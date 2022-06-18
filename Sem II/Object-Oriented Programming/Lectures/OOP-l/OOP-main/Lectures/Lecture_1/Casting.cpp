void casting_demo() {
    int x{5};
    unsigned int y = 0;    // can store only number from 0 to 4,294,967,295
    double t = 4.5;
    auto z = 3.4;        // the type of the variable that is being declared will be automatically deduced from its initializer

    x = 4.3;    // warning
    x = 7.9;    // warning
    x = -2;

    y = -3;

    t = x;

    bool flag = false;
    flag = 8;

    // C-style cast
    x = (int) 4.4; // no warning

    // only C++
    x = static_cast<int>(4.4);    // no warning
    flag = static_cast<bool>(0);

    double a = 3 / 2; // 3 and 2 are integers => division performed on integers => a will contain 1
    a = (double) 3 / 2;  // a will contain 1.5
}

//int main() {
//    casting_demo();
//    return 0;
//}