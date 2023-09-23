#include "SudokuDLXMatrix.h"
#include "DLXNode.h"
#include "EditNumber.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

SudokuDLXMatrix::SudokuDLXMatrix() {

}

vector<vector<bool>> SudokuDLXMatrix::createBoolMatrix() {
	unsigned int constraintStart[4] = { 0, 81, 81 * 2, 81 * 3 }; // Each constraint's respective starting point

	for (unsigned int i(0); i < 729; i++) {

		
		for (unsigned int j(0); j < 324; j++) {
			int constraintIndex = j / 81;
			bool node;

			// Constraint 1
			if (constraintIndex == 0) {

				// Checks in the first constraint if there should be a 1 or a 0
				i / 9 == j ? node = 1 : node = 0;

			}
			// Constraint 2
			else if (constraintIndex == 1) {

				// Checks in the second constraint if there should be a 1 or a 0
				// Gets the starting points
				(i / 81) * 9

					// Offsets the Diagonal
					+ (i % 9) 

					// 81 is the 2nd Constraint starting point
					+ constraintStart[1] == j ? node = 1 : node = 0;

			}
			// Constraint 3
			else if (constraintIndex == 2) {

				// Checks in the Third constraint if there should be a 1 or a 0
				// Gets the starting points of the diagonal.
				((i / 9) % 9) * 9 

					// Offsets the Diagonal
					+ (i % 9)
					// 81 * 2 is the 3rd Constraint starting point
					+ constraintStart[2] == j ? node = 1 : node = 0;

			}
			// Constraint 4
			else if (constraintIndex == 3) {

				// Checks in the Fourth constraint if there should be a 1 or a 0
				// splits the x-values into 1-3 along the whole height
				(i / 243) * 27

					// Splits every 1-3 into 1-9 then 1-3
					+ ((i / 27) % 3) * 9

					// Offsets the Diagonal
					+ (i % 9)

					// 81 * 3 is the 4th Constraint starting point
					+ constraintStart[3] == j ? node = 1 : node = 0;
				
			}
			row.push_back(node);
		}
		boolMatrix.push_back(row);
		row.clear();
	}

	return boolMatrix;
}

void SudokuDLXMatrix::solve(std::vector<std::vector<EditNumber*>>& board) {

	createDLXMatrix(board);
	coverZero();
	algorithmX(constraints);
}

void SudokuDLXMatrix::coverZero() {
	for (auto& row : constraints) {
		for (auto& link : row) {
			// If the number isn't a header
			if (!link->header) {
				if (!link->one) {
					link->cover();
				}
			}
		}
	}
}

int SudokuDLXMatrix::numOnes(shared_ptr<DLXNode> head) {
	int numOnes = 0;
	do {
		head = head->down;
		if (head->one)
			numOnes++;
	} while (!head->header);

	return numOnes;
}

bool SudokuDLXMatrix::matrixEmpty() {
	bool empty = true;
	for (auto& head : headers) {
		if (!head->down->header)
			empty = false;
	}
	return empty;
}

void SudokuDLXMatrix::algorithmX(vector<vector<shared_ptr<DLXNode>>> matrix) {
	// https://en.wikipedia.org/wiki/Knuth%27s_Algorithm_X
	//  /\
	// Algorithm used to efficiently find all solutions to a sudoku puzzle.

	vector<shared_ptr<DLXNode>> partial;
	if (matrixEmpty()) {

		for (auto& head : headers) {
			numOnes(head);
		}

	}
}

void SudokuDLXMatrix::createDLXMatrix(vector<vector<EditNumber*>>& board) {

	createHeaders();

	const vector<vector<bool>> boolMatrix = compareMatricies(createBoolMatrix(), board);
	
	int i = 0, j = 0;

	for (const auto& rows : boolMatrix) {

		for (const bool& num : rows) {
			DLXNode node;
			// The first time through a row
			if (!j) {
				node.setRow(i);
				num ? node.one = 1 : node.one = 0;

				// If this is the first row
				if (!i) {
					// Set the up/down
					node.up   = headers[0];
					node.down = headers[0];
					headers[0]->up   = make_shared<DLXNode>(node);
					headers[0]->down = make_shared<DLXNode>(node);
				}
				// Gaurenteed to have an up value if it's not the first row
				else {
					node.up   = constraints[i - 1][j];
					node.down = headers[j];
					constraints[i - 1][j]->down = make_shared<DLXNode>(node);

				}
			}
			else {
				
				node.setRow(i);
				num ? node.one = 1 : node.one = 0;

				// Gaurenteed to have a left value if it's not the first time
				node.left  = cRow[j - 1];
				node.right = cRow[0];
				cRow[j - 1]->right = make_shared<DLXNode>(node);
				cRow[0]->left      = make_shared<DLXNode>(node);

				// If this is the first row
				if (!i) {
					// Set the up/down
					node.up   = headers[j];
					node.down = headers[j];
					headers[j]->up   = make_shared<DLXNode>(node);
					headers[j]->down = make_shared<DLXNode>(node);
				}
				// Gaurenteed to have an up value if it's not the first row
				else {
					node.up = constraints[i - 1][j];
					node.down = headers[j];
					constraints[i - 1][j]->down = make_shared<DLXNode>(node);
				}

				

				
			}
			cRow.push_back(make_shared<DLXNode>(node));
			j++;
		}
		constraints.push_back(cRow);
		cRow.clear();
		i++;
		j = 0;
	}
}

vector<vector<bool>> SudokuDLXMatrix::compareMatricies(vector<vector<bool>> boolMatrix, vector<vector<EditNumber*>>& currentBoard) {

	for (int i(0); i < 9; i++) {
		for (int j(0); j < 9; j++) {

			int buff;

			// Switches the x and y values of the board vector because it counts (x,y) where the boolMatrix counts (y,x)
			if ((bool)currentBoard[i][j]->getID()) {
				buff = currentBoard[i][j]->getNumber();
				currentBoard[i][j]->setString(to_string(currentBoard[j][i]->getNumber()));
				currentBoard[j][i]->setString(to_string(buff));
				currentBoard[i][j]->setID(0);
				currentBoard[j][i]->setID(0);
			}
		}
	}

	int k = 0, h = 0;
	for (const auto& row : currentBoard) {

		for (const auto& cell : row) {

			int num = cell->getNumber(); // Index of the current number on the board

			if (num != 0) {
				// Get the number into Index form
				num--;

				for (int i(0); i < 9; i++) {

					// Gets the starting position for the 9 rows that are going to change
					const int rowStart = k * 9;
					// Grabing the current starting row
					auto& rows = boolMatrix[rowStart + i];
					bool rowClear = false;

					for (int j(0); j < rows.size(); j++) {

						// If the row hasn't been declared clear and the number is at a spot that shouldn't get deleted
						if (!rowClear && i % 9 - num == 0 && rows[j] == 1) {
							// Set the row to be cleared
							rowClear = true;

							for (int q(0); q < 9; q++) {
								boolMatrix[rowStart + q][j] = 0;
							}
							boolMatrix[rowStart + num][j] = 1;
						}
						else {
							
							if (rowClear && rows[j] == 1 && i % 9 - num == 0) {

								for (int q(0); q < 81; q++) {
									boolMatrix[num + (q * 9)][j] = 0;
								}
							}
							else
								rows[j] = 0;
						}
					}
				}
			}
			k++;
		}
		h++;
	}

	for (int i(0); i < 9; i++) {
		for (int j(0); j < 9; j++) {

			int buff;

			// Switches the x and y values of the board vector because it counts (x,y) where the boolMatrix counts (y,x)
			if (!(bool)currentBoard[i][j]->getID()) {
				buff = currentBoard[i][j]->getNumber();
				currentBoard[i][j]->setString(to_string(currentBoard[j][i]->getNumber()));
				currentBoard[j][i]->setString(to_string(buff));
				currentBoard[i][j]->setID(1);
				currentBoard[j][i]->setID(1);
			}
			if (currentBoard[i][j]->getNumber() == 0)
				currentBoard[i][j]->setString("");
		}
	}

	return boolMatrix;
}

void SudokuDLXMatrix::createHeaders() {

	DLXNode head;
	head.header = true;
	head.setRow(0);
	head.ID = 0;
	for (int i(0); i < 323; i++) {
		DLXNode node;
		node.header = true;
		node.setRow(0);
		node.ID = i + 1;

		// First time
		if (!i) {
			headers.push_back(make_shared<DLXNode>(head));

			node.left  = headers[0];
			node.right = headers[0];
			headers[0]->right = make_shared<DLXNode>(node);
			headers[0]->left  = make_shared<DLXNode>(node);
		}
		else {
			node.left  = headers[i];
			node.right = headers[0];
			headers[i]->right = make_shared<DLXNode>(node);
			headers[0]->left  = make_shared<DLXNode>(node);
		}
		headers.push_back(make_shared<DLXNode>(node));
	}

}