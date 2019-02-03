#ifndef FACTORY_CLASS_H
# define FACTORY_CLASS_H

# include <limits>
# include <stdexcept>
# include "Operand.class.hpp"

class Factory
{
	private:
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;

	public:
		Factory(void) {}
		Factory(Factory const & src) { *this = src; }
		~Factory(void) {}

		IOperand const * createOperand( eOperandType type, std::string const & value ) const;

	class InvalidOperandTypeException : public std::exception
	{
		public:
			InvalidOperandTypeException() { }
			virtual ~InvalidOperandTypeException() throw() { }

			virtual const char * what() const throw() { return ("Invalid operand type"); }
	};

	class OverflowException : public std::out_of_range
	{
		public:
			OverflowException () : out_of_range("Overflow") { }
			virtual ~OverflowException() throw() { }

			virtual const char * what() const throw() { return (out_of_range::what()); }
	};

	class UnderflowException : public std::out_of_range
	{
		public:
			UnderflowException() : out_of_range("Underflow") { }
			virtual ~UnderflowException() throw() { }

			virtual const char * what() const throw() { return (out_of_range::what()); }
	};
};

#endif