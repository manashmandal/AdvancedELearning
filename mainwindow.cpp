#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), file_initial("file:///" + QDir::currentPath() + "/"), html(".html")

{
    ui->setupUi(this);
    //Connect more button with searchgroupbox
    connect(ui->moreButton, SIGNAL(toggled(bool)), ui->searchGroupBox, SLOT(setVisible(bool)));

    //Connecting Search Line Edit with topic finder
    connect(ui->searchEdit, SIGNAL(textEdited(QString)), this, SLOT(findTopic(QString)));
    //Connecting topic finder with updating index list
    connect(this, SIGNAL(passFoundTopicList(QStringList)), this, SLOT(updateIndexList(QStringList)));
    //Connecting key with the link loader (WebView)
    connect(this, SIGNAL(passKey(int)), this, SLOT(loadLink(int)));
    connect(this, SIGNAL(loadUrl(QUrl)), this, SLOT(loadTheUrl(QUrl)));




    //Adding Items to the list
    loadListDefaultItems();
    //Initially searchGroupBox is invisible
    ui->searchGroupBox->setVisible(false);
    loadTopicLink();
    //WebView Loads first item on the tree
    ui->webView->load(topic_name_link_map.value(DEFAULT_INDEX).second);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//More Button Toggling Action
void MainWindow::on_moreButton_toggled(bool checked)
{
    ui->searchGroupBox->setVisible(checked);
    if (checked){
        ui->moreButton->setText(">> Less");
    } else {
        ui->moreButton->setText("<< More");
    }
}

//Loading Default item List for listwidget
void MainWindow::loadListDefaultItems()
{
    ui->indexListWidget->clear();
    QTreeWidgetItemIterator treeIterator(ui->indexTreeWidget);
    while ((*treeIterator)){
        ui->indexListWidget->addItem((*treeIterator)->text(DEFAULT_TREE_COLUMN));
        ++treeIterator;
    }
}

void MainWindow::loadTopicLink()
{
    //Getting the topics in a list
    QTreeWidgetItemIterator treeIterator(ui->indexTreeWidget);
    while ((*treeIterator)){
        topic_lists.append((*treeIterator)->text(DEFAULT_TREE_COLUMN));
        ++treeIterator;
    }

    //Processing topic name to get generic link
    for (int i = 0; i < topic_lists.size(); i++){
        QString the_link = linkMaker(topic_lists[i]);
        topic_name_link_map.insert(i, qMakePair(topic_lists[i], the_link));
    }

}


//Take a piece of string and turn into a loadable link
QString MainWindow::linkMaker(QString data)
{
    QString link = data;
    link = ((link.toLower()).replace('-','_')).replace(' ','_');
    return  file_initial + link + html;
}

//Topic Finder
void MainWindow::findTopic(QString the_topic)
{
    found_item_name.clear();
    loadListDefaultItems();
    found_items = ui->indexListWidget->findItems(the_topic, Qt::MatchContains);
    for (QList <QListWidgetItem*>::iterator it = found_items.begin(); it != found_items.end(); ++it){
        found_item_name.append((*it)->text());
    }
    emit passFoundTopicList(found_item_name);
}


//Updating Index List
void MainWindow::updateIndexList(QStringList list)
{
    ui->indexListWidget->clear();
    ui->indexListWidget->addItems(list);
    if(ui->searchEdit->text() == NULL) loadListDefaultItems();
}

void MainWindow::on_indexTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    emit passKey(topic_name_link_map.key(QPair <QString, QString> (item->text(column), linkMaker(item->text(column)))));
}

//Slot loading link
void MainWindow::loadLink(int ind)
{
    ui->webView->stop();
    QUrl url(topic_name_link_map.value(ind).second);
    emit loadUrl(url);
}

//Load item from listwidget
void MainWindow::on_indexListWidget_itemClicked(QListWidgetItem *item)
{
    emit passKey(topic_name_link_map.key(QPair <QString, QString> (item->text(), linkMaker(item->text()))));
}


//Font Settings
void MainWindow::on_fontButton_clicked()
{
    QWebSettings *settings = ui->webView->settings();
    bool *ok = new bool(true);
    QFontDialog *fontDialog = new QFontDialog(this);
    font = fontDialog->getFont(ok, QFont("Helvetica [Cronyx]", 16) , this);

    if (ok){
        settings->setFontFamily(QWebSettings::StandardFont, font.family());
        settings->setFontSize(QWebSettings::MinimumFontSize, font.pointSize());

    } else {
        settings->setFontFamily(QWebSettings::StandardFont, "Helvetica [Cronyx]");
        settings->setFontSize(QWebSettings::MinimumFontSize, 15);
    }
}


//Generate a number base converter dialog
void MainWindow::on_actionNumber_Base_Converter_triggered()
{
    converter = new NumberBaseConverter(this);
    converter->show();
}


void MainWindow::loadTheUrl(QUrl the_url)
{
    ui->webView->load(the_url);
}



void MainWindow::on_actionNumber_Base_Chart_triggered()
{
    chart = new NumberBaseChart(this);
    chart->show();
}
