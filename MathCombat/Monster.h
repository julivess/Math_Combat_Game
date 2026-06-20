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
	Difficulty m_difficulty;

  void UpdateSprites();

  QVector<QPixmap> Frames;

  QPixmap idleRight;
  QPixmap idleLeft;

  QTimer* animationTimer;

  int m_currentFrame;

  bool m_animationForward = true; 

  bool movingLeft;
  bool movingRight;
};
