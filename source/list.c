#include "../include/list.h"
#include <stdlib.h>

Cell * List_init_value(int payload_size, data * payload, Cell * next){
    Cell * C = List_init(payload_size) ; 
    C -> Payload = payload ;
    C -> Next = next ;
    return C ; 
}

Cell * List_init(int payload_size){
    data PL = malloc(sizeof(char)*payload_size);
    Cell * next = NULL;
    Cell * R = malloc(sizeof(void *));
    R->Payload = PL;
    R->Next = next;
    return R;
}

Cell * List_pop_last(Cell * L){
    char isBeforeLast(Cell * C){
        return ( C == NULL || List_isLast(C->Next) );
    }
    
    Cell * BL = List_find_all_element(isBeforeLast, L);
    return (BL->Next);
}

char List_isLast(Cell * c){
	return c != NULL && (c->Next == NULL) ;
}

Cell * List_remove_last(Cell * L){
    Cell * Last = List_pop_last(L) ; 
    if(Last == NULL)
        return NULL ; 
    else{
        free(Last) ; 
        return L ;
    } 
}

Cell * List_add(Cell * L, data * D){
    if(L == NULL)
        return List_init_value(sizeof(D), D, NULL) ; 
    else{
        Cell * Last = List_pop_last(L) ;
        Last -> Next = List_init_value(sizeof(D), D, NULL) ; 
        return L ; 
    }
}

Cell * List_map(data (*map)(Cell *), Cell * L){
    if(L == NULL)
        return NULL ;
    else{
        Cell * new_cell = List_init(sizeof(L->Payload)) ;
        new_cell->Payload = map(L);
        new_cell->Next = List_map(map, L->Next);
        return new_cell;
    }
}

Cell * List_find_all_element(char (*pred)(Cell *), Cell * L){
       
    if( L == NULL )
        return NULL ; 
        
    if(pred(L)){
        Cell * new_cell = List_init(sizeof(L->Payload)) ;
        new_cell->Payload = L->Payload; //Copy reference to data !
        new_cell->Next = List_find_all_element(pred, L->Next); 
        return new_cell;
    }else{
        return List_find_all_element(pred, L->Next); 
    }
}
