#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <Fl/Enumerations.h>
#include <Fl/fl_draw.h>

#include <DChartBase.h>
#include <BasicSeries.h>
#include <LineSeries.h>

#include <math.h>
#include <memory>
#include <random>
#include <iostream>

//std::unique_ptr<Fl_Box> & box
void onTestButton(Fl_Widget * w, void * d) {
    std::cout << "[test callback] "
              << std::endl;
}

void onAddSeriesButton(Fl_Widget * w, std::unique_ptr<DChartBase> & d) {
    std::unique_ptr<DChartBase> & dcb = d;
    dcb->addLineSeries();

    std::random_device rd;
    int start = round((double) rd() / (double) rd.max() * 10) - 5;
    int stop = round((double) rd() / (double) rd.max() * 10) + 50;

    for (double t = start; t < stop; t++)
    {
        double val = round((double) rd() / (double) rd.max() * 250) - 70;
        auto s = std::dynamic_pointer_cast<LineSeries>(dcb->series.back());
        s->addXY(t, val);
    }
    //dcb->series.back()->setColor(FL_MAGENTA);
    dcb->redraw();
}

void onAddBigSeriesButton(Fl_Widget * w, std::unique_ptr<DChartBase> & d) {
    std::unique_ptr<DChartBase> & dcb = d;
    dcb->addLineSeries();

    std::random_device rd;
    int start = 0;
    int stop = 100000;

    auto s = std::dynamic_pointer_cast<LineSeries>(dcb->series.back());

    //s->getHorizAxis()->setAutoSize(false);

    for (double t = start; t < stop; t++)
    {
        double val = round((double) rd() / (double) rd.max() * 1250) - 70;
        s->addXY(t, val);
    }
    //dcb->series.back()->setColor(FL_MAGENTA);
    //s->getHorizAxis()->doAutoSize(s->getMinX(), s->getMaxX());
    //s->getVertAxis()->doAutoSize(s->getMinY(), s->getMaxY());

    dcb->redraw();
}


void onAddAxisAndSeriesButton(Fl_Widget * w, std::unique_ptr<DChartBase> & d) {
    std::unique_ptr<DChartBase> & dcb = d;

    dcb->addVertAxis();
    dcb->vertAxes.back()->setIsFixed(true);
    dcb->vertAxes.back()->setVisible(true);
    dcb->vertAxes.back()->setFontColor(FL_GREEN);
    dcb->vertAxes.back()->setFontSize(24);
    dcb->vertAxes.back()->setFontFace(FL_TIMES_BOLD_ITALIC);
    dcb->vertAxes.back()->setGridColor(FL_MAGENTA);
    dcb->vertAxes.back()->setGridStyle(FL_DASHDOTDOT);
    //dcb->vertAxes.back()->setGridStyle(FL_SOLID);
    static char dashes[] = {7,17,3,17,0};
    dcb->vertAxes.back()->setGridDashes(dashes);
    dcb->vertAxes.back()->setGridWidth(2);
    dcb->addLineSeries();
    dcb->series.back()->setVertAxis(dcb->vertAxes.back());

    std::random_device rd;
    int start = round((double) rd() / (double) rd.max() * 10) - 5;
    int stop = round((double) rd() / (double) rd.max() * 10) + 50;

    for (double t = start; t < stop; t++)
    {
        double val = round((double) rd() / (double) rd.max() * 250) - 70;
        auto s = std::dynamic_pointer_cast<LineSeries>(dcb->series.back());
        s->addXY(t, val);
    }
    //dcb->series.back()->setColor(FL_MAGENTA);
    dcb->redraw();
}

int main (int argc, char ** argv)
{
    int horMargin = 10;
    int vertMargin = 10;
    int chartWidth = 800;
    int chartHeight = 600;
    int controlBoxHeight = 100;

    auto window = std::make_unique<Fl_Window>(chartWidth + horMargin * 2,
                 chartHeight + vertMargin + controlBoxHeight + vertMargin * 2);

    auto dcb = std::make_unique<DChartBase>(horMargin, vertMargin,
                                            chartWidth, chartHeight, "");
    window->resizable(*dcb);

    //dcb->defaultVertAxis->setIsFixed(true);
    //dcb->defaultHorizAxis->setIsFixed(true);

    auto controlBox = std::make_unique<Fl_Box>(FL_EMBOSSED_BOX,
                              horMargin,
                              vertMargin + chartHeight + vertMargin,
                              chartWidth,
                              controlBoxHeight,
                              nullptr);

    auto testButton = std::make_unique<Fl_Button>(controlBox->x() + horMargin,
                                                  controlBox->y() + vertMargin,
                                                  50, 20, "test");
    testButton->callback((Fl_Callback *) onTestButton);

    auto addSeriesButton = std::make_unique<Fl_Button>(
                controlBox->x() + horMargin + testButton->w() + horMargin,
                controlBox->y() + vertMargin,
                80, 20, "add series");
    addSeriesButton->callback((Fl_Callback *) onAddSeriesButton, &dcb);

    auto addAxisSeriesButton = std::make_unique<Fl_Button>(
                addSeriesButton->x() + addSeriesButton->w() + horMargin,
                controlBox->y() + vertMargin,
                130, 20, "add v axis && series");
    addAxisSeriesButton->callback((Fl_Callback *) onAddAxisAndSeriesButton, &dcb);

    auto addBigSeriesButton = std::make_unique<Fl_Button>(
                addAxisSeriesButton->x() + addAxisSeriesButton->w() + horMargin,
                controlBox->y() + vertMargin,
                130, 20, "add big series");
    addBigSeriesButton->callback((Fl_Callback *) onAddBigSeriesButton, &dcb);


    window->end();

    window->show(argc, argv);

    //dcb->vertAxes[0]->setIsFixed(true);

    dcb->addLineSeries();
    auto s = std::dynamic_pointer_cast<LineSeries>(dcb->series.back());
    s->addXY(0,0);
    s->addXY(1,10);
    s->addXY(3,30);
    s->addXY(2,70);
    s->addXY(4,50);
    s->addXY(5,20);
    s->addXY(10,100);
    s->addXY(-5, 40);
    s->sortByX();

    //dcb->series.back()->setColor(223);
    //dcb->series.back()->setColor(FL_RED);

    //std::cout << "max x = " << dcb->series.back()->getMaxX() << std::endl;

    dcb->addLineSeries();
    for (double t = 0; t < 15; t += 0.05)
    {
        double val = sin(t) * 10.0;
        std::dynamic_pointer_cast<LineSeries>(dcb->series.back())->addXY(t, val);
    }
    //dcb->series.back()->setColor(FL_GREEN);
    dcb->series.back()->setCaption("sinus");

    dcb->addLineSeries();
    for (double t = 5; t < 25; t += 0.1)
    {
        double val = cos(t - 5) * 5.0;
        std::dynamic_pointer_cast<LineSeries>(dcb->series.back())->addXY(t, val);
    }
    //dcb->series.back()->setColor(FL_BLUE);
    dcb->series.back()->setCaption("cosinus");

    return(Fl::run());
}
