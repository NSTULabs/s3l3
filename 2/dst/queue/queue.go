package queue

import (
	"dst/dst/dlist"
	"errors"

	"golang.org/x/exp/constraints"
)

var (
	ErrEmptyQueue = errors.New("empty queue")
)

type Queue[T constraints.Ordered] struct {
	list dlist.DList[T]
}

func (q *Queue[T]) Len() int {
	return q.list.Len()
}

func (q *Queue[T]) Push(value T) {
	q.list.PushBack(value)
}

func (q *Queue[T]) Pop() (T, error) {
	if q.list.Len() == 0 {
		var zero T
		return zero, ErrEmptyQueue
	}
	value, _ := q.list.Get(0)
	q.list.RemoveForward()
	return value, nil
}
