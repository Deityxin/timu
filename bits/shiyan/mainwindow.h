#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_random_clicked();
    void on_solve_clicked();

private:
    // 控件
    QSpinBox *spin_n;
    QSpinBox *spin_maxW;
    QSpinBox *spin_maxV;
    QSpinBox *spin_cap;
    QPushButton *btn_random;
    QPushButton *btn_solve;
    QTextEdit *text_input;
    QTextEdit *text_result;
    QChartView *chart_view;

    // 数据
    QVector<int> weights;
    QVector<int> values;
    int capacity;

    // 算法
    int dp_solve(const QVector<int>& w, const QVector<int>& v, int cap, long long& time, QVector<int>& sel);
    int bf_solve(const QVector<int>& w, const QVector<int>& v, int cap, long long& time, QVector<int>& sel);
    int bt_solve(const QVector<int>& w, const QVector<int>& v, int cap, long long& time, QVector<int>& sel);
    void backtrack(int idx, int cw, int cv, int& maxV, QVector<int>& best, QVector<int>& cur);

    // 展示
    void show_result(int dpV, long long t1, QVector<int> s1,
                     int bfV, long long t2, QVector<int> s2,
                     int btV, long long t3, QVector<int> s3);
    void draw_chart(long long t1, long long t2, long long t3);
};

#endif // MAINWINDOW_H
