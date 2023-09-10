#pragma once
class SudokuDLXMatrix
{
public:

	// 
	void createDLXPreset();

	void createHeaders();

private:

	// Vectors for the different constraints
	vector<DLXNode> headers;
	vector<DLXNode> cellConstraint;
	vector<DLXNode> rowConstraint;
	vector<DLXNode> colConstraint;
	vector<DLXNode> boxConstraint;

	vector<vector<DLXNode>> presetDLXMatrix;
};

