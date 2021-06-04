#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <Fl/Enumerations.h>

#include <DChartBase.h>
#include <Series.h>

#include <math.h>
#include <memory>

int main (int argc, char ** argv)
{
  auto window = std::make_unique<Fl_Window>(1000, 800);

  auto dcb = std::make_unique<DChartBase>(20, 20,
                                   window->w() - 40,
                                   window->h() - 140, "");
  window->resizable(*dcb);

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
  for (double t = 0; t < 15; t += 0.05) {
      double val = sin(t) * 10.0;
      dcb->series.back()->addXY(t, val);
  }
  dcb->series.back()->setColor(FL_GREEN);
  dcb->series.back()->setCaption("sinus");

  dcb->addSeries();
  for (double t = 5; t < 25; t += 0.1) {
      double val = cos(t - 5) * 5.0;
      dcb->series.back()->addXY(t, val);
  }
  dcb->series.back()->setColor(FL_BLUE);
  dcb->series.back()->setCaption("cosinus");

  //dcb->unZoom();

  return(Fl::run());
}
