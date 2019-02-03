#ifndef TOKEN_CLASS_H
# define TOKEN_CLASS_H

#include <string>

enum e_token
{
	NONE,
	PUSH,
	POP,
	DUMP,
	ASSERT,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	POW,
	AND,
	OR,
	XOR,
	PRINT,
	EXIT,
	INT8,
	INT16,
	INT32,
	FLOAT,
	DOUBLE,
	CAST,
	CAST_INT8,
	CAST_INT16,
	CAST_INT32,
	CAST_FLOAT,
	CAST_DOUBLE,
	COMMENT,
	UNKNOWN
};

class Token
{

private:
	e_token			_type;
	std::string		_value;
	unsigned int	_line;

public:
	Token() : _type(NONE), _value("") {}
	Token(e_token type, std::string value, unsigned int line) : _type(type), _value(value), _line(line) { }
	~Token() { }
	e_token			getType() { return this->_type; }
	std::string		getValue(){ return this->_value; }
	unsigned int	getLine(){ return this->_line; }

};

#endif