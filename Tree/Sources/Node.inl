#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#pragma once

#include <map>
#include <typeindex>
#include <fstream>
#include "BaseNode.h"
#include "Exceptions.h"

/*!
* Типы возможных значений, содержащихся в узлах дерева.
*/
enum class NodeValueType
{
	Integer = 0,
	Real,
	String
};

/*!
* Связь между типами данных.
*/
static const std::map<std::type_index, NodeValueType> type_id_to_node_value_type =
{
	{ typeid(int), NodeValueType::Integer },
	{ typeid(double), NodeValueType::Real },
	{ typeid(std::string), NodeValueType::String }
};

using TypeIdToNodeValueTypeMap = std::map<std::type_index, NodeValueType>;

/*!
* Возвращает внутренний тип значения в узле дерева.
*
\param[in] type_index Инофрмация о типе языка.
*
\return Внутренний тип значения в узле.
*/
inline NodeValueType ConvertTypeIdToNodeValueType(std::type_index type_index)
{
	const TypeIdToNodeValueTypeMap::const_iterator node_value_type_ptr =
			type_id_to_node_value_type.find(type_index);
	if (node_value_type_ptr == type_id_to_node_value_type.end())
	{
		throw InvalidNodeTypeException();
	}

	return node_value_type_ptr->second;
}

/*!
* Реализация интерфейса звена.
*/
template <typename T>
class Node : public BaseNode
{
public:

	/*!
	* Конструктор.
	*/
	explicit Node(T value);

	/*!
	* Возвращает количество потомков узла.
	*
	\return Количество потомков узла
	*/
	size_t LinksAmount() const override;

	/*!
	* Возвращает потомков узла.
	*
	\return Контейнер со всеми потомками узла.
	*/
	BaseNodeConstContainerPtr GetLinks() const override;

	/*!
	* Сериализует узел в поток.
	*
	\param[in] output_stream Поток, в который будет сериализован узел.
	*/
	void Serialize(
			std::ofstream& output_stream) const override;

	/*!
	* Сериализует узел в стандартный поток вывода.
	*/
	void Serialize() const override;

	/*!
	* Добавляет связь с потомком.
	*
	\param[in] Добаляемый потомок.
	*/
	void AddLink(const BaseNodePtr& link) override;

private:
	T value_;
	BaseNodeContainer links_;
};

template <typename T>
Node<T>::Node(T value)
	: value_(value)
{
}

template <typename T>
size_t Node<T>::LinksAmount() const
{
	return links_.size();
}

template <typename T>
BaseNodeConstContainerPtr Node<T>::GetLinks() const
{
	return std::make_shared<const BaseNodeContainer>(links_);
}

template <typename T>
void Node<T>::Serialize(std::ofstream& output_stream) const
{
	const NodeValueType node_value_type =
			ConvertTypeIdToNodeValueType(typeid(T));

	output_stream << static_cast<int>(node_value_type) <<
			" " << links_.size() << " " << value_ << std::endl;
}

template <typename T>
void Node<T>::Serialize() const
{
	std::cout << value_ << " ";
}

template <typename T>
void Node<T>::AddLink(const BaseNodePtr& link)
{
	links_.push_back(link);
}
#endif // NODE_H_INCLUDED
