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

}


