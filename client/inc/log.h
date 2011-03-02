#ifndef __DEF_LOG
#define __DEF_LOG

#include <iostream>
#include <string>
#include <fstream>

#define DEFAULT_LOG_PATH

enum Log_Type {
    LOG_ERROR,LOG_NORMAL,LOG_NETWORK,LOG_3D
};

class Log{
public:
    void init(string file_path);
    void set_log_type(Log_Type type);
    void write(string str,Log_Type type=LOG_NORMAL);
    void close();
private:
    ofstream m_file;
    Log_Type m_log_type;
};

#endif
