#ifndef __IOBJECT_H__
#define __IOBJECT_H__

class IObject
{
private:
public:
    virtual ~IObject() {}
    virtual char renderer() = 0;
    virtual int getPosition() = 0;
    virtual void setPosition(int position) = 0;
};

#endif // __IOBJECT_H__