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

#include <iostream>
#include "log.h"

using namespace std;

int main()
{
    cout << "Hello, world!\n" <<endl;
    Log log;
    log.init();
    log.write(LOG_NORMAL)<<"salut"<<endl;
    log.write(LOG_3D)<<"3D init fail"<<endl;
    log.close();
}
