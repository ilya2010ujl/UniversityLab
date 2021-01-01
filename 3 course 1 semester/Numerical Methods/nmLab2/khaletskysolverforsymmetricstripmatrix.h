#ifndef KhaletskySolverForSymmetricStripMatrix_hpp
#define KhaletskySolverForSymmetricStripMatrix_hpp

#include <stdio.h>
#include "symmetricstripmatrix.h"

using namespace std;

class KhaletskySolverForSymmetricStripMatrix
{
public:
    KhaletskySolverForSymmetricStripMatrix(){}

    bool Solve(SymmetricStripMatrix matrix,
               const vector<double> &result,
               vector<double> &answer,
               bool needToPrintResult = false);

    bool Solve(SymmetricStripMatrix matrix,
               vector<double> expectedAnswer,
               vector<double> &answer,
               double &error,
               bool needToPrintResult = false);
    double CountError(SymmetricStripMatrix matrix,
                      vector<double> expectedAnswer,
                      const vector<double> &answer);

    void PrintEquation(SymmetricStripMatrix matrix,
                       const vector<double> &result,
                       const vector<double> &answer);
};

#endif /* KhaletskySolverForSymmetricStripMatrix_hpp */
