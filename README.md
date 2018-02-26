# RTPlot
RTPlot is a FLTK based real time plotting solution. It has been developed to try to keep the CPU usage at the minimum so that you can feed it a large number of points in real time without impacting the rest of your system.

An old Qt based version has been developed and is still available on the [Qt branch](https://github.com/BenjaminNavarro/RTPlot/tree/Qt) but it won't be maintained anymore. It is far less optimized that the current FLTK version.

# Usage

## As a FLTK widget
It can be instanciated as any other FLTK widget:
```
#include <rtplot/Fl_plot.H>
```
then
```
auto window = new Fl_Window(655, 450, "RTPlot");

auto plot = new Fl_Plot(70, 15, 555, 380, "plot");

window->end();
```

## As a library
You can use the wrapper class RTPlot in `rtplot/rtplot.h` to use it without knowing anything about FLTK. It is a great way to embed RTPlot in other applications.

## As an application
You can use the `rtplot` app. Once it is launched, it waits for commands from stdin. Here is the list of commands currently supported (create an issue if you need something else) :

| **Commands & arguments**   | **Description**                                                                            |
|----------------------------|--------------------------------------------------------------------------------------------|
| plot xvalue yvalue         | Add a point (xvalue,yvalue) to the default curve                                           |
| plot curve xvalue yvalue   | Add a point (xvalue,yvalue) to the curve numbered (curve)                                  |
| remove_point               | Remove the first point of the default curve                                                |
| remove_point curve         | Remove the first point of the curve numbered (curve)                                       |
| max_points count           | Limit the number of points of every curve to (max_points_). Disabled for a negative value. |
| xlabel name                | Set the x axis label to (name). Can contain spaces.                                        |
| ylabel name                | Set the y axis label of the default curve to (name). Can contain spaces.                   |
| yname name                 | Set the label of the default curve to (name)                                               |
| yname curve name           | Set the label of the curve numbered (curve) to (name)                                      |
| refresh                    | Refresh the window to display all the given points                                         |
| auto_refresh on/off        | Enable or disable the automatic call to refresh every 100ms                                |
| auto_refresh on/off period | Enable or disable the automatic call to refresh every (period) ms                          |
| xrange min max             | Set the x axis range to (min,max)                                                          |
| yrange min max             | Set the y axis range to (min,max)                                                          |
| auto_xrange                | The x axis will resize itself to display every point                                       |
| auto_yrange                | The y axis will resize itself to display every point                                       |
| sem_name                   | Named semaphore to post to when RTPlot is ready                                            |
| quit                       | Terminate the program                                                                      |

Note : the default curve is numbered 0 so "plot 0.5 4" is equivalent to "plot 0 0.5 4"

To embed RTPlot in your application without using the library, create a pipe to it and then send commands. This approach is less efficient that the two other ones.

# Benchmark
On an Intel i7-6700HQ computer running archlinux (4.10.8 kernel), the `test_rtplot` app (plots six sine waves sending new values every millisecond, refreshes the plot every 20ms) consumes around 15% of the CPU.

# TODO
 * Documentation
 * Subplots (multiple plots in the same window)
 * Integration with Nanomsg
