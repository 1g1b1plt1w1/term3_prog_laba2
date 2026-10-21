package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	"laba2/tasks"
)

// sharedReader is used by the interactive menu AND passed to tasks
// that need line-by-line input. Using fmt.Scan* alongside bufio.Reader
// on the same os.Stdin is safe because both ultimately read from the
// same underlying fd; we just avoid mixing buffered readers.
var sharedReader = bufio.NewReader(os.Stdin)

func runInteractive() {
	fmt.Print("Введите задание (1, 3, 4, 5, 7 или 0 для выхода): ")
	for {
		line, _ := sharedReader.ReadString('\n')
		line = strings.TrimSpace(line)
		choice, err := strconv.Atoi(line)
		if err != nil || choice == 0 {
			break
		}
		switch choice {
		case 1:
			tasks.RunTask1(sharedReader)
		case 3:
			tasks.RunTask3(sharedReader)
		case 4:
			tasks.RunTask4(sharedReader)
		case 5:
			tasks.RunTask5(sharedReader)
		case 7:
			tasks.RunTask7(sharedReader)
		default:
			fmt.Println("Неизвестное задание.")
		}
		fmt.Print("\nВведите задание (1, 3, 4, 5, 7 или 0 для выхода): ")
	}
}

func main() {
	if len(os.Args) == 1 {
		runInteractive()
		return
	}
	// --file <filename> --query <query> mode
	var filename, query string
	for i := 1; i < len(os.Args); i++ {
		if os.Args[i] == "--file" && i+1 < len(os.Args) {
			filename = os.Args[i+1]
			i++
		} else if os.Args[i] == "--query" && i+1 < len(os.Args) {
			query = os.Args[i+1]
			i++
		}
	}
	if filename != "" && query != "" {
		if err := tasks.Parsing(filename, query); err != nil {
			fmt.Println(err)
		}
	}
}

