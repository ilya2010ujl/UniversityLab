#include "profilestoragescheme.h"

profileStorageScheme::profileStorageScheme() : m_AN(), m_DA() {}

void profileStorageScheme::readAsPSS(std::istream &ifs)
{
    quint64 sizeAN, sizeDA;

    ifs >> sizeAN;

    m_AN.resize(sizeAN);

    for(quint64 i = 0; i < sizeAN; ++i)
    {
        ifs >> m_AN[i];
    }

    ifs >> sizeDA;

    m_DA.resize(sizeDA);

    for(quint64 i = 0; i < sizeDA; ++i)
    {
        ifs >> m_DA[i];
    }
}

void profileStorageScheme::writeAsPSS(std::ostream &ofs)
{
    quint64 sizeAN = m_AN.size(), sizeDA = m_DA.size();

    ofs << sizeAN << '\n';

    for(quint64 i = 0; i < sizeAN; ++i)
    {
        ofs << m_AN[i] << ' ';
    }

    ofs << '\n' << sizeDA << '\n';

    for(quint64 i = 0; i < sizeDA; ++i)
    {
        ofs << m_DA[i] << ' ';
    }
}

void profileStorageScheme::readAsMatrix(std::istream &ifs)
{
    quint64 sizeDA;

    ifs >> sizeDA;

    qreal tmp;

    for(quint64 i = 0; i < sizeDA; ++i)
    {
        for(quint64 j = 0; j < sizeDA; ++j)
        {
            ifs >> tmp;
            if(j > i)
            {
                continue;
            }
            else if(tmp)
            {
                while(j < i)
                {
                    m_AN.push_back(tmp);
                    ifs >> tmp;
                    ++j;
                }
                m_AN.push_back(tmp);

                m_DA.push_back(m_AN.size());
            }
        }
    }
}

void profileStorageScheme::writeAsMatrix(std::ostream &ofs)
{
    int sizeDA = m_DA.size();
    ofs << sizeDA << '\n';

    for (int i = 0; i < sizeDA; i++)
    {
        if (i == 0)
        {
            ofs << m_AN[0] << ' ';
        }
        else
        {
            for (int j = 0; j < i + m_DA[i - 1] - m_DA[i] + 1; j++)
            {
                ofs << 0 << ' ';
            }
            for (int j = m_DA[i - 1]; j < m_DA[i]; j++)
            {
                ofs << m_AN[j] << ' ';
            }
        }
        for (int j = i + 1; j < sizeDA; j++)
        {
            if (j + 1 + m_DA[j - 1] - m_DA[j] > i)
            {
                ofs << 0 << ' ';
            }
            else
            {
                ofs << m_AN[i + m_DA[j] - j - 1] << ' ';
            }
        }ofs << '\n';
    }
}

