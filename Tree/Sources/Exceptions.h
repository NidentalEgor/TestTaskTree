#ifndef EXCEPTION_H_INCLUDED
#define  EXCEPTION_H_INCLUDED
#pragma once
#include <exception>
#include <string>

/*!
* Исключение для случая невозможности открыть файл.
*/
class OpenFileException : public std::exception
{
public:
	OpenFileException(const std::string& invalid_file_name);
	char const* what() const noexcept;

private:
	std::string invalid_file_name_;
};

/*!
* Исключение для случая невалидности типа звена.
*/
class InvalidNodeTypeException : public std::exception
{
public:
	InvalidNodeTypeException();
	char const* what() const noexcept;

private:
	std::string message_;
};

/*!
* Исключение для случая невалидности дерева во входном файле.
*/
class InvalidTreeException : public std::exception
{
public:
	InvalidTreeException();
	char const* what() const noexcept;

private:
	std::string message_;
};

#endif // EXCEPTION_H_INCLUDED
