#ifndef ANALOGCLOCK_H
#define ANALOGCLOCK_H

#include <QLabel>
#include <QTime>
#include <QWidget>

class AnalogClock : public QWidget {
    Q_OBJECT
public:
    explicit AnalogClock(QWidget *parent = nullptr);

    const QTime &currentTime() const;
    void setCurrentTime(const QTime &newCurrentTime);

signals:

protected:
    void paintEvent(QPaintEvent *);

private:
    QTime m_currentTime;
    void updateTime();
    QLabel *hourLabel;
    void drawHourPointer(QPainter *painter);
};

#endif // ANALOGCLOCK_H
