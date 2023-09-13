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
	int constraintStart[4] = { 0, 81, 81 * 2, 81 * 3 }; // Each constraint's respective starting point

	for (int i(0); i < 729; i++) {

		
		for (int j(0); j < 324; j++) {
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

void SudokuDLXMatrix::solve() {
	createDLXMatrix();
}

void SudokuDLXMatrix::createDLXMatrix() {

	createHeaders();

	const vector<vector<bool>> boolMatrix = createBoolMatrix();
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