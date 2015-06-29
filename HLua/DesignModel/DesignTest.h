//
//  DesignTest.h
//  HLua
//
//  Created by HSoul on 15/6/27.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#ifndef __HLua__DesignTest__
#define __HLua__DesignTest__

#include <string>
#include <iostream>
#include "Composite.h"
#include "Factory.h"
#include "Strategy.h"
#include "Concreate.h"

using namespace std;



// about design model

void CompositeTest()
{
    LQMenu *LQMenu = new CompositeMenu("祖");
    auto m1 = new CompositeMenu("父");
    auto m11 = new CompositeMenu("我");
    auto m111 = new CompositeMenu("女儿");
    auto m112 = new CompositeMenu("儿子");
    m11->Add(m111);
    m11->Add(m112);
    m1->Add(m11);
    
    auto m2 = new CompositeMenu("伯父");
    auto m21 = new SubMenu("堂兄弟");
    auto m22 = new SubMenu("堂姊妹");
    m2->Add(m21);
    m2->Add(m22);
    
    auto m3 = new CompositeMenu("叔父");
    
    auto m4 = new CompositeMenu("姑姑");
    auto m41 = new SubMenu("表兄弟");
    auto m42 = new SubMenu("表姊妹");
    m4->Add(m41);
    m4->Add(m42);
    
    LQMenu->Add(m1);
    LQMenu->Add(m2);
    LQMenu->Add(m3);
    LQMenu->Add(m4);
    LQMenu->Display();
    
    delete LQMenu;
}

void FactoryTest()
{
    int a, b;
    cin >> a >> b;
    Operation *op = CaculateFactory::create('-');
    op->init(a, b);
    printf("%f", op->GetResult());
    delete op;
}

void StrategyTest()
{ 
    Operation *op = new AddOperation();
    op->init(8, 7);
    Context context = Context(op);
    printf("%f", context.GetResult());
}

void ConcreateTest()
{
    Person *p=new Person("小李");
    
    auto bt = BigTrouser();
    BigTrouser *pbt = &bt;
    
    auto ts = TShirts();
    TShirts *pts = &ts;
    
    pbt->Decorate(p);
    pts->Decorate(pbt);
    
    pts->Show();
}

void DesignModelEnter()
{
    // CompositeTest();
    // FactoryTest();
    // StrategyTest();
    ConcreateTest();
}

#endif /* defined(__HLua__DesignTest__) */
