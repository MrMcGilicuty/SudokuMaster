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

	std::shared_ptr<DLXNode> self;
	
	void setRow(int _row);

	int getRow();

	void cover();

	void uncover();

	int ID;
	bool one;
	bool header;
private:
	int row;
};