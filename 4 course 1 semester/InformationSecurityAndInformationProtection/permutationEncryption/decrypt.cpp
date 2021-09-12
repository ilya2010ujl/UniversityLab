#include "decrypt.h"

#include "tools.h"

bool decrypt(const std::string &toDecrypt, std::string &decrypt,
             const std::vector<int> &rowsRule,
             const std::vector<int> &colsRule)
{
  const int toDecryptSize = toDecrypt.size();
  const int rowCount = rowsRule.size();
  const int colCount = colsRule.size();

  if (haveRepeats(rowsRule) || haveRepeats(colsRule) ||
      !haveCorrectNumbers(rowsRule) || !haveCorrectNumbers(colsRule) ||
      (toDecryptSize != rowCount * colCount)) {
    std::cout << "wrong input data\n";
    return false;
  }

  matrix<char> decryptMatrix(rowCount, std::vector<char>(colCount, fillSymbol));

  fillCols(toDecrypt, decryptMatrix, colsRule);

  decrypt = readRows(decryptMatrix, rowsRule);

  decrypt = deleteFillSymbol(decrypt);

  return true;
}
