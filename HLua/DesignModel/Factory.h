//
//  Factory.h
//  HLua
//
//  Created by HSoul on 15/6/27.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#ifndef __HLua__Factory__
#define __HLua__Factory__

/*
    URL : http://lh-kevin.iteye.com/blog/1981574
 */

class Operation
{
public:
    Operation();
        
    virtual ~Operation();
    
    void init(float, float);
    
    virtual float GetResult() = 0;
    
protected:
    float m_nFirst;
    
    float m_nSecond;
};

class AddOperation : public Operation
{
public:
    float GetResult() override;
};

class SubOperation : public Operation
{
public:
    float GetResult() override;
};

class CaculateFactory
{
public:
    static Operation *create(char cOperator);
};

#endif /* defined(__HLua__Factory__) */
