#include "Exceptions.h"

OpenFileException::OpenFileException(const std::string& invalid_file_name)
	: invalid_file_name_(invalid_file_name)
{
}

char const* OpenFileException::what() const noexcept
{
	return (std::string("Can't open file ") + invalid_file_name_).c_str();
}

InvalidNodeTypeException::InvalidNodeTypeException()
	: std::exception()
	, message_("Invalid node type")
{
}

const char* InvalidNodeTypeException::what() const noexcept
{
			 return message_.c_str();
}

InvalidTreeException::InvalidTreeException()
	: std::exception()
	, message_("Invalid tree structure")
{
}

const char* InvalidTreeException::what() const noexcept
{
			 return message_.c_str();
}
