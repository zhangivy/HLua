//
//  Student.h
//  HLua
//
//  Created by HSoul on 15/7/8.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#ifndef __HLua__Student__
#define __HLua__Student__

#include <stdio.h>

#include <iostream>
#include<string>
using namespace std;

class Student
{
public:
    Student();
    ~Student();
    string getName();
    void setName(string name);
    int getAge();
    void setAge(int age);
    void print();
    
private:
    string name;
    int age;
};

#endif /* defined(__HLua__Student__) */
