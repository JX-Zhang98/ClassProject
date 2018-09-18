#ifndef PUBLICINFOINUI_H
#define PUBLICINFOINUI_H

#include "publicinfo.h"

class PublicInfoInUI:public PublicInfo
{
public:
    PublicInfoInUI();
    PublicInfoInUI(PublicInfo& info);
    void setBeChecked(bool flag);
    bool getBeChecked();
private:
    bool beChecked;
};

#endif // PUBLICINFOINUI_H
