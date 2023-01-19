#include "analogclock.h"

#include <QLabel>
#include <QPainter>
#include <QPoint>
#include <QTime>
#include <QTimer>

#define hourLabelStyleSheet                                                    \
  "display: block; font: 700 32pt 'JetBrains Mono'; padding: 20px"

AnalogClock::AnalogClock(QWidget *parent)
    : QWidget{parent},
      m_currentTime(QDateTime::currentDateTimeUtc().time().addSecs(-10800)),
      hourLabel(new QLabel(this)) {
  setWindowTitle(tr("Analog Clock"));
  resize(500, 500);
  hourLabel->setText(m_currentTime.toString("hh:mm:ss"));
  hourLabel->setStyleSheet(hourLabelStyleSheet);
  hourLabel->setAlignment(Qt::AlignCenter);
  hourLabel->setMinimumWidth(width());
  hourLabel->setMinimumHeight(70);
  hourLabel->setVisible(true);

  QTimer *timer = new QTimer(this);

  connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));

  connect(timer, &QTimer::timeout, this, &AnalogClock::updateTime);

  timer->start(1000);
}

void AnalogClock::paintEvent(QPaintEvent *) {
  static const QPoint hourPoints[3] = {QPoint(7, 8), QPoint(-7, 8),
                                       QPoint(0, -40)};

  static const QPoint minutePoints[3] = {QPoint(7, 8), QPoint(-7, 8),
                                         QPoint(0, -70)};

  static const QPoint secondPoints[3] = {QPoint(7, 8), QPoint(-7, 8),
                                         QPoint(0, -80)};

  int side = qMin(width(), height() - 200);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.translate(width() / 2, height() / 2);
  painter.scale(side / 200.0, side / 200.0);
  painter.setPen(Qt::NoPen);

  QColor hourColor(127, 0, 100);
  QColor minuteColor(0, 127, 127, 150);
  QColor secondColor(10, 10, 10, 200);

  painter.setBrush(hourColor);
  painter.save();
  painter.rotate(30.0 *
                 ((currentTime().hour() + m_currentTime.minute() / 60.0)));
  painter.drawConvexPolygon(hourPoints, 3);
  painter.restore();
  painter.setPen(hourColor);

  for (int i = 0; i < 12; ++i) {
    painter.drawLine(88, 0, 96, 0);
    painter.rotate(30.0);
  }

  painter.setPen(Qt::NoPen);
  painter.setBrush(minuteColor);
  painter.save();
  painter.rotate(6.0 *
                 (currentTime().minute() + currentTime().second() / 60.0));
  painter.drawConvexPolygon(minutePoints, 3);
  painter.restore();
  painter.setPen(minuteColor);

  for (int j = 0; j < 60; ++j) {
    if ((j % 5) != 0)
      painter.drawLine(92, 0, 96, 0);
    painter.rotate(6.0);
  }

  painter.setPen(Qt::NoPen);
  painter.setBrush(secondColor);
  painter.save();
  painter.rotate(6.0 * currentTime().second());
  painter.drawConvexPolygon(secondPoints, 3);
  painter.restore();
  painter.setPen(secondColor);
}

const QTime &AnalogClock::currentTime() const { return m_currentTime; }

void AnalogClock::setCurrentTime(const QTime &newCurrentTime) {
  m_currentTime = newCurrentTime;
}

void AnalogClock::updateTime() {
  setCurrentTime(QDateTime::currentDateTimeUtc().time().addSecs(-10800));
  hourLabel->setText(currentTime().toString("hh:mm:ss"));
}
