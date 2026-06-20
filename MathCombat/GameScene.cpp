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

    addItem(m_player);

    m_player->setPos(120, 550);

    // ===== GAME LOOP =====

    m_gameTimer = new QTimer(this);

    connect(m_gameTimer,
            &QTimer::timeout,
            this,
            &GameScene::updateGame);

    m_gameTimer->start(15);
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
    }

    // ===== ДВИЖЕНИЕ ВЛЕВО =====

    if(m_movingLeft)
    {
        m_player->moveLeft();

        m_player->startAnimation();
    }

    // ===== ЕСЛИ НЕ ДВИГАЕТСЯ =====

    if(!m_movingLeft && !m_movingRight)
    {
        m_player->stopAnimation();
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
