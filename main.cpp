#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <Fl/Enumerations.h>

#include <DChartBase.h>
#include <Series.h>

#include <math.h>
#include <memory>
#include <iostream>

void onTestButton(Fl_Widget * w, void * d) {
    std::cout << "test callback\n";
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

    auto controlBox = std::make_unique<Fl_Box>(FL_EMBOSSED_BOX,
                              horMargin,
                              vertMargin + chartHeight + vertMargin,
                              chartWidth,
                              controlBoxHeight,
                              nullptr);

    auto testButton = std::make_unique<Fl_Button>(controlBox->x() + vertMargin,
                                                  controlBox->y() + horMargin,
                                                  50, 20, "test");
    testButton->callback((Fl_Callback *) onTestButton);

    window->end();

    window->show(argc, argv);

    dcb->addSeries();
    dcb->series.back()->addXY(0,0);
    dcb->series.back()->addXY(1,10);
    dcb->series.back()->addXY(3,30);
    dcb->series.back()->addXY(2,70);
    dcb->series.back()->addXY(4,50);
    dcb->series.back()->addXY(5,20);
    dcb->series.back()->addXY(10,100);
    dcb->series.back()->sortByX();
    dcb->series.back()->setColor(FL_RED);

    //std::cout << "max x = " << dcb->series.back()->getMaxX() << std::endl;

    dcb->addSeries();
    for (double t = 0; t < 15; t += 0.05)
    {
        double val = sin(t) * 10.0;
        dcb->series.back()->addXY(t, val);
    }
    dcb->series.back()->setColor(FL_GREEN);
    dcb->series.back()->setCaption("sinus");

    dcb->addSeries();
    for (double t = 5; t < 25; t += 0.1)
    {
        double val = cos(t - 5) * 5.0;
        dcb->series.back()->addXY(t, val);
    }
    dcb->series.back()->setColor(FL_BLUE);
    dcb->series.back()->setCaption("cosinus");

    //dcb->unZoom();

    return(Fl::run());
}
