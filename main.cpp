//
//  main.cpp
//  二叉树 非递归
//
//  Created by 董依萌 on 2017/6/1.
//  Copyright © 2017年 董依萌. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stack>
#include <string.h>
using namespace std;
string st;                  //字符串设置为全局变量 方便创建二叉树的时候不用递归调用字符串
typedef struct BinNode{
    char data;
    bool flag;           //后序非递归中的标记
    struct BinNode *lchild,*rchild;
}BinNode,*BinTree;
//按先序创建树 ABD##E##CF####
void creatTree(BinTree& T)
{
    static int i=-1;
    i++;
        if(st[i]=='#'){
            T=NULL;
            //i++;
        }
        else{
            T=(BinNode*)malloc(sizeof(BinNode));
            //i++;
            T->data=st[i];
            creatTree(T->lchild);
            creatTree(T->rchild);
        }
}
void visit(BinTree T)
{
    if(T->data!='#')
        cout<<T->data<<" ";
}
void preOrder(BinTree T)               //前序递归
{
    if(T)
    {
        visit(T);
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}
void inOrder(BinTree T)             //中序递归
{
    if(T)
    {
        inOrder(T->lchild);
        visit(T);
        inOrder(T->rchild);
    }
}
void postOrder(BinTree T)          //后序递归
{
    if(T)
    {
        postOrder(T->lchild);
        postOrder(T->rchild);
        visit(T);
    }
}
void preOrderUnrec(BinTree T)           //非递归前序遍历
{
    BinTree p;
    p=T;
    stack<BinTree> s;
    while(p || !s.empty())     //条件为 或 （|）有一个为真就可以执行循环
    {                          // empty 为bool 为空返回true
        while(p)
        {
            visit(p);
            s.push(p);
            p=p->lchild;
        }
        if(!s.empty())
        {
            p=s.top();
            s.pop();
            
            p=p->rchild;
        }
    }
}
void inOrderUnrec(BinTree T)             ////非递归中序遍历
{
    BinTree p;
    p=T;
    stack<BinTree> s;
    while(p || !s.empty())
    {
        while(p)
        {
            
            s.push(p);
            p=p->lchild;
        }
        if(!s.empty())
        {
            p=s.top();
            visit(p);
            s.pop();
            p=p->rchild;
        }
    }
}

void postOrderUnrec1(BinTree T)    //非递归后序遍历  这个思路更好理解一些，下面有解释
{
    BinTree p,cur;
    BinTree pre=NULL;
    p=T;
    stack<BinTree> s;
    s.push(p);
    while(!s.empty())
    {
        cur=s.top();
        if((cur->lchild==NULL && cur->rchild==NULL)||((pre!=NULL)&&(pre==cur->lchild || pre==cur->rchild)))
        {
            visit(cur);
            s.pop();
            pre=cur;
        }
        else
        {
            if(cur->rchild)
                s.push(cur->rchild);
            if(cur->lchild)
                s.push(cur->lchild);
            
        }
    }
}

int main()
{
    BinTree T;
    cin>>st;
    //cout<<st<<endl;
    creatTree(T);
    cout<<"preOrder  :"<<endl;
    preOrder(T);           //前序
    cout<<endl;
    cout<<"preOrderUnrecursion  :"<<endl;
    preOrderUnrec(T);
    cout<<endl;
    cout<<"inOrder  :"<<endl;
    inOrder(T);            //中序
    cout<<endl;
    cout<<"inOrderUnrecursion  :"<<endl;
    inOrderUnrec(T);
    cout<<endl;
    cout<<"postOrder  :"<<endl;
    postOrder(T);         //后序
    cout<<endl;
    cout<<"postOrderUnrecursion1  :"<<endl;
    postOrderUnrec1(T);
    cout<<endl;
    return 0;
}

