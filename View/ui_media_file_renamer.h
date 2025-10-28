//
// Created by Alex Nicklin on 28/10/2025.
//

/********************************************************************************
** Form generated from reading UI file 'MediaFileRenamerYJoWZu.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MEDIAFILERENAMERYJOWZU_H
#define MEDIAFILERENAMERYJOWZU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MediaFileRenamer
{
public:
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QTableView *tableView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MediaFileRenamer)
    {
        if (MediaFileRenamer->objectName().isEmpty())
            MediaFileRenamer->setObjectName("MediaFileRenamer");
        MediaFileRenamer->resize(1342, 717);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MediaFileRenamer->sizePolicy().hasHeightForWidth());
        MediaFileRenamer->setSizePolicy(sizePolicy);
        actionExit = new QAction(MediaFileRenamer);
        actionExit->setObjectName("actionExit");
        centralwidget = new QWidget(MediaFileRenamer);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(groupBox);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");

        verticalLayout->addWidget(tableView);

        MediaFileRenamer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MediaFileRenamer);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1342, 33));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MediaFileRenamer->setMenuBar(menubar);
        statusbar = new QStatusBar(MediaFileRenamer);
        statusbar->setObjectName("statusbar");
        MediaFileRenamer->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(MediaFileRenamer);

        QMetaObject::connectSlotsByName(MediaFileRenamer);
    } // setupUi

    void retranslateUi(QMainWindow *MediaFileRenamer)
    {
        MediaFileRenamer->setWindowTitle(QCoreApplication::translate("MediaFileRenamer", "Media File Renamer", nullptr));
        actionExit->setText(QCoreApplication::translate("MediaFileRenamer", "Exit", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MediaFileRenamer", "Folder Selection", nullptr));
        pushButton->setText(QCoreApplication::translate("MediaFileRenamer", "Select Folder", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MediaFileRenamer", "File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MediaFileRenamer", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MediaFileRenamer: public Ui_MediaFileRenamer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MEDIAFILERENAMERYJOWZU_H