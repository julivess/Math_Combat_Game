#include "PreviewWidget.h"
#include <QLabel>
#include <QPushButton>

PreviewWidget::PreviewWidget(QWidget* parent) : QWidget(parent) , ui(new Ui::PreviewWidgetClass())
{
	ui->setupUi(this);
  connect(ui->buttonContinue, &QPushButton::clicked, this, &PreviewWidget::ContinueSavedGame);

  ui->buttonContinue->hide();

  m_clickSound = new QSoundEffect(this);
  m_clickSound->setSource(QUrl("qrc:/MathCombat/Resource/Music/buttonClick.wav"));
  m_clickSound->setVolume(0.5f);

  connect(ui->buttonMewPlay,  &QPushButton::clicked, m_clickSound, &QSoundEffect::play);
	connect(ui->buttonRules,    &QPushButton::clicked, m_clickSound, &QSoundEffect::play);
  connect(ui->buttonExit,     &QPushButton::clicked, m_clickSound, &QSoundEffect::play);
  connect(ui->buttonContinue, &QPushButton::clicked, m_clickSound, &QSoundEffect::play);

  //обработка нажатий на кнопки 
	connect(ui->buttonMewPlay,  &QPushButton::clicked, this, &PreviewWidget::StartNewGame);
	connect(ui->buttonRules,    &QPushButton::clicked, this, &PreviewWidget::ShowRules);
  connect(ui->buttonExit,     &QPushButton::clicked, qApp, &QApplication::quit);

}

PreviewWidget::~PreviewWidget()
{
	delete ui;
}

// Показывает окно с правилами игры
void PreviewWidget::ShowRules()
{
	  QDialog *dialog = new QDialog(this);
    dialog->setFixedSize(700, 750);
    dialog->setModal(true);
    
    // Создаем вертикальный layout
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->setSpacing(20);
    layout->setContentsMargins(30, 30, 30, 30);
    
    QString congratulationText = 
    "ПРАВИЛА ИГРЫ\n\n"
    "Добро пожаловать в MATH COMBAT!\n\n"
    "Ваша цель — пройти все уровни\n"
    "и победить финального босса.\n\n"
    "• Передвигайтесь на клавиши A D\n"
    "• При столкновении с монстром\n"
    "  начинается математический бой\n"
    "• Решите пример правильно,\n"
    "  чтобы победить монстра\n"
    "• Ошибка отправит вас\n"
    "  в начало уровня\n\n"
    "Сложность монстров:\n"
    "• 1 уровень — простые примеры\n"
    "• 2 уровень — логарифмы, sin, cos\n"
    "• 3 уровень — производные\n\n"
    "Победите всех монстров!";
    
    QLabel *label = new QLabel(congratulationText);
    label->setAlignment(Qt::AlignCenter);
    label->setProperty("style_type", "RULE_LABEL");
    // Кнопка закрытия
    QPushButton *closeButton = new QPushButton("✕ Закрыть");
    closeButton->setFixedSize(200, 70);
    closeButton->setProperty("style_type", "ANSWER_BUTTON");
    // Подключаем кнопку к закрытию диалога
    QObject::connect(closeButton, &QPushButton::clicked, dialog,       &QDialog::accept);
    QObject::connect(closeButton, &QPushButton::clicked, m_clickSound, &QSoundEffect::play);
    // Добавляем виджеты в layout
    layout->addWidget(label);
    layout->addWidget(closeButton, 0, Qt::AlignCenter);


    // Показываем диалог
    dialog->exec();
    
    // Автоматическое удаление после закрытия
    dialog->deleteLater();
}

void PreviewWidget::SetContinueVisible(bool visible)
{
  ui->buttonContinue->setVisible(visible);
}
