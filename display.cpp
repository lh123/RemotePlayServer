#include "display.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <QRgb>
#include <QPainter>
#include <QDateTime>
#include <QDebug>
#include <QImage>

Display::Display(const int address)
{
    mFd = wiringPiI2CSetup(address);
    mImage = 0;
    clear();
    init();
}

Display::~Display()
{
    if(mImage != 0){
        delete mImage;
    }
}

void Display::clear()
{
    for(int i = 0;i<128*8;i++){
        mBuffer[i] = 0;
    }
    if(mImage != 0 ){
        QPainter painter(mImage);
        painter.setBrush(QBrush(Qt::black,Qt::SolidPattern));
        painter.drawRect(mImage->rect());
        painter.end();
    }
}

void Display::setPixel(int x, int y, bool on)
{
    int pos = x + (y/8) * DISPLAY_WIDTH;
    if(pos >= 0 && pos < MAX_INDEX){
        if(on){
            mBuffer[pos] |= (1 << (y & 0x07));
        }else{
            mBuffer[pos] &= ~(1 << (y & 0x07));
        }
    }
}

void Display::drawImg(QPixmap pix)
{
    QPainter painter;
    painter.begin(getImage());
    painter.drawPixmap(getImage()->rect(),pix);
    painter.end();
}

void Display::update()
{

    if(mImage != 0){
        for(int x = 0 ; x<mImage->width();x++){
            for(int y = 0 ; y<mImage->height();y++){
                QRgb rgb = mImage->pixel(x,y);
                setPixel(x,y,qGray(rgb)==0?false:true);
            }
        }
    }

    command(COLUMNADDR);
    command(0);
    command(DISPLAY_WIDTH-1);
    command(PAGEADDR);
    command(0);
    command(7);
    for(int i=0;i<128*8;i+=1){
        wiringPiI2CWriteReg8(mFd,0x40,mBuffer[i]);
    }
}

QImage* Display::getImage()
{
    if(mImage == 0){
        mImage = new QImage(DISPLAY_WIDTH,DISPLAY_HEIGHT,QImage::Format_Mono);
    }
    return mImage;
}

void Display::command(int command)
{
    command &= 0xFF;
    wiringPiI2CWriteReg8(mFd,0x00,command);
}

void Display::init()
{
    command(DISPLAYOFF);
    command(SETDISPLAYCLOCKDIV);
    command(0x80);
    command(SETMULTIPLEX);
    command(0x3F);
    command(SETDISPLAYOFFSET);
    command(0x00);
    command(SETSTARTLINE);
    command(CHARGEPUMP);
    command(0x14);
    command(MEMORYMODE);
    command(0x00);
    command(SEGREMAP|0x1);
    command(COMSCANDEC);
    command(SETCOMPINS);
    command(0x12);
    command(SETCONTRAST);
    command(0xCF);
    command(SETPRECHARGE);
    command(0xF1);
    command(SETVCOMDETECT);
    command(0x40);
    command(DISPLAYALLON_RESUME);
    command(NORMALDISPLAY);
    command(DISPLAYON);
}
