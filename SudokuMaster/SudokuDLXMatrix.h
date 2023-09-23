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

	void solve(std::vector<std::vector<EditNumber*>>& board);

	vector<vector<shared_ptr<DLXNode>>> presetDLXMatrix;
	
	// Function for running all sub-functions for creating all matricies
	void createDLXMatrix(std::vector<std::vector<EditNumber*>>& board);

	// Function for creating the completed boolMatrix for solving the puzzle, compares the full matrix with the current board possitions
	vector<vector<bool>> compareMatricies(vector<vector<bool>> boolMatrix, vector<vector<EditNumber*>>& currentBoard);
private:
	// Vectors for the different constraints
	vector<shared_ptr<DLXNode>> headers;

	vector<shared_ptr<DLXNode>> cRow;
	vector<vector<shared_ptr<DLXNode>>> constraints;

	vector<bool> row;
	vector<vector<bool>> boolMatrix;

	//
	void algorithmX();


	

	// Function for creating the headers for the matrix
	void createHeaders();
};

