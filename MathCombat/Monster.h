#pragma once

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QPixmap>
#include <QTimer>

class Monster  : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	enum Difficulty
    {
        Easy,
        Medium,
        Hard
    };

	explicit Monster(Difficulty difficulty, QObject* parent = nullptr);
  ~Monster();

  void moveLeft();
  void moveRight();

  void startAnimation();
  void stopAnimation();

  void nextFrame();

  Difficulty getDifficulty() const;

private:
	Difficulty difficulty;

  QVector<QPixmap> walkRightFrames;
  QVector<QPixmap> walkLeftFrames;

  QPixmap idleRight;
  QPixmap idleLeft;

  QTimer* animationTimer;

  int currentFrame;

  bool movingLeft;
  bool movingRight;
};
