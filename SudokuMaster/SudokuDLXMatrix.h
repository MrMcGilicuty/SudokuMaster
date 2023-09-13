#pragma once
#include "DLXNode.h"
#include "EditNumber.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class SudokuDLXMatrix
{
public:
	SudokuDLXMatrix();

	// Function that creates the whole Boolean preset matrix
	vector<vector<bool>> createBoolMatrix();

	void solve();

	vector<vector<shared_ptr<DLXNode>>> presetDLXMatrix;
private:
	// Vectors for the different constraints
	vector<shared_ptr<DLXNode>> headers;

	vector<shared_ptr<DLXNode>> cRow;
	vector<vector<shared_ptr<DLXNode>>> constraints;

	vector<bool> row;
	vector<vector<bool>> boolMatrix;

	//
	void createDLXMatrix();

	// Function for creating the headers for the matrix
	void createHeaders();
};

