#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>

#include "Player.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameScene(QObject *parent = nullptr);

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateGame();

private:

    Player* m_player;

    QTimer* m_gameTimer;

    bool m_movingLeft;
    bool m_movingRight;
};

#endif // GAMESCENE_H
