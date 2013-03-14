#include "controller.h"

Controller::Controller(QWidget *ballsParent, QObject *parent) :
    QObject(parent)
{
    this->ballsParent = ballsParent;
    this->ballGiver = new Factory(this);
    board.resize(20);
    for (int i=0; i<20; ++i) {
        board[i].resize(20);
    }
    for (int i=0; i<20; ++i) {
        for(int j=0; j<20; ++j) {
            board[i][j] = 0;
        }
    }
}

Controller* Controller::control;
void Controller::init(QWidget *ballsParent) {
    control = new Controller(ballsParent);
    control->setDefault();
}

void Controller::setPlayers(int nr) {
    this->players = nr;
}

void Controller::setSize(int nr) {
    this->size = nr;
    ballGiver->size = nr;
}

void Controller::setColors(int nr) {
    this->colors = nr;
    ballGiver->colors = nr;
}

void Controller::setDefault() {
    size = 10;
    ballsSize = 533/size ;
    margin = (533 - size*ballsSize)/2;
    colors = 5;
    joker = 5;
    bonus = 5;
    skull = 0;
    cameleon = 5;
    hourglass = 0;
    score = 0;
    multi = 1;
    ballGiver->colors = colors;
    ballGiver->size = ballsSize;
}

Ball* Controller::ballAt(int i, int j) {
    return (Ball*) ballsParent->childAt(margin+i*ballsSize+5, margin+j*ballsSize+5);
}

void Controller::fillBoard(){
    bool sthDone = false;

    //cleaning mess
    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            board[i][j] = ballAt(i,j);
        }
    }

    //proper filling
    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            if (ballAt(i, j) == 0) {
                Ball *newBall = ballGiver->giveBall(ballsParent);
                newBall->setGeometry(margin+i*ballsSize, margin+j*ballsSize, ballsSize, ballsSize);
                newBall->paint();
                board[i][j] = newBall;
                sthDone = true;
            }
        }
    }
    if (sthDone)
        removeMatching();
    else {
        emit newFirstScore(score*multi);
        score = 0;
        multi = 1;
    }

}
void Controller::removeMatching(){
    bool sthDone = false;
    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            if (i < size -2) {
                if ((board[i][j]->matches(board[i+1][j])) &&
                        (board[i][j]->matches(board[i+2][j])) &&
                        (board[i+1][j]->matches(board[i+2][j]))) {
                    board[i][j]->hide();
                    board[i+1][j]->hide();
                    board[i+2][j]->hide();
                    sthDone = true;
                }
            }
            if (j < size -2) {
                if ((board[i][j]->matches(board[i][j+1])) &&
                        (board[i][j]->matches(board[i][j+2])) &&
                        (board[i][j+2]->matches(board[i][j+1]))) {
                    board[i][j]->hide();
                    board[i][j+1]->hide();
                    board[i][j+2]->hide();
                    sthDone = true;
                }
            }
        }
    }
    gravity();
}
/*
bool Controller::checkMove(Ball *first, Ball *second){
    int firstI, firstJ, secondI, secondJ;
    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            if (board[i][j] == first) {
                firstI = i;
                firstJ = j;
            }
            if (board[i][j] == second) {
                secondI = i;
                secondJ = j;
            }
        }
    }
    if (((firstI -firstJ == 1) && (secondI - secondJ == 0)) ||
            ((firstI -firstJ == -1) && (secondI - secondJ == 0)) ||
            ((firstI -firstJ == 0) && (secondI - secondJ == 1)) ||
            ((firstI -firstJ == 0) && (secondI - secondJ == -1)) ||) {
        return true;
        //TODO

    } else {
        return false;
    }
}*/

void Controller::gravity() {
    QParallelAnimationGroup *animate = new QParallelAnimationGroup();
    bool sthDone = false;
    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            int down = 0;
            for (int k=j+1; k<size; ++k) {
                if (board[i][k]->isHidden()) {
                    down++;
                }
            }
            if (down != 0) {
                QPropertyAnimation *ballAnime = new QPropertyAnimation(board[i][j], "geometry");
                ballAnime->setDuration(200*down);
                ballAnime->setEndValue(board[i][j+down]->geometry());
                animate->addAnimation(ballAnime);
                sthDone = true;
            }
        }
    }

    if (sthDone) {
        connect(animate, SIGNAL(finished()), this, SLOT(addPoints()));
        animate->start();
    } else {
        addPoints();
    }

}

void Controller::addPoints() {
    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
           if (board[i][j]->isHidden()) {
               score += board[i][j]->value;
               multi *= board[i][j]->multiplier;
               board[i][j]->deleteLater();
            }
        }
    }
    fillBoard();
}

void Controller::moveBalls(Ball *first, Ball *second){
    QPropertyAnimation *animFirst = new QPropertyAnimation(first, "geometry");
    animFirst->setDuration(1000);
    animFirst->setEndValue(second->geometry());
    QPropertyAnimation *animSecond = new QPropertyAnimation(second, "geometry");
    animSecond->setDuration(1000);
    animSecond->setEndValue(first->geometry());
    QParallelAnimationGroup *animate = new QParallelAnimationGroup();
    animate->addAnimation(animFirst);
    animate->addAnimation(animSecond);
    connect(animate, SIGNAL(finished()), this, SLOT(removeMatching()));
    animate->start();
}
