//
//  Strategy.cpp
//  HLua
//
//  Created by HSoul on 15/6/29.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#include "Strategy.h"

Context::Context(Operation *pOperation)
{
    m_pOpertion = pOperation;
}

Context::~Context()
{
    if (m_pOpertion)
    {
        delete m_pOpertion;
    }
}

double Context::GetResult()
{
    return m_pOpertion->GetResult();
}
