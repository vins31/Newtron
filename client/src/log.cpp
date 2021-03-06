/*
    Newtron - Logging class file
    Copyright © 2011 Rémi Palandri, Vincent A., Guillaume Babin
    This file is part of Newtron.

    Newtron is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    Newtron is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Newtron.
    If not, see <http://www.gnu.org/licenses/>.
*/

#include "log.h"

Log::Log() : m_log_type(LOG_INFO) 
{
}

Log::~Log() {
    if(m_file) {
        write(LOG_INFO);
        m_file.close();
    }
}

void Log::init(string file_path) {
    // file is opened in write mode and will be erased if it already exists
    m_file.open(file_path.c_str(),ios::out|ios::trunc);
    if(!m_file) {
        cerr<<"File "<<file_path<<" could not be opened in write mode (for logging) "<<endl;
    }
}

fstream &Log::write(Log_Type type) {
    m_file<<logtype_to_prefix(type);
    return m_file;
}

void Log::close() {
    if(m_file) {
        write()<<"Closing log file"<<endl;
        m_file.close();
    }
}

string Log::logtype_to_prefix(Log_Type type) {
    string prefix="";
    switch (type) {
    case LOG_INFO:
        prefix="[INF]";
        break;
    case LOG_WARNING:
        prefix="[WAR]";
        break;
    case LOG_ERROR:
        prefix="[ERR]";
        break;
    }
    return prefix;
}
