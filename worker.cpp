#include "worker.h"
#include <QDebug>

Worker::Worker()
{

}

void Worker::run(){
    while(true){
        QPixmap pixMap = this->inter->getPixmap();
        wm->label->setPixmap(pixMap);
    }
}
