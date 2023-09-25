#include "DLXNode.h"
#include <iostream>
#include <memory>

DLXNode::DLXNode() {
	ID = -1;
	one = false;
	header = false;
	row = 0;
	this->self = self;
}

void DLXNode::setRow(int _row) {
	row = _row;
}

int DLXNode::getRow() {
	return row;
}

void DLXNode::setCol(int _col) {
	col = _col;
}

int DLXNode::getCol() {
	return col;
}

void DLXNode::cover() {
	left->right = right;
	right->left = left;
	down->up    = up;
	up->down    = down;
}

void DLXNode::uncover() {
		left->right = self;
		right->left = self;
		down->up    = self;
		up->down    = self;
}

