#include "Parser.class.hpp"

Parser::Parser(Lexer lexer, bool verbose) : _lexer(lexer), _pos(0), _verbose(verbose)
{

}

Parser::~Parser()
{

}

bool	Parser::check_error()
{
	bool	is_error = false;

	for (unsigned int i = 0; i < this->_lexer.get_lst_token().size(); i++)
	{
		try 
		{
			if (this->_lexer.get_lst_token()[i].getType() == UNKNOWN)
				throw UnknownInstructionException(this->_lexer.get_lst_token()[i].getValue());
			else if ((this->_lexer.get_lst_token()[i].getType() == PUSH ||
					this->_lexer.get_lst_token()[i].getType() == ASSERT) &&
					((i + 1 >= this->_lexer.get_lst_token().size()) ||
					(this->_lexer.get_lst_token()[i + 1].getType() < INT8 || \
					this->_lexer.get_lst_token()[i + 1].getType() > DOUBLE)))
			{
					throw MissingNumberInstructionException(this->_lexer.get_lst_token()[i].getValue());
			}
		}
		catch (const std::exception &e)
		{
			std::cerr << "Line " << this->_lexer.get_lst_token()[i].getLine() <<
					" : Error : " << e.what() << std::endl;
			is_error = true;
		}
	}
	return (is_error);
}

void			Parser::show_error(std::string str)
{
	std::cerr << "Line " << this->_lexer.get_lst_token()[this->_pos].getLine() <<
		" : Error : " << str << std::endl;
	exit(1);
}

eOperandType	Parser::switch_type(e_token type)
{
	switch (type)
	{
		case INT8:
			return (Int8);
		case INT16:
			return (Int16);
		case INT32:
			return (Int32);
		case FLOAT:
			return (Float);
		case DOUBLE:
			return (Double);
		default:
			return (Unknown);
	}
}

void	Parser::push(Token &t)
{
	try
	{
		this->_stack.push_back(this->_factory.createOperand(this->switch_type(t.getType()), t.getValue()));
		if (this->_verbose)
			std::cout << "Pushed " << this->_stack.back()->toString() << " on the top of the stack" << std::endl;
	}
	catch (const std::out_of_range &e)
	{
		if (t.getValue()[0] == '-')
			throw Factory::UnderflowException();
		throw Factory::OverflowException();
	}
}

void	Parser::pop()
{
	if (!this->_stack.size())
		throw PopEmptyStackException();
	if (this->_verbose)
		std::cout << "Remove " << this->_stack.back()->toString() << " from the stack" << std::endl;
	delete this->_stack.back();
	this->_stack.pop_back();
}

void	Parser::dump()
{
	for (size_t i = this->_stack.size(); i != 0; i--)
		std::cout << this->_stack[i - 1]->toString() << std::endl;
}

void	Parser::assert(Token &t)
{
	if (!this->_stack.size())
		throw AssertEmptyStackException();
	if (std::stod(t.getValue()) != std::stod(this->_stack.back()->toString()))
		throw AssertMismatchException(t.getValue(), this->_stack.back()->toString());
	if (this->_verbose)
		std::cout << "Successful assert : " << t.getValue() << std::endl;
}

const IOperand *	Parser::pow()
{
	if (this->_stack.size() < 2)
		throw StackTooSmallException();

	const IOperand	*v1 = this->_stack.back();
	const IOperand	*v2 = this->_stack.rbegin()[1];
	double		nb1 = std::stod(v1->toString());
	double		nb2 = std::stod(v2->toString());

	if (this->_verbose)
		std::cout << "Pow " << std::to_string(nb2) << ", " << std::to_string(nb1) << " = " << std::pow(nb2, nb1) << std::endl;
	if (v1->getPrecision() < v2->getPrecision())
		return this->_factory.createOperand(v2->getType(), std::to_string(std::pow(nb2, nb1)));
	return this->_factory.createOperand(v1->getType(), std::to_string(std::pow(nb2, nb1)));
}

const IOperand *	Parser::bitwise(e_token op)
{
	if (this->_stack.size() < 2)
		throw StackTooSmallException();

	const IOperand	*v1 = this->_stack.back();
	const IOperand	*v2 = this->_stack.rbegin()[1];

	if (v1->getType() == Float || v1->getType() == Double ||
		v2->getType() == Float || v2->getType() == Double)
		throw BitwiseFloatingException();
	int		nb1 = std::stoi(v1->toString());
	int		nb2 = std::stoi(v2->toString());

	if (op == AND)
	{
		if (this->_verbose)
			std::cout << "And " << nb2 << ", " << nb1 << " = " << std::to_string(nb2 & nb1) << std::endl;
		if (v1->getPrecision() < v2->getPrecision())
			return this->_factory.createOperand(v2->getType(), std::to_string(nb2 & nb1));
		return this->_factory.createOperand(v1->getType(), std::to_string(nb2 & nb1));
	}
	else if (op == OR)
	{
		if (this->_verbose)
			std::cout << "Or " << nb2 << ", " << nb1 << " = " << std::to_string(nb2 | nb1) << std::endl;
		if (v1->getPrecision() < v2->getPrecision())
			return this->_factory.createOperand(v2->getType(), std::to_string(nb2 | nb1));
		return this->_factory.createOperand(v1->getType(), std::to_string(nb2 | nb1));
	}
	else if (op == XOR)
	{
		if (this->_verbose)
			std::cout << "Xor " << nb2 << ", " << nb1 << " = " << std::to_string(nb2 ^ nb1) << std::endl;
		if (v1->getPrecision() < v2->getPrecision())
			return this->_factory.createOperand(v2->getType(), std::to_string(nb2 ^ nb1));
		return this->_factory.createOperand(v1->getType(), std::to_string(nb2 ^ nb1));
	}
	else
		throw UnknownTokenTypeException();

}

void	Parser::operation(e_token op)
{
	if (this->_stack.size() < 2)
			throw StackTooSmallException();
	const IOperand *result = NULL;

	switch (op)
	{
		case ADD:
			result = *this->_stack.back() + *this->_stack.rbegin()[1];
			if (this->_verbose)
				std::cout << "Add " << this->_stack.back()->toString() << ", " << 
				this->_stack.rbegin()[1]->toString() << " = " << result->toString() << std::endl;
			break;
		case SUB:
			result = *this->_stack.back() - *this->_stack.rbegin()[1];
			if (this->_verbose)
				std::cout << "Sub " << this->_stack.back()->toString() << ", " << 
				this->_stack.rbegin()[1]->toString() << " = " << result->toString() << std::endl;
			break ;
		case MUL:
			result = *this->_stack.back() * *this->_stack.rbegin()[1];
			if (this->_verbose)
				std::cout << "Mul " << this->_stack.back()->toString() << ", " << 
				this->_stack.rbegin()[1]->toString() << " = " << result->toString() << std::endl;
			break;
		case DIV:
			if (!std::stod(this->_stack.back()->toString()))
				throw DividedByZeroException();
			result = *this->_stack.back() / *this->_stack.rbegin()[1];
			if (this->_verbose)
				std::cout << "Div " << this->_stack.back()->toString() << ", " << 
				this->_stack.rbegin()[1]->toString() << " = " << result->toString() << std::endl;
			break;
		case MOD:
			if (!std::stod(this->_stack.back()->toString()))
				throw DividedByZeroException();
			result = *this->_stack.back() % *this->_stack.rbegin()[1];
			if (this->_verbose)
				std::cout << "Mod " << this->_stack.back()->toString() << ", " << 
				this->_stack.rbegin()[1]->toString() << " = " << result->toString() << std::endl;
			break;
		case POW:
			result = this->pow();
			break ;
		case AND:
			result = this->bitwise(AND);
			break ;
		case OR:
			result = this->bitwise(OR);
			break ;
		case XOR:
			result = this->bitwise(XOR);
			break ;
		default:
			break;
	}
	this->pop();
	this->pop();
	this->_stack.push_back(result);
}

void	Parser::print()
{
	if (!this->_stack.size())
		throw PrintEmptyStackException();
	if (this->_stack.back()->getType() != Int8)
		throw PrintInvalidTypeException();
	std::cout << static_cast<char>(std::stoi(this->_stack.back()->toString()));
}

void			Parser::cast(Token &t)
{
	if (!this->_stack.size())
		throw CastOnEmptyStackException();
	
	const IOperand *result = NULL;

	if (t.getType() == CAST_INT8)
		result = this->_factory.createOperand(Int8,
			std::to_string(static_cast<int8_t>(std::stod(this->_stack.back()->toString()))));
	else if (t.getType() == CAST_INT16)
		result = this->_factory.createOperand(Int16,
			std::to_string(static_cast<int16_t>(std::stod(this->_stack.back()->toString()))));
	else if (t.getType() == CAST_INT32)
		result = this->_factory.createOperand(Int32,
			std::to_string(static_cast<int32_t>(std::stod(this->_stack.back()->toString()))));
	else if (t.getType() == CAST_FLOAT)
		result = this->_factory.createOperand(Float,
			std::to_string(static_cast<float>(std::stod(this->_stack.back()->toString()))));
	else if (t.getType() == CAST_DOUBLE)
		result = this->_factory.createOperand(Double,
			std::to_string(std::stod(this->_stack.back()->toString())));
	else
		throw UnknownTokenTypeException();
	this->pop();
	this->_stack.push_back(result);
}

void	Parser::exec()
{
	try
	{
		while (this->_pos < this->_lexer.get_lst_token().size())
		{
			switch (this->_lexer.get_lst_token()[this->_pos].getType())
			{
				case PUSH:
					this->push(this->_lexer.get_lst_token()[++this->_pos]);
					break ;
				case POP:
					this->pop();
					break ;
				case DUMP:
					this->dump();
					break ;
				case ASSERT:
					this->assert(this->_lexer.get_lst_token()[++this->_pos]);
					break ;
				case ADD:
					this->operation(ADD);
					break ;
				case SUB:
					this->operation(SUB);
					break ;
				case MUL:
					this->operation(MUL);
					break ;
				case DIV:
					this->operation(DIV);
					break ;
				case MOD:
					this->operation(MOD);
					break ;
				case POW:
					this->operation(POW);
					break ;
				case AND:
					this->operation(AND);
					break ;
				case OR:
					this->operation(OR);
					break ;
				case XOR:
					this->operation(XOR);
					break ;
				case PRINT:
					this->print();
					break ;
				case CAST:
					this->cast(this->_lexer.get_lst_token()[++this->_pos]);
				case EXIT:
					break ;
				default:
					throw UnknownTokenTypeException();
			}
			if (this->_lexer.get_lst_token()[this->_pos].getType() == EXIT)
				break ;
			++this->_pos;
		}
		if (this->_lexer.get_lst_token()[this->_pos].getType() != EXIT)
		{
			if (this->_pos > 0)
				--this->_pos;
			throw MissingExitException();
		}
	}
	catch (const std::exception &e)
	{
		this->show_error(e.what());
	}
	for (size_t i = 0; i < this->_stack.size(); i++)
		this->pop();
}