package tasks

import (
	"bufio"
	"fmt"
	"strconv"
	"strings"

	"laba2/str"
)

// RunTask7 reads LRU cache capacity and Q queries (SET x y / GET x),
// prints GET results space-separated.
func RunTask7(reader *bufio.Reader) {
	fmt.Print("Введите емкость кэша (cap): ")
	capLine, _ := reader.ReadString('\n')
	cap, _ := strconv.Atoi(strings.TrimSpace(capLine))

	fmt.Print("Введите количество запросов (Q): ")
	qLine, _ := reader.ReadString('\n')
	Q, _ := strconv.Atoi(strings.TrimSpace(qLine))

	lru := str.NewLru(cap)
	step := 0

	fmt.Println("Введите запросы (SET x y / GET x):")

	firstOutput := true
	processed := 0
	for processed < Q {
		line, err := reader.ReadString('\n')
		line = strings.TrimRight(line, "\r\n")
		if line == "" {
			if err != nil {
				break
			}
			continue
		}
		tokens := strings.Fields(line)
		i := 0
		for i < len(tokens) && processed < Q {
			token := tokens[i]
			if token == "SET" && i+2 < len(tokens) {
				key := tokens[i+1]
				val := tokens[i+2]
				lru.Set(key, val, step)
				step++
				i += 3
				processed++
			} else if token == "GET" && i+1 < len(tokens) {
				key := tokens[i+1]
				result := lru.Get(key, step)
				step++
				if !firstOutput {
					fmt.Print(" ")
				}
				fmt.Print(result)
				firstOutput = false
				i += 2
				processed++
			} else {
				i++
			}
		}
		if err != nil {
			break
		}
	}
	if !firstOutput {
		fmt.Println()
	}
}

