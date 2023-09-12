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

void SudokuDLXMatrix::createDLXMatrix(vector<vector<bool>> boolMatrix, vector<vector<EditNumber*>> currentBoard) {

	createHeaders();

}

void SudokuDLXMatrix::createHeaders() {

	DLXNode head;
	for (int i(0); i < 323; i++) {
		DLXNode node;
		node.header = true;
		node.setRow(0);
		node.ID = i + 1;

		// First time
		if (!i) {
			head.header = true;
			head.setRow(0);
			head.ID = 0;
			headers.push_back(make_shared<DLXNode>(head));

			node.left  = headers[0];
			node.right = headers[0];
			headers[0]->right = make_shared<DLXNode>(node);
			headers[0]->left  = make_shared<DLXNode>(node);
		}
		else {
			node.left = headers[i];
			node.right = headers[0];
			headers[i]->right = make_shared<DLXNode>(node);
			headers[0]->left = make_shared<DLXNode>(node);
		}
		headers.push_back(make_shared<DLXNode>(node));
	}

}