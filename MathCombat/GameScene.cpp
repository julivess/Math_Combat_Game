#include "GameScene.h"

GameScene::GameScene(std::vector<std::pair<Monster*, QPointF>> vectorMonsters, QString BackgroundTheme, QPointF playerPos, QObject* parent)
	: QGraphicsScene(parent), m_vectorMonsters(vectorMonsters)
{

	m_movingLeft = false;
	m_movingRight = false;

	// ===== Музыка ====
	
	m_walkingSound = new QSoundEffect(this);
	m_walkingSound->setSource(QUrl("qrc:/MathCombat/Resource/Music/Walking.wav"));
	m_walkingSound->setLoopCount(QSoundEffect::Infinite);

	m_monsterSound = new QSoundEffect(this);
	m_monsterSound->setSource(QUrl("qrc:/MathCombat/Resource/Music/Monster.wav"));
	m_monsterSound->setVolume(0.3f);
	m_monsterSound->setLoopCount(QSoundEffect::Infinite);
	m_monsterSound->play();
	// ===== ФОН =====

	QPixmap background(BackgroundTheme);
	addPixmap(background);
	setSceneRect(background.rect());

	// ===== ИГРОК =====

	m_player = new Player(this);
	addItem(m_player); // Добавляем на сцену
	m_player->setPos(playerPos); // Задаем положение

	// ===== МОНСТЕР =====

	for (auto monster : m_vectorMonsters)
	{
		addItem(monster.first); // Добавляем монстра на сцену
		monster.first->setPos(monster.second); // Задаем ему позицию
		monster.first->startAnimation(); // Начинаем анимацию
	}

	// ===== GAME LOOP =====

	m_gameTimer = new QTimer(this);
	connect(m_gameTimer, &QTimer::timeout, this, &GameScene::updateGame);

	m_gameTimer->start(15);
}

GameScene::~GameScene()
{
	// При удалении объекта сцены так же удаляются все ее монстры 
	for (auto monster : m_vectorMonsters)
	{
		if (monster.first) {
			monster.first->deleteLater();
		}
	}
}

// =====================================================
// ОБНОВЛЕНИЕ ИГРЫ
// =====================================================

void GameScene::updateGame()
{
	// ===== ДВИЖЕНИЕ ВПРАВО =====

	if (m_movingRight)
	{
		m_player->moveRight();
		m_player->startAnimation();
		//m_monster->moveLeft();
	}

	// ===== ДВИЖЕНИЕ ВЛЕВО =====

	if (m_movingLeft)
	{
		m_player->moveLeft();
		m_player->startAnimation();
		//m_monster->moveRight();
	}

	// ===== ЕСЛИ НЕ ДВИГАЕТСЯ =====

	if (!m_movingLeft && !m_movingRight)
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

			emit CombatSignal(monster->getDifficulty()); // Отправляем сигнал о том что произошло столкновение 
			// с монстром сложности monster->getDifficulty() (Его поймает класс MathCombat)


			monster->moveBy(-1000, -1000); // Визуально убирает монстра со сцены 
			// Это нужно что бы он перестал отображаться на сцене, если его победят

			m_gameTimer->stop(); // Останавливаем таймер для обновления игры
			m_combatBegin = true;   // Флаг что бой начался. Нажатия на клавиутуру не обрабатываются во время боя
			m_movingLeft  = false;  // Нет движения вправо
			m_movingRight = false;  // нет движения влево
			m_walkingSound->stop(); //останавливает звук ходьбы
			m_monsterSound->stop();
			return;
		}
	}

}

// =====================================================
// НАЖАТИЕ КЛАВИШ
// =====================================================

void GameScene::keyPressEvent(QKeyEvent* event)
{
	// если идет бой - не обрабатываем события с клавиатуры
	if (m_combatBegin)
	{
		return;
	}
	// Чтобы событие не спамилось
	if (event->isAutoRepeat())
	{
		return;
	}

	// ===== D =====

	if (event->key() == Qt::Key_D)
	{
  if (!m_movingRight)
		{
			m_walkingSound->play();
			m_movingRight = true;
		}
	}

	// ===== A =====

	if (event->key() == Qt::Key_A)
	{
		if (!m_movingLeft)
		{
			m_walkingSound->play();
			m_movingLeft = true;
		}
	}


	QGraphicsScene::keyPressEvent(event);
}

// =====================================================
// ОТПУСКАНИЕ КЛАВИШ
// =====================================================

void GameScene::keyReleaseEvent(QKeyEvent* event)
{
	if (event->isAutoRepeat())
	{
		return;
	}

	// ===== D =====

	if (event->key() == Qt::Key_D)
	{
		if (m_movingRight)
		{
			m_walkingSound->stop();
			m_movingRight = false;
		}
	}

	// ===== A =====

	if (event->key() == Qt::Key_A)
	{
		if (m_movingLeft)
		{
			m_walkingSound->stop();
			m_movingLeft = false;
		}
	}

	QGraphicsScene::keyReleaseEvent(event);
}

// true - если на сцене все монстры побеждены
bool GameScene::AllMonstersDefeated()
{
	return numberDefeatedMonsters >= m_vectorMonsters.size();
}


// Продолжаем игру
void GameScene::ContinueGame()
{
	m_combatBegin = false; // Бой закончился (снова обрабатывает собития с клавиатуры)

	m_monsterSound->play();
	m_gameTimer->start(); // Снова запускаем таймер
}

void GameScene::ResolveCombat(bool result)
{
	if (result)
  {
		numberDefeatedMonsters++;
  }
}

int GameScene::GetNumberDefeatedMonsters()
{
	return numberDefeatedMonsters;
}
