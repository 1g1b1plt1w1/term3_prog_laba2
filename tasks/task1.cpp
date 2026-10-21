#include "task1.h"
#include "stack.h"
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

static bool stack_is_empty(const Stack& s) {
    return s.list.head == nullptr;
}

static string stack_peek(const Stack& s) {
    if (s.list.head == nullptr) {
        return "";
    }
    return s.list.head->data;
}

static int get_precedence(const string& op) {
    if (op == "+" || op == "-") {
        return 1;
    }
    if (op == "*") {
        return 2;
    }
    return 0;
}

static bool apply_top_op(Stack& vals, Stack& ops) {
    if (stack_is_empty(ops)) {
        return false;
    }
    string op = Stack_pop(ops);
    if (op == "(") {
        return false;
    }
    if (stack_is_empty(vals)) {
        return false;
    }
    long long b = stoll(Stack_pop(vals));
    if (stack_is_empty(vals)) {
        return false;
    }
    long long a = stoll(Stack_pop(vals));
    long long res = 0;
    if (op == "+") {
        res = a + b;
    } else if (op == "-") {
        res = a - b;
    } else if (op == "*") {
        res = a * b;
    } else {
        return false;
    }
    Stack_push_back(vals, to_string(res));
    return true;
}

bool evaluate_expression(const string& expr, long long& result) {
    size_t n = expr.size();
    if (n == 0) {
        return false;
    }

    bool inside_num = false;
    bool had_space_after_num = false;
    for (size_t i = 0; i < n; i++) {
        char c = expr[i];
        if (isdigit(static_cast<unsigned char>(c))) {
            if (had_space_after_num) {
                return false;
            }
            inside_num = true;
        } else if (isspace(static_cast<unsigned char>(c))) {
            if (inside_num) {
                had_space_after_num = true;
                inside_num = false;
            }
        } else {
            inside_num = false;
            had_space_after_num = false;
        }
    }

    Stack vals = Stack_create();
    Stack ops = Stack_create();

    bool expect_operand = true;
    size_t i = 0;
    bool has_token = false;

    while (i < n) {
        char c = expr[i];
        if (isspace(static_cast<unsigned char>(c))) {
            i++;
            continue;
        }

        if (isdigit(static_cast<unsigned char>(c))) {
            if (!expect_operand) {
                Stack_destroy(vals);
                Stack_destroy(ops);
                return false;
            }
            string num_str;
            while (i < n && isdigit(static_cast<unsigned char>(expr[i]))) {
                num_str.push_back(expr[i]);
                i++;
            }
            Stack_push_back(vals, num_str);
            expect_operand = false;
            has_token = true;
            continue;
        }

        if (c == '(') {
            if (!expect_operand) {
                Stack_destroy(vals);
                Stack_destroy(ops);
                return false;
            }
            Stack_push_back(ops, "(");
            expect_operand = true;
            has_token = true;
            i++;
            continue;
        }

        if (c == ')') {
            if (expect_operand) {
                Stack_destroy(vals);
                Stack_destroy(ops);
                return false;
            }
            while (!stack_is_empty(ops) && stack_peek(ops) != "(") {
                if (!apply_top_op(vals, ops)) {
                    Stack_destroy(vals);
                    Stack_destroy(ops);
                    return false;
                }
            }
            if (stack_is_empty(ops) || stack_peek(ops) != "(") {
                Stack_destroy(vals);
                Stack_destroy(ops);
                return false;
            }
            Stack_pop(ops);
            expect_operand = false;
            i++;
            continue;
        }

        if (c == '+' || c == '-' || c == '*') {
            if (c == '-' && expect_operand) {
                Stack_push_back(vals, "0");
                Stack_push_back(ops, "-");
                expect_operand = true;
                has_token = true;
                i++;
                continue;
            }

            if (expect_operand) {
                Stack_destroy(vals);
                Stack_destroy(ops);
                return false;
            }

            string curr_op(1, c);
            while (!stack_is_empty(ops) && get_precedence(stack_peek(ops)) >= get_precedence(curr_op)) {
                if (!apply_top_op(vals, ops)) {
                    Stack_destroy(vals);
                    Stack_destroy(ops);
                    return false;
                }
            }
            Stack_push_back(ops, curr_op);
            expect_operand = true;
            has_token = true;
            i++;
            continue;
        }

        Stack_destroy(vals);
        Stack_destroy(ops);
        return false;
    }

    if (!has_token || expect_operand) {
        Stack_destroy(vals);
        Stack_destroy(ops);
        return false;
    }

    while (!stack_is_empty(ops)) {
        if (stack_peek(ops) == "(") {
            Stack_destroy(vals);
            Stack_destroy(ops);
            return false;
        }
        if (!apply_top_op(vals, ops)) {
            Stack_destroy(vals);
            Stack_destroy(ops);
            return false;
        }
    }

    if (stack_is_empty(vals)) {
        Stack_destroy(vals);
        Stack_destroy(ops);
        return false;
    }

    result = stoll(Stack_pop(vals));
    bool ok = stack_is_empty(vals);

    Stack_destroy(vals);
    Stack_destroy(ops);
    return ok;
}

void run_task1() {
    cout << "Введите арифметическое выражение: ";
    string expr;
    cin.ignore();
    getline(cin, expr);
    long long result = 0;
    if (evaluate_expression(expr, result)) {
        cout << "Результат: " << result << endl;
    } else {
        cout << "Ошибка в выражении" << endl;
    }
}