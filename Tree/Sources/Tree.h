#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED
#pragma once

#include <memory>
#include <string>
#include "Node.inl"

using NodeDescription = std::pair<BaseNodePtr, size_t>;

/*!
* Структура данных для хранения дерева.
*/
class Tree
{
public:
	/*!
	* Сериализует дерево в файл.
	*
	\param[in] output_file_path Путь к файлу, в который будет сериализовано дерево.
	*/
	void Serialize(const std::string& output_file_path) const;

	/*!
	* Сериализует дерево в стандартный поток вывода.
	* Узлы разных уровней разделены строкой "Level #".
	* Потомки узла в рамках одного уровня разделены пробелом ' '. 
	* Потомки разных узлов в рамках одного уровня разделены вертикальной чертой '|'.
	*/
	void Serialize() const;

	/*!
	* Десериализует дерево из файла.
	*
	\param[in] input_file_path Путь к файлу, из которого будет десериализовано дерево.
	*/
	void Desirialize(const std::string& input_file_path);

private:
	/*!
	* Десериализует узел дерева.
	*
	\param[in] input_file Поток, из которого будет десериализован узел.
	*
	\return Звено дерева, инициализированное своим значением, и количество его потомков.
	*/
	NodeDescription DesirializeNode(std::ifstream& input_file) const;

private:
	BaseNodePtr root_ = nullptr;
};

#endif // TREE_H_INCLUDED
