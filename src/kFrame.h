#ifndef KFRAME_H
#define KFRAME_H

#include "KeyFrame.h"
#include "TList.h"

class keyFrame : public QFrame
{

  Q_OBJECT

 public:
  keyFrame(QFrame *parent = 0);

  virtual ~keyFrame();
  void updateKeyList(TList *lst);
  

  
  signals:
    void hidden(QString s);
    void itemClicked(QString s); 

 protected:
    void closeEvent(QCloseEvent *event);

    protected slots:
      void listItemClicked(QListWidgetItem *w);

 private:
    Ui::KeyFrame *kFrame; 


}; 


#endif 
