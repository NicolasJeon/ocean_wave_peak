#ifndef WAVEDATAGENERATOR_H
#define WAVEDATAGENERATOR_H

#include <QDebug>
#include <QObject>
#include <QSurfaceDataProxy>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>

constexpr int CACHE_SIZE = 5;

class WaveDataGenerator : public QObject
{
    Q_OBJECT
public:
    explicit WaveDataGenerator(QObject *parent = nullptr);
    ~WaveDataGenerator();

public:
    void startGeneration();
    void stopGeneration();
    bool dataAvailable();
    std::unique_ptr<QSurfaceDataArray> fetchData();

private:
    void generateData();

signals:
    void dataGenerated();

private:
    QQueue<QSurfaceDataArray*> m_dataCache;
    QMutex m_cacheMutex;
    QWaitCondition m_cacheCondition;
    bool m_running;
    float m_wavePhase = 0.0;
};

#endif // WAVEDATAGENERATOR_H
