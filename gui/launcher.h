#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "logger/logger.h"
#include "others/sound.h"
#include "settings.h"

#include <QMainWindow>
#include <QPoint>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include <QMap>
#include <QUrl>

enum TabType {
    HOME,
    SERVER,
    SETTINGS,
    CONSOLE
};

class Tab
{
public:
    Tab(TabType _type, QString _name, QWidget* _selector) :
        type(_type),
        name(_name),
        selector(_selector),
        window(NULL) { }

    TabType type;
    QString name;
    QWidget* selector;
    QWidget* window;
};

namespace Ui {
class Launcher;
}

class SelfUpdater;

class Launcher : public QMainWindow
{
    Q_OBJECT

public:
    explicit Launcher(QWidget* parent = 0);
    ~Launcher();

    Settings* settings;

private:
    Ui::Launcher* ui;
    Logger* log;
    QPoint mpos;
    QSystemTrayIcon* trayIcon;
    QMap<QObject*, QUrl> urls;
    QMap<QObject*, Tab*> tabs;
    Tab* previousTab;
    QWidget* currentWindows;
    SelfUpdater* selfUpdater;

    void closeEvent(QCloseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void changeEvent(QEvent* event);

    void startUpdate();
    void startGame(QString gamePath);

    void switchSelectedTab(Tab* selectedTab);

public slots:
    void onCloseApp();

private slots:
    void onClickLinkButton();
    void onClickCloseButton();
    void onClickMinimizeButton();
    void onClickSystemTrayIcon(QSystemTrayIcon::ActivationReason reason);
    void onOpenApp();
    void onChangeTab();
    void onNewUpdaterVersion();
};

#endif // LAUNCHER_H
