#include "tools.h"

#include <algorithm>

bool haveRepeats(const std::vector<int> &vector)
{
  const int vectorSize = vector.size();

  for (int i = 0; i < vectorSize; ++i) {
    for (int j = i + 1; j < vectorSize; ++j) {
      if (vector[i] == vector[j]) {
        return true;
      }
    }
  }

  return false;
}

bool haveCorrectNumbers(const std::vector<int> &vector)
{
  const int vectorSize = vector.size();

  for (int i = 0; i < vectorSize; ++i) {
    if (std::find(vector.begin(), vector.end(), i) == vector.end()) {
      return false;
    }
  }

  return true;
}

std::string deleteFillSymbol(const std::string &string)
{
  const int stringSize = string.size();

  int lastFillSymbolIndex = stringSize;

  while (string[--lastFillSymbolIndex] == fillSymbol) {
  }

  return string.substr(0, lastFillSymbolIndex);
}

void readWordAndRules(std::istream &is, std::string &word,
                      std::vector<int> &rowsRule, std::vector<int> &colsRule)
{
  std::getline(is, word);

  int rowsCount;
  is >> rowsCount;

  int colsCount;
  is >> colsCount;

  rowsRule.resize(rowsCount);
  colsRule.resize(colsCount);

  for (int i = 0; i < rowsCount; ++i) {
    is >> rowsRule[i];
  }

  for (int i = 0; i < colsCount; ++i) {
    is >> colsRule[i];
  }
}

void writeWordAndRules(std::ostream &is, std::string &word,
                       std::vector<int> &rowsRule, std::vector<int> &colsRule)
{
  is << word << '\n';

  const int rowsCount = rowsRule.size();
  const int colsCount = colsRule.size();

  is << rowsCount << '\n' << colsCount << '\n';

  for (int i = 0; i < rowsCount; ++i) {
    is << rowsRule[i] << ' ';
  }
  is << '\n';

  for (int i = 0; i < colsCount; ++i) {
    is << colsRule[i] << ' ';
  }
  is << '\n';
}

// encrypt

void fillRows(const std::string &toEncrypt, matrix<char> &encryptMatrix,
              const std::vector<int> &rowsRule)
{
  const int toEncryptSize = toEncrypt.size();
  const int rowsCount = encryptMatrix.size();
  const int colsCount = encryptMatrix[0].size();

  for (int i = 0; i < rowsCount; ++i) {
    for (int j = 0; j < colsCount; ++j) {
      if (i * colsCount + j > toEncryptSize) {
        return;
      } else {
        encryptMatrix[rowsRule[i]][j] = toEncrypt[i * colsCount + j];
      }
    }
  }
}

std::string readCols(const matrix<char> &encryptMatrix,
                     const std::vector<int> &colsRule)
{
  const int rowsCount = encryptMatrix.size();
  const int colsCount = colsRule.size();

  std::string encrypted;
  encrypted.resize(rowsCount * colsCount);

  for (int i = 0; i < colsCount; ++i) {
    for (int j = 0; j < rowsCount; ++j) {
      encrypted[i * rowsCount + j] = encryptMatrix[j][colsRule[i]];
    }
  }

  return encrypted;
}

// decrypt

void fillCols(const std::string &toDecrypt, matrix<char> &decryptMatrix,
              const std::vector<int> &colsRule)
{
  const int rowsCount = decryptMatrix.size();
  const int colsCount = colsRule.size();

  for (int i = 0; i < colsCount; ++i) {
    for (int j = 0; j < rowsCount; ++j) {
      decryptMatrix[j][colsRule[i]] = toDecrypt[i * rowsCount + j];
    }
  }
}

std::string readRows(const matrix<char> &decryptMatrix,
                     const std::vector<int> &rowsRule)
{
  const int rowsCount = decryptMatrix.size();
  const int colsCount = decryptMatrix[0].size();

  std::string decrypt;
  decrypt.resize(rowsCount * colsCount);

  for (int i = 0; i < rowsCount; ++i) {
    for (int j = 0; j < colsCount; ++j) {
      decrypt[i * colsCount + j] = decryptMatrix[rowsRule[i]][j];
    }
  }

  return decrypt;
}
