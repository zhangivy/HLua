//
//  Factory.cpp
//  HLua
//
//  Created by HSoul on 15/6/27.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#include "Factory.h"
#include <stdio.h>

#pragma mark Operation

Operation::Operation():
m_nFirst(0),
m_nSecond(0)
{
    
}

Operation::~Operation()
{
    
}

void Operation::init(float first, float second)
{
    m_nFirst = first;
    m_nSecond = second;
}


#pragma mark Operation

float AddOperation::GetResult()
{
    return m_nFirst + m_nSecond;
}


#pragma mark Operation

float SubOperation::SubOperation::GetResult()
{
    return m_nFirst - m_nSecond;
}


#pragma mark CaculateFactory

Operation *CaculateFactory::create(char cOperator)
{
    Operation *oper;
    switch (cOperator)
    {
        case '+':
            oper = new AddOperation();
            break;
            
        case '-':
            oper = new SubOperation();
            break;

        default:
            printf("Error : CaculateFactory::create() input wrong oper [%c] \n", cOperator);
            oper = new AddOperation();
            break;
    }
    return oper;
}
