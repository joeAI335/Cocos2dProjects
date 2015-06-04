//
//  CuttingPhotos.h
//  CuttingPhotots
//
//  Created by 李正宁 on 6/2/15.
//
//

#ifndef __CuttingPhotots__CuttingPhotos__
#define __CuttingPhotots__CuttingPhotos__

#include <stdio.h>
#include "cocos2d.h"
#include <vector>

USING_NS_CC;

class CuttingPhotos: public Layer
{
    CuttingPhotos();
    virtual ~CuttingPhotos();
public:
    static CuttingPhotos* create(const char* photo, unsigned int rows = 3,
                                 unsigned int cols = 3);
protected:
    
    unsigned int _rows;
    unsigned int _cols;
    unsigned int _sliceWidth;
    unsigned int _sliceHeight;
    
    std::vector<std::vector<Sprite*>> _slices;
    
    virtual bool initWithPhoto(const char* photo, unsigned int rows,
                               unsigned int cols);
    
    bool initSlices(const char* photo);
    
    void initTouchEventListener();
    
    void move(int x, int y);
    
    
    
public:
    void restart();
    
};

#endif /* defined(__CuttingPhotots__CuttingPhotos__) */
