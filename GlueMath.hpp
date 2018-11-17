//
//  GlueMath.hpp
//  LinearAlgebra
//
//  Created by Alexander Fomenko on 12/11/2018.
//  Copyright © 2018 Alexander Fomenko. All rights reserved.
//

#ifndef GlueMath_hpp
#define GlueMath_hpp

#include <stdio.h>
#include <math.h>
#include <vector>

using namespace std;

struct Vector3
{
    float X;
    float Y;
    float Z;
    
    Vector3();
    Vector3(float X, float Y, float Z);
    ~Vector3(){}
    Vector3 operator*(Vector3 otherVector);
    Vector3 operator-(Vector3 otherVector);
    static Vector3 normal(Vector3 vector);
};

struct Operators
{
    static void transp(vector<vector<float>>&matrix);
};

#endif /* GlueMath_hpp */
