#include <filesystem>
#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
    /* QApplication a(argc, argv);
    # QPushButton button("Hello world!", nullptr);
    # button.resize(200, 100);
    # button.show();
    # return QApplication::exec(); */

    const std::filesystem::path sandbox{"."};

    // directory_iterator can be iterated using a range-for loop
    for (auto const& dir_entry : filesystem::directory_iterator{sandbox})
        if (!dir_entry.is_directory()) {
            string raw_filename = dir_entry.path().string();
            raw_filename = raw_filename.substr(2);

            if (raw_filename[0] != '.') {
                int dot_position = raw_filename.find(".");
                string final_filename;

                if (dot_position == -1)
                    final_filename = raw_filename;
                else {
                    final_filename = raw_filename.substr(0, dot_position);
                }
                std::cout << final_filename << '\n';
            }
        }
}