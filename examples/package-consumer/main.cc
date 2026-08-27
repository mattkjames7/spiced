#include <cmath>
#include <iostream>

#include <spiced.h>

int main() {
    initModels();

    float mlt[1] = {12.0f};
    float radius[1] = {3.0f};
    float out[1] = {NAN};

    getAvProb(1, mlt, radius, true, false, true, 1, 3, out);

    if (std::isnan(out[0])) {
        std::cerr << "spiced returned NaN for a valid sample input" << std::endl;
        return 1;
    }

    std::cout << "Average probability at MLT=12, R=3: " << out[0] << std::endl;
    return 0;
}