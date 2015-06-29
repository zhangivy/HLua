//
//  Composite.h
//  LQGame
//
//  Created by HSoul on 15/6/27.
//
//

#ifndef __LQGame__Composite__
#define __LQGame__Composite__

#include <string>
#include <vector>

/*
    将对象组合成树形结构以表示“部分-整体”的层次结构。组合模式使得用户对单个对象和组合对象的使用具有一致性。
 */

// 组件统一接口, 方便用户操作, 接口定义在父类中
class LQMenu
{
public:
    virtual ~LQMenu();
    
    virtual void Add(LQMenu *);
    
    virtual void Remove(LQMenu *);
    
    virtual LQMenu *GetChild(int);
    
    virtual void Clear();
    
    virtual void Display() = 0;
    
protected:
    LQMenu();
    
    LQMenu(std::string);
    
    std::string m_strName;
};

class SubMenu : public LQMenu
{
public:
    SubMenu();
    
    SubMenu(std::string);
    
    ~SubMenu() override;
    
    void Display() override;
};

class CompositeMenu : public LQMenu
{
public:
    CompositeMenu();
    
    CompositeMenu(std::string);
    
    ~CompositeMenu() override;
    
    void Add(LQMenu *) override;
    
    void Remove(LQMenu *) override;
    
    LQMenu *GetChild(int) override;
    
    void Clear() override;
    
    void Display() override;
    
private:
    std::vector<LQMenu *> m_vMenu;
};

#endif /* defined(__LQGame__Composite__) */
