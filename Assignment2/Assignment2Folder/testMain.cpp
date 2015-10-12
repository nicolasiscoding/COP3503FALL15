#include "SparseMatrix.cpp"
#include <string>

int main()
{
	SparseMatrix<int>* iSp = new SparseMatrix<int>();

	SparseMatrix<bool>* bSp = new SparseMatrix<bool>();

	SparseMatrix<int>* cSp = new SparseMatrix<int>();

	std::cout << "Reading int Matrix\n" <<std::endl;
	iSp->read();	
	std::cout << "\nPrinting int Matrix\n" << std::endl;
	iSp->print();

	std::cout << "\nReading bool Matrix\n" <<std::endl;
	bSp->read();
	std::cout << "\nPrinting bool Matrix\n" << std::endl;
	bSp->print();

	// std::cout<< iSp->getElementAt(1, 1) << std::endl;

	std::cout << "\nMasking int matrix with bool matrix"<< std::endl;
	iSp->mask(bSp, cSp);


	std::cout << "\nPrinting masked C Matrix" << std::endl;
	cSp->print();

	// delete sp;
}