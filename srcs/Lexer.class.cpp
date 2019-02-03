#include "Lexer.class.hpp"

Lexer::Lexer(std::vector<std::string> text) : _text(text)
{

}
Lexer::~Lexer()
{

}

std::vector<std::string>	Lexer::split_whitespace(std::string str) const
{
	std::vector<std::string>	arr;
	std::stringstream			stream(str);
	std::string 				tmp;

	while(getline(stream, tmp, ' '))
		arr.push_back(tmp);
	return (arr);
}

bool	Lexer::is_number(const std::string &s) const
{
	bool is_point = false;

	std::string::const_iterator it = s.begin();
	while (it != s.end() && (std::isdigit(*it) || *it == '.' || (*it == '-' && it == s.begin())))
	{
		if (*it == '.')
		{
			if (!is_point)
				is_point = true;
			else
				return (false);
		}
		++it;
	}
	return !s.empty() && it == s.end();
}

std::pair<e_token, std::string> Lexer::get_number_type(std::string str) const
{
	std::cmatch		m;
	std::regex_match(str.c_str(), m, std::regex("((int(.*?))\\(([-]?\\d+)\\)|(float|double)\\(([-]?\\d+\\.\\d+)\\))"));

	if (!m[2].compare("int8") && this->is_number(m[4]))
		return (std::make_pair(INT8, m[4]));
	else if (!m[2].compare("int16") && this->is_number(m[4]))
		return (std::make_pair(INT16, m[4]));
	else if (!m[2].compare("int32") && this->is_number(m[4]))
		return (std::make_pair(INT32, m[4]));
	else if (!m[5].compare("float") && this->is_number(m[6]))
		return (std::make_pair(FLOAT, m[6]));
	else if (!m[5].compare("double") && this->is_number(m[6]))
		return (std::make_pair(DOUBLE, m[6]));
	return (std::make_pair(UNKNOWN, m[0]));
}

e_token	Lexer::get_cast_type(std::string str) const
{
	if (!str.compare("int8"))
		return CAST_INT8;
	else if (!str.compare("int16"))
		return CAST_INT16;
	else if (!str.compare("int32"))
		return CAST_INT32;
	else if (!str.compare("float"))
		return CAST_FLOAT;
	else if (!str.compare("double"))
		return CAST_DOUBLE;
	return UNKNOWN;
}

Token	Lexer::get_next_token(std::string line, unsigned int nb_line) const
{
	std::pair<e_token, std::string>	tmp;
	e_token							tmp2;

	if (!line.length() || line[0] == ';')
		return (Token(COMMENT, line, nb_line));
	else if (!line.compare("pop"))
		return (Token(POP, line, nb_line));
	else if (!line.compare("dump"))
		return (Token(DUMP, line, nb_line));
	else if (!line.compare("add"))
		return (Token(ADD, line, nb_line));
	else if (!line.compare("sub"))
		return (Token(SUB, line, nb_line));
	else if (!line.compare("mul"))
		return (Token(MUL, line, nb_line));
	else if (!line.compare("div"))
		return (Token(DIV, line, nb_line));
	else if (!line.compare("mod"))
		return (Token(MOD, line, nb_line));
	else if (!line.compare("pow"))
		return (Token(POW, line, nb_line));
	else if (!line.compare("and"))
		return (Token(AND, line, nb_line));
	else if (!line.compare("or"))
		return (Token(OR, line, nb_line));
	else if (!line.compare("xor"))
		return (Token(XOR, line, nb_line));
	else if (!line.compare("print"))
		return (Token(PRINT, line, nb_line));
	else if (!line.compare("exit"))
		return (Token(EXIT, line, nb_line));
	else if (!line.compare("push"))
		return (Token(PUSH, line, nb_line));
	else if (!line.compare("cast"))
		return (Token(CAST, line, nb_line));
	else if (!line.compare("assert"))
		return (Token(ASSERT, line, nb_line));
	else if ((tmp = this->get_number_type(line)).first != UNKNOWN)
		return (Token(tmp.first, tmp.second, nb_line));
	else if ((tmp2 = this->get_cast_type(line)) != UNKNOWN)
		return (Token(tmp2, line, nb_line));
	return (Token(UNKNOWN, line, nb_line));
}

void	Lexer::exec()
{
	Token				curr_token;
	unsigned int		pos = 0;
	unsigned int		line = 1;

	for (std::vector<std::string>::iterator it = this->_text.begin(); it != this->_text.end(); it++)
	{
		std::vector<std::string>	splited;
		splited = split_whitespace(*it);

		while (pos != splited.size())
		{
			curr_token = this->get_next_token(splited[pos], line);
			if (curr_token.getType() == COMMENT)
				break ;
			this->_lst_token.push_back(curr_token);
			++pos;
		}
		pos = 0;
		++line;
	}
}

void	Lexer::view_token()
{
	std::vector<Token>::iterator it;

	for (it = this->_lst_token.begin(); it < this->_lst_token.end(); it++)
	{
		std::cout << "Token: " << it->getType() << ", Value: " << it->getValue() << std::endl;
	}
}

std::vector<Token>			Lexer::get_lst_token()
{
	return (this->_lst_token);
}
