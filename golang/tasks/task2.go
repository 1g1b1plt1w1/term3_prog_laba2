package tasks

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"laba2/str"
)

// Ensure os is used (for os.Open, os.Create)
var _ = os.Open

// --- In-memory state ---

var (
	llists    = map[string]str.LinkedList{}
	onellists = map[string]str.OneLinkedList{}
	arrays    = map[string]str.Array{}
	queues    = map[string]str.Queue{}
	stacks    = map[string]str.Stack{}
	trees     = map[string]str.Tree{}
	sets      = map[string]str.Set{}
)

// --- File I/O ---

func readFile(filename string) {
	// Reset state
	llists = map[string]str.LinkedList{}
	onellists = map[string]str.OneLinkedList{}
	arrays = map[string]str.Array{}
	queues = map[string]str.Queue{}
	stacks = map[string]str.Stack{}
	trees = map[string]str.Tree{}
	sets = map[string]str.Set{}

	f, err := os.Open(filename)
	if err != nil {
		return // file may not exist yet
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		line := scanner.Text()
		fields := strings.Fields(line)
		if len(fields) < 2 {
			continue
		}
		datatype := fields[0]
		name := fields[1]
		values := fields[2:]

		switch datatype {
		case "Array":
			arr := str.NewArray(16)
			for _, v := range values {
				arr.PushBack(v)
			}
			arrays[name] = arr
		case "OneLinkedList":
			ol := str.NewOneLinkedList()
			for _, v := range values {
				ol.PushBack(v)
			}
			onellists[name] = ol
		case "LinkedList":
			ll := str.NewLinkedList()
			for _, v := range values {
				ll.PushBack(v)
			}
			llists[name] = ll
		case "Queue":
			q := str.NewQueue()
			for _, v := range values {
				q.PushBack(v)
			}
			queues[name] = q
		case "Stack":
			s := str.NewStack()
			for _, v := range values {
				s.PushBack(v)
			}
			stacks[name] = s
		case "Tree":
			t := str.NewTree()
			for _, v := range values {
				n, err := strconv.Atoi(v)
				if err == nil {
					t.Insert(n)
				}
			}
			trees[name] = t
		case "Set":
			s := str.NewSet(16)
			for _, v := range values {
				s.Add(v)
			}
			sets[name] = s
		}
	}
}

func writeFile(filename string) error {
	f, err := os.Create(filename)
	if err != nil {
		return fmt.Errorf("не удалось открыть файл при записи: %w", err)
	}
	defer f.Close()

	w := bufio.NewWriter(f)

	for name, obj := range arrays {
		fmt.Fprintf(w, "Array %s%s\n", name, obj.Read())
	}
	for name, obj := range onellists {
		fmt.Fprintf(w, "OneLinkedList %s%s\n", name, obj.ReadHT())
	}
	for name, obj := range llists {
		fmt.Fprintf(w, "LinkedList %s%s\n", name, obj.ReadHT())
	}
	for name, obj := range queues {
		fmt.Fprintf(w, "Queue %s%s\n", name, obj.Read())
	}
	for name, obj := range stacks {
		fmt.Fprintf(w, "Stack %s%s\n", name, obj.Read())
	}
	for name, obj := range trees {
		fmt.Fprintf(w, "Tree %s%s\n", name, obj.Read())
	}
	for name, obj := range sets {
		keys := obj.Keys()
		fmt.Fprintf(w, "Set %s", name)
		for _, k := range keys {
			fmt.Fprintf(w, " %s", k)
		}
		fmt.Fprintln(w)
	}

	return w.Flush()
}

// --- Command dispatch ---

type command int

const (
	cmdPrint command = iota

	cmdMCreate
	cmdMPush
	cmdMPushIdx
	cmdMGet
	cmdMDelIdx
	cmdMSetIdx
	cmdMLength
	cmdMRead

	cmdFPush
	cmdFPushHead
	cmdFPushBefore
	cmdFPushAfter
	cmdFPop
	cmdFPopHead
	cmdFPopBefore
	cmdFPopAfter
	cmdFDelVal
	cmdFFindVal
	cmdFReadHT
	cmdFReadTH

	cmdLPushHead
	cmdLPush
	cmdLPushBefore
	cmdLPushAfter
	cmdLPopHead
	cmdLPop
	cmdLPopBefore
	cmdLPopAfter
	cmdLDelVal
	cmdLFindVal
	cmdLReadHT
	cmdLReadTH

	cmdSPush
	cmdSPop
	cmdSRead

	cmdQPush
	cmdQPop
	cmdQRead

	cmdTInsert
	cmdIsMember
	cmdTDelete
	cmdTRead

	cmdSetAdd
	cmdSetDel
	cmdSetAt
)

var commandMap = map[string]command{
	"PRINT": cmdPrint,

	"MCREATE":  cmdMCreate,
	"MPUSH":    cmdMPush,
	"MPUSHIDX": cmdMPushIdx,
	"MGET":     cmdMGet,
	"MDELIDX":  cmdMDelIdx,
	"MSETIDX":  cmdMSetIdx,
	"MLENGTH":  cmdMLength,
	"MREAD":    cmdMRead,

	"FPUSH":       cmdFPush,
	"FPUSHHEAD":   cmdFPushHead,
	"FPUSHBEFORE": cmdFPushBefore,
	"FPUSHAFTER":  cmdFPushAfter,
	"FPOP":        cmdFPop,
	"FPOPHEAD":    cmdFPopHead,
	"FPOPBEFORE":  cmdFPopBefore,
	"FPOPAFTER":   cmdFPopAfter,
	"FDELVAL":     cmdFDelVal,
	"FFINDVAL":    cmdFFindVal,
	"FREADHT":     cmdFReadHT,
	"FREADTH":     cmdFReadTH,

	"LPUSHHEAD":   cmdLPushHead,
	"LPUSH":       cmdLPush,
	"LPUSHBEFORE": cmdLPushBefore,
	"LPUSHAFTER":  cmdLPushAfter,
	"LPOPHEAD":    cmdLPopHead,
	"LPOP":        cmdLPop,
	"LPOPBEFORE":  cmdLPopBefore,
	"LPOPAFTER":   cmdLPopAfter,
	"LDELVAL":     cmdLDelVal,
	"LFINDVAL":    cmdLFindVal,
	"LREADHT":     cmdLReadHT,
	"LREADTH":     cmdLReadTH,

	"SPUSH": cmdSPush,
	"SPOP":  cmdSPop,
	"SREAD": cmdSRead,

	"QPUSH": cmdQPush,
	"QPOP":  cmdQPop,
	"QREAD": cmdQRead,

	"TINSERT":  cmdTInsert,
	"ISMEMBER": cmdIsMember,
	"TDELETE":  cmdTDelete,
	"TREAD":    cmdTRead,

	"SETADD": cmdSetAdd,
	"SETDEL": cmdSetDel,
	"SET_AT": cmdSetAt,
}

func makeChange(name string, data []string, cmd command) {
	switch cmd {
	case cmdMCreate:
		arrays[name] = str.NewArray(16)

	case cmdMPush:
		arr := arrays[name]
		for _, v := range data {
			arr.PushBack(v)
		}
		arrays[name] = arr

	case cmdMPushIdx:
		if len(data) >= 2 {
			idx, _ := strconv.Atoi(data[0])
			arr := arrays[name]
			arr.Insert(idx, data[1])
			arrays[name] = arr
		}

	case cmdMGet:
		if len(data) > 0 {
			idx, _ := strconv.Atoi(data[0])
			arr := arrays[name]
			v, ok := arr.Get(idx)
			if ok {
				fmt.Println(v)
			}
		}

	case cmdMDelIdx:
		if len(data) > 0 {
			idx, _ := strconv.Atoi(data[0])
			arr := arrays[name]
			arr.Erase(idx)
			arrays[name] = arr
		}

	case cmdMSetIdx:
		if len(data) >= 2 {
			idx, _ := strconv.Atoi(data[0])
			arr := arrays[name]
			arr.Set(idx, data[1])
			arrays[name] = arr
		}

	case cmdMLength:
		arr := arrays[name]
		fmt.Println("Length:", arr.Length())

	case cmdMRead:
		arr := arrays[name]
		fmt.Println(arr.Read())

	// OneLinkedList
	case cmdFPush:
		ol := onellists[name]
		for _, v := range data {
			ol.PushBack(v)
		}
		onellists[name] = ol

	case cmdFPushHead:
		ol := onellists[name]
		for _, v := range data {
			ol.PushFront(v)
		}
		onellists[name] = ol

	case cmdFPushBefore:
		if len(data) >= 2 {
			ol := onellists[name]
			ol.PushBefore(data[0], data[1])
			onellists[name] = ol
		}

	case cmdFPushAfter:
		if len(data) >= 2 {
			ol := onellists[name]
			ol.PushAfter(data[0], data[1])
			onellists[name] = ol
		}

	case cmdFPop:
		ol := onellists[name]
		v := ol.PopBack()
		onellists[name] = ol
		if v != "" {
			fmt.Println(v)
		}

	case cmdFPopHead:
		ol := onellists[name]
		v := ol.PopFront()
		onellists[name] = ol
		if v != "" {
			fmt.Println(v)
		}

	case cmdFPopAfter:
		if len(data) > 0 {
			ol := onellists[name]
			v := ol.PopAfter(data[0])
			onellists[name] = ol
			if v != "" {
				fmt.Println(v)
			}
		}

	case cmdFPopBefore:
		if len(data) > 0 {
			ol := onellists[name]
			v := ol.PopBefore(data[0])
			onellists[name] = ol
			if v != "" {
				fmt.Println(v)
			}
		}

	case cmdFDelVal:
		if len(data) > 0 {
			ol := onellists[name]
			ol.DelByValue(data[0])
			onellists[name] = ol
		}

	case cmdFFindVal:
		if len(data) > 0 {
			ol := onellists[name]
			fmt.Println(ol.FindByValue(data[0]))
		}

	case cmdFReadHT:
		ol := onellists[name]
		fmt.Println(ol.ReadHT())

	case cmdFReadTH:
		ol := onellists[name]
		fmt.Println(ol.ReadTH())

	// LinkedList
	case cmdLPushHead:
		ll := llists[name]
		for _, v := range data {
			ll.PushFront(v)
		}
		llists[name] = ll

	case cmdLPush:
		ll := llists[name]
		for _, v := range data {
			ll.PushBack(v)
		}
		llists[name] = ll

	case cmdLPushBefore:
		if len(data) >= 2 {
			ll := llists[name]
			ll.PushBefore(data[0], data[1])
			llists[name] = ll
		}

	case cmdLPushAfter:
		if len(data) >= 2 {
			ll := llists[name]
			ll.PushAfter(data[0], data[1])
			llists[name] = ll
		}

	case cmdLPopHead:
		ll := llists[name]
		v := ll.PopFront()
		llists[name] = ll
		if v != "" {
			fmt.Println(v)
		}

	case cmdLPop:
		ll := llists[name]
		v := ll.PopBack()
		llists[name] = ll
		if v != "" {
			fmt.Println(v)
		}

	case cmdLPopBefore:
		if len(data) > 0 {
			ll := llists[name]
			v := ll.PopBefore(data[0])
			llists[name] = ll
			if v != "" {
				fmt.Println(v)
			}
		}

	case cmdLPopAfter:
		if len(data) > 0 {
			ll := llists[name]
			v := ll.PopAfter(data[0])
			llists[name] = ll
			if v != "" {
				fmt.Println(v)
			}
		}

	case cmdLDelVal:
		if len(data) > 0 {
			ll := llists[name]
			ll.DelByValue(data[0])
			llists[name] = ll
		}

	case cmdLFindVal:
		if len(data) > 0 {
			ll := llists[name]
			fmt.Println(ll.Find(data[0]))
		}

	case cmdLReadHT:
		ll := llists[name]
		fmt.Println(ll.ReadHT())

	case cmdLReadTH:
		ll := llists[name]
		fmt.Println(ll.ReadTH())

	// Stack
	case cmdSPush:
		s := stacks[name]
		for _, v := range data {
			s.PushBack(v)
		}
		stacks[name] = s

	case cmdSPop:
		s := stacks[name]
		v := s.Pop()
		stacks[name] = s
		if v != "" {
			fmt.Println(v)
		}

	case cmdSRead:
		s := stacks[name]
		fmt.Println(s.Read())

	// Queue
	case cmdQPush:
		q := queues[name]
		for _, v := range data {
			q.PushBack(v)
		}
		queues[name] = q

	case cmdQPop:
		q := queues[name]
		v := q.Pop()
		queues[name] = q
		if v != "" {
			fmt.Println(v)
		}

	case cmdQRead:
		q := queues[name]
		fmt.Println(q.Read())

	// Tree
	case cmdTInsert:
		t := trees[name]
		for _, v := range data {
			n, err := strconv.Atoi(v)
			if err == nil {
				t.Insert(n)
			}
		}
		trees[name] = t

	case cmdTDelete:
		if len(data) > 0 {
			t := trees[name]
			n, err := strconv.Atoi(data[0])
			if err == nil {
				t.Delete(n)
			}
			trees[name] = t
		}

	case cmdTRead:
		t := trees[name]
		fmt.Println(t.Read())

	case cmdIsMember:
		if len(data) > 0 {
			t := trees[name]
			n, err := strconv.Atoi(data[0])
			if err == nil {
				if t.IsMember(n) {
					fmt.Println("TRUE")
				} else {
					fmt.Println("FALSE")
				}
			}
		}

	// Set
	case cmdSetAdd:
		s, ok := sets[name]
		if !ok {
			s = str.NewSet(16)
		}
		for _, v := range data {
			s.Add(v)
		}
		sets[name] = s

	case cmdSetDel:
		if s, ok := sets[name]; ok {
			for _, v := range data {
				s.Del(v)
			}
			sets[name] = s
		}

	case cmdSetAt:
		if len(data) > 0 {
			s, ok := sets[name]
			if ok && s.Has(data[0]) {
				fmt.Println("true")
			} else {
				fmt.Println("false")
			}
		}

	case cmdPrint:
		fmt.Println("=== PRINT ===")
		if arr, ok := arrays[name]; ok {
			fmt.Printf("Array %s:%s\n", name, arr.Read())
			return
		}
		if ol, ok := onellists[name]; ok {
			fmt.Printf("OneLinkedList %s (Head→Tail):%s\n", name, ol.ReadHT())
			fmt.Printf("OneLinkedList %s (Tail→Head):%s\n", name, ol.ReadTH())
			return
		}
		if ll, ok := llists[name]; ok {
			fmt.Printf("LinkedList %s (Head→Tail):%s\n", name, ll.ReadHT())
			fmt.Printf("LinkedList %s (Tail→Head):%s\n", name, ll.ReadTH())
			return
		}
		if q, ok := queues[name]; ok {
			fmt.Printf("Queue %s:%s\n", name, q.Read())
			return
		}
		if s, ok := stacks[name]; ok {
			fmt.Printf("Stack %s:%s\n", name, s.Read())
			return
		}
		if t, ok := trees[name]; ok {
			t.Print()
			return
		}
		if s, ok := sets[name]; ok {
			keys := s.Keys()
			fmt.Printf("Set %s: {", name)
			for i, k := range keys {
				if i > 0 {
					fmt.Print(", ")
				}
				fmt.Print(k)
			}
			fmt.Println("}")
			return
		}
		fmt.Printf("Объект \"%s\" не найден.\n", name)

	default:
		fmt.Println("Неизвестная команда.")
	}
}

// Parsing reads the file, executes the query, and writes the file back.
func Parsing(filename, query string) error {
	readFile(filename)

	fields := strings.Fields(query)
	if len(fields) == 0 {
		return fmt.Errorf("пустой запрос")
	}
	cmdStr := fields[0]
	cmd, ok := commandMap[cmdStr]
	if !ok {
		return fmt.Errorf("неизвестная команда: %s", cmdStr)
	}
	name := ""
	if len(fields) > 1 {
		name = fields[1]
	}
	data := []string{}
	if len(fields) > 2 {
		data = fields[2:]
	}

	makeChange(name, data, cmd)

	return writeFile(filename)
}

// RunTask2 is the interactive mode: asks for filename and query.
func RunTask2(reader *bufio.Reader) {
	fmt.Println("Task 2 (Set ADT)")
	fmt.Print("Enter filename: ")
	filenameLine, _ := reader.ReadString('\n')
	filename := strings.TrimSpace(filenameLine)
	fmt.Print("Enter query (e.g. SETADD myset val1, SETDEL myset val1, SET_AT myset val1, PRINT myset):\n> ")
	queryLine, _ := reader.ReadString('\n')
	query := strings.TrimSpace(queryLine)
	if err := Parsing(filename, query); err != nil {
		fmt.Println(err)
	}
}
