#include <iostream>

#include "decrypt.h"
#include "encrypt.h"
#include "tools.h"

#include <fstream>

int main(int argc, char *argv[])
{
  std::ifstream ifs("toEncrypt.txt");

  std::string toEncrypt;
  std::vector<int> rowsRule;
  std::vector<int> colsRule;

  readWordAndRules(ifs, toEncrypt, rowsRule, colsRule);

  std::cout << "toEncrypt: " << toEncrypt << '\n';

  std::string encrypted;

  if (!encrypt(toEncrypt, encrypted, rowsRule, colsRule)) {
    std::cout << "encrypt error\n";
    return -1;
  } else {
    std::cout << "encrypted: " << encrypted << '\n';
  }

  std::ofstream ofs("toDecrypt.txt");

  writeWordAndRules(ofs, encrypted, rowsRule, colsRule);

  ofs.close();

  ifs.close();
  ifs.open("toDecrypt.txt");

  std::string toDecrypt;

  readWordAndRules(ifs, toDecrypt, rowsRule, colsRule);

  std::cout << "toDecrypt: " << toDecrypt << '\n';

  std::string decrypted;

  if (!decrypt(toDecrypt, decrypted, rowsRule, colsRule)) {
    std::cout << "decrypt error\n";
    return -1;
  } else {
    std::cout << "decrypted: " << decrypted << '\n';
  }

  return 0;
}
