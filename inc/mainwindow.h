/* 	File: mainwindow.h 	
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "qcustomplot.h"
#include "inputparserthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
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

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QCPGraph* getCurve(int curve);

    Qt::GlobalColor getNewColor();

private:
    Ui::MainWindow *ui;

    InputParserThread parser;
    QCustomPlot* plot;
    QMap<uint, QCPGraph*> curve_to_graph;
    QTimer auto_update_timer;
    bool auto_x_range, auto_y_range;
    uint color_index;
    double xmin, xmax, ymin, ymax;
};

#endif // MAINWINDOW_H
