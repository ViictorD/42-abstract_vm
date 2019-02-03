#include "Factory.class.hpp"

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const
{
	switch (type)
	{
		case Int8:
			return this->createInt8(value);
		case Int16:
			return this->createInt16(value);
		case Int32:
			return this->createInt32(value);
		case Float:
			return this->createFloat(value);
		case Double:
			return this->createDouble(value);
		default:
			throw InvalidOperandTypeException();
	}
}

IOperand const * Factory::createInt8( std::string const & value ) const
{
	int nb = std::stoi(value);
	if (nb > SCHAR_MAX)
		throw OverflowException();
	else if (nb < SCHAR_MIN)
		throw UnderflowException();
	return new Operand<int8_t>(value);
}

IOperand const * Factory::createInt16( std::string const & value ) const
{
	int nb = std::stoi(value);
	if (nb > SHRT_MAX)
		throw OverflowException();
	else if (nb < SHRT_MIN)
		throw UnderflowException();
	return new Operand<int16_t>(value);
}

IOperand const * Factory::createInt32( std::string const & value ) const
{
	try
	{
		std::stoi(value);
	}
	catch (std::out_of_range &e)
	{
		if (value[0] != '-')
			throw OverflowException();
		else
			throw UnderflowException();
	}
	return new Operand<int32_t>(value);
}

IOperand const * Factory::createFloat( std::string const & value ) const
{
	try
	{
		std::stof(value);
	}
	catch (std::out_of_range &e)
	{
		if (value[0] != '-')
			throw OverflowException();
		else
			throw UnderflowException();
	}
	return new Operand<float>(value);
}

IOperand const * Factory::createDouble( std::string const & value ) const
{
	try
	{
		std::stod(value);
	}
	catch (std::out_of_range &e)
	{
		if (value[0] != '-')
			throw OverflowException();
		else
			throw UnderflowException();
	}
	return new Operand<double>(value);
}
