package tests

import (
	"dst/dst/queue"
	"testing"

	"github.com/stretchr/testify/require"
)

func TestQueue(t *testing.T) {
	var dst queue.Queue[int]
	for i := 0; i < 10; i++ {
		dst.Push(i)
	}
	require.Equal(t, 10, dst.Len())
	for i := 0; i < 10; i++ {
		value, err := dst.Pop()
		require.NoError(t, err)
		require.Equal(t, i, value)
	}
	require.Equal(t, 0, dst.Len())
}

func TestEmpty(t *testing.T) {
	var dst queue.Queue[int]
	value, err := dst.Pop()
	require.Equal(t, 0, value)
	require.ErrorIs(t, queue.ErrEmptyQueue, err)
	require.Equal(t, 0, dst.Len())
}

func BenchmarkPush(b *testing.B) {
	cases := []struct {
		name  string
		count int
	}{
		{"Count100", 100},
		{"Count10000", 10000},
		{"Count1000000", 1000000},
	}
	for i := 0; i < b.N; i += 1 {
		for _, c := range cases {
			b.Run(c.name, func(bb *testing.B) {
				for i := 0; i < b.N; i++ {
					dst := queue.Queue[int]{}
					for j := 0; j < c.count; j++ {
						dst.Push(j)
					}
				}
			})
		}
	}
}
