#include <iterator>
#include <fstream>
#include "gtest/gtest.h"
#include "../Tree/Sources/Tree.h"
#include "../Tree/Sources/Exceptions.h"

bool AreFilesEqual(
		const std::string& first_file_path,
		const std::string& second_file_path)
{
	std::ifstream first_file(first_file_path);
	std::ifstream second_file(second_file_path);

	const std::istream_iterator<char> first_file_begin(first_file), first_file_end;
	const std::istream_iterator<char> second_file_begin(second_file);

	return std::equal(first_file_begin, first_file_end, second_file_begin);
}

class ExceptionTest : public testing::Test
{
protected:
	template <typename T>
	static void ExpectedExceptionTest(
			const std::string& input_file_path,
			const std::string& error_message)
	{
		Tree tree;
		EXPECT_THROW(
				tree.Desirialize(input_file_path),
				T) << error_message;
	}
};

TEST_F(ExceptionTest, NonexistentFileTest)
{
	ExpectedExceptionTest<OpenFileException>(
			R"(../../../../Tests/ResourceFiles/ExceptionTests/NonexistentFileTest/nonexistent_file.txt)",
			"Expected exception type is OpenFileException");
}

TEST_F(ExceptionTest, InvalidTreeTest)
{
	ExpectedExceptionTest<InvalidTreeException>(
			R"(../../../../Tests/ResourceFiles/ExceptionTests/InvalidTreeTest/input.txt)",
			"Expected exception type is InvalidTreeException");
}

TEST_F(ExceptionTest, InvalidNodeTypeTest)
{
	ExpectedExceptionTest<InvalidNodeTypeException>(
			R"(../../../../Tests/ResourceFiles/ExceptionTests/InvalidNodeTypeTest/input.txt)",
			"Expected exception type is InvalidNodeTypeException");
}

class TreeTest : public testing::Test
{
protected:
	static void TreeProcessingTest(
			const std::string& input_file_path,
			const std::string& output_file_path,
			const std::string error_message)
	{
		Tree tree;
		tree.Desirialize(input_file_path);
		tree.Serialize(output_file_path);

		EXPECT_TRUE(
				AreFilesEqual(
					input_file_path,
					output_file_path)) << error_message;
	}
};

TEST_F(TreeTest, OneNodeTreeTest)
{
	TreeProcessingTest(
			R"(../../../../Tests/ResourceFiles/TreeTests/OneNodeTreeTest/input.txt)",
			R"(../../../../Tests/ResourceFiles/TreeTests/OneNodeTreeTest/output.txt)",
			"Input and output files are different.");
}

TEST_F(TreeTest, BigTreeTest)
{
	TreeProcessingTest(
			R"(../../../../Tests/ResourceFiles/TreeTests/BigTreeTest/input.txt)",
			R"(../../../../Tests/ResourceFiles/TreeTests/BigTreeTest/output.txt)",
			"Input and output files are different.");
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
