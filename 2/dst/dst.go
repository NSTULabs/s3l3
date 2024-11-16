package dst

import "errors"

var (
	ErrOpenFile       = errors.New("can't open file")
	ErrWrite          = errors.New("write error")
	ErrRead           = errors.New("read error")
	ErrIntSelialize   = errors.New("only int type can be selialized")
	ErrIntDeselialize = errors.New("only int type can be deselialized")
)
