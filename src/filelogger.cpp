
#include "filelogger.h"

FileLogger::FileLogger(const char *filename) : m_filename(filename)
{
    m_file = fopen(m_filename, LOGGER_FILE_OPEN_MODE);
    m_log_line = (char *)malloc(sizeof(char) * LOGGER_LINE_MAX_LEN);
    m_file_err = new wxLogStderr(m_file);
    delete wxLog::SetActiveTarget(m_file_err);
    wxLog::SetLogLevel(wxLOG_Trace);
    wxLog::SetVerbose(true);
}

FileLogger::~FileLogger()
{
    if (m_log_line != NULL)
        free(m_log_line);
    if (m_file != NULL)
        fclose(m_file);
}

void FileLogger::Debug(const char *fmt, ...)
{
    if (m_level <= static_cast<logger_level_t>(Levels::Debug))
    {
        va_list arglist;
        va_start(arglist, fmt);
        vsprintf(m_log_line, fmt, arglist);
        wxLogVerbose("Debug:%s", m_log_line);
        va_end(arglist);
    }
}

void FileLogger::SetLevel(logger_level_t level)
{
    m_level = level;
}