//
// Created by Alex Nicklin on 22/10/2025.
//

#include "view.h"

view::view (int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);

    QFont font ("Courier");
    button.setFont(font);

    button.resize(200, 100);
    button.show();
    QApplication::exec();
}

