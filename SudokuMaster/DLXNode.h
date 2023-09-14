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

	
	void setRow(int _row);

	int getRow();

	void cover();

	void uncover();

	int ID = -1;
	bool one = false;
	bool header = false;
private:
	int row = 0;
};