//
//  CuttingPhotos.cpp
//  CuttingPhotots
//
//  Created by 李正宁 on 6/2/15.
//
//

#include "CuttingPhotos.h"

CuttingPhotos::CuttingPhotos():
_rows(3),
_cols(3)
{
    
}

CuttingPhotos::~CuttingPhotos()
{
    this->removeAllChildren();
}

CuttingPhotos* CuttingPhotos::create(const char *photo, unsigned int rows,
                                     unsigned int cols)
{
    CuttingPhotos *cp = new CuttingPhotos();
    if (cp && cp->initWithPhoto(photo, rows, cols)) {
        cp->autorelease();
        return cp;
    }
    
    CC_SAFE_DELETE(cp);
    
    return nullptr;
}

bool CuttingPhotos::initWithPhoto(const char *photo, unsigned int rows, unsigned int cols)
{
    bool result = false;
    
    if (Layer::init()) {
        _rows = rows;
        _cols = cols;
        
        if (initSlices(photo)) {
            initTouchEventListener();
            
            restart();
            
            result = true;
        } else {
            result = false;
        }
    } else {
        result = false;
    }
    
    return result;
}

bool CuttingPhotos::initSlices(const char *photo)
{
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(photo);
    
    if (texture == nullptr) {
        return false;
    }
    
    for (int w = 0 ; w < _rows; ++w) {
        std::vector<Sprite*> rows;
        for (int h = 0; h < _cols; ++h) {
            rows.push_back(nullptr);
        }
        _slices.push_back(rows);
    }
    
    auto size = texture->getContentSize();
    _sliceWidth = size.width / _rows;
    _sliceHeight = size.height / _cols;
    
    this->setContentSize(size);
    
    
    auto endSlice = Sprite::createWithTexture(texture, Rect(_sliceWidth * (_rows - 1), _sliceHeight * (_cols - 1),
                                                            _sliceWidth, _sliceHeight));
    endSlice->setAnchorPoint(Vec2(0, 0));
    endSlice->setPosition(_sliceWidth *(_rows - 1), 0);
    endSlice->setOpacity(100);
    this->addChild(endSlice);
    
    _slices[_rows - 1][_cols - 1] = nullptr;
    
    
    
    for (int w = 0 ; w < _rows; w++) {
        for (int h = 0; h < _cols; h++) {
            if (w == _rows - 1 && h == _cols - 1) {
                break;
            }
            Sprite *slice = Sprite::createWithTexture(texture, Rect(_sliceWidth * w, _sliceHeight * h, _sliceWidth, _sliceHeight));
            
            slice->setAnchorPoint(Vec2(0, 0));
            slice->setPosition(w * _sliceWidth, size.height - (h+1) * _sliceHeight);
            this->addChild(slice);
            
            _slices[w][h] = slice;
        }
       
    }

    return true;
}


void CuttingPhotos::initTouchEventListener()
{
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [&](Touch *touch, Event *event){
        Point locationInNode = this->convertToNodeSpace(touch->getLocation());
        Size s = this->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode)) {
            return true;
        } else {
            return false;
        }
    };
    
    listener->onTouchEnded = [&](Touch *touch, Event *event){
        Point locationInNode = this->convertToNodeSpace(touch->getLocation());
        
        int x = static_cast<int>(floor(locationInNode.x / this->_sliceWidth));
        int y = static_cast<int>(floor(locationInNode.y / this->_sliceHeight));
        
        this->move(x, y);
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}


void CuttingPhotos::move(int x, int y)
{
    y = _cols - y - 1;
    auto slice = _slices[x][y];
    
    if (slice == nullptr) {
        return;
    }
    
    //test whether there are still empty blocks or not
    bool isFind = false;
    Point targetPos;
    
    if (y < _cols - 1 && _slices[x][y + 1] == nullptr) {
        targetPos.x = x;
        targetPos.y = y + 1;
        isFind = true;
    } else if (y > 0 && _slices[x][y - 1] == nullptr){
        targetPos.x = x;
        targetPos.y = y - 1;
        isFind = true;
    } else if (x < _rows - 1 && _slices[x + 1][y] == nullptr) {
        targetPos.x = x + 1;
        targetPos.y = y;
        isFind = true;
    } else if (x > 0 && _slices[x - 1][y] == nullptr) {
        targetPos.x = x - 1;
        targetPos.y = y;
        isFind = true;
    }
    
    if (isFind == false) {
        return;
    }
    
    slice->runAction(MoveTo::create(0.25f, Vec2(targetPos.x * _sliceWidth,
                                                _sliceHeight * _cols - (targetPos.y + 1) * _sliceHeight)));
    
    _slices[targetPos.x][targetPos.y] = slice;
    _slices[x][y] = nullptr;
}

void CuttingPhotos::restart()
{
    //Just fetch all the blocks
    Vector<Sprite*> list;
    
    for (int w = 0; w < _rows; ++w) {
        for (int h = 0; h < _cols; ++h) {
            auto slice = _slices[w][h];
            if (slice != nullptr) {
                list.pushBack(slice);
            }
        }
    }
    
    for (int w = 0; w < _rows; ++w) {
        for (int h = 0; h < _cols; ++h) {
            if (w == _rows - 1 && h == _cols - 1) {
                //eliminate the right bottom one
                _slices[w][h] = nullptr;
                break;
            }
            
            auto length = list.size();
            auto value = static_cast<int>(CCRANDOM_0_1() * length);
            
            auto slice = list.at(value);
            list.eraseObject(slice);
            
            _slices[w][h] = slice;
            
            slice->setPosition(w * _sliceWidth, _sliceHeight * _cols - (h + 1) *
                               _sliceHeight );
        }
    }
}