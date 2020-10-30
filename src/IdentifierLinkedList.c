//
// Created by Griffin Prechter on 10/30/20.
//

#include <string.h>
#include "IdentifierLinkedList.h"

VALUE_TYPE getTypeForIDENTIFIER(LinkedListPtr lnk, IDENTIFIER identifier) {
    DoubleLinkPtr ptr = lnk->head;
    while (ptr != NULL) {
        IDENTIFIER * elem = (IDENTIFIER *) (ptr->elem);
        if (strcmp(elem->id, identifier.id) == 0) {
            return elem->type;
        }
        ptr = ptr->next;
    }
    return VALUE_TYPE_unknown;
}