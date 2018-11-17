//
//  Commi.hpp
//  Commivoyager
//
//  Created by Alexander Fomenko on 10/11/2018.
//  Copyright © 2018 Alexander Fomenko. All rights reserved.
//

#ifndef Commi_hpp
#define Commi_hpp

#include <stdio.h>
#include <iostream>
#include <limits>
#include <algorithm>
#include "GlueMath.hpp"

using namespace std;

struct Indecies
{
    int row;
    int col;
    Indecies()
    {
        row = 0;
        col = 0;
    }
    Indecies(int r, int c)
    {
        row = r;
        col = c;
    }
    ~Indecies(){}
    
    bool operator==(Indecies otherIndecies)
    {
        if (otherIndecies.row == this->row && otherIndecies.col == this->col)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
};

class Commi
{
public:
    Commi(vector<vector<float>>matrix);
    Commi();
    ~Commi(){}
    void showOptimalPath();
    float getTax();

private:
    const int SIZE = 5;
    vector<vector<float>>matrix;
    vector<vector<float>>sourceMatrix;
    vector<Indecies>bestWay;
    float commSum;
    
    vector<float>minByRow();
    vector<float>minByCol(vector<vector<float>>matr);
    vector<vector<float>>outlayMatrix(vector<float>h, vector<vector<float>>);
    vector<vector<float>>getSourceMatrix();
    void setMatrix(vector<vector<float>>matrix);
    void setSourceMatrix(vector<vector<float>>matrix);
    vector<Indecies>findZeroes(bool flag);
    vector<float>minR();
    vector<float>minM();
    vector<vector<float>>createTaxMatrix(vector<float>h, vector<float>g);
    Indecies findMaxCellPosition(vector<vector<float>>tax);
    void reduceRowsAndColumns(Indecies indecies, Indecies extraIndecies);
    bool isInfSet(vector<float> set);
    void sollution();
    Indecies findLastWay();
    
    void setTax(vector<Indecies>indecies, vector<float>h, vector<vector<float>>&matr);
};

#endif /* Commi_hpp */
