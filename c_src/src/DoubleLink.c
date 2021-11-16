//
//  DoubleLink.c
//  
//
//  Created by Griffin Prechter on 10/8/20.
//

#include "DoubleLink.h"

void freeLink(DoubleLinkPtr link) {
    if (link == NULL) return;
    free(link);
}

DoubleLinkPtr newLink(void * elem){
    DoubleLinkPtr link = (DoubleLinkPtr) malloc(sizeof(DoubleLink));
    link->elem = elem;
    link->next = NULL;
    link->prev = NULL;
    return link;
}
