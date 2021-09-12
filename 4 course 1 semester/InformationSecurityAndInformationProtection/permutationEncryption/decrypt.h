#ifndef DECRYPT_H
#define DECRYPT_H

#include <iostream>
#include <string>
#include <vector>

bool decrypt(const std::string &toDecrypt, std::string &decrypt,
             const std::vector<int> &rowsRule,
             const std::vector<int> &colsRule);

#endif // DECRYPT_H
