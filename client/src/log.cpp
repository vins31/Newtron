#include "log.h"

Log::Log() : m_log_type(LOG_NORMAL) 
{
}

Log::~Log() {
    if(m_file) {
        write("Log file has not been closed properly during execution!");
        m_file.close();
    }
}

void Log::init(string file_path) {
    // file is opened in write mode and will be erased if it already exists
    m_file.open(file_path,ios::out|ios::trunc);
    if(!m_file) {
        cerr<<"File "<<file_path<<" could not be opened in write mode (for logging) "<<endl;
    }
}

void Log::write(string str,Log_Type type) {
    string prefix="";
    switch (type) {
    case LOG_ERROR:
        prefix="(ERR)";
        break;
    case LOG_NORMAL:
        prefix="";
        break;
    case LOG_NETWORK:
        prefix="(NET)";
        break;
    case LOG_3D:
        prefix="(OGR)";
        break;
    }
    m_file<<prefix<<" : "<<str<<endl;
}



void Log::close() {
    if(m_file) {
        write("Closing log file");
        m_file.close();
    }
}


