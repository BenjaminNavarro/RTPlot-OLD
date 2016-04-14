/* 	File: mainwindow.cpp 	
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
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    auto_x_range(true),
    auto_y_range(true),
    color_index(1)
{
    ui->setupUi(this);
    setGeometry(400, 250, 542, 390);
    setWindowTitle("RTPlot");

    plot = ui->customPlot;

    connect(&parser, SIGNAL(newPoint(int,double,double)), this, SLOT(newPoint(int,double,double)));
    connect(&parser, SIGNAL(removeFirstPoint(int)), this, SLOT(removeFirstPoint(int)));
    connect(&parser, SIGNAL(quit()), this, SLOT(quit()));
    connect(&parser, SIGNAL(setXLabel(QString)), this, SLOT(setXLabel(QString)));
    connect(&parser, SIGNAL(setYLabel(QString)), this, SLOT(setYLabel(QString)));
    connect(&parser, SIGNAL(setCurveName(int,QString)), this, SLOT(setCurveName(int,QString)));
    connect(&parser, SIGNAL(refresh()), this, SLOT(refresh()));
    connect(&parser, SIGNAL(autoRefresh(bool, uint)), this, SLOT(autoRefresh(bool, uint)));
    connect(&parser, SIGNAL(setXRange(double,double)), this, SLOT(setXRange(double,double)));
    connect(&parser, SIGNAL(setYRange(double,double)), this, SLOT(setYRange(double,double)));
    connect(&parser, SIGNAL(autoXRange()), this, SLOT(autoXRange()));
    connect(&parser, SIGNAL(autoYRange()), this, SLOT(autoYRange()));

    connect(&auto_update_timer, SIGNAL(timeout()), this, SLOT(refresh()));

    plot->replot();
    plot->addGraph();

    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iMultiSelect);

    plot->legend->setVisible(true);

    parser.start();
}

MainWindow::~MainWindow()
{
    parser.stop();
    parser.wait();
    delete ui;
}

QCPGraph* MainWindow::getCurve(int curve) {
    QCPGraph* graph;

    if(curve_to_graph.size() == 0) {
        curve_to_graph[curve] = plot->graph(0);
    }

    if(curve == -1)
        graph = curve_to_graph.first();
    else
        graph = curve_to_graph[curve];

    if(graph == NULL) {
        graph = plot->addGraph();
        graph->setPen(QPen(getNewColor()));
        curve_to_graph[curve] = graph;
    }
    return graph;
}

Qt::GlobalColor MainWindow::getNewColor() {
    Qt::GlobalColor color;
    switch(color_index) {
    case 0:
        color = Qt::blue;
        break;
    case 1:
        color = Qt::red;
        break;
    case 2:
        color = Qt::green;
        break;
    case 3:
        color = Qt::cyan;
        break;
    case 4:
        color = Qt::magenta;
        break;
    case 5:
        color = Qt::yellow;
        break;
    case 6:
        color = Qt::gray;
        break;
    case 7:
        color = Qt::black;
        break;
    case 8:
        color = Qt::darkBlue;
        break;
    case 9:
        color = Qt::darkRed;
        break;
    case 10:
        color = Qt::darkGreen;
        break;
    case 11:
        color = Qt::darkCyan;
        break;
    case 12:
        color = Qt::darkMagenta;
        break;
    case 13:
        color = Qt::darkYellow;
        break;
    case 14:
        color = Qt::darkGray;
        break;
    }

    if(color_index < 14)
        ++color_index;
    else
        color_index = 0;

    return color;
}

void MainWindow::newPoint(int curve, double x, double y) {
    QCPGraph* graph = getCurve(curve);
    graph->addData(x, y);
}

void MainWindow::removeFirstPoint(int curve) {
    QCPGraph* graph = getCurve(curve);
    graph->removeData(graph->data()->first().key);
}

void MainWindow::setXLabel(QString name) {
    plot->xAxis->setLabel(name);
    refresh();
}

void MainWindow::setYLabel(QString name) {
    plot->yAxis->setLabel(name);
    refresh();
}

void MainWindow::setCurveName(int curve, QString name) {
    QCPGraph* graph = getCurve(curve);
    graph->setName(name);
    refresh();
}

void MainWindow::refresh() {
    if(auto_x_range)
        plot->xAxis->rescale();
    else
        plot->xAxis->setRange(xmin, xmax);

    if(auto_y_range)
        plot->yAxis->rescale();
    else
        plot->yAxis->setRange(ymin, ymax);

    plot->replot();
}

void MainWindow::quit() {
    QApplication::quit();
}

void MainWindow::autoRefresh(bool enable, uint period_ms) {
    if(enable)
        auto_update_timer.start(period_ms);
    else
        auto_update_timer.stop();
}

void MainWindow::setXRange(double min, double max) {
    auto_x_range = false;
    xmin = min;
    xmax = max;
    refresh();
}

void MainWindow::setYRange(double min, double max) {
    auto_y_range = false;
    ymin = min;
    ymax = max;
    refresh();
}

void MainWindow::autoXRange() {
    auto_x_range = true;
    refresh();
}

void MainWindow::autoYRange() {
    auto_y_range = true;
    refresh();
}
