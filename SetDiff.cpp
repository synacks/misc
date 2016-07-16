// SetDiff.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>

using namespace std;


template<typename SetType>
void diffSet(const SetType& left, const SetType& right, SetType& leftOnly, SetType& rightOnly)
{
	auto itRightBegin = right.begin();
	for (auto itLeft = left.begin(); itLeft != left.end(); ++itLeft)
	{
		auto itRight = right.find(*itLeft);
		if (itRight == right.end())
		{
			leftOnly.insert(*itLeft);
		}
		else
		{
			if (itRightBegin != itRight)
			{
				rightOnly.insert(itRightBegin, itRight);
			}
			itRightBegin = ++itRight;
		}
	}

	if (itRightBegin != right.end())
	{
		rightOnly.insert(itRightBegin, right.end());
	}
}

template<typename SetType>
void diffSetPlain(const SetType& left, const SetType& right, SetType& leftOnly, SetType& rightOnly)
{
	for (auto elem : left)
	{
		if (right.find(elem) == right.end())
		{
			leftOnly.insert(elem);
		}
	}

	for (auto elem : right)
	{
		if (left.find(elem) == left.end())
		{
			rightOnly.insert(elem);
		}
	}
}

void test()
{
	set<int> left;
	set<int> right;

	for (int i = 0; i < rand() % 100; i++)
	{
		left.insert(rand() % 1000000);
	}

	for (int i = 0; i < rand() % 100; i++)
	{
		left.insert(rand() % 1000000);
	}

	set<int> leftOnly, rightOnly;
	diffSet(left, right, leftOnly, rightOnly);

	set<int> leftOnlyPlain, rightOnlyPlain;
	diffSetPlain(left, right, leftOnlyPlain, rightOnlyPlain);

	if (leftOnly != leftOnlyPlain)
	{
		printf("leftOnly != leftOnlyPlain\n");
		assert(false);
	}

	if (rightOnly != rightOnlyPlain)
	{
		printf("rightOnly != rightOnlyPlain\n");
		assert(false);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	for (int i = 0; i < 100; i++)
	{
		test();
		printf("test over!\n");
	}
	printf("all tests over!\n");
	return 0;
}

