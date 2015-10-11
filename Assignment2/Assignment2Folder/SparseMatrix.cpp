#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <typeinfo>

//Name:				Nicolas Fry
//UF ID:			
//GatorID:			nicolascoding
//Discussion Section: 1085
//Assignment 2
//Sparse Matrix 


//To do:
//	*Use Inhertiance/OOP design a interface
//	*Implement case handling of matrix that is not sorted
// 	*taking a already made 'C' matrix and making sure if works as needed

template<class T>
class SparseMatrix 
{
	public:
		SparseMatrix();
		void read();
		void print() const;
		~SparseMatrix();
		T parseValue(std::string str);
		void mask(SparseMatrix<bool> *bMatrix, SparseMatrix<T> *matrixToMask);
		int getNumberOfRows();
		int getNumberOfColumns();
		T getElementAt(int row, int col);

	private:
		struct node
		{
			//next node
			node* next;
			int column; 
			T data;
			node(int col, T &dat)
			{
				column = col;
				data = dat;
			}

		};

		void privateInsert(int row, int col, T val);
		int numCols;
		int numRows;
		node** rows;
};


//constructor
template<class T>
SparseMatrix<T>::SparseMatrix()
{
	rows = 0;		//initialize root and last pointers to null
	numRows = 0;
	numCols = 0;
}

//Destructor implementation
template<class T>
SparseMatrix<T>::~SparseMatrix()
{
	// int fullsize = size();	//Figure out size and deallocate each memory address
	// node * toDelete; 
	// int i = 0;
	// while(i++ < fullsize)
	// {
	// 	toDelete = root;
	// 	root = root->next;
	// 	delete toDelete;
	// }
	std::cout <<" " << std::endl;
}

template<class T>
void SparseMatrix<T>::print() const
{
	std::cout << "\n\nPrinting method" << std::endl;
	std::cout << "rows = " << numRows << " columns = " << numCols << "\n" << std::endl;

	for(int i = 0; i < numRows; i++)
	{
		if(rows[i] == 0)
		{
			std::cout << "Row " << i+1 << " is empty skipping on print" << std::endl;
			continue;
		}

		std::cout<< "row " << (i+1) <<"[";

		//node** rowPtr = rows[i];
		node* current = rows[i];

 		while(current != 0)
		{
			//std::cout << "Pointer address " << current;
			std::cout<< "col: " << current->column << " value: " << current->data << ", ";
			current = current->next;
		}

		std::cout << "]" << std::endl;
	}
}

/* A nice illustration of how I stored everything
node ** - new node**[numofrows]
	 ||
	 ||
	 ||
	 ||
	\  /
	 \/
|node*  | ---> new node (colNum, Value) -> new node(ColNum, Value)
|node*  |
|node*  |
|node*  |
|node*  |
|node*  |
|node*  | -> \first element \ - > \.....\ -> \lastNode\ ->
|node*  |
|node*  |
|node*  |
*/


//insert T data to index index
template<class T>
void SparseMatrix<T>::read()
{
	std::cout << "Beginning Reading for new Matrix\n\nEnter number of rows, columns\n";

	//read rows and columns
	std:: string rowsAndColsSTR;
	std::getline(std::cin, rowsAndColsSTR);

	numRows = atoi(rowsAndColsSTR.substr(0, rowsAndColsSTR.find(' ')).c_str());
	rowsAndColsSTR.erase(0, rowsAndColsSTR.find(' ')+ 1);
	numCols = atoi(rowsAndColsSTR.substr(0, rowsAndColsSTR.find(' ')).c_str());

	//declare rows array to hold nodes

	//double pointer to nodes = new *node[Num of rows]
	rows = new node*[numRows];

	std::cout << "\n";
	
	for(int i = 0; i < numRows; i++)
	{
		std::cout << "Enter number of terms in row " << (i+1) << std::endl;

		std::string numTermsstr;

		std::getline(std::cin, numTermsstr);
		int numTerms = atoi(numTermsstr.c_str());

		//if the number of terms in the row is zero, continue through the loop
		if(numTerms == 0)
		{
			continue;
		}

		if(numTerms > numCols)
		{
			std::cout << "Error more terms then columns" << std::endl;
			continue;
		}

		//parse get each line and parse it to colNumigure out which node we are in
		std::cout << "Enter element's column, and value for each term in the row " << (i+1) << "\n";
		std::string colsAndVals;
		std::getline(std::cin, colsAndVals);

		//Always pointing to current node for efficiency
		rows[i] = 0;
		node *current = 0;
		while(numTerms != 0)
		{
			//parse column number
			int colNum = atoi(colsAndVals.substr(0, colsAndVals.find(' ')).c_str());
			colsAndVals.erase(0, colsAndVals.find(' ')+ 1);

			// std::cout << colsAndVals << std::endl;

			//Declare the value to be saved in the node
			T value;

			//Determine if we are on the last term or the general case
			if(numTerms == 1)
			{
				value = parseValue(colsAndVals.substr(0));
			}
			else	//generalcase
			{
				//parse value of T
				value = parseValue(colsAndVals.substr(0, colsAndVals.find(' ')));
				colsAndVals.erase(0, colsAndVals.find(' ')+ 1);
			}

			//column parse to make sure that we are not putting an invalid entry in the matrix.
			if(colNum > numCols || colNum < 0)
			{
				std::cout << "Error " << colNum << " is an invalid column. Entry col:" << colNum << ", value: " << value << " will be skipped." << std::endl;
				numTerms--;
				continue;
			}

			if(getElementAt((i+1),colNum) != 0)
			{
				std::cout << "Error, value is already at column " << colNum << std::endl;
				numTerms--;
				continue;
			}

			//if matrix is sparse, we do not want 0s. Skip inserting all 0 entries. 
			if (value == 0)
			{
				numTerms--;
				continue;
			}

			

			//first case where there are no nodes in the row
			if(current == 0)
			{
				std::cout << "Inserting beginning node " << std::endl;
				current = new node(colNum, value);
				current->next = 0;
				//current = current->next;
				numTerms--;
				rows[i] = current;
				continue;	
			}

			current->next = new node(colNum, value);
			current = current->next;
			current->next = 0;	
			numTerms--;		
		}
	}
}

template<class T>
T SparseMatrix<T>::parseValue(std::string str)
{
	
	std::string type = typeid( T ).name();

	int val = atoi(str.c_str());
	if(type.compare("i") == 0)
	{
		return val;
	}

	//For Parse, 
	if(type.compare("b") == 0 && str.size() == 1 && (val == 1 || val == 0))
	{
		return val;
	}

	if(type.compare("b") == 0)
	{
		std::cout << "Error, " << val << " is not a valid value for a boolean matrix" << std::endl;
		return 0;
	}

	std::cout << "Error encountered in parseValue function" << std::endl;
	return 0;
}

template<class T>
int SparseMatrix<T>::getNumberOfColumns()
{
	return numCols;
}

template<class T>
int SparseMatrix<T>::getNumberOfRows()
{
	return numRows;
}

template<class T>
void SparseMatrix<T>::privateInsert(int row, int col, T val)
{
	//error handling

	//std::cout << "\nprivate insert method" << std::endl;

	if(row > numRows || col > numCols || row < 1 || col < 1)
	{
		std::cout << "Error, can not insert element at " << row << ", " << col << std::endl;
		return;
	}

	node *conductor = rows[row-1];
	//std::cout << "Conductor's address: " << conductor << std::endl;
	bool found = false;
	while(conductor != 0)
	{
		std::cout << "Inside while loop" << std::endl;
		std:: cout << "Conductor's address: " << conductor << std::endl;
		if(conductor->column == col)
		{
			std::cout << "Found a column that is similar" << std::endl;
			found = true;
			break;
		}

		conductor = conductor->next;
	}

	if(found)
	{
		std::cout << "Element exists, can not overwrite.";
		return;
	}


	conductor = new node(col, val);

	//if inserting at beginning of rows, make sure we tie row in
	if(rows[row-1] == 0)
	{
		rows[row-1] = conductor;
	}
	conductor->next = 0;
}

template<class T>
T SparseMatrix<T>::getElementAt(int row, int col)
{
	//error handling
	if(row > numRows || col > numCols || row < 1 || col < 1)
	{
		std::cout << "Error, can not retrieve element at " << row << ", " << col << std::endl;
		return 0;
	}

	node *conductor = rows[row-1];

	bool found = false;
	while(conductor != 0)
	{
		if(conductor->column == col)
		{
			found = true;
			break;
		}

		conductor = conductor->next;
	}

	if(!found)
	{
		return 0;
	}

	return conductor->data;
}

template<class T>
void SparseMatrix<T>::mask(SparseMatrix<bool> *bMatrix, SparseMatrix<T> *matrixToMask)
{
	//not of same dimension case
	if(this->numRows != bMatrix->getNumberOfRows() || this->numCols != bMatrix->getNumberOfColumns())
	{
		std::cout << "Both Matrixes are not of same dimension" << std::endl;
		return;
	}

	if(matrixToMask->numRows != 0 || matrixToMask->numCols !=0)
	{
		std::cout << "Error, the matrix to mask onto is not empty, can not mask" << std::endl;
	}

	//instanciate values in maskedMatrix
	matrixToMask->numRows = this->numRows;
	matrixToMask->numCols = this->numCols;
	matrixToMask->rows = new node*[numRows];

	// std::cout << "Masked Matrix rows: " << matrixToMask->numRows << " Masked Matrix Cols: " << matrixToMask ->numCols << std::endl;

	//for each row in bool and this
	for(int i = 1; i <= numRows; i++)
	{
		for(int j = 1; j <= numCols; j++)
		{
			T Ival = getElementAt((i), (j));
			bool bval = bMatrix->getElementAt((i), (j));

			// std::cout << "value at row " << i << " col " << j << std::endl; 
			// std::cout << "int matrix val: " << Ival << "\nbool matrix val: " << bval << std::endl;

			if(Ival == 0 || bval == 0)
			{
				continue;
			}

			matrixToMask->privateInsert(i, j, Ival);
			// std::cout << "Mask complete for row " << i << " col " << j << std::endl;

		}
	}
	/*

	//Get boolean matrix row[i]
		node* boolRow = bMatrix->rows[i];

		//if bool matrix row[i] is nothing, safely delete everything in this->row[i]
		if(boolRow == 0)
		{
			std::cout << "boolRow doesnt exist, calling delete" << std::endl;
		}

		//if this matrix has nothing in the row[i], continue onto next row

		//look at first column in bool row[i] any column in this row[i] that is less then that, delete those nodes

		//if the node's col after deleting/moving is the same as bool's col, do the masking operation

		//if col after/deleting/moving is not the same as bool,move bool one over (if possible if not delete entire row) and go to if statement above for masking
	
	*/

}
