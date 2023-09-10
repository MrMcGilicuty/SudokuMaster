#include "SudokuDLXMatrix.h"
#include "DLXNode.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

void SudokuDLXMatrix::createDLXPreset() {
	int x = 0;
	// 4 different contraints
	for (int i(0); i < 4; i++) {

		// 9 different sections for each constraint
		for (int j(0); j < 9; j++) {

			// 1-9 in each section for the constraint
			for (int k(0); k < 9; i++) {

				// Every 1-9 should have it's own 1-9 for each cell
				for (int r(0); r < 9; r++) {
					
					if (i == 0) {
						if (r == 0) {
							createHeaders();
						}
						DLXNode node;

					}
					
					x++;
				}
			}
		}
	}
}

void SudokuDLXMatrix::createHeaders() {
	// 4 different contraints
	for (int i(0); i < 4; i++) {

		// 9 different sections for each constraint
		for (int j(0); j < 9; j++) {

			// 1-9 in each section for the constraint
			for (int k(0); k < 9; i++) {
				
				DLXNode head;

			}
		}
	}
}