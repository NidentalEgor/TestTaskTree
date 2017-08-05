#include "Exceptions.h"

OpenFileException::OpenFileException(const std::string& invalid_file_name)
	: invalid_file_name_(invalid_file_name)
{
}

char const* OpenFileException::what() const
{
	return (std::string("Can't open file ") + invalid_file_name_).c_str();
}

InvalidNodeTypeException::InvalidNodeTypeException()
	: std::exception("Invalid node type")
{
}

InvalidTreeException::InvalidTreeException()
	: std::exception("Invalid tree structure")
{
}
