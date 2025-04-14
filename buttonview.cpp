#include "buttonview.h"



buttonView::buttonView(QWidget *parent) : QWidget(parent)
{
    // === Widgets ===
    saveButton = new QPushButton("Save maze");
    loadButton = new QPushButton("Load maze");
    randomMazeButton = new QPushButton("Generate random maze");
    randomRobotButton = new QPushButton("Change robot position");
    start_stopButton = new QPushButton("Start/Stop");
    colorAnimationButton = new QPushButton("Chose the animation color");
    colorRobotButton = new QPushButton("Chose the robot color");
    colorWallButton = new QPushButton("Chose the wall color");
    colorExitButton = new QPushButton("Chose the exit color");

    rows = new QLineEdit("");
    rows->setPlaceholderText("Enter width size (5-100)");
    cols = new QLineEdit("");
    cols->setPlaceholderText("Enter height size (5-100)");

    // Input size
    rows->setFixedWidth(160);
    cols->setFixedWidth(160);

    // Label and progression bar
    statusLabel = new QLabel("");
    progressBar = new QProgressBar();
    progressBar->setRange(0, 0); // mode indéterminé
    progressBar->setVisible(false);
    statusLabel->setVisible(false);

    // Timer label
    timer = new QLabel("00:00:00");
    timer->setVisible(false);

    // Label style
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

    // Lign for inputs
    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addStretch();
    inputLayout->addWidget(rows);
    inputLayout->addSpacing(10);
    inputLayout->addWidget(cols);
    inputLayout->addStretch();

    // Principle vertical layout
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

    layout->addSpacing(40);
    layout->addWidget(colorAnimationButton);
    layout->addWidget(colorRobotButton);
    layout->addWidget(colorWallButton);
    layout->addWidget(colorExitButton);

    layout->addStretch(); // Push everything on top

    // Loading bar and text
    layout->addSpacing(20);
    layout->addWidget(statusLabel);
    layout->addWidget(progressBar);

    // Timer
    layout->addSpacing(20);
    layout->addWidget(timer);

    this->setLayout(layout);

    QString buttonStyle = R"(
    QPushButton {
        background-color: #2c2c2c;
        color: white;
        border: 1px solid #555;
        border-radius: 6px;
        padding: 6px;
        font-size: 12px;
    }
    QPushButton:hover {
        background-color: #3d3d3d;
    }
    QPushButton:pressed {
        background-color: #1e1e1e;
    }

    QLineEdit {
        background-color: #1e1e1e;
        color: #ddd;
        border: 1px solid #555;
        border-radius: 4px;
        padding: 4px;
    }

    QLabel {
        color: white;
    }

    QProgressBar {
        border: 1px solid #555;
        border-radius: 5px;
        text-align: center;
        background-color: #222;
        color: white;
    }

    QProgressBar::chunk {
        background-color: #0078D7;
    }
    )";
    this->setStyleSheet(buttonStyle);


    // === Connexions ===
    connect(saveButton, &QPushButton::clicked, this, &buttonView::saveRequested);
    connect(loadButton, &QPushButton::clicked, this, &buttonView::loadRequested);
    connect(randomMazeButton, &QPushButton::clicked, this, &buttonView::randMazeRequested);
    connect(randomRobotButton, &QPushButton::clicked, this, &buttonView::randRobotPosRequested);
    connect(start_stopButton, &QPushButton::clicked, this, &buttonView::start_stopSimulRequested);
    connect(colorAnimationButton, &QPushButton::clicked, this, [=]() {
        auto* dialog = new QColorDialog(this);
        dialog->setCurrentColor(Qt::cyan);
        dialog->setOption(QColorDialog::ShowAlphaChannel);

        connect(dialog, &QColorDialog::currentColorChanged, this, [=](QColor color){
            emit colorAnimationChanged(color); // envoi immédiat
        });

        dialog->open();
    });

    connect(colorRobotButton, &QPushButton::clicked, this, [=]() {
        auto* dialog = new QColorDialog(this);
        dialog->setCurrentColor(Qt::red);

        connect(dialog, &QColorDialog::currentColorChanged, this, [=](QColor color){
            emit colorRobotChanged(color);
        });

        dialog->open();
    });

    connect(colorWallButton, &QPushButton::clicked, this, [=]() {
        auto* dialog = new QColorDialog(this);
        dialog->setCurrentColor(Qt::black);

        connect(dialog, &QColorDialog::currentColorChanged, this, [=](QColor color){
            emit colorWallChanged(color);
        });

        dialog->open();
    });

    connect(colorExitButton, &QPushButton::clicked, this, [=]() {
        auto* dialog = new QColorDialog(this);
        dialog->setCurrentColor(Qt::green);

        connect(dialog, &QColorDialog::currentColorChanged, this, [=](QColor color){
            emit colorExitChanged(color);
        });

        dialog->open();
    });

}

// Extract rows from the Line Edit
int buttonView::getRows() const
{
    return rows->text().toInt();
}

// Extract cols from the Line Edit
int buttonView::getCols() const
{
    return cols->text().toInt();
}

// Display the UI while searching the exit
void buttonView::showProcessingUI()
{
    statusLabel->setText("Robot is searching the exit...");
    statusLabel->setVisible(true);
    progressBar->setVisible(true);
    timer->setVisible(true);
}

// Display the UI after robot has found the exit
void buttonView::winProcessingUI()
{
    statusLabel->setText("Robot has found the exit!\n"
                         "Admire the animation :)");
    statusLabel->setVisible(true);
    progressBar->setVisible(false);
}

// Hide the processing UI
void buttonView::hideProcessingUI()
{
    statusLabel->setText("");
    statusLabel->setVisible(false);
    progressBar->setVisible(false);
    timer->setVisible(false);
}

// Display the UI after a pause has been requested
void buttonView::pauseProcessingUI()
{
    statusLabel->setText("Pausing process...");
    statusLabel->setVisible(true);
    progressBar->setVisible(false);
}

// Set the Label with the chronometer value and display it
void buttonView::setTimer(int min, int sec, int cent)
{
    QString timeText = QString("%1:%2:%3")
    .arg(min, 2, 10, QChar('0'))  // min sur 2 chiffres
        .arg(sec, 2, 10, QChar('0'))  // sec sur 2 chiffres
        .arg(cent, 2, 10, QChar('0'));// centièmes sur 2 chiffres

    timer->setText(timeText);
}


