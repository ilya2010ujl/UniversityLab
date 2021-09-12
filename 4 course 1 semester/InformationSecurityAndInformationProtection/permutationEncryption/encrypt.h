#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <string>
#include <vector>

bool encrypt(const std::string &toEncrypt, std::string &encrypted,
             const std::vector<int> &rowsRule,
             const std::vector<int> &colsRule);

#endif // ENCRYPT_H
