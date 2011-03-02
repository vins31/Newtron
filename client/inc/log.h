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

/**
 * @file log.h
 * \brief Logging class file.
 * Logging class file (will be used everywhere in Newtron to log stuff).
 */

/* Example : 
 Log log;
 log.init();
 log.write(LOG_3D)<<"Ogre initialisation"<<endl;
 log.close();
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define DEFAULT_LOG_PATH "newtron_log.log"

/**
 * \enum Log Types
 * The different log types (used with the write function to affect output).
 */
enum Log_Type {
    LOG_ERROR, 
    LOG_NORMAL,
    LOG_NETWORK,
    LOG_3D
};


/**
 * \class Newtron's logging class.
 */
class Log{
public:
    /** \brief Default constructor.
     */
    Log();

    /** \brief Destructor. 
     * Class destructor. Will close the file if no call to Log::close has been done.
     */
    ~Log();

    /** \brief Init function.
     * To be called at the beginning of Newtron's execution.
     * \param file_path Optional parameter to set a new log file path.
     */
    void init(string file_path=DEFAULT_LOG_PATH);

    /** \brief Write function.
     * Returns a fstream-type flow to use as a "cout" one to write in the logging file.
     * \param type Optional log's type (if void, it will be considered as LOG_NORMAL)
     * \return The file stream to write on (to be used as a normal fstream)
     */
    fstream &write(Log_Type type=LOG_NORMAL);

    /** \brief Closes the logging class.
     */
    void close();

private:
    string logtype_to_prefix(Log_Type type);
    fstream m_file;
    Log_Type m_log_type;
};

#endif
