#include <iostream>
#include <fstream>
#include <math.h>
#include "imageIO.h"

using namespace std;

double Ex, Ey, Ez;
double Vx, Vy, Vz;
double Fangle;
int Rw, Rh;
double SOx, SOy, SOz, Sr;
double T11x, T11y, T11z, T12x, T12y, T12z, T13x, T13y, T13z;
double T21x, T21y, T21z, T22x, T22y, T22z, T23x, T23y, T23z;

void readFile() {
    ifstream ifile("hw1_input.txt");
    string test;
    while( ifile >> test ) {
        switch (test[0]) {
            case 'E':
                ifile >> Ex >> Ey >> Ez;
                break;
            case 'V':
                ifile >> Vx >> Vy >> Vz;
                break;
            case 'F':
                ifile >> Fangle;
                break;
            case 'R':
                ifile >> Rw >> Rh;
                break;
            case 'S':
                ifile >> SOx >> SOy >> SOz >> Sr;
                break;
            case 'T':
                ifile >> T11x >> T11y >> T11z >> T12x >> T12y >> T12z >> T13x >> T13y >> T13z >> test;
                ifile >> T21x >> T21y >> T21z >> T22x >> T22y >> T22z >> T23x >> T23y >> T23z;
                break;
        }
    }
}

bool isIntersectedSphere(double Fx, double Fy, double Fz) {
//  AT^2 + BT + C = 0;
    double A = Fx*Fx+Fy*Fy+Fz*Fz;
    double B = 2*(Fx*(Ex-SOx)+Fy*(Ey-SOy)+Fz*(Ez-SOz));
    double C = (Ex-SOx)*(Ex-SOx)+(Ey-SOy)*(Ey-SOy)+(Ez-SOz)*(Ez-SOz)-Sr*Sr;

    if ( (B*B - 4*A*C) >= 0 ) { return true; }
    return false;
}


int main()
{
    readFile();

    ColorImage imageSphere, imageTri1, imageTri2;
    imageSphere.init(Rw, Rh);
    imageTri1.init(Rw, Rh);
    imageTri2.init(Rw, Rh);

    Pixel B = {0,0,0};
    Pixel W = {255,255,255};

    for (int i = 0; i < Rw; ++i) {
        for (int j = 0; j < Rh; ++j) {
            double Fx = -tan(Fangle/2)+tan(Fangle/2)/Rw*i*2;
            double Fy = -tan(Fangle/2)+tan(Fangle/2)/Rw*j*2;
            double Fz = Vz;
            if(isIntersectedSphere(Fx, Fy, Fz)) {
                imageSphere.writePixel(i, j, B);
            } else {
                imageSphere.writePixel(i, j, W);
            }
        }
    }

    imageSphere.outputPPM("hw1_output_Sphere.ppm");

    return 0;
}
