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
//	*Masking matrix
//	*Error catching for reading a boolean matrix
//	*duplicate column numbers



template<class T>
class SparseMatrix
{
	public:
		SparseMatrix();
		void read();
		void print() const;
		~SparseMatrix();
		T parseValue(std::string str);
		void mask(SparseMatrix<bool> *s);
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
			continue;

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

/*
node ** - new node**[numofrows]
	 ||
	 ||
	 ||
	 ||
	\  /
	 \/
|node*  | ---> new node (colNum, Value)
|node*  |
|node*  |
|node*  |
|node*  |
|node*  |
|node*  |
|node*  |
|node*  |
|node*  |
*/


//insert T data to index index
template<class T>
void SparseMatrix<T>::read()
{
	std::cout << "Enter number of rows, columns\n";

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

		//parse get each line and parse it to fcolNumigure out which node we are in
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

			std::cout << colsAndVals << std::endl;

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
	if(type.compare("b") == 0 && str.size() == 1 /*&& (val == 1 || val == 0)*/)
	{
		return val;
	}

	std::cout << "exception" << std::endl;
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

// template<class T>
// void SparseMatrix<T>::mask(SparseMatrix<bool> *bMatrix)
// {

// 	//not of same dimension case
// 	if(this->numRows != bMatrix->getNumberOfRows() || this->numCols != bMatrix->getNumberOfColumns())
// 	{
// 		std::cout << "Both Matrixes are not of same dimension" << std::endl;
// 		return;
// 	}

// 	//for each row in bool and this
// 	for(int i = 0; i < numRows; i++)
// 	{
// 		//Get boolean matrix row[i]
// 		node<bool> *boolRow = bMatrix->rows[i];

// 		//if bool matrix row[i] is nothing, safely delete everything in this->row[i]
// 		if(boolRow == 0)
// 		{
// 			std::cout << "boolRow doesnt exist, calling delete" << std::endl;
// 		}

// 		//if this matrix has nothing in the row[i], continue onto next row

// 		//look at first column in bool row[i] any column in this row[i] that is less then that, delete those nodes

// 		//if the node's col after deleting/moving is the same as bool's col, do the masking operation

// 		//if col after/deleting/moving is not the same as bool,move bool one over (if possible if not delete entire row) and go to if statement above for masking
// 	}

// }
