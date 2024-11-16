package queue

import (
	"dst/dst/dlist"
	"errors"
)

var (
	ErrEmptyQueue = errors.New("empty queue")
)

type Queue struct {
	list dlist.DList
}

func (q *Queue) Len() int {
	return q.list.Len()
}

func (q *Queue) Push(value int) {
	q.list.PushBack(value)
}

func (q *Queue) Pop() (int, error) {
	if q.list.Len() == 0 {
		var zero int
		return zero, ErrEmptyQueue
	}
	value, _ := q.list.Get(0)
	q.list.RemoveForward()
	return value, nil
}

func (q *Queue) SerializeBinary(filename string) error {
	return q.list.SerializeBinary(filename)
}

func (q *Queue) DeserializeBinary(filename string) error {
	return q.list.DeserializeBinary(filename)
}

func (q *Queue) Serialize(filename string) error {
	return q.list.Serialize(filename)
}

func (q *Queue) Deserialize(filename string) error {
	return q.list.Deserialize(filename)
}
