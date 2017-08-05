#ifndef BASE_NODE_H_INCLUDED
#define BASE_NODE_H_INCLUDED
#pragma once

#include <vector>
#include <memory>

class BaseNode;

using BaseNodePtr = std::shared_ptr<BaseNode>;
using BaseNodeContainer = std::vector<BaseNodePtr>;
using BaseNodeConstContainerPtr = std::shared_ptr<const BaseNodeContainer>;

/*!
* Интерфейс звена.
*/
class BaseNode
{
public:
	/*!
	* Деструктор.
	*/
	virtual ~BaseNode() {};

	/*!
	* Возвращает количество потомков узла.
	*
	\return Количество потомков узла.
	*/
	virtual size_t LinksAmount() const = 0;

	/*!
	* Возвращает потомков узла.
	*
	\return Контейнер со всеми потомками узла.
	*/
	virtual BaseNodeConstContainerPtr GetLinks() const = 0;

	/*!
	* Сериализует узел в поток.
	*
	\param[in] output_stream Поток, в который будет сериализован узел.
	*/
	virtual void Serialize(
			std::ofstream& output_stream) const = 0;

	/*!
	* Сериализует узел в стандартный поток вывода.
	*/
	virtual void Serialize() const = 0;

	/*!
	* Добавляет связь с потомком.
	*
	\param[in] Добаляемый потомок.
	*/
	virtual void AddLink(
			const BaseNodePtr& link) = 0;
};

#endif // BASE_NODE_H_INCLUDED
