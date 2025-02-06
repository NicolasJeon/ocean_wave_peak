#ifndef WAVEDATAPROXY_H
#define WAVEDATAPROXY_H

#include <QDebug>
#include <QSurfaceDataProxy>
#include <QObject>
#include <QtQml>
#include <QThread>
#include <QVector3D>
#include "WaveDataGenerator.h"

class WaveDataProxy : public QSurfaceDataProxy
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QVector3D highestPeakPos READ highestPeakPos NOTIFY highestPeakChanged)
    Q_PROPERTY(QVector3D highestPeakLabelPos READ highestPeakLabelPos CONSTANT)

public:
    WaveDataProxy();

    QVector3D highestPeakPos() const { return m_highestPeakPos; }
    QVector3D highestPeakLabelPos() const { return m_highestPeakLabelPos; }

    void update();

private:
    QVector3D findHighestPeak(const QSurfaceDataArray &surfaceData);
    void setHighestPeak(const QVector3D &peak);

signals:
    void highestPeakChanged();

private:
    QTimer m_timer;

    WaveDataGenerator m_dataGen;
    QVector3D m_highestPeakPos;
    QVector3D m_highestPeakLabelPos;
};

#endif // WAVEDATAPROXY_H
