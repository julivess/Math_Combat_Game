#include "GameScene.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
{

    m_movingLeft = false;
    m_movingRight = false;

    // ===== ФОН =====

    QPixmap background(":/MathCombat/Resource/Level1.png");

    addPixmap(background);

    setSceneRect(background.rect());
    // ===== ИГРОК =====

    m_player = new Player(this);

    // ===== МОНСТЕР =====
    m_monster = new Monster(Monster::Difficulty::Easy, this);

    addItem(m_player);
    addItem(m_monster);

    m_player->setPos(120, 550);
    m_monster->setPos(900, 485);

    // ===== GAME LOOP =====

    m_gameTimer = new QTimer(this);
    connect(m_gameTimer, &QTimer::timeout, this, &GameScene::updateGame);

    m_gameTimer->start(15);
    m_monster->startAnimation();
}

// =====================================================
// ОБНОВЛЕНИЕ ИГРЫ
// =====================================================

void GameScene::updateGame()
{
    // ===== ДВИЖЕНИЕ ВПРАВО =====

    if(m_movingRight)
    {
        m_player->moveRight();
        m_player->startAnimation();
        //m_monster->moveLeft();
    }

    // ===== ДВИЖЕНИЕ ВЛЕВО =====

    if(m_movingLeft)
    {
        m_player->moveLeft();
        m_player->startAnimation();
        //m_monster->moveRight();
    }

    // ===== ЕСЛИ НЕ ДВИГАЕТСЯ =====

    if(!m_movingLeft && !m_movingRight)
    {
        m_player->stopAnimation();
    }

    QList<QGraphicsItem*> collisions =
        m_player->collidingItems();

    for (QGraphicsItem* item : collisions)
    {
        Monster* monster =
            dynamic_cast<Monster*>(item);

        if (monster)
        {
            qDebug() << "Столкновение!";

            emit CombatSignal();

            m_player->stopAnimation();
            m_monster->stopAnimation();
            disconnect(m_gameTimer, &QTimer::timeout, this, &GameScene::updateGame);
            return;
        }
    }

}

// =====================================================
// НАЖАТИЕ КЛАВИШ
// =====================================================

void GameScene::keyPressEvent(QKeyEvent *event)
{
    // Чтобы событие не спамилось
    if(event->isAutoRepeat())
    {
        return;
    }

    // ===== D =====

    if(event->key() == Qt::Key_D)
    {
        m_movingRight = true;
    }

    // ===== A =====

    if(event->key() == Qt::Key_A)
    {
        m_movingLeft = true;
    }
    m_monster->startAnimation();


    QGraphicsScene::keyPressEvent(event);
}

// =====================================================
// ОТПУСКАНИЕ КЛАВИШ
// =====================================================

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
    {
        return;
    }

    // ===== D =====

    if(event->key() == Qt::Key_D)
    {
        m_movingRight = false;
    }

    // ===== A =====

    if(event->key() == Qt::Key_A)
    {
        m_movingLeft = false;
    }

    QGraphicsScene::keyReleaseEvent(event);
}
