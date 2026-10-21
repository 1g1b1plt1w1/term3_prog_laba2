package tasks

import (
	"bufio"
	"fmt"
	"strconv"
	"strings"

	"laba2/str"
)

// checkAVLNode recursively checks that all nodes have balance in [-1, 1].
func checkAVLNode(node *str.TreeNode) bool {
	if node == nil {
		return true
	}
	bal := str.GetBalanceNode(node)
	if bal < -1 || bal > 1 {
		return false
	}
	return checkAVLNode(node.Left) && checkAVLNode(node.Right)
}

// checkAVL checks that the whole tree is a valid AVL tree.
func checkAVL(t *str.Tree) bool {
	return checkAVLNode(t.TreeRoot())
}

// RunTask5 reads numbers until 0, inserts them into an AVL tree, and prints YES/NO.
func RunTask5(reader *bufio.Reader) {
	fmt.Print("Введите последовательность чисел, оканчивающуюся нулем: ")
	t := str.NewTree()
	for {
		line, err := reader.ReadString('\n')
		line = strings.TrimSpace(line)
		tokens := strings.Fields(line)
		done := false
		for _, tok := range tokens {
			val, e := strconv.Atoi(tok)
			if e != nil {
				continue
			}
			if val == 0 {
				done = true
				break
			}
			t.Insert(val)
		}
		if done || err != nil {
			break
		}
	}
	if checkAVL(&t) {
		fmt.Println("YES")
	} else {
		fmt.Println("NO")
	}
}

