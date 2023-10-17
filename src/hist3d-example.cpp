#include "hist3d.h"
/* C++ API */
#include <iostream>

int main(void) {
    Hist3D * hist3D = new Hist3D(-10, 10, 21, 4, 9, 11, 1, 3, 21);
    
    for(int i = 0; i < 20; i++) {
        const double x = -10 + i;
        for(int j = 0; j < 10; j++) {
            const double y = 4 + j * 0.5;
            for(int k = 0; k < 20; k++) {
                const double z = 1 + k * 0.1;
                hist3D->Fill(x, y, z, (y*y)/(x*z*x*z + 1));
            }
        }
    }
    
    long entries = hist3D->GetEntries();
    std::cout << "XXX entries: " << entries << std::endl;
    for(int i = 0; i < 20; i++) {
        const double x = hist3D->GetXBinCenter(i);
        for(int j = 0; j < 10; j++) {
            const double y = hist3D->GetYBinCenter(j);
            for(int k = 0; k < 20; k++) {
                const double z = hist3D->GetZBinCenter(k);
                double content = hist3D->GetContent(i, j, k);
                double content2 = hist3D->GetContent2(i, j, k);
                std::cout << x << " " << y << " " << z << ": " <<
                        content << " " << content2 << std::endl;
            }
        }
    }
    
    delete hist3D;    
    return EXIT_SUCCESS;
}
