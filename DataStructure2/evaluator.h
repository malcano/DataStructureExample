//
//  evaluator.h
//  DataStructure2
//
//  Created by Minho Lee on 2021/11/08.
//

#ifndef evaluator_h
#define evaluator_h
#include "dnode.h"
#include "bag.h"
#include <typeinfo>

class evaluator
{
public:
    string read_expression();
    string convert_to_postfix(string s);
    double evaluate_postfix(string s);
};

string evaluator::read_expression()
{
    string expInput;
    cout<<">";
    std::cin >> expInput;
    if(expInput=="exit")
        return "exit";
    return expInput;
}

string evaluator::convert_to_postfix(string s)
{
    bag<char> printliststack;
    bag<char> stack;
    string postfixResult;
    
    
    for(int i=0;i<s.length();i++)
    {
        if((s[i]>='A' && s[i]<='z')||(s[i] >= '0' && s[i] <= '9' )||s[i]=='.')
        {
//            printliststack.insert(s[i]);
            while((s[i] >= '0' && s[i] <= '9') ||s[i]=='.'){
                printliststack.insert(s[i]);
                i++;
            }
            i--;
            
        }else
        {
            if(s[i] == ')')
            {
                while(stack.listSize()!=0&&stack.getHeaddata()!='(')
                {
                    printliststack.insert(stack.headOut());
                }
                if(stack.getHeaddata()=='(')
                    stack.headOut();
            }else if(s[i] == '('){
                stack.insert(s[i]);
            }else {
                if(s[i]=='*' || s[i]=='/')
                {
                    if(stack.listSize()!=0&&(stack.getHeaddata()=='*'||stack.getHeaddata()=='/')){
                        printliststack.insert(stack.headOut());
        
                    }
                }
                else{
                    while (stack.listSize()!=0&&stack.getHeaddata()!='(') {
                        printliststack.insert(stack.headOut());
                    }
                }
                printliststack.insert(' ');
                stack.insert(s[i]);
            }
        }
    }
    while(stack.listSize()!=0){
        printliststack.insert(stack.headOut());
    }
    int resultlength=(int)printliststack.listSize();
    bag<char> tempstack;
    
    for(int i=0;i<resultlength;i++)
    {
        tempstack.insert(printliststack.headOut());
    }
    printliststack = tempstack;
    
    for(int i=0;i<resultlength;i++)
    {
        postfixResult+=printliststack.headOut();
    }
    
    return postfixResult;
}

double evaluator::evaluate_postfix(string s)
{
    bag<double> stack;
    double firstOpr;
    double secondOpr;
    double buffer=0;
    bool isNumbefore = false;
    bool isCharbefore = false;
    bool dot = false;
    double dem=1;
    int ro=1;
    
    for(int i=0;i<s.length();i++)
    {
        if((s[i]!='+'&&s[i]!='-'&&s[i]!='*'&&s[i]!='/')||s[i]==' '||s[i]=='.')//is number or blank or dot
        {
            if(s[i]==' '&&isNumbefore==true)//is blank and was number before
            {
                stack.insert(buffer);
                buffer = 0;
                isNumbefore= false;
                dot=false;
                
            }else if(s[i]=='.'){
                dot=true;
                ro=1;
            }else if(dot == true)
            {
                if(s[i]!=' ')// was not blank
                {
                    dem = 1;
                    for(int j=0;j<ro;j++)
                    {
                        dem*=0.1;
                    }
                    buffer=buffer + (s[i]-'0')*dem;
                    ro++;
                }else{//was blank
                    dem=1;
                    ro=1;
                    dot= false;
                }
            }
            else if(dot==false){
                if(isNumbefore==true)//was number
                {
                    buffer = buffer*10+(s[i]-'0');
                }else if(s[i]!=' ')// was not blank
                {
                    buffer=s[i]-'0';
                }
                isNumbefore = true;
            }
            isCharbefore = false;
        }
        else{//is char
            
            if(isCharbefore==false)
            {
                stack.insert(buffer);
                buffer = 0;
            }
            if(dot==true)
            {
                dem=1;
                ro=1;
                dot= false;
            }
            
            secondOpr = stack.headOut();
            firstOpr = stack.headOut();
         
            switch(s[i]){
                case '+': stack.insert(firstOpr+secondOpr); break;
                case '-': stack.insert(firstOpr-secondOpr); break;
                case '*': stack.insert(firstOpr*secondOpr); break;
                case '/': stack.insert(firstOpr/secondOpr); break;
                
            }
            isNumbefore=false;
            isCharbefore=true;
            
        }
    }
    
    
    
    return stack.headOut();
}



#endif /* evaluator_h */
