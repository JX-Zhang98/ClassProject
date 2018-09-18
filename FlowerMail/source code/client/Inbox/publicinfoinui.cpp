#include "publicinfoinui.h"

PublicInfoInUI::PublicInfoInUI():PublicInfo ("","","")
{
    beChecked=false;
}

PublicInfoInUI::PublicInfoInUI(PublicInfo & info):PublicInfo(info)
{
    beChecked=false;
}

void PublicInfoInUI::setBeChecked(bool flag)
{
    beChecked=flag;
}

bool PublicInfoInUI::getBeChecked()
{
    return beChecked;
}
