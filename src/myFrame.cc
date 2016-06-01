#include "myFrame.h"
#include <iostream>


namespace Ui {

  class myframe; 

}

myFrame::myFrame(QFrame *parent)
  : QFrame(parent), ui(new Ui::myframe()) 
{ 

  ui->setupUi(this);
  kFrame = NULL;
  f = NULL; 
  //Post-UI setup prepare Root Canvas
  fRootTimer = new QTimer(this);
  QObject::connect (fRootTimer, SIGNAL(timeout()), this, SLOT(handle_root_events()));
  QObject::connect (ui->LoadBtn, SIGNAL(clicked()), this, SLOT(loadFile()));
  QObject::connect (ui->Forward, SIGNAL(clicked()), this, SLOT(forward()));
  QObject::connect (ui->Back, SIGNAL(clicked()), this, SLOT(back()));
  QObject::connect (ui->KeyBtn, SIGNAL(clicked()), this, SLOT(keyList())); 
  
  fRootTimer->start(20);
  /*  std::cout << "Canvas win ID:" << ui->widget->winId() << std::endl;
  std::cout << "Back Arrow ID:" << ui->Back->winId() << std::endl;
  std::cout << "Front Arrow ID:" << ui->Forward->winId() << std::endl; */
  ui->widget->getCanvas()->Clear();
  ui->widget->getCanvas()->cd();
  ui->widget->getCanvas()->SetBorderMode(0);
  ui->widget->getCanvas()->SetFillColor(0);
  ui->widget->getCanvas()->SetGrid();

  //Note: ROOT objects clean up things that they own, hence the no delete with
  //the TLatex object
  TLatex *l = new TLatex(0.15, 0.5, "ROOT Canvas");
  l->SetTextSize(0.1);
  l->Draw();
  
  ui->widget->getCanvas()->Modified();
  ui->widget->getCanvas()->Update();

  
}


myFrame::~myFrame() {
  delete ui;
  delete kFrame;
  delete fRootTimer; 

  if (f) {
    f->Close();
    delete f;
  }
      
  
}

void myFrame::handle_root_events() {

  //Call ROOT's inner loop 
  gSystem->ProcessEvents(); 
}

void myFrame::loadFile() {

  //Load a Root Pulse File
  auto fileName = QFileDialog::getOpenFileName(this, tr("Open Pulses File"), ".",
					       tr("ROOT Files (*.root)"));


  if (fileName.isEmpty())
    return; 

  //Add error checking
  if (f) {
    f->Close();
    delete f;
    o = NULL; 
  }

  
  std::cout << "You chose: " << fileName.toStdString() << std::endl;
  f = new TFile(fileName.toStdString().c_str()); 
  
  if (f) {

    TKey *k = f->GetKey("pulses", 9999);
    std::cout << "Waveform Count:" << k->GetCycle()  << std::endl;
    // we should have around 50 for the cycle count
    // get the first entry and update our canvas
    k = f->GetKey("pulses", 1);

    if (k == nullptr)
      return; 

    o = k->ReadObj(); 
    current = k; 
    ui->widget->getCanvas()->Clear();
    ui->widget->getCanvas()->cd();
    ui->widget->getCanvas()->SetBorderMode(0);
    ui->widget->getCanvas()->SetFillColor(0);
    ui->widget->getCanvas()->SetGrid();

    updateCanvas(); 

      
    

  }
  
}

//May want to turn into one function with forward/backward arg
void myFrame::forward() {
  //Move to next waveform

  if (f == NULL)
    return; 
  ui->widget->getCanvas()->Clear();
  ui->widget->getCanvas()->cd();
  auto c = f->GetKey(current->GetName(), 9999)->GetCycle(); 
  if (current->GetCycle() < c) 
    current = f->GetKey(current->GetName(), current->GetCycle()+1);
  else
    current = f->GetKey(current->GetName(), 1);

  std::cout << "Next Cycle:" << current->GetCycle() << std::endl; 
  o = current->ReadObj();
  updateCanvas(); 

  

}
void myFrame::back() {
  //Move to previous waveform
  if (f == NULL)
    return; 
  ui->widget->getCanvas()->Clear();
  ui->widget->getCanvas()->cd();
  auto c = f->GetKey(current->GetName(), 9999)->GetCycle(); 
  if (current->GetCycle() > 1) 
    current = f->GetKey(current->GetName(), current->GetCycle()-1);
  else
    current = f->GetKey(current->GetName(), c);

  std::cout << "Previous Cycle:" << current->GetCycle() << std::endl; 
  o = current->ReadObj();
  updateCanvas(); 
  



}

void myFrame::updateKey(QString s) {
  //SLOT for updating currently view ROOT object 

  //  std::cout << "Key:" << s.toStdString() << std::endl;
  auto key = f->GetKey(s.toStdString().c_str(), 1);

  if (key == NULL)
    return;
  
  /*  TString cname(key->GetClassName());

  if (cname != "TH1F")
    return;

  current = key; 
  
  
  ex = dynamic_cast<TH1F*>(current->ReadObj());
  ex->Draw();*/
  current = key; 
  o = key->ReadObj();
  updateCanvas(); 
  

}


void myFrame::keyList() {
  //Generate a frame containing the list of keys in the currently opened ROOT file
  if (f == NULL) { 
    std::cout << "Open a ROOT File!" << std::endl;
    return; 
  }

  
  if (kFrame == NULL) { 
    kFrame = new keyFrame();
    // QObject::connect(kFrame, SIGNAL(hidden(QString)), this, SLOT(updateKey(QString)));
    QObject::connect(kFrame, SIGNAL(itemClicked(QString)), this, SLOT(updateKey(QString))); 
  }

  
  kFrame->show(); 

  kFrame->updateKeyList(f->GetListOfKeys()); 


  
}


void myFrame::updateCanvas() {
  //Update our canvas after a change
  ui->widget->getCanvas()->cd();
  o->Draw(); 
  ui->widget->getCanvas()->Modified();
  ui->widget->getCanvas()->Update();

}
