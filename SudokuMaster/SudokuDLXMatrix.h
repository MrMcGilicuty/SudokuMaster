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

	void solve(std::vector<std::vector<EditNumber*>>& board);

	// Function for creating the completed boolMatrix for solving the puzzle, compares the full matrix with the current board possitions
	vector<vector<bool>> compareMatricies(vector<vector<bool>>& boolMatrix, vector<vector<EditNumber*>>& currentBoard);

private:

	// Vectors for the different constraints
	vector<shared_ptr<DLXNode>> headers;

	vector<shared_ptr<DLXNode>> cRow;
	vector<vector<shared_ptr<DLXNode>>> constraints;

	// Function that creates the whole Boolean preset matrix
	vector<vector<bool>>& createBoolMatrix();
	
	// Function for running all sub-functions for creating all matricies
	void createDLXMatrix(std::vector<std::vector<EditNumber*>>& board);

	// Follows a recursive checklist to solve the puzzle
	void algorithmX(vector<vector<shared_ptr<DLXNode>>> solution);

	// Covers all the zeros to make the matrix only full of 1s
	void coverZero();

	// Covers a column header
	void coverHead(shared_ptr<DLXNode> column);

	// Uncovers a column header
	void uncoverHead(shared_ptr<DLXNode> column);

	// Covers a whole row
	void coverRow(shared_ptr<DLXNode> row);

	// Uncovers a whole row
	void uncoverRow(shared_ptr<DLXNode> row);
	
	// counts the amount of ones in each column
	shared_ptr<DLXNode> lowestOnesColumn(shared_ptr<DLXNode> origin);

	int numOnes(shared_ptr<DLXNode> head);

	// Function for creating the headers for the matrix
	void createHeaders();
};

