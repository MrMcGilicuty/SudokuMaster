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

	//
	void createDLXMatrix(vector<vector<bool>> boolMatrix, vector<vector<EditNumber*>> currentBoard);


	vector<vector<shared_ptr<DLXNode>>> presetDLXMatrix;
private:
	// Vectors for the different constraints
	vector<shared_ptr<DLXNode>> headers;
	vector<shared_ptr<DLXNode>> cellConstraint;
	vector<shared_ptr<DLXNode>> rowConstraint;
	vector<shared_ptr<DLXNode>> colConstraint;
	vector<shared_ptr<DLXNode>> boxConstraint;

	vector<bool> row;
	vector<vector<bool>> boolMatrix;
	// Function for creating the headers for the matrix
	void createHeaders();
};

