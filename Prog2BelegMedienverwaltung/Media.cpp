//
//  Media.cpp
//  Prog2BelegMedienverwaltung
//
//  Created by Markus Klemm on 27.07.14.
//  Copyright (c) 2014 net.markusklemm. All rights reserved.
//

#include "Media.h"


Media::Media () : pLender(nullptr)
{
}

Person const* Media::lendstatus () const
{
    return pLender;
}

void Media::setLender(const Person *lender)
{
    pLender = lender;
}
