#include "WaveDataProxy.h"
#include <QSurface3DSeries>
#include <QCustom3DItem>

WaveDataProxy::WaveDataProxy()
{
    qDebug() << "Constructor of WaveDataProvider";
    m_dataGen.startGeneration();

    connect(&m_dataGen, &WaveDataGenerator::dataGenerated, this, &WaveDataProxy::update);
    m_timer.start(25);
}

void WaveDataProxy::update()
{
    std::unique_ptr<QSurfaceDataArray> surfaceData = m_dataGen.fetchData();
    if (surfaceData) {
        this->resetArray(*surfaceData); // Pass the data as needed

        QVector3D peak = findHighestPeak(*surfaceData);
        setHighestPeak(peak);
    }
}

QVector3D WaveDataProxy::findHighestPeak(const QSurfaceDataArray &surfaceData)
{
    QVector3D highestPoint;
    float maxHeight = -std::numeric_limits<float>::infinity();

    for (int rowIndex = 0; rowIndex < surfaceData.size(); ++rowIndex) {
        const QSurfaceDataRow &row = surfaceData.at(rowIndex);
        for (int colIndex = 0; colIndex < row.size(); ++colIndex) {
            float height = row.at(colIndex).y(); // Access the y-coordinate (height).

            if (height > maxHeight) {
                maxHeight = height;
                highestPoint = QVector3D(colIndex, height - 0.3, rowIndex);
            }
        }
    }
    return highestPoint;
}

void WaveDataProxy::setHighestPeak(const QVector3D &peak)
{
    if (m_highestPeakPos != peak) {
        m_highestPeakPos = peak;
        m_highestPeakLabelPos = QVector3D(peak.x(), peak.y() + 2, peak.z());
        emit highestPeakChanged();
    }
}
