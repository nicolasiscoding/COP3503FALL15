#include "SparseMatrix.cpp"
#include <string>

int main()
{
	SparseMatrix<int>* iSp = new SparseMatrix<int>();

	SparseMatrix<bool>* bSp = new SparseMatrix<bool>();

	SparseMatrix<int>* cSp = new SparseMatrix<int>();

	iSp->read();
	iSp->print();

	bSp->read();
	bSp->print();

	std::cout<< iSp->getElementAt(1, 1) << std::endl;

	std::cout << "\n"<< std::endl;
	iSp->mask(bSp, cSp);


	std::cout << "Printing masked C Matrix" << std::endl;
	cSp->print();

	// delete sp;
}