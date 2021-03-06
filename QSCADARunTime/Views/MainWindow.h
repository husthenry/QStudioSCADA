﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QMutexLocker>
#include <QMutex>
#include <stdlib.h>
#include "GraphPage.h"
#include "propertymodel.h"
#include "propertytableview.h"
#include "GraphPageManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static MainWindow *instance() {
        QMutexLocker locker(&mutex_);
        if (instance_ == nullptr) {
            instance_ = new MainWindow();
            ::atexit(deleteInstance);
        }
        return instance_;
    }


    static void deleteInstance() {
        if(instance_ != nullptr) {
            delete instance_;
            instance_ = nullptr;
        }
    }

    // 打开画面
    void openGraphPage(const QString &pagePath, const QString &pageName);
    // 切换至画面
    void switchGraphPage(const QString &pageName);
    // 返回切换画面
    void returnGraphPage();
    // 加载工程画面
    void loadGraphPages(const QString &pagePath);
    // 卸载工程画面
    void unLoadGraphPages();

private:
    void updateGraphPageViewInfo(const QString &);
    bool isGraphPageOpen(const QString &filename);
    bool createDocument(GraphPage *graphPage, const QString &filename);
    void moveCenter();

public:
    QStack<GraphPage *> showedGraphPageStack_;
    static QString projpath_;
    static QString graphPageName_;

private:
    static MainWindow *instance_;
    static QMutex mutex_;
    GraphPage *currentGraphPage_;

};

#endif // MAINWINDOW_H
