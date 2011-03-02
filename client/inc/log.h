/*
    Newtron
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

#ifndef __DEF_LOG
#define __DEF_LOG

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define DEFAULT_LOG_PATH "newtron_log.log"

enum Log_Type {
    LOG_ERROR,LOG_NORMAL,LOG_NETWORK,LOG_3D
};

class Log{
public:
    Log();
    ~Log();
    void init(string file_path=DEFAULT_LOG_PATH);
    fstream &write(Log_Type type=LOG_NORMAL);
    void close();
private:
    string logtype_to_prefix(Log_Type type);
    fstream m_file;
    Log_Type m_log_type;
};

#endif
