#pragma once
#include <memory>
class DLXNode
{
public:
	DLXNode();

	std::shared_ptr<DLXNode> left;
	std::shared_ptr<DLXNode> right;
	std::shared_ptr<DLXNode> up;
	std::shared_ptr<DLXNode> down;

	
	
	int num = 0;
	bool header = 0;

};