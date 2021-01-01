#include "system.h"

#include <iostream>
#include <QtMath>

System::System(QVector<double> a,
               QVector<double> b,
               QVector<double> c,
               QVector<double> f,
               const unsigned int &WhenP,
               QVector<double> p,
               const unsigned int &WhenQ,
               QVector<double> q) : m_WhenP(WhenP), m_WhenQ(WhenQ)
{
    Q_ASSERT(a.size() >= 5);
    Q_ASSERT(a.size() != 0);
    Q_ASSERT(a.size() == b.size());
    Q_ASSERT(a.size() == c.size());
    Q_ASSERT(a.size() == f.size());
    Q_ASSERT(a.size() == p.size());
    Q_ASSERT(a.size() == q.size());

    Q_ASSERT(static_cast<int>(m_WhenP) < a.size());
    Q_ASSERT(static_cast<int>(m_WhenQ) < a.size());
    Q_ASSERT(m_WhenQ - m_WhenP == 2);

    Q_ASSERT(b[0] == 0);
    Q_ASSERT(c[0] == 0);

    Q_ASSERT(p[WhenP] == a[WhenP]);
    Q_ASSERT(q[WhenQ] == a[WhenQ]);
    Q_ASSERT(p[WhenP + 1] == b[WhenP + 1]);
    Q_ASSERT(q[WhenQ + 1] == b[WhenQ + 1]);
    Q_ASSERT(p[WhenP - 1] == c[WhenP]);
    Q_ASSERT(q[WhenQ - 1] == c[WhenQ]);

    DataToPointers(a, m_a);
    DataToPointers(b, m_b);
    DataToPointers(c, m_c);
    DataToPointers(f, m_f);
    DataToPointers(p, m_p);
    DataToPointers(q, m_q);

    delete m_p[WhenP];
    m_p[WhenP] = m_a[WhenP];
    delete m_q[WhenQ];
    m_q[WhenQ] = m_a[WhenQ];
    delete m_p[WhenP + 1];
    m_p[WhenP + 1] = m_b[WhenP + 1];
    delete m_q[WhenQ + 1];
    m_q[WhenQ + 1] = m_b[WhenQ + 1];
    delete m_p[WhenP - 1];
    m_p[WhenP - 1] = m_c[WhenP];
    delete m_q[WhenQ - 1];
    m_q[WhenQ - 1] = m_c[WhenQ];
}

System::~System()
{
    for(int i = 0; i < m_a.size(); ++i)
    {
        delete m_a[i];
        delete m_c[i];
        delete m_b[i];
        delete m_f[i];
    }

    for(unsigned int i = 0; i < static_cast<unsigned int>(m_p.size()); ++i)
    {
        if(i == m_WhenP || i == m_WhenP + 1 || i == m_WhenP - 1) continue;

        delete m_p[i];
    }

    for(unsigned int i = 0; i < static_cast<unsigned int>(m_q.size()); ++i)
    {
        if(i == m_WhenQ || i == m_WhenQ + 1 || i == m_WhenQ - 1) continue;

        delete m_q[i];
    }
}

bool System::solveSystem(QVector<double> &answer)
{
    if (!this->FirstStep()) return false;
    if (!this->SecondStep()) return false;
    if (!this->ThirdStep()) return false;
    if (!this->FourthStep()) return false;

    QVector<double> result;
    PointersToData(m_f, result);

    answer = result;

    return true;
}

bool System::FirstStep()
{
    // можно забить на одинаковые строки из-за того что в начале будет 0
    for(unsigned int i = 0; i < m_WhenP; ++i)
    {
        if(*m_a[i] == 0) return false;

        *m_b[i + 1] /= *m_a[i];
        *m_f[i] /= *m_a[i];
        *m_a[i] = 1;

        *m_a[i + 1] -= *m_c[i + 1] * *m_b[i + 1];
        *m_f[i + 1] -= *m_c[i + 1] * *m_f[i];
        *m_c[i + 1] = 0;

        *m_p[i + 1] -= *m_p[i] * *m_b[i + 1];
        *m_f[m_WhenP] -= *m_p[i] * *m_f[i];
        *m_p[i] = 0;

        *m_q[i + 1] -= *m_q[i] * *m_b[i + 1];
        *m_f[m_WhenQ] -= *m_q[i] * *m_f[i];
        *m_q[i] = 0;
    }

    return true;
}

bool System::SecondStep()
{
    // можно забить на одинаковые строки из-за того что в начале будет 0
    for(unsigned int i = m_a.size() - 1; i > m_WhenQ; --i)
    {
        if(*m_a[i] == 0) return false;

        *m_c[i] /= *m_a[i];
        *m_f[i] /= *m_a[i];
        *m_a[i] = 1;

        *m_a[i - 1] -= *m_b[i] * *m_c[i];
        *m_f[i - 1] -= *m_b[i] * *m_f[i];
        *m_b[i] = 0;

        *m_p[i - 1] -= *m_p[i] * *m_c[i];
        *m_f[m_WhenP] -= *m_p[i] * *m_f[i];
        *m_p[i] = 0;

        *m_q[i - 1] -= *m_q[i] * *m_c[i];
        *m_f[m_WhenQ] -= *m_q[i] * *m_f[i];
        *m_q[i] = 0;
    }

    return true;
}

bool System::ThirdStep()
{
    int i = m_WhenP;

    if(*m_p[i] == 0) return false;

    *m_p[i + 1] /= *m_p[i];
    *m_p[i + 2] /= *m_p[i];
    *m_f[i] /= *m_p[i];
    *m_p[i] = 1;

    *m_a[i + 1] -= *m_c[i + 1] * *m_p[i + 1];
    *m_b[i + 2] -= *m_c[i + 1] * *m_p[i + 2];
    *m_f[i + 1] -= *m_c[i + 1] * *m_f[i];
    *m_c[i + 1] = 0;

    *m_q[i + 1] -= *m_q[i] * *m_p[i + 1];
    *m_q[i + 2] -= *m_q[i] * *m_p[i + 2];
    *m_f[i + 2] -= *m_q[i] * *m_f[i];
    *m_q[i] = 0;

    if(*m_a[i + 1] == 0) return false;

    *m_b[i + 2] /= *m_a[i + 1];
    *m_f[i + 1] /= *m_a[i + 1];
    *m_a[i + 1] = 1;

    *m_q[i + 2] -= *m_q[i + 1] * *m_b[i + 2];
    *m_f[i + 2] -= *m_q[i + 1] * *m_f[i + 1];
    *m_q[i + 1] = 0;

    if(*m_q[i + 2] == 0) return false;
    *m_f[i + 2] /= *m_q[i + 2];
    *m_q[i + 2] = 1;

    *m_f[i + 1] -= *m_b[i + 2] * *m_f[i + 2];
    *m_b[i + 2] = 0;

    *m_f[i] -= *m_p[i + 1] * *m_f[i + 1];
    *m_p[i + 1] = 0;

    *m_f[i] -= *m_p[i + 2] * *m_f[i + 2];
    *m_p[i + 2] = 0;

    return true;
}

bool System::FourthStep()
{
    for(int i = m_WhenP - 1; i >= 0; --i)
    {
        *m_f[i] -= *m_f[i + 1] * *m_b[i + 1];
        *m_b[i + 1] = 0;
    }

    for(int i = m_WhenQ + 1; i < m_f.size(); ++i)
    {
        *m_f[i] -= *m_c[i] * *m_f[i - 1];
        *m_c[i] = 0;
    }

    return true;
}

void System::DataToPointers(const QVector<double> &data, QVector<double *> &pointers)
{
    pointers.resize(data.size());

    for(int i = 0; i < data.size(); ++i)
    {
        pointers[i] = new double(data[i]);
    }
}

void System::PointersToData(const QVector<double *> &pointers, QVector<double> &data)
{
    data.resize(pointers.size());

    for(int i = 0; i < pointers.size(); ++i)
    {
        data[i] = *pointers[i];
    }
}

std::ostream &operator<<(std::ostream &out, const System &system)
{
    for (int i = 0; i < system.m_a.size(); ++i)
    {
        for (int j = 0; j < system.m_a.size(); ++j)
        {
            if(static_cast<unsigned int>(i) == system.m_WhenP)
            {
                out << *system.m_p[j] << ' ';
            }
            else if(static_cast<unsigned int>(i) == system.m_WhenQ)
            {
                out << *system.m_q[j] << ' ';
            }
            else if(i == j)
            {
                out << *system.m_a[i] << ' ';
            }
            else if(i - j == -1)
            {
                out << *system.m_b[i + 1] << ' ';
            }
            else if(i - j == 1)
            {
                out << *system.m_c[i] << ' ';
            }
            else
            {
                out << 0 << ' ';
            }
            out.width(7);
            out.precision(5);
        }
        out << '\t' << *system.m_f[i] << '\n';
    }

    return out;
}
