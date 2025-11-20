#pragma once
#include <string>
#include "stack.h"
#include "task1.h"

using namespace std;

static int prec(const string& op){
    if(op == "!") return 3;
    if(op == "&") return 2;
    if(op == "|" || op == "^") return 1;
    return -1;
}

static bool applyOp(const string& op, Stack& values){
    if(op == "!"){
        string a = Stack_peek(values);
        if(a == "") return false;
        Stack_pop(values);
        if(a!="0" && a!="1") return false;
        Stack_push_back(values, (a=="1") ? "0" : "1");
        return true;
    }

    string rhs = Stack_peek(values);
    if(rhs == "") return false;
    Stack_pop(values);

    string lhs = Stack_peek(values);
    if(lhs == "") return false;
    Stack_pop(values);

    if((lhs!="0" && lhs!="1") || (rhs!="0" && rhs!="1"))
        return false;

    int a = lhs=="1";
    int b = rhs=="1";
    int r = 0;
    if(op=="&") r = (a & b);
    else if(op=="|") r = (a | b);
    else if(op=="^") r = (a ^ b);
    else return false;

    Stack_push_back(values, r?"1":"0");
    return true;
}

static bool flush(Stack& ops, Stack& values, int min_prec){
    while(true){
        string op = Stack_peek(ops);
        if(op=="" || op=="(") break;

        int p = prec(op);
        if(p < min_prec) break;

        Stack_pop(ops);
        if(!applyOp(op, values)) return false;
    }
    return true;
}

bool eval_logic_with_stack(const string& expr, string& result){
    Stack values = Stack_create();
    Stack ops = Stack_create();

    auto fail = [&](){
        Stack_destroy(values);
        Stack_destroy(ops);
        return false;
    };

    bool expectValue = true;

    for(size_t i=0; i<expr.size(); ++i){
        char c = expr[i];
        string s(1, c);

        if(c==' ') continue;

        if(c=='0' || c=='1'){
            if(!expectValue) return fail();
            Stack_push_back(values, s);
            expectValue = false;
        }
        else if(c=='!'){
            Stack_push_back(ops, s);
            expectValue = true;
        }
        else if(c=='&' || c=='|' || c=='^'){
            if(expectValue) return fail();
            int p = prec(s);
            if(!flush(ops, values, p)) return fail();
            Stack_push_back(ops, s);
            expectValue = true;
        }
        else if(c=='('){
            Stack_push_back(ops, s);
            expectValue = true;
        }
        else if(c==')'){
            if(expectValue) return fail();
            bool found = false;

            while(true){
                string op = Stack_peek(ops);
                if(op == "") return fail();
                Stack_pop(ops);

                if(op=="("){
                    found = true; 
                    break;
                }

                if(!applyOp(op, values)) return fail();
            }
            if(!found) return fail();
        }
        else return fail();
    }

    if(expectValue) return fail();

    while(true){
        string op = Stack_peek(ops);
        if(op=="") break;
        Stack_pop(ops);

        if(op=="(") return fail();
        if(!applyOp(op, values)) return fail();
    }

    string res = Stack_peek(values);
    if(res=="") return fail();
    Stack_pop(values);

    bool ok = (Stack_peek(values) == "");
    if(!ok) return fail();

    result = res;
    Stack_destroy(values);
    Stack_destroy(ops);
    return true;
}
