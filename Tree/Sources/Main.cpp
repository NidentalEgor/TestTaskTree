#include <boost/program_options.hpp>
#include <iostream>
#include <exception>
#include "Tree.h"

int main(int argc, char** argv)
{
	boost::program_options::options_description program_options_description("Console options");
	program_options_description.add_options()
		("help,h", "Show help")
		("input,i", boost::program_options::value<std::string>()->required(), "Input file with tree.")
		("output,o", boost::program_options::value<std::string>()->required(), "Output file.");

	boost::program_options::variables_map variables_map;

	try
	{
		boost::program_options::store(
				boost::program_options::parse_command_line(
					argc,
					argv,
					program_options_description),
				variables_map);

		if (variables_map.count("help"))
		{
			std::cout << program_options_description << std::endl;
			return 0;
		}

		boost::program_options::notify(variables_map);

		std::string input_file_path;
		if (variables_map.count("input"))
		{
			input_file_path = variables_map["input"].as<std::string>();
		}
		
		std::string output_file_path;
		if (variables_map.count("output"))
		{
			output_file_path = variables_map["output"].as<std::string>();
		}

		Tree tree;
		tree.Desirialize(input_file_path);
		tree.Serialize();
		tree.Serialize(output_file_path);
	}
	catch(const boost::program_options::error& program_options_error)
	{
		std::cerr << program_options_error.what() << std::endl;
		return -1;
	}

	catch(const InvalidNodeTypeException& invalid_node_type_exception)
	{
		std::cout << invalid_node_type_exception.what() << std::endl;
		return -2;
	}

	catch(const OpenFileException& open_file_exception)
	{
		std::cout << open_file_exception.what() << std::endl;
		return -3;
	}

	catch(const InvalidTreeException& invalid_tree_exception)
	{
		std::cout << invalid_tree_exception.what() << std::endl;
		return -4;
	}

	catch(const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return -5;
	}

	std::cout << "Press any key to exit." << std::endl;
	std::cin.get();
	return 0;
}
