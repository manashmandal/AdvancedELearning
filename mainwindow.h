#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define DEFAULT_TREE_COLUMN 0
#define DEFAULT_INDEX 0

#include "numberbaseconverter.h"
#include "numberbasechart.h"

#include <QMainWindow>
#include <QWebView>
#include <QString>
#include <QStringList>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QList>
#include <QPair>
#include <QDir>
#include <QMap>
#include <QMessageBox>
#include <QFontDialog>
#include <QFont>
#include <QWebSettings>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void loadListDefaultItems();
    void loadTopicLink();
    QString linkMaker(QString);

private slots:
    void on_moreButton_toggled(bool checked);
    void findTopic(QString the_topic);
    void updateIndexList(QStringList list);
    void on_indexTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void loadLink(int);

    void on_indexListWidget_itemClicked(QListWidgetItem *item);

    void on_fontButton_clicked();

    void on_actionNumber_Base_Converter_triggered();


    void loadTheUrl(QUrl);

    void on_actionNumber_Base_Chart_triggered();

signals:
    void passFoundTopicList(QStringList topic_list);
    void passKey(int);
    void loadUrl(QUrl);

private:
    Ui::MainWindow *ui;
    const QString file_initial;
    const QString html;
    QFont font;

    QList<QListWidgetItem *> found_items;
    QStringList found_item_name;
    QStringList topic_lists;
    QStringList topic_links;
    QList <QPair <QString, QString> > topic_name_link;
    QMap < int, QPair <QString, QString> > topic_name_link_map;

    NumberBaseConverter *converter;
    NumberBaseChart *chart;

};

#endif // MAINWINDOW_H
