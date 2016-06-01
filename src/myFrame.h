#ifndef WIDGETTEST_H
#define WIDGETTEST_H

#include "myframe.h"
#include "kFrame.h"
#include "QRootCanvas.h"
#include "QtWidgets/QFileDialog"
#include "TFile.h"
#include "TKey.h"
#include "TLatex.h"


class myFrame : public QFrame
{
  Q_OBJECT

 public:
  myFrame(QFrame *parent =0);
  virtual ~myFrame();


  void updateCanvas(); 
  public slots:
    void handle_root_events(); 
    void loadFile();
    void forward();
    void back();
    void keyList();
    void updateKey(QString s); 
    
 private:
  Ui::myframe *ui;

  keyFrame *kFrame; 
  QTimer *fRootTimer;
  TObject *o; 
  TFile *f;
  TKey *current; 
}; 

#endif
