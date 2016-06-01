#include "gmock/gmock.h"
#include "myFrame.h"

#include <TApplication.h>
#include <TSystem.h>


int main(int argc, char **argv) {

  TApplication rootapp("Simple Qt ROOT Application", &argc, argv);
  QApplication app(argc, argv);

  myFrame *f = new myFrame;
  f->move(600, 200); 
  f->show();
  app.exec(); 

  delete f; 
  //  testing::InitGoogleMock(&argc, argv);
  //  return RUN_ALL_TESTS(); 
  return 0; 
}

