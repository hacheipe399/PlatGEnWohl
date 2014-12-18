/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2014 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "data_configs.h"



void dataconfigs::loadRotationTable()
{
    unsigned int i;

    obj_rotation_table rTable;
    long totalEntries;
    QString rtables_ini = config_dir + "rotation_table.ini";

    if(!QFile::exists(rtables_ini))
    {
        addError(QString("Rotation tables wasn't load: rotation_table.ini does not exist"), QtWarningMsg);
        return;
    }

    QSettings rtable_set(rtables_ini, QSettings::IniFormat);
    rtable_set.setIniCodec("UTF-8");

    rtable_set.beginGroup("main");
        totalEntries = rtable_set.value("total", "0").toInt();
    rtable_set.endGroup();

    if(totalEntries==0)
    {
        addError(QString("ERROR LOADING of rotation_table.ini: number of items not define, or empty config"), QtWarningMsg);
        return;
    }

    main_rotation_table.clear();

    for(i=1; i<=totalEntries; i++)
    {

        rtable_set.beginGroup( QString("rule-"+QString::number(i)) );
            rTable.type=rtable_set.value("type", "0").toInt();
            rTable.id=rtable_set.value("id", "0").toInt();
            rTable.rotate_left=rtable_set.value("rotate-left", "0").toInt();
            rTable.rotate_right=rtable_set.value("rotate-right", "0").toInt();
            rTable.flip_h=rtable_set.value("flip-h", "0").toInt();
            rTable.flip_v=rtable_set.value("flip-v", "0").toInt();
        rtable_set.endGroup();

        main_rotation_table.push_back(rTable);

        if( rtable_set.status() != QSettings::NoError )
        {
            addError(QString("ERROR LOADING lvl_bgo.ini N:%1 (bgo-%2)").arg(rtable_set.status()).arg(i), QtCriticalMsg);
        }
    }
}