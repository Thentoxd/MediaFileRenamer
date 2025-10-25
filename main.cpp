#include <filesystem>
#include <iostream>
#include <string>

#include "main.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

// We use the third-party CLI11 library for managing the command-line parameters
// https://github.com/CLIUtils/CLI11?tab=readme-ov-file#usage
#include "CLI/CLI.hpp"

int main(int argc, char *argv[]) {
    try
    {
        // CLI11 https://github.com/CLIUtils/CLI11
        CLI::App app{"Media File Renamer. A utility to rename media files"};
        argv = app.ensure_utf8(argv);

        std::filesystem::path sandbox{"."};
        app.add_option("-d,--directory", sandbox, "The default ");

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
        SPDLOG_CRITICAL("This is a critical level message");



        SPDLOG_INFO("Current Working Directory: {}", std::filesystem::current_path().string());

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
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}