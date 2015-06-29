//
//  Concreate.h
//  HLua
//
//  Created by HSoul on 15/6/29.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#ifndef __HLua__Concreate__
#define __HLua__Concreate__

#include <stdio.h>
#include <string>
#include <iostream> 

using namespace std;

class Person
{
public:
    Person(string strName)
    {
        m_strName=strName;
    }
    
    Person(){}
    
    virtual void Show()
    {
        cout<<"装扮是:"<<m_strName<<endl;
    }
    
private:
    string m_strName;
};

// 装饰类
class Finery :public Person
{
public:
    void Decorate(Person* component)
    {
        m_component=component;
    }
    
    virtual void Show()
    {
        m_component->Show();
    }
    
protected:
    Person* m_component;
};

// 衬衫
class TShirts : public Finery
{
public:
    virtual void Show()
    {
        cout<<"T Shirts"<<endl; m_component->Show();
    }
};

// 裤子
class BigTrouser : public Finery
{
public:
    virtual void Show()
    {
        cout<<" Big Trouser"<<endl;
        m_component->Show();
    }
};

#endif /* defined(__HLua__Concreate__) */
