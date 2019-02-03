#ifndef AVM_H
# define AVM_H

# include <iostream>
# include <vector>
# include <string>
# include <fstream>
# include <stdexcept>

enum eOperandType
{ 
	Int8,
	Int16,
	Int32,
	Float,
	Double,
	Unknown
};

std::vector<std::string>	read_stdin();
std::vector<std::string>	read_file(std::string path);

#endif