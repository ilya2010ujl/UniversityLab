#ifndef SYSTEM_H
#define SYSTEM_H

#include <QVector>

class System
{
public:
    System(QVector<double> a,
     QVector<double> b,
     QVector<double> c,
     QVector<double> f,
    const unsigned int &WhenP,
     QVector<double> p,
    const unsigned int &WhenQ,
     QVector<double> q);

    ~System();

    bool solveSystem(QVector<double> &answer);
private:
    bool FirstStep();
    bool SecondStep();
    bool ThirdStep();
    bool FourthStep();

    static void DataToPointers(const QVector<double> &data, QVector<double *> &pointers);
    static void PointersToData(const QVector<double *> &pointers, QVector<double> &data);
private:
    QVector<double *> m_a; // главная диагональ
    QVector<double *> m_b; // верхняя кодиагональ
    QVector<double *> m_c; // нижняя кодиагональ
    QVector<double *> m_f;

    unsigned int m_WhenP; // на какой строке стоит p
    QVector<double *> m_p; // p выше чем q

    unsigned int m_WhenQ; // на какой строке стоит q
    QVector<double *> m_q;

    friend std::ostream& operator<< (std::ostream &out, const System &system);
};

std::ostream& operator<< (std::ostream &out, const System &system);

#endif // SYSTEM_H
