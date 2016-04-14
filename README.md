# Usage

RTPlot is a simple utility designed to display graphs in real time with minimum overhead.

Once RTPlot is launched, it waits for commands from stdin. Here is the list of commands currently supported (create an issue if you need something else) : 

| **Commands & arguments**   | **Description**                                              |
|----------------------------|--------------------------------------------------------------|
| plot xvalue yvalue         | Add a point (xvalue,yvalue) to the default graph             |
| plot curve xvalue yvalue   | Add a point (xvalue,yvalue) to the graph numbered (curve)    |
| remove_point               | Remove the first point of the default graph                  |
| remove_point curve         | Remove the first point of the graph numbered (curve)         |
| xlabel name                | Set the x axis label to (name)                               |
| ylabel name                | Set the y axis label of the default graph to (name)          |
| ylabel curve name          | Set the y axis label of the graph numbered (curve) to (name) |
| refresh                    | Refresh the window to display all the given points           |
| auto_refresh on/off        | Enable or disable the call to refresh every 100ms            |
| auto_refresh on/off period | Enable or disable the call to refresh every (period) ms      |
| xrange min max             | Set the x axis range to (min,max)                            |
| yrange min max             | Set the y axis range to (min,max)                            |
| auto_x_range               | The x axis will resize itself to display every point         |
| auto_y_range               | The y axis will resize itself to display every point         |
| quit                       | Terminate the program                                        |

Note : the default graph is numbered 0 so "plot 0.5 4" is equivalent to "plot 0 0.5 4" 

To embed RTPlot in your application, you can create a pipe to it and then send some commands

# System dependency

Since RTPlot uses Qt and Qt uses OpenGL, you may have to install the OpenGL development files. On Ubuntu this can be done by installing the following package : mesa-common-dev

```
sudo apt-get install mesa-common-dev
```
