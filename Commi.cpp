//
//  Commi.cpp
//  Commivoyager
//
//  Created by Alexander Fomenko on 10/11/2018.
//  Copyright © 2018 Alexander Fomenko. All rights reserved.
//

#include "Commi.hpp"

Commi::Commi()
{
    auto INF = std::numeric_limits<float>::infinity();
    matrix.resize(SIZE);
    
    for (int i = 0; i < SIZE; i++)
    {
        matrix[i].resize(SIZE);
    }
    
    matrix[0][0] = INF;
    matrix[0][1] = 3;
    matrix[0][2] = 4;
    matrix[0][3] = 7;
    matrix[0][4] = 5;
    
    matrix[1][0] = 6;
    matrix[1][1] = INF;
    matrix[1][2] = 7;
    matrix[1][3] = 4;
    matrix[1][4] = 8;
    
    matrix[2][0] = 9;
    matrix[2][1] = 6;
    matrix[2][2] = INF;
    matrix[2][3] = 5;
    matrix[2][4] = 10;
    
    matrix[3][0] = 4;
    matrix[3][1] = 7;
    matrix[3][2] = 5;
    matrix[3][3] = INF;
    matrix[3][4] = 8;
    
    matrix[4][0] = 3;
    matrix[4][1] = 9;
    matrix[4][2] = 8;
    matrix[4][3] = 7;
    matrix[4][4] = INF;
    
    sollution();
}

Commi::Commi(vector<vector<float>>matr)
{
    matrix = matr;
    
    sollution();
}

vector<float> Commi::minByRow()
{
    auto INF = std::numeric_limits<float>::infinity();
    vector<float>h;
    
    for (auto row : matrix)
    {
        float min = INF;
        for (auto el : row)
        {
            if (el < min)
            {
                min = el;
            }
        }
        h.push_back(min);
    }
    
    return h;
}

vector<float> Commi::minByCol(vector<vector<float>>matr)
{
    auto INF = std::numeric_limits<float>::infinity();
    vector<float>g;
    Operators::transp(matr);
    
    for (auto row : matr)
    {
        float min = INF;
        for (auto el : row)
        {
            if (el < min)
            {
                min = el;
            }
        }
        g.push_back(min);
    }
    
    return g;
}

vector<vector<float>>Commi::getSourceMatrix()
{
    return matrix;
}

void Commi::setMatrix(vector<vector<float>>matrix)
{
    this->matrix = matrix;
}

void Commi::setSourceMatrix(vector<vector<float>>matrix)
{
    this->sourceMatrix = matrix;
}

vector<vector<float>>Commi::outlayMatrix(vector<float>h, vector<vector<float>>inMatrix)
{
    vector<vector<float>>tmpMatrix = inMatrix;
    
    int j = 0;
    
    for (auto &row : tmpMatrix)
    {
        for (int i = 0; i < h.size(); i++)
        {
            row[i] -= h[j];
        }
        ++j;
    }
    
    return tmpMatrix;
}

vector<float>Commi::minR()
{
    auto INF = std::numeric_limits<float>::infinity();
    vector<float>h;
    vector<Indecies>indecies = findZeroes(true);
    
    for (int row = 0; row < matrix.size(); row++)
    {
        float min = INF;
        Indecies current = indecies[row];
        
        for (int col = 0; col < matrix[row].size(); col++)
        {
            if (!(current == Indecies(row, col)))
            {
                if (matrix[row][col] < min)
                {
                    min = matrix[row][col];
                }
            }
        }
        h.push_back(min);
    }
    
    return h;
}

vector<float>Commi::minM()
{
    auto INF = std::numeric_limits<float>::infinity();
    vector<float>g;
    Operators::transp(matrix);
    vector<Indecies>indecies = findZeroes(true);
    
    for (int row = 0; row < matrix.size(); row++)
    {
        float min = INF;
        Indecies current = indecies[row];
        
        for (int col = 0; col < matrix[row].size(); col++)
        {
            if (!(current == Indecies(row, col)))
            {
                if (matrix[row][col] < min)
                {
                    min = matrix[row][col];
                }
            }
        }
        g.push_back(min);
    }
    
    Operators::transp(matrix);
    
    return g;
}

vector<Indecies>Commi::findZeroes(bool flag)
{
    vector<Indecies>indecies;
    
    for (int row = 0; row < matrix.size(); row++)
    {
        int cnt = 0;
        
        for (int col = 0; col < matrix[row].size(); col++)
        {
            if (matrix[row][col] == 0.f)
            {
                indecies.push_back(Indecies(row, col));
                ++cnt;
                if (flag) break;
            }
        }
        if (cnt == 0)
        {
            indecies.push_back(Indecies(row, 0));
        }
    }
    return indecies;
}

vector<vector<float>>Commi::createTaxMatrix(vector<float>h, vector<float>g)
{
    vector<Indecies>rowIndecies = findZeroes(false);
    Operators::transp(matrix);
    vector<Indecies>colIndecies = findZeroes(false);
    Operators::transp(matrix);
    vector<vector<float>>resMatrix;
    
    resMatrix.resize(matrix.size());
    
    for (int i = 0; i < resMatrix.size(); i++)
    {
        resMatrix[i].resize(matrix[i].size());
    }
    
    setTax(rowIndecies, h, resMatrix);
    Operators::transp(resMatrix);
    setTax(colIndecies, g, resMatrix);
    Operators::transp(resMatrix);
    
    return resMatrix;
}

void Commi::setTax(vector<Indecies>indecies, vector<float>h, vector<vector<float>>&matr)
{
    auto INF = std::numeric_limits<float>::infinity();
    
    for (int row = 0; row < matr.size(); row++)
    {
        for (int col = 0; col < matr[row].size(); col++)
        {
            if (matr[row][col] == NULL)
            {
                matr[row][col] = 0.f;
            }
            
            if (find(indecies.begin(), indecies.end(), Indecies(row, col)) != indecies.end())
            {
                matr[row][col] += h[row];
            }
            else
            {
                matr[row][col] = INF;
            }
        }
    }
}

Indecies Commi::findMaxCellPosition(vector<vector<float>>tax)
{
    auto INF = std::numeric_limits<float>::infinity();
    Indecies indecies = Indecies(0, 0);
    float max = 0.f;
    
    for (int row = 0; row < tax.size(); row++)
    {
        for (int col = 0; col < tax[row].size(); col++)
        {
            if ((tax[row][col] > max) && (tax[row][col] != INF))
            {
                max = tax[row][col];
                indecies = Indecies(row, col);
            }
        }
    }
    
    return indecies;
}

void Commi::reduceRowsAndColumns(Indecies indecies, Indecies extraIndex)
{
    auto INF = std::numeric_limits<float>::infinity();
    
    for (int row = 0; row < matrix.size(); row++)
    {
        for (int col = 0; col < matrix[row].size(); col++)
        {
            if (
                    (indecies.row == row)
                    || (indecies.col == col)
                    || indecies == Indecies(col, row)
                    || extraIndex == Indecies(col, row)
                )
            {
                matrix[row][col] = INF;
            }
        }
    }
}

bool Commi::isInfSet(vector<float> set)
{
    auto INF = std::numeric_limits<float>::infinity();
    
    int cnt = 0;
    for (auto el : set)
    {
        if (el == INF) ++cnt;
    }
    
    if (cnt == set.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Commi::sollution()
{
    commSum = 0.f;
    float sumH = 0.f;
    float sumG = 0.f;
    vector<float>h;
    vector<float>g;
    
    while (true)
    {
        
        h = minByRow();
        
        vector<vector<float>>outlayMatr = outlayMatrix(h, getSourceMatrix());
        
        g = minByCol(outlayMatr);
        Operators::transp(outlayMatr);
        
        vector<vector<float>>reducedMatrix = outlayMatrix(g, outlayMatr);
        Operators::transp(reducedMatrix);
        
        for (auto el : h)
        {
            if (el != INFINITY)
            {
                sumH += el;
            }
        }
        for (auto el : g)
        {
            if (el != INFINITY)
            {
                sumG += el;
            }
        }
        commSum = sumH + sumG;
        
        setMatrix(reducedMatrix);
        
        h = minR();
        g = minM();
        
        if (isInfSet(h) && isInfSet(g))
        {
            //find all rest possible ways and pick
            //the one suitable
            bestWay.push_back(findLastWay());
            break;
        }
        
        vector<vector<float>>maxTax = createTaxMatrix(h, g);
        Indecies reduceIndecies = findMaxCellPosition(maxTax);
        bestWay.push_back(reduceIndecies);
        
        
        //instead of deleting row and column, the app will assing INF for each element in
        //current row and column
        reduceRowsAndColumns(
                             reduceIndecies,
                             Indecies(bestWay[0].row, (bestWay.back()).col)
                             );
        setSourceMatrix(matrix);
    }
    
    bestWay.push_back(Indecies(-1, bestWay[0].row));
}

Indecies Commi::findLastWay()
{
    auto INF = std::numeric_limits<float>::infinity();
    vector<Indecies> allPossibleWays;
    vector<Indecies> possibleWays;
    Indecies lastWay = Indecies(-1.f, -1.f);
    
    for (int row = 0; row < sourceMatrix.size(); row++)
    {
        for (int col = 0; col < sourceMatrix[row].size(); col++)
        {
            allPossibleWays.push_back(Indecies(row, col));
        }
    }
    
    for (auto way : allPossibleWays)
    {
        if (
                find(bestWay.begin(), bestWay.end(), way) == bestWay.end()
                && sourceMatrix[way.row][way.col] != INF
                && !isnan(sourceMatrix[way.row][way.col])
            )
        {
            possibleWays.push_back(way);
        }
    }
    
    float max = 0.f;
    
    for (int i = 0; i < possibleWays.size(); i++)
    {
        float currentValue = sourceMatrix[possibleWays[i].row][possibleWays[i].col];
        if (currentValue > max)
        {
            max = currentValue;
            lastWay = Indecies(possibleWays[i].col, possibleWays[i].row);
        }
    }
    
    return lastWay;
}

void Commi::showOptimalPath()
{
    cout << bestWay[0].row + 1 << "->" << bestWay[0].col + 1;
    
    for (int i = 1; i < bestWay.size(); i++)
    {
        cout << "->" << bestWay[i].col + 1;
    }
    
    cout << endl;
}

float Commi::getTax()
{
    return commSum;
}
