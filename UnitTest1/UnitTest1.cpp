#include "pch.h"
#include "CppUnitTest.h"
#include "../AVLTree/main.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AVLTreeTests
{
	TEST_CLASS(AVLTreeTest)
	{
	public:

		TEST_METHOD(TestInsert)
		{
			AVLTree avlTree;
			avlTree.add(30);
			avlTree.add(10);
			avlTree.add(50);
			avlTree.add(60);
			avlTree.add(20);

			Assert::IsTrue(avlTree.contains(30));
		}

		TEST_METHOD(TestRemove)
		{
			AVLTree avlTree;
			avlTree.add(30);
			avlTree.add(10);
			avlTree.add(50);
			avlTree.add(60);
			avlTree.add(20);

			Assert::IsTrue(avlTree.contains(30));
			avlTree.remove(30);
			Assert::IsFalse(avlTree.contains(30));

			Assert::IsTrue(avlTree.contains(10));
			avlTree.remove(10);
			Assert::IsFalse(avlTree.contains(10));

			Assert::IsTrue(avlTree.contains(50));
			avlTree.remove(50);
			Assert::IsFalse(avlTree.contains(50));
		}

		TEST_METHOD(TestContains)
		{
			AVLTree avlTree;
			avlTree.add(30);
			avlTree.add(10);
			avlTree.add(50);
			avlTree.add(60);
			avlTree.add(20);

			Assert::IsTrue(avlTree.contains(30));
			Assert::IsTrue(avlTree.contains(10));
			Assert::IsTrue(avlTree.contains(50));
			Assert::IsTrue(avlTree.contains(60));
			Assert::IsTrue(avlTree.contains(20));
			Assert::IsFalse(avlTree.contains(40));
		}
	};
}
