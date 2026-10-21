package str

import (
	"fmt"
	"strings"
)

// TreeNode is a node in an AVL tree.
type TreeNode struct {
	Data   int
	Height int
	Left   *TreeNode
	Right  *TreeNode
}

// Tree is an AVL tree.
type Tree struct {
	Root *TreeNode
}

// NewTree creates an empty Tree.
func NewTree() Tree {
	return Tree{}
}

func getHeight(n *TreeNode) int {
	if n == nil {
		return 0
	}
	return n.Height
}

func updateHeight(n *TreeNode) {
	if n != nil {
		lh := getHeight(n.Left)
		rh := getHeight(n.Right)
		if lh > rh {
			n.Height = 1 + lh
		} else {
			n.Height = 1 + rh
		}
	}
}

func getBalance(n *TreeNode) int {
	if n == nil {
		return 0
	}
	return getHeight(n.Left) - getHeight(n.Right)
}

func leftRotate(n *TreeNode) *TreeNode {
	r := n.Right
	rl := r.Left
	r.Left = n
	n.Right = rl
	updateHeight(n)
	updateHeight(r)
	return r
}

func rightRotate(n *TreeNode) *TreeNode {
	l := n.Left
	lr := l.Right
	l.Right = n
	n.Left = lr
	updateHeight(n)
	updateHeight(l)
	return l
}

func makeBalance(n *TreeNode) *TreeNode {
	bal := getBalance(n)
	if bal < -1 && getBalance(n.Right) <= 0 {
		return leftRotate(n)
	}
	if bal > 1 && getBalance(n.Left) >= 0 {
		return rightRotate(n)
	}
	if bal < -1 && getBalance(n.Right) > 0 {
		n.Right = rightRotate(n.Right)
		return leftRotate(n)
	}
	if bal > 1 && getBalance(n.Left) < 0 {
		n.Left = leftRotate(n.Left)
		return rightRotate(n)
	}
	return n
}

func insertNode(n *TreeNode, data int) *TreeNode {
	if n == nil {
		return &TreeNode{Data: data, Height: 1}
	}
	if data > n.Data {
		n.Right = insertNode(n.Right, data)
	} else if data < n.Data {
		n.Left = insertNode(n.Left, data)
	} else {
		return n
	}
	updateHeight(n)
	return makeBalance(n)
}

// Insert inserts data into the AVL tree.
func (t *Tree) Insert(data int) {
	t.Root = insertNode(t.Root, data)
}

func findMax(n *TreeNode) *TreeNode {
	for n != nil && n.Right != nil {
		n = n.Right
	}
	return n
}

func deleteNode(n *TreeNode, data int) *TreeNode {
	if n == nil {
		return nil
	}
	if data < n.Data {
		n.Left = deleteNode(n.Left, data)
	} else if data > n.Data {
		n.Right = deleteNode(n.Right, data)
	} else {
		if n.Left == nil && n.Right == nil {
			return nil
		} else if n.Left == nil {
			return n.Right
		} else if n.Right == nil {
			return n.Left
		}
		temp := findMax(n.Left)
		n.Data = temp.Data
		n.Left = deleteNode(n.Left, temp.Data)
	}
	updateHeight(n)
	return makeBalance(n)
}

// Delete removes data from the AVL tree.
func (t *Tree) Delete(data int) {
	t.Root = deleteNode(t.Root, data)
}

// IsMember returns true if data is in the tree.
func (t *Tree) IsMember(data int) bool {
	cur := t.Root
	for cur != nil {
		if cur.Data == data {
			return true
		} else if data < cur.Data {
			cur = cur.Left
		} else {
			cur = cur.Right
		}
	}
	return false
}

func readNode(n *TreeNode, sb *strings.Builder) {
	if n == nil {
		return
	}
	readNode(n.Left, sb)
	sb.WriteString(" ")
	fmt.Fprintf(sb, "%d", n.Data)
	readNode(n.Right, sb)
}

// Read returns in-order traversal as a space-separated string.
func (t *Tree) Read() string {
	if t.Root == nil {
		return ""
	}
	var sb strings.Builder
	readNode(t.Root, &sb)
	return sb.String()
}

func getLevelNodes(node *TreeNode, targetDepth, currentDepth int, path string, sb *strings.Builder) {
	if node == nil {
		return
	}
	if currentDepth == targetDepth {
		fmt.Fprintf(sb, "%s = %d\n", path, node.Data)
		return
	}
	getLevelNodes(node.Left, targetDepth, currentDepth+1, path+"->left", sb)
	getLevelNodes(node.Right, targetDepth, currentDepth+1, path+"->right", sb)
}

// Print prints the tree level by level with paths from root.
func (t *Tree) Print() {
	if t.Root == nil {
		return
	}
	var sb strings.Builder
	for d := 0; d < t.Root.Height; d++ {
		getLevelNodes(t.Root, d, 0, "root", &sb)
	}
	fmt.Print(sb.String())
}

// GetBalance returns the balance factor of the root.
func (t *Tree) GetBalance() int {
	return getBalance(t.Root)
}

// GetBalanceNode returns the balance factor of a given node (exported for task5).
func GetBalanceNode(n *TreeNode) int {
	return getBalance(n)
}

// TreeRoot returns the root node (for traversal in task5).
func (t *Tree) TreeRoot() *TreeNode {
	return t.Root
}

