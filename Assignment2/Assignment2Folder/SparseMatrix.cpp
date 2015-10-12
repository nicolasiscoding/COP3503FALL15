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
		//using a node struct because it is light
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
		void intializeAllRowPointers();
		int numCols;
		int numRows;
		node** rows;
};

/* 

A nice illustration of how I stored everything

node ** = new node*[numRows]
	 ||
	 ||
	 ||
	 ||
	\  /
	 \/
|node*  | = new node (colNum, Value) -> new node(ColNum, Value)
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
	for(int i = 0; i < numRows; i++)
	{
		//if row is empty, skip
		if(rows[i] == 0)
		{

			continue;
		}

		node * toDelete = rows[i]; 

		while(toDelete->next != 0)
		{
			node* temp = toDelete;
			toDelete = toDelete->next;
			delete temp;
		}

		delete toDelete;
	}
	
	//delete pointer to pointer
	delete rows;
}

//method for initializing all pointers in row to zero, ran into case where OS was assigning garbage pointers
template<class T>
void SparseMatrix<T>::intializeAllRowPointers()
{
	for(int i = 0; i < numRows; i++)
	{
		rows[i] = 0;
	}
}

//basic print method
template<class T>
void SparseMatrix<T>::print() const
{
	std::cout << "rows = " << numRows << " columns = " << numCols << std::endl;


	std::stringstream ss; 
	for(int i = 0; i < numRows; i++)
	{
		if(rows[i] == 0)
		{
			std::cout << "row " << i+1 << "[]" <<std::endl;
			continue;
		}
		ss<< "row " << (i+1) <<"[";

		node* current = rows[i];

 		while(current != 0)
		{
			ss<< "col: " << current->column << " value: " << current->data << ", ";
			current = current->next;
		}

		std::string toPrint = ss.str().substr(0, ss.str().size()-2);
		std::cout << toPrint << "]" << std::endl;;
		ss.str(std::string());
	}
	std::cout << "" <<std::endl;
}

//A class to parse input and 
template<class T>
void SparseMatrix<T>::read()
{
	std::cout << "Enter number of rows, columns" <<std::endl;

	//read rows and columns
	std:: string rowsAndColsSTR;
	std::getline(std::cin, rowsAndColsSTR);

	numRows = atoi(rowsAndColsSTR.substr(0, rowsAndColsSTR.find(' ')).c_str());
	rowsAndColsSTR.erase(0, rowsAndColsSTR.find(' ')+ 1);
	numCols = atoi(rowsAndColsSTR.substr(0, rowsAndColsSTR.find(' ')).c_str());

	//declare rows array to hold nodes
	rows = new node*[numRows];
	intializeAllRowPointers();

	std::cout << "\n";
	
	for(int i = 0; i < numRows; i++)
	{
		//parse to get number of terms
		std::cout << "Enter number of terms in row " << (i+1) << std::endl;
		std::string numTermsstr;
		std::getline(std::cin, numTermsstr);
		int numTerms = atoi(numTermsstr.c_str());

		//if the number of terms in the row is zero, continue through the loop
		if(numTerms == 0)
		{
			rows[i] = 0;
			continue;
		}

		if(numTerms > numCols)
		{
			std::cout << "Error more terms then columns\n" << std::endl;
			continue;
		}

		//parse get each line and parse it to colNumigure out which node we are in
		std::cout << "Enter element's column, and value for each term in the row " << (i+1) << "\n";
		std::string colsAndVals;
		std::getline(std::cin, colsAndVals);

		//Always pointing to current node for efficiency
		rows[i] = 0;
		node *current = 0;

		//parse using space as delimeter
		while(numTerms != 0)
		{
			//parse column number
			int colNum = atoi(colsAndVals.substr(0, colsAndVals.find(' ')).c_str());
			colsAndVals.erase(0, colsAndVals.find(' ')+ 1);

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

			//Error handling
			//column parse to make sure that we are not putting an invalid entry in the matrix.
			if(colNum > numCols || colNum < 0)
			{
				std::cout << "Error " << colNum << " is an invalid column. Entry col:" << colNum << ", value: " << value << " will be skipped.\n" << std::endl;
				numTerms--;
				continue;
			}

			//check to see if column already exists
			if(getElementAt((i+1),colNum) != 0)
			{
				std::cout << "Error, value is already at column " << colNum << "\n"<< std::endl;
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
				current = new node(colNum, value);
				current->next = 0;
				//current = current->next;
				numTerms--;
				rows[i] = current;
				continue;	
			}

			//general case
			current->next = new node(colNum, value);
			current = current->next;
			current->next = 0;	
			numTerms--;		
		}
	}
}

//function for parsing value if the matrix is a boolean, or a int matrix
template<class T>
T SparseMatrix<T>::parseValue(std::string str)
{
	//depending on if the matrix is int or bool, wed handle this differently
	std::string type = typeid( T ).name();

	int val = atoi(str.c_str());
	if(type.compare("i") == 0)
	{
		return val;
	}

	//For boolean, value can either be zero  or one 
	if(type.compare("b") == 0 && str.size() == 1 && (val == 1 || val == 0))
	{
		return val;
	}

	if(type.compare("b") == 0)
	{
		std::cout << "Error, " << val << " is not a valid value for a boolean matrix\n" << std::endl;
		return 0;
	}

	std::cout << "Error encountered in parseValue function\n" << std::endl;
	return 0;
}

//simple getter function for number of columns
template<class T>
int SparseMatrix<T>::getNumberOfColumns()
{
	return numCols;
}

//simple getter function for number of rows
template<class T>
int SparseMatrix<T>::getNumberOfRows()
{
	return numRows;
}

//this is a private method for when other sparsematricies need to make a insert 
//(used for masking)
template<class T>
void SparseMatrix<T>::privateInsert(int row, int col, T val)
{
	//error handling
	if(row > numRows || col > numCols || row < 1 || col < 1)
	{
		std::cout << "Error, can not insert element at " << row << ", " << col << "\n"<< std::endl;
		return;
	}

	//if inserting at beginning of rows, make sure we tie row in
	if(rows[row-1] == 0)
	{
		rows[row-1] = new node(col, val);
		rows[row-1]->next = 0;
		return;
	}

	//iterate through the rows to the second to last row
	node *conductor = rows[row-1];
	while(conductor->next != 0)
	{
		if(conductor->column == col)
		{
			std::cout << "Element exists, can not overwrite.\n\n" << std::endl;
			return;
		}
		conductor = conductor->next;
	}

	//if on last column and its the one we are looking for
	if(conductor->column == col)
	{
		return;
	}

	conductor->next = new node(col, val);
	conductor->next->next = 0;
}

//getter function to get a specific element given a location
template<class T>
T SparseMatrix<T>::getElementAt(int row, int col)
{
	//error handling
	if(row > numRows || col > numCols || row < 1 || col < 1)
	{
		std::cout << "Error, can not retrieve element at " << row << ", " << col <<"\n"<< std::endl;
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

//mask function takes in a bool matrix, and another matrix of the same type
template<class T>
void SparseMatrix<T>::mask(SparseMatrix<bool> *bMatrix, SparseMatrix<T> *matrixToMask)
{
	//not of same dimension case
	if(this->numRows != bMatrix->getNumberOfRows() || this->numCols != bMatrix->getNumberOfColumns())
	{
		std::cout << "Both Matrixes are not of same dimension\n" << std::endl;
		return;
	}

	if(matrixToMask->numRows != 0 || matrixToMask->numCols !=0)
	{
		std::cout << "Error, the matrix to mask onto is not empty, can not mask\n" << std::endl;
	}

	//instanciate values in maskedMatrix
	matrixToMask->numRows = this->numRows;
	matrixToMask->numCols = this->numCols;
	matrixToMask->rows = new node*[numRows];
	matrixToMask->intializeAllRowPointers();

	for(int i = 1; i <= numRows; i++)
	{
		for(int j = 1; j <= numCols; j++)
		{
			T Ival = getElementAt((i), (j));
			bool bval = bMatrix->getElementAt((i), (j));

			if(Ival == 0 || bval == 0)
			{
				continue;
			}

			matrixToMask->privateInsert(i, j, Ival);
		}
	}
}


