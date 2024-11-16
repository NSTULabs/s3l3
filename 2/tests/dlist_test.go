package tests

import (
	"dst/dst/dlist"
	"testing"

	"github.com/stretchr/testify/require"
)

func TestDList_PushBack_Get_RemoveBack(t *testing.T) {
	var list dlist.DList[int]

	for i := 0; i < 10; i++ {
		list.PushBack(i)
	}
	require.Equal(t, 10, list.Len())
	require.Equal(t, 0, list.Head().Value)
	require.Equal(t, 9, list.Tail().Value)
	err := list.RemoveBack()
	require.Equal(t, 9, list.Len())
	require.NoError(t, err)
	for i := 0; i < 9; i++ {
		value, err := list.Get(i)
		require.NoError(t, err)
		require.Equal(t, i, value)
	}
	value, err := list.Get(10)
	require.Equal(t, 0, value)
	require.ErrorIs(t, dlist.ErrInvalidIndex, err)
}

func Test_PushForward_Get(t *testing.T) {
	var list dlist.DList[int]

	for i := 0; i < 10; i++ {
		list.PushForward(i)
	}
	require.Equal(t, 10, list.Len())

	err := list.RemoveForward()
	require.Equal(t, 9, list.Len())
	require.NoError(t, err)
	for i := 0; i < 9; i++ {
		value, err := list.Get(i)
		require.NoError(t, err)
		require.Equal(t, 10-i-2, value)
	}
	value, err := list.Get(9)
	require.Equal(t, 0, value)
	require.ErrorIs(t, dlist.ErrInvalidIndex, err)
}

func Test_Empty(t *testing.T) {
	var list dlist.DList[int]

	err := list.RemoveBack()
	require.ErrorIs(t, dlist.ErrEmptyList, err)
	err = list.RemoveForward()
	require.ErrorIs(t, dlist.ErrEmptyList, err)
	value, err := list.Get(0)
	require.Equal(t, 0, value)
	require.ErrorIs(t, dlist.ErrInvalidIndex, err)
	err = list.RemoveValue(1)
	require.ErrorIs(t, dlist.ErrEmptyList, err)
}

func Test_RemoveBack_RemoveForward_One(t *testing.T) {
	var list dlist.DList[int]

	list.PushBack(1)
	err := list.RemoveBack()
	require.Equal(t, 0, list.Len())
	require.NoError(t, err)

	list.PushBack(2)
	err = list.RemoveForward()
	require.Equal(t, 0, list.Len())
	require.NoError(t, err)
}

func Test_RemoveValue(t *testing.T) {
	var list dlist.DList[int]

	for i := 0; i < 10; i++ {
		list.PushBack(1)
	}
	for i := 0; i < 5; i++ {
		list.PushBack(2)
	}
	list.PushBack(1)
	list.PushBack(2)
	require.Equal(t, 17, list.Len())
	err := list.RemoveValue(1)
	require.NoError(t, err)
	require.Equal(t, 6, list.Len())
}

func Test_FindHeadTail(t *testing.T) {
	var list dlist.DList[int]

	list.PushBack(10)
	found := list.Find(10)
	require.Equal(t, list.Head(), found)
	require.Equal(t, list.Tail(), found)
}
