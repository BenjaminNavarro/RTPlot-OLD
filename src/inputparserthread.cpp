/* 	File: inputparserthread.cpp 	
*	This file is part of the program rtplot
*  	Program description : rtplot takes commands from stdin to display graphs. See the wiki for usage
*  	Copyright (C) 2015 -  Benjamin Navarro (LIRMM). All Right reserved.
*
*	This software is free software: you can redistribute it and/or modify
*	it under the terms of the CeCILL-C license as published by
*	the CEA CNRS INRIA, either version 1 
*	of the License, or (at your option) any later version.
*	This software is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*	CeCILL-C License for more details.
*
*	You should have received a copy of the CeCILL-C License
*	along with this software. If not, it can be found on the official website 
*	of the CeCILL licenses family (http://www.cecill.info/index.en.html).
*/
#include "inputparserthread.h"

#include <QDebug>
#include <QSystemSemaphore>
#include <QMessageBox>
#include <iostream>
#include <unistd.h>

#include <semaphore.h>
#include <sys/sem.h>
#include <fcntl.h>

using namespace std;

InputParserThread::InputParserThread() : stop_(false)
{

}

InputParserThread::~InputParserThread()
{

}

void InputParserThread::run() {
    while(!stop_) {
        if(peek_stdin(5) != 0) { // wait for 5s before checking if we have to exit or not (stop_ flag)
            string input;
            getline(cin, input);
            QStringList args;
            args = QString(input.c_str()).split(' ');
            QString cmd = args[0];

            // Handle names with spaces
            if(cmd == "xlabel") {
                args.removeFirst();
                emit setXLabel(args.join(' '));
            }
            else if(cmd == "ylabel") {
                args.removeFirst();
                emit setXLabel(args.join(' '));
            }
            else if(cmd == "yname") {
                int curve;
                if(args.size() > 2) {
                    curve = args[1].toUInt();
                    args.removeFirst();
                }
                else
                    curve = -1;

                args.removeFirst();
                emit setCurveName(curve, args.join(' '));
            }
            else {
                switch(args.size()) {
                case 1:
                    if(cmd == "remove_point")
                        emit removeFirstPoint(-1);
                    else if(cmd == "refresh")
                        emit refresh();
                    else if(cmd == "auto_x_range")
                        emit autoXRange();
                    else if(cmd == "auto_y_range")
                        emit autoYRange();
                    else if(cmd == "quit") {
                        stop_ = true;
                        emit quit();
                    }
                    break;
                case 2:
                    if(cmd == "remove_point")
                        emit removeFirstPoint(args[1].toUInt());
                    else if(cmd == "auto_refresh")
                        emit autoRefresh(args[1] == "on", 100);
                    else if(cmd == "sem_name") {
                        sem_t * mutex;
                        if ((mutex = sem_open(args[1].toStdString().c_str(), O_CREAT, 0644, 0)) == SEM_FAILED) {
                            std::cerr << "semaphore " + args[1].toStdString() + "failed to initialized" << std::endl;;
                        }
                        else {
                            sem_post(mutex);
                        }
                    }
                    break;
                case 3:
                    if(cmd == "plot")
                        emit newPoint(-1, args[1].toDouble(), args[2].toDouble());
                    else if(cmd == "auto_refresh")
                        emit autoRefresh(args[1] == "on", args[2].toUInt());
                    else if(cmd == "xrange")
                        emit setXRange(args[1].toDouble(), args[2].toDouble());
                    else if(cmd == "yrange")
                        emit setYRange(args[1].toDouble(), args[2].toDouble());
                    break;
                case 4:
                    if(cmd == "plot")
                        emit newPoint(args[1].toUInt(), args[2].toDouble(), args[3].toDouble());
                    break;
                default:
                    break;
                }
            }
        }
    }
}

int InputParserThread::peek_stdin(unsigned int secs) {
    // timeout structure passed into select
    struct timeval tv;
    // fd_set passed into select
    fd_set fds;
    // Set up the timeout.  here we can wait for 1 second
    tv.tv_sec = secs;
    tv.tv_usec = 0;

    // Zero out the fd_set - make sure it's pristine
    FD_ZERO(&fds);
    // Set the FD that we want to read
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    // select takes the last file descriptor value + 1 in the fdset to check,
    // the fdset for reads, writes, and errors.  We are only passing in reads.
    // the last parameter is the timeout.  select will return if an FD is ready or 
    // the timeout has occurred
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    // return 0 if STDIN is not ready to be read.
    return FD_ISSET(STDIN_FILENO, &fds);
}

void InputParserThread::stop() {
    stop_ = true;
}