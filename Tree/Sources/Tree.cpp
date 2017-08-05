#include <fstream>
#include <iostream>
#include <queue>
#include "Exceptions.h"
#include "Tree.h"

void Tree::Serialize(const std::string& output_file_path) const
{
	if (!root_)
	{
		std::cout << "Tree is empty!" << std::endl;
		return;
	}

	std::ofstream output_file;
	output_file.open(output_file_path);

	if (!output_file.is_open())
	{
		throw OpenFileException(output_file_path);
	}

	std::queue<BaseNodePtr> supporting_queue;
	supporting_queue.push(root_);
	BaseNodePtr current_node;

	while (!supporting_queue.empty())
	{
		current_node = supporting_queue.front();
		current_node->Serialize(output_file);

		const BaseNodeConstContainerPtr current_node_links =
				current_node->GetLinks();
		
		for (BaseNodeContainer::const_iterator current_node_link = current_node_links->begin()
			; current_node_link != current_node_links->end()
			; ++current_node_link)
		{
			supporting_queue.push(*current_node_link);
		}

		supporting_queue.pop();
	}
}

void Tree::Desirialize(const std::string& input_file_path)
{
	std::ifstream input_file;
	input_file.open(input_file_path);

	if (!input_file.is_open())
	{
		throw OpenFileException(input_file_path);
	}

	std::queue<NodeDescription> supporting_queue;

	NodeDescription current_node_description =
			DesirializeNode(input_file);

	root_ = current_node_description.first;
	supporting_queue.push(current_node_description);

	while (!supporting_queue.empty())
	{
		current_node_description = supporting_queue.front();

		for (size_t link_index = 0
			; link_index < current_node_description.second
			; ++link_index)
		{
			const NodeDescription node_description = DesirializeNode(input_file);
			supporting_queue.push(node_description);
			current_node_description.first->AddLink(node_description.first);
		}

		supporting_queue.pop();
	}
}

NodeDescription Tree::DesirializeNode(std::ifstream& input_file) const
{
	int current_node_value_type;
	size_t current_node_links_amount;

	if (!(input_file >> current_node_value_type &&
		input_file >> current_node_links_amount))
	{
		// Если попали сюда, то файл закончился. Это означает,
		// что дерево некорректное.
		throw InvalidTreeException();
	}

	auto GetNode = [&input_file](auto value) -> BaseNodePtr
	{
		if (!(input_file >> value))
		{
			// Если попали сюда, то файл закончился. Это означает,
			// что дерево некорректное.
			throw InvalidTreeException();
		}

		return std::make_shared<Node<decltype(value)>>(value);
	};

	BaseNodePtr node;
	switch (static_cast<NodeValueType>(current_node_value_type))
	{
		case NodeValueType::Integer:
		{
			node = GetNode(int{});
		}
		break;

		case NodeValueType::Real:
		{
			node = GetNode(double{});
		}
		break;

		case NodeValueType::String:
		{
			node = GetNode(std::string{});
		}
		break;

		default:
		{
			throw InvalidNodeTypeException();
		}
	}

	return std::make_pair(node, current_node_links_amount);
}

void Tree::Serialize() const
{
	size_t current_level = 0;
	std::deque<BaseNodePtr> supporting_deque;
	supporting_deque.push_back(root_);

	auto print_ending_sequence = []()
	{
		std::cout << std::endl << std::endl;
	};

	auto print_level_and_increase = [](size_t& level)
	{
		std::cout << std::endl << "   Level " << level++ << std::endl;
	};

	print_level_and_increase(current_level);
	root_->Serialize();

	if (!root_->LinksAmount())
	{
		print_ending_sequence();
		return;
	}

	print_level_and_increase(current_level);

	size_t current_level_size = 1;
	size_t next_level_size = 0;

	do
	{
		const BaseNodePtr current_node = supporting_deque.front();

		const size_t current_node_links_size =
			current_node->LinksAmount();

		if (current_node_links_size)
		{
			next_level_size += current_node_links_size;

			const BaseNodeConstContainerPtr current_node_links =
				current_node->GetLinks();

			for (const BaseNodePtr& current_node_link : *current_node_links)
			{
				current_node_link->Serialize();
				supporting_deque.push_back(current_node_link);
			}
		}

		supporting_deque.pop_front();
		--current_level_size;

		if (!current_level_size)
		{
			const std::deque<BaseNodePtr>::const_iterator find =
				std::find_if(
					supporting_deque.begin(),
					supporting_deque.end(),
					[](const BaseNodePtr& node)
			{
				return node->LinksAmount() > 0;
			});

			if (find == supporting_deque.end())
			{
				print_ending_sequence();
				return;
			}

			print_level_and_increase(current_level);
			current_level_size = next_level_size;
			next_level_size = 0;
		}
		else
		{
			std::cout << " | ";
		}

	} while (!supporting_deque.empty());

	print_ending_sequence();
}