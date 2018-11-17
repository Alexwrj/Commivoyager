//
//  main.cpp
//  Commivoyager
//
//  Created by Alexander Fomenko on 30/10/2018.
//  Copyright © 2018 Alexander Fomenko. All rights reserved.
//

#include <iostream>
#include "Commi.hpp"

int main() {
    auto INF = std::numeric_limits<float>::infinity();
    vector<vector<float>>matrix;
    matrix.resize(5);
    
    for (int i = 0; i < 5; i++)
    {
        matrix[i].resize(5);
    }
    
    matrix[0][0] = INF;
    matrix[0][1] = 25;
    matrix[0][2] = 26;
    matrix[0][3] = 29;
    matrix[0][4] = 27;
    
    matrix[1][0] = 28;
    matrix[1][1] = INF;
    matrix[1][2] = 29;
    matrix[1][3] = 26;
    matrix[1][4] = 30;
    
    matrix[2][0] = 31;
    matrix[2][1] = 27;
    matrix[2][2] = INF;
    matrix[2][3] = 26;
    matrix[2][4] = 32;
    
    matrix[3][0] = 26;
    matrix[3][1] = 29;
    matrix[3][2] = 26;
    matrix[3][3] = INF;
    matrix[3][4] = 30;
    
    matrix[4][0] = 25;
    matrix[4][1] = 31;
    matrix[4][2] = 30;
    matrix[4][3] = 29;
    matrix[4][4] = INF;
    
    
    Commi Voyager(matrix);
    
    cout << "\nThe best way is: ";
    Voyager.showOptimalPath();
    cout << "\nCommon tax is: " << Voyager.getTax() << endl;
    
    return 0;
}
