#include <iostream>
#include <fstream>
#include "dnode.h"
#include "bag.h"
#include "evaluator.h"

using namespace std;

int main(int argc, const char * argv[]) {
   
    evaluator evaluate;
    string gotString;
    
    std::cout << "이름:   이민호     학번:     2015202047"<<endl;
    
    while(1)
    {
        gotString=evaluate.read_expression();
        cout<<"*****************************************************************"<<endl;
        cout<<"[read_expression operated] \nInput Expression >> "<<gotString<<"\n"<<endl;
        if(gotString=="exit")
            break;
        cout<<"[string convert_to_postfix(string s) operated] \nPostfix Expression >> "<<evaluate.convert_to_postfix(gotString)<<"\n"<<endl;
        cout<<"[double evaluate_postfix(string s) operated] \nEvaluation Result >> "<<evaluate.evaluate_postfix(evaluate.convert_to_postfix(gotString))<<endl;
        cout<<"*****************************************************************"<<endl;

    }
    cout<<"exit call. Goodbye"<<endl;


    return 0;
}
