#include "SudokuDLXMatrix.h"
#include "DLXNode.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

SudokuDLXMatrix::SudokuDLXMatrix() {

}

vector<vector<bool>> SudokuDLXMatrix::createBoolMatrix() {
	
	for (int i(0); i < 729; i++) {

		
		for (int j(0); j < 324; j++) {

			bool node;

			// Constraint 1
			if (j / 81 == 0) {

				// Checks in the first constraint if there should be a 1 or a 0
				i / 9 == j ? node = 1 : node = 0;

			}
			// Constraint 2
			else if (j / 81 == 1) {

				// Checks in the second constraint if there should be a 1 or a 0
				(i / 81 + 1) * 81 + (i % 9) == j ? node = 1 : node = 0;

			}
			// Constraint 3
			else if (j / 81 == 2) {

				node = 0;

			}
			// Constraint 4
			else if (j / 81 == 3) {

				node = 0;
				
			}
			row.push_back(node);
		}
		boolMatrix.push_back(row);
		row.clear();
	}

	return boolMatrix;
}

void SudokuDLXMatrix::createHeaders() {
	// 4 different contraints
	for (int i(0); i < 4; i++) {

		// 9 different sections for each constraint
		for (int j(0); j < 9; j++) {

			// 1-9 in each section for the constraint
			for (int k(0); k < 9; i++) {
				
				DLXNode head;
				head.header = true;
				headers.push_back(make_shared<DLXNode>(head));
			}
		}
	}
}