#include "mainwindow.h"
#include <QLabel>
#include <QGridLayout>
#include <QKeyEvent>
#include <QCoreApplication>
#include <cstdlib>
#include <ctime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    gridLayout(new QGridLayout),
    board{{0}},
    tiles{{nullptr}}
{
    srand(time(nullptr)); // Seed for random number generation

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setLayout(gridLayout);

    initializeGame();
}

MainWindow::~MainWindow()
{
    // Clean up dynamically allocated memory
    delete gridLayout;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            delete tiles[i][j];
        }
    }
}

void MainWindow::initializeGame()
{
    // Initialize board
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            board[i][j] = 0;
            tiles[i][j] = new QLabel("");
            tiles[i][j]->setAlignment(Qt::AlignCenter);
            gridLayout->addWidget(tiles[i][j], i, j);
        }
    }

    // Place two initial random tiles
    placeRandomTile();
    placeRandomTile();
    updateTiles();
}

void MainWindow::placeRandomTile()
{
    // Find an empty spot on the board
    int emptySpots[16];
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 0) {
                emptySpots[count++] = i * 4 + j;
            }
        }
    }

    if (count == 0) {
        // No empty spots left
        return;
    }

    // Choose a random empty spot
    int index = rand() % count;
    int spot = emptySpots[index];
    int row = spot / 4;
    int col = spot % 4;

    // Place a 2 or 4 randomly (90% chance for 2, 10% chance for 4)
    int newValue = (rand() % 10 == 0) ? 4 : 2;
    board[row][col] = newValue;
}

void MainWindow::updateTiles()
{
    // Update visual representation of the board
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == 0) {
                tiles[i][j]->setText("");
            } else {
                tiles[i][j]->setText(QString::number(board[i][j]));
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    bool moved = false;

    // Handle key presses to move tiles
    if (event->key() == Qt::Key_Left) {
        moved = moveTilesLeft();
    } else if (event->key() == Qt::Key_Right) {
        moved = moveTilesRight();
    } else if (event->key() == Qt::Key_Up) {
        moved = moveTilesUp();
    } else if (event->key() == Qt::Key_Down) {
        moved = moveTilesDown();
    }

    if (moved) {
        placeRandomTile();
        updateTiles();
        // Check for game over condition here if needed
    }
}

bool MainWindow::moveTilesLeft()
{
    bool moved = false;

    // Move tiles to the left
    for (int row = 0; row < 4; ++row) {
        for (int col = 1; col < 4; ++col) {
            if (board[row][col] != 0) {
                int current = col;
                while (current > 0 && board[row][current - 1] == 0) {
                    // Shift tile to the left
                    board[row][current - 1] = board[row][current];
                    board[row][current] = 0;
                    --current;
                    moved = true;
                }
                if (current > 0 && board[row][current - 1] == board[row][current]) {
                    // Merge tiles if they are the same
                    board[row][current - 1] *= 2;
                    board[row][current] = 0;
                    moved = true;
                }
            }
        }
    }

    return moved;
}

bool MainWindow::moveTilesRight()
{
    bool moved = false;

    // Move tiles to the right
    for (int row = 0; row < 4; ++row) {
        for (int col = 2; col >= 0; --col) {
            if (board[row][col] != 0) {
                int current = col;
                while (current < 3 && board[row][current + 1] == 0) {
                    // Shift tile to the right
                    board[row][current + 1] = board[row][current];
                    board[row][current] = 0;
                    ++current;
                    moved = true;
                }
                if (current < 3 && board[row][current + 1] == board[row][current]) {
                    // Merge tiles if they are the same
                    board[row][current + 1] *= 2;
                    board[row][current] = 0;
                    moved = true;
                }
            }
        }
    }

    return moved;
}

bool MainWindow::moveTilesUp()
{
    bool moved = false;

    // Move tiles up
    for (int col = 0; col < 4; ++col) {
        for (int row = 1; row < 4; ++row) {
            if (board[row][col] != 0) {
                int current = row;
                while (current > 0 && board[current - 1][col] == 0) {
                    // Shift tile up
                    board[current - 1][col] = board[current][col];
                    board[current][col] = 0;
                    --current;
                    moved = true;
                }
                if (current > 0 && board[current - 1][col] == board[current][col]) {
                    // Merge tiles if they are the same
                    board[current - 1][col] *= 2;
                    board[current][col] = 0;
                    moved = true;
                }
            }
        }
    }

    return moved;
}

bool MainWindow::moveTilesDown()
{
    bool moved = false;

    // Move tiles down
    for (int col = 0; col < 4; ++col) {
        for (int row = 2; row >= 0; --row) {
            if (board[row][col] != 0) {
                int current = row;
                while (current < 3 && board[current + 1][col] == 0) {
                    // Shift tile down
                    board[current + 1][col] = board[current][col];
                    board[current][col] = 0;
                    ++current;
                    moved = true;
                }
                if (current < 3 && board[current + 1][col] == board[current][col]) {
                    // Merge tiles if they are the same
                    board[current + 1][col] *= 2;
                    board[current][col] = 0;
                    moved = true;
                }
            }
        }
    }

    return moved;
}
