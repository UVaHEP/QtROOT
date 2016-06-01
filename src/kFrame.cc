#include "kFrame.h"
#include <set>

using std::set; 
namespace Ui {

  class KeyFrame;

}


keyFrame::keyFrame(QFrame *parent)
  : QFrame(parent), kFrame(new Ui::KeyFrame())
{
  kFrame->setupUi(this);
  QObject::connect(kFrame->Keys, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(listItemClicked(QListWidgetItem *))); 

}

keyFrame::~keyFrame() {
  delete kFrame;
}


void keyFrame::closeEvent(QCloseEvent *event)  {

  auto chosen = kFrame->Keys->currentItem();
  QString s(chosen->text());
  
  emit hidden(s); 
}

void keyFrame::listItemClicked(QListWidgetItem *w) {

  auto chosen = kFrame->Keys->currentItem();
  QString s(chosen->text());
  
  emit itemClicked(s); 
  

}

void keyFrame::updateKeyList(TList *lst) {
  //Rebuilding the list everytime is inefficient, but unlikely to slow things
  //down much in the long run. If it becomes a problem it can get replaced


  if (lst == NULL)
    return;

  kFrame->Keys->clear(); 
  TIter b(lst->begin());
  auto keyList = kFrame->Keys;

  std::set<std::string> strs;
  
  while (auto key = b.Next()) {
    auto search = strs.find(key->GetName());
    if (search == strs.end()) {
      strs.insert(key->GetName());
      QString label(key->GetName());
      keyList->addItem(label);
    }

  }




}
