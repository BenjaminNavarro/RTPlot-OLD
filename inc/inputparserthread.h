/* 	File: inputparserthread.h 	
*	This file is part of the program rtplot
*  	Program description : rtplot takes commands from stdin to display graphs. See the readme for usage
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
#ifndef INPUTPARSERTHREAD_H
#define INPUTPARSERTHREAD_H

#include <QThread>

class InputParserThread : public QThread
{
    Q_OBJECT
public:
    InputParserThread();
    ~InputParserThread();

    void run();

    void stop();

signals:
    void newPoint(int curve, double x, double y);
    void removeFirstPoint(int curve);
    void quit();
    void setXLabel(QString name);
    void setYLabel(QString name);
    void setCurveName(int curve, QString name);
    void refresh();
    void autoRefresh(bool enable, uint period_ms);
    void setXRange(double min, double max);
    void setYRange(double min, double max);
    void autoXRange();
    void autoYRange();

private:
    int peek_stdin(unsigned int secs);
    bool stop_;
};

#endif // INPUTPARSERTHREAD_H
