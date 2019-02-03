#ifndef OPERAND_CLASS_H
# define OPERAND_CLASS_H

# include <cmath>
# include <sstream>
# include "avm.hpp"
# include "IOperand.hpp"
# include "Factory.class.hpp"

template<class T> class Operand : public IOperand
{
	public:

		Operand(void);
		Operand(std::string str);
		Operand(Operand const & src);
		Operand(T value);
		virtual ~Operand(void);

		virtual int 				getPrecision( void ) const; // Precision of the type of the instance
		virtual eOperandType		getType( void ) const; // Type of the instance

		virtual IOperand const *	operator+( IOperand const & rhs ) const; // Sum
		virtual IOperand const *	operator-( IOperand const & rhs ) const; // Difference
		virtual IOperand const *	operator*( IOperand const & rhs ) const; // Product
		virtual IOperand const *	operator/( IOperand const & rhs ) const; // Quotient
		virtual IOperand const *	operator%( IOperand const & rhs ) const; // Modulo

		virtual std::string const &	toString( void ) const; // String representation of the instance

		std::string			trimZero(std::string str);

	private:

		T					_value;
		std::string			_value_str;
};

#endif