#include "DLXNode.h"
#include <memory>

DLXNode::DLXNode() {

}

void DLXNode::setRow(int _row) {
	row = _row;
}

int DLXNode::getRow() {
	return row;
}

void DLXNode::cover() {
	left->right = right;
	right->left = left;
	down->up    = up;
	up->down    = down;
}

void DLXNode::uncover() {
	left->right = std::make_shared<DLXNode>(this);
	right->left = std::make_shared<DLXNode>(this);
	down->up    = std::make_shared<DLXNode>(this);
	up->down    = std::make_shared<DLXNode>(this);
}
