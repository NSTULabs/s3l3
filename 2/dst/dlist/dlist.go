package dlist

import (
	"errors"

	"golang.org/x/exp/constraints"
)

var (
	ErrInvalidIndex = errors.New("invalid index")
	ErrEmptyList    = errors.New("list is empty")
)

type Node[T constraints.Ordered] struct {
	Value T
	Next  *Node[T]
	Prev  *Node[T]
}

type DList[T constraints.Ordered] struct {
	head *Node[T]
	tail *Node[T]
	len  int
}

func (l *DList[T]) Len() int {
	return l.len
}

func (l *DList[T]) Head() *Node[T] {
	return l.head
}

func (l *DList[T]) Tail() *Node[T] {
	return l.tail
}

func (l *DList[T]) PushForward(value T) {
	newNode := &Node[T]{
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

func (l *DList[T]) PushBack(value T) {
	newNode := &Node[T]{
		Value: value,
		Next:  nil,
		Prev:  l.tail, // устанавливаем Prev для нового узла
	}
	if l.len == 0 {
		l.head = newNode
	} else {
		l.tail.Next = newNode
	}
	l.tail = newNode
	l.len++
}

func (l *DList[T]) Get(index int) (T, error) {
	if index < 0 || index >= l.len {
		var zero T
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

func (l *DList[T]) RemoveForward() error {
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

func (l *DList[T]) RemoveBack() error {
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

func (l *DList[T]) RemoveValue(value T) error {
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

func (l *DList[T]) Find(value T) *Node[T] {
	current := l.head
	for current != nil {
		if current.Value == value {
			return current
		}
		current = current.Next
	}
	return nil
}
