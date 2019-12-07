#include <iostream>
#include <math.h>
#include <vector>

using std::vector;
using std::cout; 

float euclidianDist(vector<float> x ,vector<float> y){
    float sum = 0;
    for(int i = 0; i<x.size();i++){
        sum += pow((x[i] - y[i]),2);
    }
    return sqrt(sum);
}

void testCase(){
    vector<float> x{7,4,3};
    vector<float> y{17,6,2};
    cout << euclidianDist(x,y);
}

int main(){
    testCase();
    return 0;
}