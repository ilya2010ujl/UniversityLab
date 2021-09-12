#include "encrypt.h"

#include "tools.h"

#include <iostream>

bool encrypt(const std::string &toEncrypt, std::string &encrypted,
             const std::vector<int> &rowsRule,
             const std::vector<int> &colsRule)
{
  const int toEncryptSize = toEncrypt.size();
  const int rowCount = rowsRule.size();
  const int colCount = colsRule.size();

  if (haveRepeats(rowsRule) || haveRepeats(colsRule) ||
      !haveCorrectNumbers(rowsRule) || !haveCorrectNumbers(colsRule) ||
      (toEncryptSize > rowCount * colCount)) {
    std::cout << "wrong input data\n";
    return false;
  }

  matrix<char> encryptMatrix(rowCount, std::vector<char>(colCount, fillSymbol));

  fillRows(toEncrypt, encryptMatrix, rowsRule);

  encrypted = readCols(encryptMatrix, colsRule);

  return true;
}
