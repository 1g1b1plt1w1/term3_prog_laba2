#ifndef TASK1_H
#define TASK1_H
#include <string>
using namespace std;

bool eval_logic_with_stack(const string& expr, string& result);
static bool flush(Stack& ops, Stack& values, int min_prec);
static bool applyOp(const string& op, Stack& values);
static int prec(const string& op);
#endif