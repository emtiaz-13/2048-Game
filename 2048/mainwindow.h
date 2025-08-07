#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void initializeGame();
    void placeRandomTile();
    void updateTiles();

    bool moveTilesLeft();
    bool moveTilesRight();
    bool moveTilesUp();
    bool moveTilesDown();

    QGridLayout *gridLayout;
    QLabel *tiles[4][4];
    int board[4][4];
};

#endif // MAINWINDOW_H
