#include "mainwindow.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <algorithm>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("0/1背包可视化 - 第8题");
    this->resize(900, 700);

    spin_n = new QSpinBox(this);
    spin_n->setRange(5, 18);
    spin_n->setValue(10);

    spin_maxW = new QSpinBox(this);
    spin_maxW->setRange(1, 50);
    spin_maxW->setValue(20);

    spin_maxV = new QSpinBox(this);
    spin_maxV->setRange(1, 200);
    spin_maxV->setValue(100);

    spin_cap = new QSpinBox(this);
    spin_cap->setRange(10, 200);
    spin_cap->setValue(50);

    btn_random = new QPushButton("生成随机数据", this);
    btn_solve = new QPushButton("开始求解对比", this);

    text_input = new QTextEdit(this);
    text_input->setPlaceholderText("物品数据将显示在这里");

    text_result = new QTextEdit(this);
    text_result->setPlaceholderText("算法结果将显示在这里");

    chart_view = new QChartView(this);
    chart_view->setRenderHint(QPainter::Antialiasing);

    // 布局
    QHBoxLayout *lay_top = new QHBoxLayout;
    lay_top->addWidget(spin_n);
    lay_top->addWidget(spin_maxW);
    lay_top->addWidget(spin_maxV);
    lay_top->addWidget(spin_cap);
    lay_top->addWidget(btn_random);
    lay_top->addWidget(btn_solve);

    QHBoxLayout *lay_mid = new QHBoxLayout;
    lay_mid->addWidget(text_input);
    lay_mid->addWidget(text_result);

    QVBoxLayout *lay_main = new QVBoxLayout;
    lay_main->addLayout(lay_top);
    lay_main->addLayout(lay_mid);
    lay_main->addWidget(chart_view);

    QWidget *central = new QWidget(this);
    central->setLayout(lay_main);
    setCentralWidget(central);

    // 信号槽
    connect(btn_random, &QPushButton::clicked, this, &MainWindow::on_random_clicked);
    connect(btn_solve, &QPushButton::clicked, this, &MainWindow::on_solve_clicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_random_clicked()
{
    int n = spin_n->value();
    int maxW = spin_maxW->value();
    int maxV = spin_maxV->value();
    int cap = spin_cap->value();

    weights.clear();
    values.clear();
    for (int i=0; i<n; i++) {
        weights.append(QRandomGenerator::global()->bounded(1, maxW+1));
        values.append(QRandomGenerator::global()->bounded(1, maxV+1));
    }
    capacity = cap;

    QString s = "序号 | 重量 | 价值\n";
    for (int i=0; i<n; i++) {
        s += QString("%1 | %2 | %3\n").arg(i+1).arg(weights[i]).arg(values[i]);
    }
    s += QString("\n背包容量：%1").arg(capacity);
    text_input->setText(s);
    text_result->clear();
}
全局随机生成器QRandomGenerator::global()，生成[1, maxW]和[1, maxV]区间的随机数，分别保存到重量列表weights和价值列表values中
最后把背包容量保存到成员变量capacity中供后续计算使用
// 动态规划
int MainWindow::dp_solve(const QVector<int>& w, const QVector<int>& v, int cap, long long& time, QVector<int>& sel)
{
    QElapsedTimer t; t.start();
    int n = w.size();
    QVector<QVector<int>> dp(n+1, QVector<int>(cap+1, 0));

    for (int i=1; i<=n; i++) {
        for (int j=0; j<=cap; j++) {
            if (j < w[i-1]) dp[i][j] = dp[i-1][j];
            else dp[i][j] = qMax(dp[i-1][j], dp[i-1][j-w[i-1]] + v[i-1]);
        }
    }
    sel.clear();
    int j = cap;
    for (int i=n; i>=1; i--) {
        if (dp[i][j] != dp[i-1][j]) {
            sel.append(i);
            j -= w[i-1];
        }
    }
    std::reverse(sel.begin(), sel.end());// 反转选中的列表 得到具体的物品序列
    time = t.nsecsElapsed();
    return dp[n][cap];
}

// 暴力枚举
int MainWindow::bf_solve(const QVector<int>& w, const QVector<int>& v, int cap, long long& time, QVector<int>& sel)
{
    QElapsedTimer t; t.start();// 高精度计时器
    int n = w.size();
    int maxV = 0;
    sel.clear();

    for (int mask=0; mask < (1<<n); mask++) {
        int tw=0, tv=0;
        QVector<int> tmp;
        for (int i=0; i<n; i++) {
            if (mask & (1<<i)) {
                tw += w[i]; tv += v[i]; tmp.append(i+1);
            }
        }
        if (tw <= cap && tv > maxV) {
            maxV = tv; sel = tmp;
        }
    }
    time = t.nsecsElapsed()；
    return maxV;
}

// 回溯
void MainWindow::backtrack(int idx, int cw, int cv, int& maxV, QVector<int>& best, QVector<int>& cur)  
{
    if (idx == weights.size()) {
        if (cv > maxV) { maxV = cv; best = cur; }
        return;
    }
    backtrack(idx+1, cw, cv, maxV, best, cur); 
    if (cw + weights[idx] <= capacity) {
        cur.append(idx+1);// 把当前物品序号加入临时方案
        backtrack(idx+1, cw+weights[idx], cv+values[idx], maxV, best, cur); // 总重量加上当前物品重量，总价值加上当前物品价值，继续考虑下一个物品
        cur.pop_back();
    }
}

int MainWindow::bt_solve(const QVector<int>& w, const QVector<int>& v, int cap, long long& time, QVector<int>& sel)
{
    QElapsedTimer t; t.start();
    int maxV = 0;
    QVector<int> cur;
    sel.clear();
    backtrack(0,0,0, maxV, sel, cur);
    time = t.nsecsElapsed();
    return maxV;
}

void MainWindow::show_result(int dpV, long long t1, QVector<int> s1,
                             int bfV, long long t2, QVector<int> s2,
                             int btV, long long t3, QVector<int> s3)
{
    auto f = [](QVector<int> s){
        QString r;
        for(int x:s) r += QString::number(x)+" ";
        return r.isEmpty() ? "无" : r;
    };

    QString res = "===== 0/1背包算法对比 =====\n\n";
    res += QString("动态规划：价值=%1 耗时=%2ns 选中：%3\n\n").arg(dpV).arg(t1).arg(f(s1));
    res += QString("暴力枚举：价值=%1 耗时=%2ns 选中：%3\n\n").arg(bfV).arg(t2).arg(f(s2));
    res += QString("回溯剪枝：价值=%1 耗时=%2ns 选中：%3\n").arg(btV).arg(t3).arg(f(s3));
    text_result->setText(res);
}

// 绘图
void MainWindow::draw_chart(long long t1, long long t2, long long t3)
{
    QBarSet *set = new QBarSet("耗时(ns)");
    *set << t1 << t2 << t3;

    QBarSeries *series = new QBarSeries;
    series->append(set);

    QChart *chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("算法耗时对比");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList cats = {"动态规划","暴力枚举","回溯剪枝"};
    QBarCategoryAxis *x = new QBarCategoryAxis;
    x->append(cats);
    QValueAxis *y = new QValueAxis;

    chart->addAxis(x, Qt::AlignBottom);
    chart->addAxis(y, Qt::AlignLeft);
    series->attachAxis(x);
    series->attachAxis(y);

    chart_view->setChart(chart);
}

// 求解按钮
void MainWindow::on_solve_clicked()
{
    if (weights.isEmpty()) {
        QMessageBox::warning(this,"提示","先生成数据！");
        return;
    }

    long long t1,t2,t3;
    QVector<int> s1,s2,s3;
    int v1 = dp_solve(weights, values, capacity, t1, s1);
    int v2 = bf_solve(weights, values, capacity, t2, s2);
    int v3 = bt_solve(weights, values, capacity, t3, s3);

    show_result(v1,t1,s1, v2,t2,s2, v3,t3,s3);
    draw_chart(t1,t2,t3);
}
