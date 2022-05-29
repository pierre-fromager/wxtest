#ifndef APP_LOGGER_H
#define APP_LOGGER_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#define LOGGER_LINE_MAX_LEN 1024
#define LOGGER_FILE_OPEN_MODE "a+"

typedef unsigned long logger_level_t;

/**
 * @brief Logger manager
 *
 */
class FileLogger
{
public:
    enum class Levels : logger_level_t
    {
        Fatal = 0,
        Error,
        Warning,
        Message,
        Status,
        Info,
        Debug,
        Trace,
        Progess,
        User,
        Max
    };
    explicit FileLogger(const char *filename);
    virtual ~FileLogger();
    void SetLevel(logger_level_t level);
    void Debug(const char *format, ...);

private:
    //void Log();
    const char *m_filename;
    FILE *m_file = nullptr;
    wxLogStderr *m_file_err = nullptr;
    char *m_log_line;
    logger_level_t m_level;
};

#endif