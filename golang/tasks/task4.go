package tasks

import (
	"bufio"
	"fmt"
	"strconv"
	"strings"

	"laba2/str"
)

func countCapitals(s string) int {
	cnt := 0
	for _, c := range s {
		if c >= 'A' && c <= 'Z' {
			cnt++
		}
	}
	return cnt
}

func toLowerCaseStr(s string) string {
	var sb strings.Builder
	for _, c := range s {
		if c >= 'A' && c <= 'Z' {
			sb.WriteRune(c - 'A' + 'a')
		} else {
			sb.WriteRune(c)
		}
	}
	return sb.String()
}

// countStressErrors counts words in text with incorrect stress marking.
func countStressErrors(dict str.Array, text string) int {
	words := strings.Fields(text)
	errors := 0

	for _, word := range words {
		lowerWord := toLowerCaseStr(word)
		inDict := false
		exactMatch := false

		for i := 0; i < dict.Length(); i++ {
			dictWord, ok := dict.Get(i)
			if !ok {
				continue
			}
			if toLowerCaseStr(dictWord) == lowerWord {
				inDict = true
				if dictWord == word {
					exactMatch = true
					break
				}
			}
		}

		if inDict {
			if !exactMatch {
				errors++
			}
		} else {
			if countCapitals(word) != 1 {
				errors++
			}
		}
	}
	return errors
}

// RunTask4 reads a dictionary and sentence, then prints the error count.
func RunTask4(reader *bufio.Reader) {
	fmt.Print("Введите количество слов в словаре: ")
	line, _ := reader.ReadString('\n')
	line = strings.TrimSpace(line)
	dictQuantity, _ := strconv.Atoi(line)

	dict := str.NewArray(16)
	remaining := dictQuantity
	for remaining > 0 {
		wline, _ := reader.ReadString('\n')
		wline = strings.TrimSpace(wline)
		words := strings.Fields(wline)
		for _, w := range words {
			if remaining <= 0 {
				break
			}
			dict.PushBack(w)
			remaining--
		}
	}

	fmt.Print("Введите предложение: ")
	sentence, _ := reader.ReadString('\n')
	sentence = strings.TrimRight(sentence, "\r\n")

	errors := countStressErrors(dict, sentence)
	fmt.Println(errors)
}

