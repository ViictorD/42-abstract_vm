#ifndef LEXER_CLASS_H
# define LEXER_CLASS_H

# include <sstream>
# include <regex>
# include <utility>
# include "Token.class.hpp"
# include "avm.hpp"

class Lexer
{
private:
	std::vector<Token>			_lst_token;
	std::vector<std::string>	_text;

public:
	Lexer(std::vector<std::string> text);
	~Lexer();
	void							exec();
	Token							get_next_token(std::string str, unsigned int nb_line) const;
	std::vector<std::string>		split_whitespace(std::string str) const;
	std::pair<e_token, std::string> get_number_type(std::string str) const;
	e_token							get_cast_type(std::string str) const;
	bool							is_number(const std::string& s) const;
	void							view_token();
	std::vector<Token>				get_lst_token();


};

#endif