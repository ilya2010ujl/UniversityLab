#ifndef VECTORSPARSELINEFORMAT_H
#define VECTORSPARSELINEFORMAT_H

#include <iostream>
#include <QVector>

class VectorSparseLineFormat
{
public:
    VectorSparseLineFormat();

    void readAsVector(std::istream& is);
    void readAsSLF(std::istream& is);
    void writeAsVector(std::ostream& os);
    void writeAsSLF(std::ostream& os);

    quint64 span();

private:
    QVector<qreal> m_AN;
    QVector<quint64> m_JA;
    quint64 m_span; // размах

    friend VectorSparseLineFormat  sumExtendedRealPointerMethod(const VectorSparseLineFormat& left,
                                                         const VectorSparseLineFormat& right);

    friend VectorSparseLineFormat mergeVectorSLF(const VectorSparseLineFormat& left,
                                          const VectorSparseLineFormat& right);
};

VectorSparseLineFormat  sumExtendedRealPointerMethod(const VectorSparseLineFormat& left,
                                                     const VectorSparseLineFormat& right);

QVector<quint64> mergeQvectors(const QVector<quint64>& left,
                               const QVector<quint64>& right,
                               const quint64& span);

#endif // VECTORSPARSELINEFORMAT_H
