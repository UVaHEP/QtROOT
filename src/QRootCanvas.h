#ifndef QROOTCANVAS_H
#define QROOTCANVAS_H

#include <QtWidgets/QWidget>
#include <QtCore/QTimer>
#include <QtGui/QPaintEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QMessageBox>



#include <TCanvas.h>
#include <TVirtualX.h>
#include <TSystem.h>
#include <TFormula.h>
#include <TF1.h>
#include <TH1.h>
#include <TFrame.h>
#include <TTimer.h>



class QRootCanvas : public QWidget
{
  Q_OBJECT

 public:
  QRootCanvas ( QWidget *parent = 0 );
  virtual ~QRootCanvas(); 
  TCanvas* getCanvas() { return fCanvas; }

 protected:
  TCanvas *fCanvas;

  virtual void mouseMoveEvent( QMouseEvent *e );
  virtual void mousePressEvent( QMouseEvent *e );
  virtual void mouseReleaseEvent( QMouseEvent *e );
  virtual void paintEvent( QPaintEvent *e );
  virtual void resizeEvent( QResizeEvent *e );

  virtual QPaintEngine* paintEngine() const; 

};


#endif
