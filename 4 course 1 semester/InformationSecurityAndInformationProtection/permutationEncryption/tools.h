#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <vector>
#include <iostream>

template <class T> using matrix = std::vector<std::vector<T>>;
constexpr char fillSymbol = '~';

bool haveRepeats(const std::vector<int> &vector);

bool haveCorrectNumbers(const std::vector<int> &vector);

std::string deleteFillSymbol(const std::string &string);

void readWordAndRules(std::istream &is, std::string &word,
                      std::vector<int> &rowsRule, std::vector<int> &colsRule);

void writeWordAndRules(std::ostream &is, std::string &word,
                       std::vector<int> &rowsRule, std::vector<int> &colsRule);

// encrypt

void fillRows(const std::string &toEncrypt, matrix<char> &encryptMatrix,
              const std::vector<int> &rowsRule);

std::string readCols(const matrix<char> &encryptMatrix,
                     const std::vector<int> &colsRule);

// decrypt

void fillCols(const std::string &toDcrypt, matrix<char> &decryptMatrix,
              const std::vector<int> &coslRule);

std::string readRows(const matrix<char> &decryptMatrix,
                     const std::vector<int> &rowsRule);

#endif // TOOLS_H
