#include "Operand.class.hpp"

template<class T> Operand<T>::Operand(void)
{
	this->_value = static_cast<T>(0);
	this->_value_str = this->trimZero(std::to_string(this->_value));
}

template<class T> Operand<T>::Operand(std::string str)
{
	this->_value = static_cast<T>(std::stod(str));
	this->_value_str = this->trimZero(std::to_string(this->_value));
}

template<class T> Operand<T>::Operand(Operand const & src)
{
	*this = src;
}

template<class T> Operand<T>::Operand(T value)
{
	this->_value = value;
	this->_value_str = this->trimZero(std::to_string(value));
}

template<class T> Operand<T>::~Operand(void) { }

template<> int 				Operand<int8_t>::getPrecision(void) const
{
	return Int8;
}

template<> eOperandType		Operand<int8_t>::getType(void) const
{
	return Int8;
}

template class Operand<int8_t>;

template<> int 				Operand<int16_t>::getPrecision(void) const
{
	return Int16;
}

template<> eOperandType		Operand<int16_t>::getType(void) const
{
	return Int16;
}

template class Operand<int16_t>;

template<> int 				Operand<int32_t>::getPrecision(void) const
{
	return Int32;
}

template<> eOperandType		Operand<int32_t>::getType(void) const
{
	return Int32;
}

template class Operand<int32_t>;


template<> int 				Operand<float>::getPrecision(void) const
{
	return Float;
}

template<> eOperandType		Operand<float>::getType(void) const
{
	return Float;
}

template class Operand<float>;


template<> int 				Operand<double>::getPrecision(void) const
{
	return Double;
}

template<> eOperandType		Operand<double>::getType(void) const
{
	return Double;
}

template class Operand<double>;


template<class T> IOperand const *	Operand<T>::operator+(IOperand const & rhs) const
{
	Factory	f;

	if (this->getPrecision() < rhs.getPrecision())
		return (f.createOperand(rhs.getType(), std::to_string(std::stod(rhs.toString()) + this->_value)));
	return (f.createOperand(this->getType(), std::to_string(static_cast<T>(std::stod(rhs.toString())) + this->_value)));
}

template<class T> IOperand const *	Operand<T>::operator-(IOperand const & rhs) const
{
	Factory	f;

	if (this->getPrecision() < rhs.getPrecision())
		return (f.createOperand(rhs.getType(), std::to_string(std::stod(rhs.toString()) - this->_value)));
	return (f.createOperand(this->getType(), std::to_string(static_cast<T>(std::stod(rhs.toString())) - this->_value)));
}

template<class T> IOperand const *	Operand<T>::operator*(IOperand const & rhs) const
{
	Factory	f;

	if (this->getPrecision() < rhs.getPrecision())
		return (f.createOperand(rhs.getType(), std::to_string(std::stod(rhs.toString()) * this->_value)));
	return (f.createOperand(this->getType(), std::to_string(static_cast<T>(std::stod(rhs.toString())) * this->_value)));
}

template<class T> IOperand const *	Operand<T>::operator/(IOperand const & rhs) const
{
	Factory	f;

	if (this->getPrecision() < rhs.getPrecision())
		return (f.createOperand(rhs.getType(), std::to_string(std::stod(rhs.toString()) / this->_value)));
	return (f.createOperand(this->getType(), std::to_string(static_cast<T>(std::stod(rhs.toString())) / this->_value)));
}

template<class T> IOperand const *	Operand<T>::operator%(IOperand const & rhs) const
{
	Factory	f;

	return (f.createOperand(Double, std::to_string(std::fmod(std::stod(rhs.toString()), this->_value))));
}

template<class T> std::string const &	Operand<T>::toString(void) const
{
	return this->_value_str;
}

template<class T> std::string			Operand<T>::trimZero(std::string str)
{
	if ((this->getType() != Float && this->getType() != Double) || str[str.length() - 1] != '0')
		return str;

	size_t	i = str.length() - 1;

	while (i > 0)
	{
		if (str[i] != '0' || str[i - 1] == '.')
		{
			++i;
			break ;
		}
		--i;
	}
	return str.substr(0, i);
}
