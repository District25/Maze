#include "buttonview.h"



buttonView::buttonView(QWidget *parent) : QWidget(parent)
{
    // === Widgets ===
    saveButton = new QPushButton("Save maze");
    loadButton = new QPushButton("Load maze");
    randomMazeButton = new QPushButton("Generate random maze");
    randomRobotButton = new QPushButton("Change robot position");
    start_stopButton = new QPushButton("Start/Stop");

    rows = new QLineEdit("80");
    rows->setPlaceholderText("Enter width size (10-100)");
    cols = new QLineEdit("80");
    cols->setPlaceholderText("Enter height size (10-100)");

    // Style des champs input
    rows->setFixedWidth(120);
    cols->setFixedWidth(120);

    // Barre et label de progression
    statusLabel = new QLabel("");
    progressBar = new QProgressBar();
    progressBar->setRange(0, 0); // mode indéterminé
    progressBar->setVisible(false);
    statusLabel->setVisible(false);

    // Label du Timer
    timer = new QLabel("00:00:00");
    timer->setVisible(false);

    // Style du label
    QFont font = statusLabel->font();
    font.setPointSize(18);
    font.setBold(true);
    statusLabel->setFont(font);
    statusLabel->setAlignment(Qt::AlignCenter);

    QFont font2 = timer->font();
    font2.setPointSize(14);
    font2.setBold(true);
    timer->setFont(font2);
    timer->setAlignment(Qt::AlignCenter);

    // === Layouts ===

    // Ligne pour les inputs
    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addStretch();
    inputLayout->addWidget(rows);
    inputLayout->addSpacing(10);
    inputLayout->addWidget(cols);
    inputLayout->addStretch();

    // Layout principal vertical
    QVBoxLayout *layout = new QVBoxLayout;

    layout->addSpacing(20);
    layout->addLayout(inputLayout);
    layout->addSpacing(10);

    layout->addWidget(randomMazeButton);
    layout->addWidget(randomRobotButton);
    layout->addWidget(start_stopButton);

    layout->addSpacing(30);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);

    layout->addStretch(); // pousse tout vers le haut

    // Barre de chargement et texte en bas
    layout->addSpacing(20);
    layout->addWidget(statusLabel);
    layout->addWidget(progressBar);

    // Timer
    layout->addSpacing(20);
    layout->addWidget(timer);

    this->setLayout(layout);

    // === Connexions ===
    connect(saveButton, &QPushButton::clicked, this, &buttonView::saveRequested);
    connect(loadButton, &QPushButton::clicked, this, &buttonView::loadRequested);
    connect(randomMazeButton, &QPushButton::clicked, this, &buttonView::randMazeRequested);
    connect(randomRobotButton, &QPushButton::clicked, this, &buttonView::randRobotPosRequested);
    connect(start_stopButton, &QPushButton::clicked, this, &buttonView::start_stopSimulRequested);
}


int buttonView::getRows() const
{
    return rows->text().toInt();
}

int buttonView::getCols() const
{
    return cols->text().toInt();
}

void buttonView::showProcessingUI()
{
    statusLabel->setText("Robot is searching the exit...");
    statusLabel->setVisible(true);
    progressBar->setVisible(true);
    timer->setVisible(true);
}

void buttonView::winProcessingUI()
{
    statusLabel->setText("Robot has found the exit!");
    statusLabel->setVisible(true);
    progressBar->setVisible(false);
}

void buttonView::hideProcessingUI()
{
    statusLabel->setText("");
    statusLabel->setVisible(false);
    progressBar->setVisible(false);
    timer->setVisible(false);
}

void buttonView::pauseProcessingUI()
{
    statusLabel->setText("Pausing process...");
    statusLabel->setVisible(true);
    progressBar->setVisible(false);
}

void buttonView::setTimer(int min, int sec, int cent)
{
    QString timeText = QString("%1:%2:%3")
    .arg(min, 2, 10, QChar('0'))  // min sur 2 chiffres
        .arg(sec, 2, 10, QChar('0'))  // sec sur 2 chiffres
        .arg(cent, 2, 10, QChar('0'));// centièmes sur 2 chiffres

    timer->setText(timeText);
}


