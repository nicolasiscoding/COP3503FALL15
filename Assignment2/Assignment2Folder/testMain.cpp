#include "SparseMatrix.cpp"
#include <string>

int main()
{
	SparseMatrix<int>* iSp = new SparseMatrix<int>();

	SparseMatrix<bool>* bSp = new SparseMatrix<bool>();

	iSp->read();
	iSp->print();

	bSp->read();
	bSp->print();

	std::cout<< iSp->getElementAt(1, 1) << std::endl;
	//iSp->mask(bSp);

	// delete sp;
}