package tasks

import (
	"bufio"
	"fmt"
	"strings"

	"laba2/str"
)

// countGenomeSimilarity counts how many 2-char substrings of first appear in second.
func countGenomeSimilarity(first, second string) int {
	if len(second) < 2 || len(first) < 2 {
		return 0
	}

	secondSet := str.NewSet(16)
	for i := 0; i+1 < len(second); i++ {
		secondSet.Add(second[i : i+2])
	}

	count := 0
	for i := 0; i+1 < len(first); i++ {
		if secondSet.Has(first[i : i+2]) {
			count++
		}
	}
	return count
}

// RunTask3 reads two genome strings and prints the similarity count.
func RunTask3(reader *bufio.Reader) {
	fmt.Print("Введите первый геном: ")
	first, _ := reader.ReadString('\n')
	first = strings.TrimRight(first, "\r\n ")

	fmt.Print("Введите второй геном: ")
	second, _ := reader.ReadString('\n')
	second = strings.TrimRight(second, "\r\n ")

	count := countGenomeSimilarity(first, second)
	fmt.Println(count)
}

