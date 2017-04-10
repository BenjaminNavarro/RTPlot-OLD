#ifndef RTPLOT_H
#define RTPLOT_H

#include <string>
#include <memory>

class RTPlot
{
public:
	RTPlot(int argc, char* argv[], bool start_stdin_parser = true);
	RTPlot(bool start_stdin_parser = true);
	~RTPlot();

	void newPoint(int curve, float x, float y);
	void removeFirstPoint(int curve);
	void setMaxPoints(int count);
	void quit();
	void setXLabel(const std::string& name);
	void setYLabel(const std::string& name);
	void setCurveName(int curve, const std::string& name);
	void refresh();
	void autoRefresh(bool enable, uint period_ms = 0);
	void setXRange(float min, float max);
	void setYRange(float min, float max);
	void autoXRange();
	void autoYRange();

private:
	void create(bool start_stdin_parser);

	struct rtplot_members;
	std::unique_ptr<rtplot_members> impl_;
};

#endif // RTPLOT_H
