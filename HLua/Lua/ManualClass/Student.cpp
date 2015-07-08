//
//  Student.cpp
//  HLua
//
//  Created by HSoul on 15/7/8.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#include "Student.h"

Student::Student()
:name("default")
{
    cout<<"Student Contructor called"<<endl;
}

Student::~Student()
{
    cout<<"Student Destructor called"<<endl;
}

string Student::getName()
{
    return name;
}

void Student::setName(string name)
{
    this->name = name;
}

int Student::getAge()
{
    return age;
}

void Student::setAge(int age)
{
    this->age = age;
}

void Student::print()
{
    cout<<"My name is: "<<name<<", and my age is "<<age<<endl;
}