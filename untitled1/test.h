#ifndef TEST_H
#define TEST_H

#include <QMainWindow>

namespace Ui {
class test;
}

class test : public QMainWindow
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = nullptr);
    ~test();
    void bfs();
    void render();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::test *ui;
    QString currentFile;
};

#endif // TEST_H
