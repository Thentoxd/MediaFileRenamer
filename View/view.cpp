//
// Created by Alex Nicklin on 22/10/2025.
//

#include "view.h"

#include <QPushButton>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QGroupBox>
#include <qscreen.h>
#include <QComboBox>

int view::create_window(int argc, char *argv[]) {
    // QApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);
    // QApplication::setAttribute(Qt::AA_DontUseNativeMenuWindows);
    QApplication app(argc, argv);

    QFont font("Verdana");
    font.setPointSize(10);
    //font.setStyleHint(QFont::Monospace);
    app.setFont(font);

    QMainWindow mainWindow;

    QWidget *centralWidget = new QWidget;

    auto createLayout = [&mainWindow](QWidget *parent) -> QBoxLayout* {
        if (mainWindow.screen()->primaryOrientation() == Qt::PortraitOrientation)
            return new QHBoxLayout(parent);
        return new QVBoxLayout(parent);
    };

    QBoxLayout *mainLayout = createLayout(centralWidget);
    centralWidget->setLayout(mainLayout);

    // Set up the menu bar.
    auto *menuBarMenu = new QMenu("File", mainWindow.menuBar());
    QAction action1("Exit", centralWidget);
    menuBarMenu->addAction(&action1);
    mainWindow.menuBar()->addMenu(menuBarMenu);

    // Set up the context menu.
    QMenu contextMenu("Context menu", centralWidget);
    contextMenu.addAction(&action1);
    // contextMenu.addAction(&action2);
    // contextMenu.addAction(&action3);

    mainWindow.setContextMenuPolicy(Qt::CustomContextMenu);
    QObject::connect(&mainWindow, &QWidget::customContextMenuRequested,
        &mainWindow, [&contextMenu, &mainWindow](const QPoint &pos) {
            contextMenu.exec(mainWindow.mapToGlobal(pos));
        });

    // Set up the buttons that interact with/modify the context menu.
    auto *contextMenuGroup = new QGroupBox("Current Working Directory", centralWidget);
    QBoxLayout *contextMenuGroupLayout = createLayout(contextMenuGroup);

    /*
    // Useful for opening the menu on systems that apparently don't emit customContextMenuRequested,
    // like Android: https://bugreports.qt.io/browse/QTBUG-122732
    auto *openContextMenuButton = new QPushButton("Open", contextMenuGroup);
    QObject::connect(openContextMenuButton, &QPushButton::clicked, [&contextMenu, &mainWindow, openContextMenuButton](){
        contextMenu.move(mainWindow.geometry().center());
        contextMenu.show();
    });
    contextMenuGroupLayout->addWidget(openContextMenuButton);

    auto *appendButton = new QPushButton("Append menu item", contextMenuGroup);
    QObject::connect(appendButton, &QPushButton::clicked, [&centralWidget, &contextMenu](){
        auto action = new QAction("Extra context menu item", centralWidget);
        contextMenu.addAction(action);
    });
    contextMenuGroupLayout->addWidget(appendButton);

    auto *removeButton = new QPushButton("Remove menu item", contextMenuGroup);
    QObject::connect(removeButton, &QPushButton::clicked, [&contextMenu, removeButton](){
        contextMenu.removeAction(contextMenu.actions().last());
        removeButton->setEnabled(!contextMenu.actions().isEmpty());
    });
    contextMenuGroupLayout->addWidget(removeButton);

    auto *addSubMenuButton = new QPushButton("Add sub-menu", contextMenuGroup);
    auto *addSubMenuItemButton = new QPushButton("Add sub-menu item", contextMenuGroup);
    addSubMenuItemButton->setEnabled(false);
    QMenu *subMenu = nullptr;
    QObject::connect(addSubMenuButton, &QPushButton::clicked, [&](){
        subMenu = new QMenu("Sub-menu", centralWidget);

        contextMenu.addMenu(subMenu);
        addSubMenuButton->setEnabled(false);
        addSubMenuItemButton->setEnabled(true);
    });
    contextMenuGroupLayout->addWidget(addSubMenuButton);

    QObject::connect(addSubMenuItemButton, &QPushButton::clicked, [&](){
        auto action = new QAction(QString::fromLatin1("Sub-menu item %1").arg(
            subMenu->actions().size() + 1), centralWidget);
        subMenu->addAction(action);
    });
    */
    //contextMenuGroupLayout->addWidget(addSubMenuItemButton);
    //contextMenuGroup->setLayout(contextMenuGroupLayout);
    mainLayout->addWidget(contextMenuGroup);

    // Add ComboBox.
    auto *comboBoxGroup = new QGroupBox("", centralWidget);
    QBoxLayout *comboBoxGroupLayout = createLayout(comboBoxGroup);
    auto *comboBox = new QComboBox(comboBoxGroup);
    //'for (int i = 0; i < 10; ++i)
    //    comboBox->addItem(QString::fromLatin1("Item %1").arg(i));
    //comboBoxGroupLayout->addWidget(comboBox);
    comboBoxGroup->setLayout(comboBoxGroupLayout);
    mainLayout->addWidget(comboBoxGroup);

    mainWindow.setCentralWidget(centralWidget);

    mainWindow.resize(400, 400);
    mainWindow.show();

    return app.exec();
}

