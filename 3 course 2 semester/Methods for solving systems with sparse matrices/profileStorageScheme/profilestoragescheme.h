#ifndef PROFILESTORAGESCHEME_H
#define PROFILESTORAGESCHEME_H

#include <QVector>
#include <iostream>

class profileStorageScheme
{
public:
    profileStorageScheme();

    void readAsPSS(std::istream &ifs);
    void writeAsPSS(std::ostream &ofs);

    void readAsMatrix(std::istream &ifs);
    void writeAsMatrix(std::ostream &ofs);
private:
    QVector<qreal> m_AN;
    QVector<qreal> m_DA;
};

#endif // PROFILESTORAGESCHEME_H
