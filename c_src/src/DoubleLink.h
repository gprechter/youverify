//
//  DoubleLink.h
//  
//
//  Created by Griffin Prechter on 10/8/20.
//

#ifndef DoubleLink_h
#define DoubleLink_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct dlink DoubleLink;
typedef struct dlink *DoubleLinkPtr;

struct dlink {
    void *elem;
    DoubleLinkPtr next;
    DoubleLinkPtr prev;
};

void freeLink(DoubleLinkPtr link);
DoubleLinkPtr newLink(void *elem);

#endif /* DoubleLink_h */
