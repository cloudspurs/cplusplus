#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

void abssort(float* l, unsigned n) {
    sort(l, l+n, [](float x, float y) { return abs(x) < abs(y); });
}

int main() {
    //float abs[] = { 0, 3, 4.5, 100.1, -4.5, -2.3 };
    //abssort(abs, 6); 
    // print sorted abs
    
    cout << [](float f) { return abs(f); } (-3.5) << endl;
    cout << [](float f) -> int { return abs(f); } (-3.5) << endl;

    auto lambda = []() { return "auto lambda"; };
    cout << lambda() << endl;

    function<string()> lambda1 = []() { return "function lambda"; };
    cout << lambda1() << endl;

    float a = 1.0;
    cout << [=](float x) { return a + abs(x); } (-3.5) << '\t' << a << endl;
    cout << [a](float x) { return a + abs(x); } (-3.5) << '\t' << a << endl;

    float b = 1.0;
    cout << [&](float x) { return b += abs(x); } (-3.5) << '\t' << b << endl;
    cout << b << endl;

    float c = 1.0;
    cout << [=](float x) mutable { return c += abs(x); } (-3.5) << '\t' << c << endl;
    cout << c << endl;

    float d = 1.0;
    float e = 10.0;
    cout << [=, &d](float x) { return d += e + abs(x); } (-3.5) << '\t' << d << '\t' << e << endl;
    cout << d << '\t' << e << endl;
}

