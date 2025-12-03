#include <filesystem>
#include <string>

#include <QFile>
#include <QImageReader>

#include "main.h"
#include "View/view.h"
#include "Model/model.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

// We use the third-party CLI11 library for managing the command-line parameters
// https://github.com/CLIUtils/CLI11?tab=readme-ov-file#usage
#include "CLI/CLI.hpp"

#include <fstream>



int main(int argc, char *argv[]) {
    try
    {
        // CLI11 https://github.com/CLIUtils/CLI11
        CLI::App app{"Media File Renamer. A utility to rename media files"};
        argv = app.ensure_utf8(argv);

        auto current_working_directory = std::filesystem::current_path();

        app.add_option("-d,--directory", current_working_directory, "The default ");
        app.set_version_flag("--version", std::string(MFR_VERSION));

        CLI11_PARSE(app, argc, argv);

        //
        // This code sets up the SPD loggers. See https://github.com/gabime/spdlog
        // Basically we create two loggers (sinks), one for console output and one for a rotating 3 * 5MB files in the log sub-directory
        // We join them together and set the default logger to that sink_list
        //
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::trace);

        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/MediaFileRenamer.log", 1024 * 1024 * 5, 3);
        file_sink->set_level(spdlog::level::trace);

        spdlog::sinks_init_list sink_list = { file_sink, console_sink };

        spdlog::logger logger("multi_sink", sink_list.begin(), sink_list.end());
        logger.set_level(spdlog::level::trace);

        spdlog::set_default_logger(std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list({console_sink, file_sink})));
        spdlog::set_level(spdlog::level::trace);

        // Now this is done, we can just call these MACROs to log various messages at different log levels

        // SPDLOG_TRACE("This is a trace level message");
        // SPDLOG_DEBUG("This is a debug level message");
        // SPDLOG_INFO("This is a info level message");
        // SPDLOG_WARN("This is a warning level message");
        // SPDLOG_ERROR("This is a error level message {}", 1);
        // SPDLOG_CRITICAL("This is a critical level message");

        SPDLOG_INFO("Current Working Directory: {}", current_working_directory.string());

        // current_working_directory = current_working_directory.parent_path();
        // SPDLOG_INFO("Moving up one level Directory: {}", current_working_directory.string());


        // const tao::config::value config = tao::config::from_file( "foo.cfg" );

        // We are using the Model-View-Controller design pattern to better separate classes
        // [1] The model is created, and it initializes its data
        // [2] The view is created and observes the Model
        // [3] The controller is created and gets references to the model and the view; it observes the model
        // [4] The application starts event processing

        auto p_model = new Model();

        p_model->initialise();


        auto * p_QApplication = new QApplication(argc, argv);

        QImageReader::setAllocationLimit(512);

        auto p_view = new mediaFileRenamerMainView(p_model);

        QFile file("stylesheet.qss");
        file.open(QFile::ReadOnly);
        QString styleSheet = QLatin1String(file.readAll());

        // p_QApplication->setStyleSheet(styleSheet);

        p_view -> create_window();
        QApplication::exec();
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
    catch (const std::exception& ex)
    {
        std::cout << "General std::exception caught: " << ex.what() << std::endl;
    }
}