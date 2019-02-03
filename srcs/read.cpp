#include "avm.hpp"

std::vector<std::string>	read_stdin()
{
	std::vector<std::string>	arr;
	std::string 				tmp;

	while (1)
	{
		std::getline(std::cin, tmp);
		if (!std::strcmp(tmp.c_str(), ";;"))
			break ;
		arr.push_back(tmp);
	}
	return (arr);
}

std::vector<std::string>	read_file(std::string path)
{
	std::vector<std::string>	arr;
	std::string 				tmp;
	std::ifstream t(path);

	if (t.is_open())
	{
		while (std::getline(t, tmp))
			arr.push_back(tmp);
	}
	else
	{
		std::cerr << "Avm : Error : Invalid file" << std::endl;
		exit(1);
	}
	return (arr);
}
