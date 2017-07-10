#ifndef DISPLAY_H
#define DISPLAY_H
#include <QPixmap>
class QImage;
class Display
{
public:
    Display(const int address);
    ~Display();
    void clear();
    void setPixel(int x,int y,bool on);
    void drawImg(QPixmap pix);
    void update();
    QImage* getImage();
    enum OLED{
        DEFAULT_DISPLAY_ADDRESS = 0x3C,

        DISPLAY_WIDTH = 128,
        DISPLAY_HEIGHT = 64,
        MAX_INDEX = (DISPLAY_HEIGHT / 8) * DISPLAY_WIDTH,

        SETCONTRAST = 0x81,
        DISPLAYALLON_RESUME = 0xA4,
        DISPLAYALLON = 0xA5,
        NORMALDISPLAY = 0xA6,
        INVERTDISPLAY = 0xA7,
        DISPLAYOFF = 0xAE,
        DISPLAYON = 0xAF,

        SETDISPLAYOFFSET = 0xD3,
        SETCOMPINS = 0xDA,

        SETVCOMDETECT = 0xDB,

        SETDISPLAYCLOCKDIV = 0xD5,
        SETPRECHARGE = 0xD9,

        SETMULTIPLEX = 0xA8,

        SETLOWCOLUMN = 0x00,
        SETHIGHCOLUMN = 0x10,

        SETSTARTLINE = 0x40,

        MEMORYMODE = 0x20,
        COLUMNADDR = 0x21,
        PAGEADDR = 0x22,

        COMSCANINC = 0xC0,
        COMSCANDEC = 0xC8,

        SEGREMAP = 0xA0,

        CHARGEPUMP = 0x8D,

        EXTERNALVCC = 0x1,
        SWITCHCAPVCC = 0x2
    };
private:
    void command(int command);
    void data(const unsigned char buffer[]);
    void init();

    int mFd;
    QImage *mImage;
    unsigned char mBuffer[128*8];
};

#endif // DISPLAY_H
