package tasks

import (
	"bufio"
	"fmt"
	"strconv"
	"strings"

	"laba2/str"
)

func getPrecedence(op string) int {
	switch op {
	case "+", "-":
		return 1
	case "*":
		return 2
	}
	return 0
}

func stackPeek(s *str.Stack) string {
	if s.List.Tail == nil {
		return ""
	}
	return s.List.Tail.Data
}

func stackIsEmpty(s *str.Stack) bool {
	return s.List.Head == nil
}

func applyTopOp(vals *str.Stack, ops *str.Stack) bool {
	if stackIsEmpty(ops) {
		return false
	}
	op := ops.Pop()
	if op == "(" {
		return false
	}
	if stackIsEmpty(vals) {
		return false
	}
	bStr := vals.Pop()
	if stackIsEmpty(vals) {
		return false
	}
	aStr := vals.Pop()
	b, err1 := strconv.ParseInt(bStr, 10, 64)
	a, err2 := strconv.ParseInt(aStr, 10, 64)
	if err1 != nil || err2 != nil {
		return false
	}
	var res int64
	switch op {
	case "+":
		res = a + b
	case "-":
		res = a - b
	case "*":
		res = a * b
	default:
		return false
	}
	vals.PushBack(strconv.FormatInt(res, 10))
	return true
}

// evaluateExpression parses and evaluates an arithmetic expression
// with +, -, *, parentheses using two stacks.
func evaluateExpression(expr string) (int64, bool) {
	n := len(expr)
	if n == 0 {
		return 0, false
	}

	// Validate: no space in the middle of a number
	insideNum := false
	hadSpaceAfterNum := false
	for i := 0; i < n; i++ {
		c := expr[i]
		if c >= '0' && c <= '9' {
			if hadSpaceAfterNum {
				return 0, false
			}
			insideNum = true
		} else if c == ' ' || c == '\t' {
			if insideNum {
				hadSpaceAfterNum = true
				insideNum = false
			}
		} else {
			insideNum = false
			hadSpaceAfterNum = false
		}
	}

	vals := str.NewStack()
	ops := str.NewStack()

	expectOperand := true
	hasToken := false
	i := 0

	for i < n {
		c := expr[i]
		if c == ' ' || c == '\t' {
			i++
			continue
		}
		if c >= '0' && c <= '9' {
			if !expectOperand {
				return 0, false
			}
			numStr := ""
			for i < n && expr[i] >= '0' && expr[i] <= '9' {
				numStr += string(expr[i])
				i++
			}
			vals.PushBack(numStr)
			expectOperand = false
			hasToken = true
			continue
		}
		if c == '(' {
			if !expectOperand {
				return 0, false
			}
			ops.PushBack("(")
			expectOperand = true
			hasToken = true
			i++
			continue
		}
		if c == ')' {
			if expectOperand {
				return 0, false
			}
			for !stackIsEmpty(&ops) && stackPeek(&ops) != "(" {
				if !applyTopOp(&vals, &ops) {
					return 0, false
				}
			}
			if stackIsEmpty(&ops) || stackPeek(&ops) != "(" {
				return 0, false
			}
			ops.Pop() // discard "("
			expectOperand = false
			i++
			continue
		}
		if c == '+' || c == '-' || c == '*' {
			if c == '-' && expectOperand {
				vals.PushBack("0")
				ops.PushBack("-")
				expectOperand = true
				hasToken = true
				i++
				continue
			}
			if expectOperand {
				return 0, false
			}
			currOp := string(c)
			for !stackIsEmpty(&ops) && getPrecedence(stackPeek(&ops)) >= getPrecedence(currOp) {
				if !applyTopOp(&vals, &ops) {
					return 0, false
				}
			}
			ops.PushBack(currOp)
			expectOperand = true
			hasToken = true
			i++
			continue
		}
		return 0, false
	}

	if !hasToken || expectOperand {
		return 0, false
	}

	for !stackIsEmpty(&ops) {
		if stackPeek(&ops) == "(" {
			return 0, false
		}
		if !applyTopOp(&vals, &ops) {
			return 0, false
		}
	}

	if stackIsEmpty(&vals) {
		return 0, false
	}
	resultStr := vals.Pop()
	if !stackIsEmpty(&vals) {
		return 0, false
	}
	result, err := strconv.ParseInt(resultStr, 10, 64)
	if err != nil {
		return 0, false
	}
	return result, true
}

// RunTask1 reads an arithmetic expression from the reader and evaluates it.
func RunTask1(reader *bufio.Reader) {
	fmt.Print("Введите арифметическое выражение: ")
	expr, _ := reader.ReadString('\n')
	expr = strings.TrimRight(expr, "\r\n")
	result, ok := evaluateExpression(expr)
	if ok {
		fmt.Println("Результат:", result)
	} else {
		fmt.Println("Ошибка в выражении")
	}
}

