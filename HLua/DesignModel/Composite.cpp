//
//  Composite.cpp
//  LQGame
//
//  Created by HSoul on 15/6/27.
//
//

#include "Composite.h"
#include <iostream>
#include <sstream>

using namespace std;

static int depth = 0;

#pragma mark LQMenu

LQMenu::LQMenu()
{
    
}

LQMenu::LQMenu(std::string strName)
{
    m_strName = strName;
}

LQMenu::~LQMenu()
{
    
}

void LQMenu::Add(LQMenu *pMenu)
{
    
}

void LQMenu::Remove(LQMenu *pMenu)
{
    
}

LQMenu * LQMenu::GetChild(int index)
{
    return nullptr;
}

void LQMenu::Clear()
{
    
}

#pragma mark Menu

SubMenu::SubMenu()
{
    
}

SubMenu::SubMenu(std::string strName) : LQMenu(strName)
{
    
}

SubMenu::~SubMenu()
{
    
}

void SubMenu::Display()
{
    stringstream ssr;
    for (int i = 0; i < depth; i++)
    {
        ssr << "  ";
    }
    cout<< ssr.str() << "-" << m_strName << " " << depth << endl;
}

#pragma mark CompositeMenu

CompositeMenu::CompositeMenu()
{
    
}

CompositeMenu::CompositeMenu(string strName) : LQMenu(strName)
{
    
}

CompositeMenu::~CompositeMenu()
{
    Clear();
}

void CompositeMenu::Add(LQMenu *pMenu)
{
    m_vMenu.push_back(pMenu);
}

void CompositeMenu::Remove(LQMenu *pMenu)
{
    for (auto it = m_vMenu.begin(); it != m_vMenu.end(); it++)
    {
        if ((*it) == pMenu)
        {
            delete pMenu;
            m_vMenu.erase(it);
            break;
        }
    }
}

LQMenu * CompositeMenu::GetChild(int index)
{
    if (0 <= index && index < m_vMenu.size())
    {
        return m_vMenu[index];
    }
    return nullptr;
}

void CompositeMenu::Clear()
{
    for (auto item : m_vMenu)
    {
         if(item)
         {
             delete item;
             item = nullptr;
         }
    }
    m_vMenu.clear();
}

void CompositeMenu::Display()
{
    stringstream ssr;
    for (int i = 0; i < depth; i++)
    {
        ssr << "  ";
    }
    cout<< ssr.str() << "+" << m_strName << " " << depth << endl;
    vector<LQMenu *>::iterator iter = m_vMenu.begin();
    
    bool temp = false;
    for (; iter != m_vMenu.end(); ++iter)
    {
        if (!temp)
        {
            temp = true;
            depth++;
        }
        (*iter)->Display();
    }
    if (temp)
    {
        depth--;
    }
}
