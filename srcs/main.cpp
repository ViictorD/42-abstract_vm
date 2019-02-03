#include <sstream>
#include "avm.hpp"
#include "Lexer.class.hpp"
#include "Parser.class.hpp"

int		main(int ac, char **av)
{
	std::vector<std::string>	arr;
	bool		verbose = false;

	if (ac == 1)
		arr = read_stdin();
	else if (ac == 2 && !std::string(av[1]).compare("-v"))
	{
		verbose = true;
		arr = read_stdin();
	}
	else if (ac == 2)
		arr = read_file(av[1]);
	else if (ac == 3 && !std::string(av[1]).compare("-v"))
	{
		verbose = true;
		arr = read_file(av[2]);
	}
	else
	{
		std::cerr << "Usage: ./avm [-v] [file]" << std::endl;
		return 1;
	}

	std::vector<Token>		lst_token;

	Lexer	lexer(arr);
	lexer.exec();
	if (verbose)
	{
		std::cout << "------------ Token list ------------" << std::endl << std::endl;
		lexer.view_token();
		std::cout << std::endl << "-------------------------------------" << std::endl << std::endl;
	}
	Parser	parser(lexer, verbose);
	if (parser.check_error() == true)
		return (1);
	else
		parser.exec();
	return 0;
}
