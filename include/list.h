#ifndef LIST
#define LIST
/*
 *The purpose of this library is to provide a extremely versatile set of tools to create and manage linked lists of generic data.
 *
*/
typedef void * data; //Generic pointer to be casted as needed

typedef struct cell{
    data Payload ; //An array of bytes = a way to implement a generic payload (adjacent bytes)
    struct cell * Next ;
} Cell ;

//Initiates an empty list
Cell * List_init(int payload_size); //Payload size = size of the data

//Initiates an empty list with data reference and a next cell pointer
Cell * List_init_value(int payload_size, data * payload, Cell * next) ; 

//Adding elements

//Create a new cell and the end of a with given data
Cell * List_add(Cell * L, data * D) ; 

//Removing elements

//Removes the last element of a list (returns the new list)
Cell * List_remove_last(Cell * L) ;

//Removes the last element of a list (returns the new list)
Cell * List_remove_first(Cell * L) ;

//Removes the first accountered element from a list based on a given predicate on the data (returns the new list)
Cell * List_remove_element(char (*pred)(Cell *), Cell * L) ;

//Removes all encountered element from a list based on a given predicate on the data (returns the new list)
Cell * List_remove_all_element(char (*pred)(Cell *), Cell * L) ;


//Popping elements (destructive functions)

//Removes the last element of a list (returns the popped element)
Cell * List_pop_last(Cell * L) ;

//Removes the last element of a list (returns the popped element)
Cell * List_pop_first(Cell * L) ;

//Removes the first accountered element from a list based on a given predicate on the data (returns the popped element)
Cell * List_pop_element(char (*pred)(Cell *), Cell * L) ;

//Removes all encountered element from a list based on a given predicate on the data (returns the popped elements in a new list)
Cell * List_pop_all_element(char (*pred)(Cell *), Cell * L) ;


//Finding elements

//Returns the last element on a list
Cell List_last(Cell * L) ;

//Returns the first accountered element from a list based on a given predicate on the data
Cell List_find_element(char (*pred)(Cell *), Cell * L) ;

//Returns the list of all encountered element from a list based on a given predicate on the data
Cell * List_find_all_element(char (*pred)(Cell *), Cell * L) ;

//Applies a (Cell *)->data function to each data (returns the new list)
Cell * List_map(data (*map)(Cell *), Cell * L) ;

//Concatenates two list (returns the new list)
Cell * List_concatenate(Cell * A, Cell * B) ;

//Frees each element of the list (returns 0 if success, 1 otherwise)
char List_free(Cell * L) ;

//Returns 0 is the element is not the last, 1 if it is or if the given parameter is NULL
char List_isLast(Cell * L);

#endif
