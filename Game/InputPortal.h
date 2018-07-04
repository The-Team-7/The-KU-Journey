#pragma once
#include<iostream>
#include<unordered_map>
class InputPortal
{
public:
	InputPortal();
	~InputPortal();

	std::unordered_map<int,bool> input;
};

