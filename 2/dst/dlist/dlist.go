package dlist

import (
	"dst/dst"
	"encoding/binary"
	"errors"
	"io"
	"os"
	"strconv"
	"strings"
)

var (
	ErrInvalidIndex = errors.New("invalid index")
	ErrEmptyList    = errors.New("list is empty")
)

type Node struct {
	Value int
	Next  *Node
	Prev  *Node
}

type DList struct {
	head *Node
	tail *Node
	len  int
}

func (l *DList) Len() int {
	return l.len
}

func (l *DList) Head() *Node {
	return l.head
}

func (l *DList) Tail() *Node {
	return l.tail
}

func (l *DList) PushForward(value int) {
	newNode := &Node{
		Value: value,
		Next:  l.head,
		Prev:  nil,
	}
	if l.len == 0 {
		l.tail = newNode
	} else {
		l.head.Prev = newNode
	}
	l.head = newNode
	l.len++
}

func (l *DList) PushBack(value int) {
	newNode := &Node{
		Value: value,
		Next:  nil,
		Prev:  l.tail,
	}
	if l.len == 0 {
		l.head = newNode
	} else {
		l.tail.Next = newNode
	}
	l.tail = newNode
	l.len++
}

func (l *DList) Get(index int) (int, error) {
	if index < 0 || index >= l.len {
		var zero int
		return zero, ErrInvalidIndex
	}

	current := l.head
	c := 0
	for c != index {
		current = current.Next
		c++
	}
	return current.Value, nil
}

func (l *DList) RemoveForward() error {
	if l.head == nil {
		return ErrEmptyList
	}

	if l.head == l.tail {
		l.head = nil
		l.tail = nil
	} else {
		l.head = l.head.Next
		l.head.Prev = nil
	}
	l.len--

	return nil
}

func (l *DList) RemoveBack() error {
	if l.head == nil {
		return ErrEmptyList
	}

	if l.head == l.tail {
		l.head = nil
		l.tail = nil
	} else {
		l.tail = l.tail.Prev
		if l.tail != nil {
			l.tail.Next = nil
		}
	}
	l.len--

	return nil
}

func (l *DList) RemoveValue(value int) error {
	if l.head == nil {
		return ErrEmptyList
	}

	current := l.head
	for current != nil {
		if current.Value == value {
			if current == l.head {
				l.head = current.Next
				if l.head != nil {
					l.head.Prev = nil
				} else {
					l.tail = nil
				}
			} else if current == l.tail {
				l.tail = current.Prev
				l.tail.Next = nil
			} else {
				current.Prev.Next = current.Next
				current.Next.Prev = current.Prev
			}
			l.len--
		}
		current = current.Next
	}

	return nil
}

func (l *DList) Find(value int) *Node {
	current := l.head
	for current != nil {
		if current.Value == value {
			return current
		}
		current = current.Next
	}
	return nil
}

func (l *DList) SerializeBinary(filename string) error {
	file, err := os.OpenFile(filename, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0744)
	if err != nil {
		return dst.ErrOpenFile
	}
	defer file.Close()

	err = binary.Write(file, binary.LittleEndian, int32(l.len))
	if err != nil {
		return dst.ErrWrite
	}

	current := l.head
	for current != nil {
		binary.Write(file, binary.LittleEndian, int32(current.Value))
		current = current.Next
	}

	return nil
}

func (l *DList) DeserializeBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return dst.ErrOpenFile
	}
	defer file.Close()

	var desLen int32
	err = binary.Read(file, binary.LittleEndian, &desLen)
	if err != nil {
		return dst.ErrRead
	}

	for {
		var value int32
		err = binary.Read(file, binary.LittleEndian, &value)
		if err == io.EOF {
			break
		}
		if err != nil {
			return dst.ErrRead
		}
		l.PushBack(int(value))
	}

	return nil
}

func (l *DList) Serialize(filename string) error {
	file, err := os.OpenFile(filename, os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0744)
	if err != nil {
		return dst.ErrOpenFile
	}
	defer file.Close()

	current := l.head
	if current == nil {
		return nil
	}

	for current.Next != nil {
		_, err := file.Write([]byte(strconv.Itoa(current.Value) + " "))
		if err != nil {
			return dst.ErrWrite
		}
		current = current.Next
	}
	_, err = file.Write([]byte(strconv.Itoa(current.Value)))
	if err != nil {
		return dst.ErrWrite
	}

	return nil
}

func (l *DList) Deserialize(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return dst.ErrOpenFile
	}
	defer file.Close()

	fileData, err := io.ReadAll(file)
	if err != nil {
		return dst.ErrRead
	}
	if err == io.EOF {
		return nil
	}
	numbers := strings.Split(string(fileData), " ")
	for _, number := range numbers {
		value, err := strconv.Atoi(number)
		if err != nil {
			return dst.ErrIntDeselialize
		}
		l.PushBack(value)
	}

	return nil
}
