/*
 * GIFs2PNG, a free tool for merge GIF images with his masks and save into PNG
 * This is a part of the Platformer Game Engine by Wohlstand, a free platform for game making
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

#include <QCoreApplication>
#include <QImage>
#include <QDir>
#include <QDirIterator>
#include <QString>
#include <QTextStream>
#include <QFileInfo>
#include "version.h"

QImage setAlphaMask(QImage image, QImage mask)
{
    if(mask.isNull())
        return image;

    if(image.isNull())
        return image;

    QImage target = image;
    QImage newmask = mask;

    if(target.size()!= newmask.size())
    {
        newmask = newmask.copy(0,0, target.width(), target.height());
    }

    newmask.invertPixels();

    target.setAlphaChannel(newmask);

    return target;
}

void doMagicIn(QString path, QString q, QString OPath, bool removeMode)
{
    QRegExp isMask = QRegExp("*m.gif");
    isMask.setPatternSyntax(QRegExp::Wildcard);

    QRegExp isBackupDir = QRegExp("*/_backup/");
    isBackupDir.setPatternSyntax(QRegExp::Wildcard);

    if(isBackupDir.exactMatch(path))
        return; //Skip backup directories

    if(isMask.exactMatch(q))
        return;

    QImage target;
    QString imgFileM;
    QStringList tmp = q.split(".", QString::SkipEmptyParts);
    if(tmp.size()==2)
        imgFileM = tmp[0] + "m." + tmp[1];
    else
        return;

    QImage image = QImage(path+q);
    QImage mask = QImage(path+imgFileM);

    target = setAlphaMask(image, mask);

    if(!target.isNull())
    {
        target.save(OPath+tmp[0]+".png");
        QTextStream(stdout) << path+q <<"\n";
        QTextStream(stdout) << OPath+tmp[0]+".png" <<"\n";
        if(removeMode)
        {
            QFile::remove( path+q );
            QFile::remove( path+imgFileM );
        }
    }
    else
    QTextStream(stderr) << path+q+" - WRONG!\n";
}

int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath(".");
    QCoreApplication a(argc, argv);
    QStringList filters;
    QDir imagesDir;
    QString path;
    QString OPath;
    bool removeMode=false;
    QStringList fileList;

    bool nopause=false;
    bool walkSubDirs=false;
    bool cOpath=false;
    bool singleFiles=false;

    QString argPath;
    QString argOPath;

    QTextStream(stdout) <<"============================================================================\n";
    QTextStream(stdout) <<"Pair of GIFs to PNG converter tool by Wohlstand. Version "<<_FILE_VERSION<<_FILE_RELEASE<<"\n";
    QTextStream(stdout) <<"============================================================================\n";
    QTextStream(stdout) <<"This program is distributed under the GNU GPLv3 license \n";
    QTextStream(stdout) <<"============================================================================\n";


    QRegExp isGif = QRegExp("*.gif");
    isGif.setPatternSyntax(QRegExp::Wildcard);

    QRegExp isMask = QRegExp("*m.gif");
    isMask.setPatternSyntax(QRegExp::Wildcard);


    if(a.arguments().size()==1)
    {
        goto DisplayHelp;
    }

    for(int arg=0; arg<a.arguments().size(); arg++)
    {
        if(a.arguments().at(arg)=="--help")
        {
            goto DisplayHelp;
        }
        else
        if(a.arguments().at(arg)=="-R")
        {
            removeMode=true;
        }
        else
        if(a.arguments().at(arg)=="-W")
        {
            walkSubDirs=true;
        }
        else
        if(a.arguments().at(arg)=="--nopause")
        {
            nopause=true;
        }
        else
        {
            //if begins from "-O"
            if(a.arguments().at(arg).size()>=2 && a.arguments().at(arg).at(0)=='-'&& a.arguments().at(arg).at(1)=='O')
              {  argOPath=a.arguments().at(arg); argOPath.remove(0,2); }
            else
            {
                if(isMask.exactMatch(a.arguments().at(arg)))
                    continue;
                else
                    if(isGif.exactMatch(a.arguments().at(arg)))
                    {
                        fileList << a.arguments().at(arg);
                        singleFiles=true;
                    }
                else
                    argPath=a.arguments().at(arg);
            }
        }
    }

    if(!singleFiles)
    {
        if(argPath.isEmpty()) goto WrongInputPath;
        if(!QDir(argPath).exists()) goto WrongInputPath;

        imagesDir.setPath(argPath);
        filters << "*.gif" << "*.GIF";
        imagesDir.setSorting(QDir::Name);
        imagesDir.setNameFilters(filters);

        path = imagesDir.absolutePath() + "/";
    }

    if(!argOPath.isEmpty())
    {
        OPath = argOPath;
        if(!QFileInfo(OPath).isDir())
            goto WrongOutputPath;

        OPath = QDir(OPath).absolutePath() + "/";
    }
    else
    {
        OPath=path;
        cOpath=true;
    }

    QTextStream(stdout) <<"============================================================================\n";
    QTextStream(stdout) <<"Converting images...\n";
    QTextStream(stdout) <<"============================================================================\n";

    if(!singleFiles)
      QTextStream(stdout) << QString("Input path:  "+path+"\n");
    QTextStream(stdout) << QString("Output path: "+OPath+"\n");
    QTextStream(stdout) <<"============================================================================\n";
    if(singleFiles) //By files
    {
        foreach(QString q, fileList)
        {
            path=QFileInfo(q).absoluteDir().path()+"/";
            QString fname = QFileInfo(q).fileName();
            if(cOpath) OPath=path;
            doMagicIn(path, fname , OPath, removeMode);
        }
    }
    else
    {
        fileList << imagesDir.entryList(filters);
    if(!walkSubDirs) //By directories
        foreach(QString q, fileList)
        {
            doMagicIn(path, q, OPath, removeMode);
        }
        else
        {
            QDirIterator dirsList(imagesDir.absolutePath(), filters,
                                      QDir::Files|QDir::NoSymLinks|QDir::NoDotAndDotDot,
                                  QDirIterator::Subdirectories);

            while(dirsList.hasNext())
              {
                    dirsList.next();
                    if(QFileInfo(dirsList.filePath()).dir().dirName()=="_backup") //Skip LazyFix's Backup dirs
                        continue;

                    if(cOpath) OPath = QFileInfo(dirsList.filePath()).dir().absolutePath()+"/";
                    doMagicIn(QFileInfo(dirsList.filePath()).dir().absolutePath()+"/", dirsList.fileName(), OPath, removeMode);
              }


        }
    }

    QTextStream(stdout) <<"============================================================================\n";
    QTextStream(stdout) <<"Done!\n\n";

    if(!nopause) getchar();

    return 0;

DisplayHelp:
    QTextStream(stdout) <<"============================================================================\n";
    QTextStream(stdout) <<"This utility will merge GIF images and his mask into solid PNG image:\n";
    QTextStream(stdout) <<"============================================================================\n";
    QTextStream(stdout) <<"Syntax:\n\n";
    QTextStream(stdout) <<"   GIFs2PNG [--help] [-R] file1.gif [file2.gif] [...] [-O/path/to/out]\n";
    QTextStream(stdout) <<"   GIFs2PNG [--help] [-W] [-R] /path/to/folder [-O/path/to/out]\n\n";
    QTextStream(stdout) <<" --help              - Display this help\n";
    QTextStream(stdout) <<" /path/to/folder     - path to a directory with pairs of GIF files\n";
    QTextStream(stdout) <<" -O/path/to/out      - path to a directory where the PNG images will be saved\n";
    QTextStream(stdout) <<" -R                  - Remove source images after succesfull converting\n";
    QTextStream(stdout) <<" -W                  - Also look for images in subdirectories\n";
    QTextStream(stdout) <<"\n\n";

    getchar();

    exit(0);
    return 0;
WrongInputPath:
    QTextStream(stdout) <<"============================================================================\n";
    QTextStream(stderr) <<"Wrong input path!\n";
    goto DisplayHelp;
WrongOutputPath:
    QTextStream(stdout) <<"============================================================================\n";
    QTextStream(stderr) <<"Wrong output path!\n";
    goto DisplayHelp;
}
