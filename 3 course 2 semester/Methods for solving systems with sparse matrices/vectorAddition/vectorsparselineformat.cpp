#include "vectorsparselineformat.h"

VectorSparseLineFormat::VectorSparseLineFormat() : m_AN(), m_JA(), m_span(0) {}

void VectorSparseLineFormat::readAsVector(std::istream &is)
{
    int size;
    is >> size;

    double tmp;

    for(int i = 0; i < size; ++i)
    {
        is >> tmp;
        if(tmp)
        {
            m_AN.push_back(tmp);
            m_JA.push_back(i);
            m_span = i;
        }
    }

    ++m_span;
}

void VectorSparseLineFormat::readAsSLF(std::istream &is)
{
    int ANSize;

    is >> ANSize;

    m_AN.resize(ANSize);
    m_JA.resize(ANSize);

    for(int i = 0; i < ANSize; ++i)
    {
        is >> m_AN[i];
    }

    is >> m_span;
    m_JA[0] = m_span;

    for(int i = 1; i < ANSize; ++i)
    {
        is >> m_JA[i];
        if(m_JA[i] > m_span)
        {
            m_span = m_JA[i];
        }
    }

    ++m_span;
}

void VectorSparseLineFormat::writeAsVector(std::ostream &os)
{
    os << m_span << '\n';

    qint64 tmpIndex;

    for(quint64 i = 0; i < m_span; ++i)
    {
        tmpIndex = m_JA.indexOf(i);

        if(tmpIndex != -1)
        {
            os << m_AN[tmpIndex];
        }
        else
        {
            os << 0;
        }
        os << ' ';
    }
}

void VectorSparseLineFormat::writeAsSLF(std::ostream &os)
{
    int ANSize = m_AN.size();

    os << ANSize << '\n';

    for(int i = 0; i < ANSize; ++i)
    {
        os << m_AN[i] << ' ';
    }

    os << '\n';

    for(int i = 0; i < ANSize; ++i)
    {
        os << m_JA[i] << ' ';
    }
}

quint64 VectorSparseLineFormat::span()
{
    return m_span;
}

QVector<quint64> mergeQvectors(const QVector<quint64> &left,
                               const QVector<quint64> &right,
                               const quint64 &span)
{
    QVector<bool> tmp(span + 1);

    for(int i = 0; i < left.size(); ++i)
    {
        tmp[left[i]] = true;
    }
    for(int i = 0; i < right.size(); ++i)
    {
        tmp[right[i]] = true;
    }

    QVector<quint64> result;

    for(quint64 i = 0; i < span + 1; ++i)
    {
        if(tmp[i])
        {
            result.push_back(i);
        }
    }

    return result;
}

VectorSparseLineFormat sumExtendedRealPointerMethod(const VectorSparseLineFormat &left,
                                                    const VectorSparseLineFormat &right)
{
    VectorSparseLineFormat result;

    quint64 maxSpan = qMax(left.m_span, right.m_span);

    result.m_JA = mergeQvectors(left.m_JA, right.m_JA, maxSpan);

    QVector<qreal> sum(maxSpan + 1, 0);

    for(int i = 0; i < left.m_JA.size(); ++i)
    {
        sum[left.m_JA[i]] += left.m_AN[i];
    }

    for(int i = 0; i < right.m_JA.size(); ++i)
    {
        sum[right.m_JA[i]] += right.m_AN[i];
    }

    result.m_span = maxSpan;

    for(int i = 0; i < result.m_JA.size(); ++i)
    {
        result.m_AN.push_back(sum[result.m_JA[i]]);
    }

    for(int i = 0; i < result.m_AN.size(); ++i)
    {
        if(!result.m_AN[i])
        {
            result.m_AN.erase(result.m_AN.begin() + i);
            result.m_JA.erase(result.m_JA.begin() + i);
            --i;
        }
    }

    return result;
}
