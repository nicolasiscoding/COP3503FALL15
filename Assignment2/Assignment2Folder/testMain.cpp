#include "SparseMatrix.cpp"
#include <string>

int main()
{
	SparseMatrix<int>* a = new SparseMatrix<int>();

	SparseMatrix<bool>* b = new SparseMatrix<bool>();

	SparseMatrix<int>* c = new SparseMatrix<int>();

	std::cout << "Reading Matrix A" <<std::endl;
	a->read();	

	std::cout << "Matrix A:" << std::endl;
	a->print();

	std::cout << "Reading Matrix B" <<std::endl;
	b->read();
	std::cout << "Matrix B, the boolean mask matrix" << std::endl;
	b->print();

	//masking
	a->mask(b, c);


	std::cout << "Matrix C, result:" << std::endl;
	c->print();

	std::cout <<"Deleting Matrix A" <<std::endl;
	delete a;

	std::cout <<"Deleting Matrix B" <<std::endl;
	delete b;

	std::cout <<"Deleting Matrix C" <<std::endl;
	delete c;


	return 0;
	// delete sp;
}