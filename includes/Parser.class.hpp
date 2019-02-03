#ifndef PARSER_CLASS_H
# define PARSER_CLASS_H

# include "Token.class.hpp"
# include "Lexer.class.hpp"
# include "Operand.class.hpp"
# include "Factory.class.hpp"

class Parser
{
private:
	Lexer							_lexer;
	Factory							_factory;
	std::vector<const IOperand*>	_stack;
	unsigned int					_pos;
	bool							_verbose;

public:
	Parser(Lexer lexer, bool verbose);
	~Parser();
	bool			check_error();
	void			exec();
	eOperandType	switch_type(e_token type);
	void			show_error(std::string);
	void			push(Token &t);
	void			pop();
	void			dump();
	void			assert(Token &t);
	void			operation(e_token op);
	const IOperand *pow();
	const IOperand *bitwise(e_token op);
	void			cast(Token &t);

	void			print();

	class	UnknownInstructionException : public std::exception
	{
		private:
			std::string	_instruction;

		public:
			UnknownInstructionException(std::string str) : _instruction(str) { }
			virtual ~UnknownInstructionException() throw() { }

			virtual const char * what() const throw()
			{
				std::string	tmp("Unknown instruction \"" + this->_instruction + "\"");
				return (tmp.c_str());
			}
	};

	class	MissingNumberInstructionException : public std::exception
	{
		private:
			std::string	_instruction;

		public:
			MissingNumberInstructionException(std::string str) : _instruction(str) { }
			virtual ~MissingNumberInstructionException() throw() { }

			virtual const char * what() const throw()
			{
				std::string	tmp("Missing number after instruction \"" + this->_instruction + "\"");
				return (tmp.c_str());
			}
	};

	class	PopEmptyStackException : public std::exception
	{
		public:
			PopEmptyStackException() { }
			virtual ~PopEmptyStackException() throw() { }

			virtual const char * what() const throw() { return ("Pop on empty stack"); }
	};

	class	AssertEmptyStackException : public std::exception
	{
		public:
			AssertEmptyStackException() { }
			virtual ~AssertEmptyStackException() throw() { }

			virtual const char * what() const throw() { return ("Assert on empty stack"); }
	};

	class	AssertMismatchException : public std::exception
	{
		private:
			std::string		_v1;
			std::string		_v2;

		public:
			AssertMismatchException(std::string assert_value, std::string stack_value) : _v1(assert_value), _v2(stack_value) { }
			virtual ~AssertMismatchException() throw() { }

			virtual const char * what() const throw()
			{
				std::string tmp("Assert value (" + this->_v1 +
					") and stack value (" + this->_v2 + ") are differents");
				return (tmp.c_str());
			}
	};

	class	StackTooSmallException : public std::exception
	{
		public:
			StackTooSmallException() { }
			virtual ~StackTooSmallException() throw() { }

			virtual const char * what() const throw() { return ("The stack contain less than 2 numbers"); }
	};

	class	DividedByZeroException : public std::exception
	{
		public:
			DividedByZeroException() { }
			virtual ~DividedByZeroException() throw() { }

			virtual const char * what() const throw() { return ("Division by zero"); }
	};

	class	PrintEmptyStackException : public std::exception
	{
		public:
			PrintEmptyStackException() { }
			virtual ~PrintEmptyStackException() throw() { }

			virtual const char * what() const throw() { return ("Print on empty stack"); }
	};

	class	PrintInvalidTypeException : public std::exception
	{
		public:
			PrintInvalidTypeException() { }
			virtual ~PrintInvalidTypeException() throw() { }

			virtual const char * what() const throw() { return ("Value on the top of the stack isn't an 8-bit integer"); }
	};

	class	MissingExitException : public std::exception
	{
		public:
			MissingExitException() { }
			virtual ~MissingExitException() throw() { }

			virtual const char * what() const throw() { return ("Missing exit instruction"); }
	};

	class	UnknownTokenTypeException : public std::exception
	{
		public:
			UnknownTokenTypeException() { }
			virtual ~UnknownTokenTypeException() throw() { }

			virtual const char * what() const throw() { return ("Unknown token during execution"); }
	};


	class	BitwiseFloatingException : public std::exception
	{
		public:
			BitwiseFloatingException() { }
			virtual ~BitwiseFloatingException() throw() { }

			virtual const char * what() const throw() { return ("Bitwise floating-point number"); }
	};

	class	CastOnEmptyStackException : public std::exception
	{
		public:
			CastOnEmptyStackException() { }
			virtual ~CastOnEmptyStackException() throw() { }

			virtual const char * what() const throw() { return ("Cast on empty stack"); }
	};

};

#endif