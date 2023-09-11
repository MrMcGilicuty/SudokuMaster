#pragma once
#include "DLXNode.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class SudokuDLXMatrix
{
public:
	SudokuDLXMatrix();

	// Function that creates the whole preset matrix
	vector<vector<bool>> createBoolMatrix();

	

private:
	// Vectors for the different constraints
	vector<shared_ptr<DLXNode>> headers;
	vector<shared_ptr<DLXNode>> cellConstraint;
	vector<shared_ptr<DLXNode>> rowConstraint;
	vector<shared_ptr<DLXNode>> colConstraint;
	vector<shared_ptr<DLXNode>> boxConstraint;

	vector<vector<shared_ptr<DLXNode>>> presetDLXMatrix;

	vector<bool> row;
	vector<vector<bool>> boolMatrix;
	// Function for creating the headers for the matrix
	void createHeaders();
};

