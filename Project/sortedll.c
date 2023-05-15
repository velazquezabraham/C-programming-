// ============================================================================
// File: sortedll.c (Spring 2019)
// ============================================================================
// This program allows the user to insert, remove and display integer values
// in a linked list.  Every entry in the list is dynamically allocated, so the
// user should be able to enter as many values as desired.  The list is
// maintained in sorted ascending order, so each insertion requires the list be
// traversed to find the correct location for a new value.  Duplicate values
// are permitted.  Once the user quits the program, all allocated memory is
// released before the program ends.
// ============================================================================

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <ctype.h>
#include    "sortedll.h"


// ==== main ==================================================================
//
// ============================================================================

int     main(void)
{
    auto    int             intVal;
    auto    LNode           *headPtr = NULL;
    auto    char            buf[BUFLEN];
    auto    int             result;

    do  {
        // ask the user what they want to do
        DisplayMenu();
        printf("Please enter a selection: ");
        fgets(buf, BUFLEN, stdin);
        *buf = toupper(*buf);
        switch (*buf)
            {
            case   'A':
                // prompt the user for a value; if we get one, add it to the
                // list
                printf("Please enter an integer value to add: ");
                fgets(buf, BUFLEN, stdin);
                if (1 != sscanf(buf, "%d", &intVal))
                    {
                    puts("Error reading the integer value...");
                    }
                else
                    {
                    headPtr = AddItem(headPtr, intVal);
                    }
                break;

            case   'R':
                // if the list is empty display a message; else, get a value
                // from the user and attempt to remove it from the list
                if (NULL == headPtr)
                    {
                    puts("The list is currently empty...");
                    }
                else
                    {
                    printf("Please enter an integer value to remove: ");
                    fgets(buf, BUFLEN, stdin);
                    if (1 != sscanf(buf, "%d", &intVal))
                        {
                        puts("Error reading the integer value...");
                        }
                    else
                        {
                        headPtr = RemoveItem(headPtr, intVal);
                        }
                    }
                break;

            case   'D':
                // display the current contents of the list
                result = DisplayList(headPtr);
                printf("Currently there %s %d node%s in the list.\n"
                                    , (result != 1) ? "are" : "is"
                                    , result
                                    , (result != 1) ? "s" : "");
                break;

            case   'Q':
                // release all allocated memory and set the head pointer to
                // NULL to indicate that it is empty
                result = ReleaseMemory(headPtr);
                printf("There %s %d node%s released."
                                    , (result != 1) ? "were" : "was"
                                    , result
                                    , (result != 1) ? "s" : "");
                headPtr = NULL;
                break;

            default:
                puts("Unrecognized option; please try again.");
                break;
            }
        puts(" ");

        } while ('Q' != *buf);

    puts("Thanks for playing!  Bye!!\n");
    return  0;

}  // end of "main"



// ==== AddItem ===============================================================
//
// This function inserts an item into the list by dynamically allocating a node
// to store the value and locating the correct position for the new item so
// that the list is maintained in ascending sorted order.
//
// Input:
//      headPtr     -- a pointer to the head of the list.
//
//      newItem     -- the new item to insert into the list.
//
// Output:
//      A pointer to the (potentially new) head of the linked list.
//
// ============================================================================

LNode*  AddItem(LNode  *headPtr, int  newItem)
{
   
   
    auto	LNode	*heapNodePtr;// to dynamically allocate a node
    heapNodePtr = malloc(sizeof(LNode));//get a memory address from the heap
    if ( NULL == heapNodePtr )
        {
            puts("Error!!! memory leak...");
            return headPtr;
        }
    else
        {
            heapNodePtr->value = newItem;//store the new item in the heap node
            heapNodePtr->next = headPtr;//store the old head memory address
        }
               
    return heapNodePtr;//return the new heapNodePtr which will be the new head ptr
    

    /**
    if ( headPtr == NULL ) //if empty list
        {
            auto	LNode	*heapNodePtr;// to dynamically allocate a node
            heapNodePtr = malloc(sizeof(LNode));//get a memory address from the heap
            if ( NULL == heapNodePtr )
                {
                    puts("Error!!! memory leak...");
                }
            else
                {
                    heapNodePtr->value = newItem;//store the new item in the heap node
                    heapNodePtr->next = headPtr;//store the old head memory address
                }
               
            return heapNodePtr;//return the new head Ptr
        }
    else
        {
            if ( NULL == heapNodePtr )
                {
                    puts("Error...");
                    return headPtr;
                }
            else
                {
                    heapNodePtr->value = newItem;
                }
            while( headPtr )//not null
                {
                    if (  (headPtr->value < newItem) 
                        && (headPtr->next->value > newItem)
                        || (headPtr->value < newItem)&&(headPtr->next != NULL)) 
                        {
                            auto LNode *localPtr = headPtr ->next;//point2next
                            headPtr->next = heapNodePtr;//point to the new node
                            heapNodePtr->next = localPtr;
                            return headPtr;
                        }
                }//end of while
        }//end of if
        
        
        **/

}  // end of "AddItem"



// ==== DisplayList ===========================================================
//
// This function displays all of the values contained in the linked list to the
// standard output stream.
//
// Input:
//      headPtr     -- a pointer to the head of the linked list
//
// Output:
//      The total number of nodes displayed is returned.
//
// ============================================================================

int     DisplayList(LNode  *nodePtr)
{
    auto    int         counter = 0;

    // if the list is empty, indicate as such and return zero
    if (NULL == nodePtr)
        {
        puts("The list is currently empty...");
        return 0;
        }

    while (NULL != nodePtr)
        {
        printf("%d\n", nodePtr->value);
        nodePtr = nodePtr->next;
        counter++;
        }

    return counter;

}  // end of "DisplayList"



// ==== DisplayMenu ===========================================================
//
// This function displays the menu to stdout.
//
// Input:
//      Nothing
//
// Output:
//      Nothing
//
// ============================================================================

void    DisplayMenu(void)
{
    puts("A)dd a value");
    puts("R)emove a value");
    puts("D)isplay the list");
    puts("Q)uit");

}  // end of "DisplayMenu"



// ==== ReleaseMemory =========================================================
//
// This function traverses the linked list and releases the memory allocated
// for each individual node.
//
// Input:
//      headPtr     -- a pointer to the head of the linked list
//
// Output:
//      The total number of nodes released is returned.
//
// ============================================================================

int     ReleaseMemory(LNode  *headPtr)
{
    auto LNode	*localPtr1 = headPtr;
    auto int	counter = 0;
    while(headPtr)
    {
        free(localPtr1);
        headPtr = headPtr->next;//move to next headPtr
        localPtr1 = headPtr;
        counter++;
    }

    return counter;
}  // end of "ReleaseMemory"



// ==== RemoveItem ============================================================
//
// This function removes an item from the list.  If the target item is located
// in the list, the memory allocated for its node is released and any adjacent
// nodes are joined so as not to break the list.  If the target item is not
// found in the list, an appropriate error message is displayed to stdout.
//
// Input:
//      target      -- the item to remove
//
// Output:
//      A pointer to the head of the linked list.
//
// ============================================================================

LNode*  RemoveItem(LNode  *headPtr, int  target)
{
    auto LNode *localPtr1 = headPtr;//points to head
    if ( target == headPtr->value )
        {
            headPtr = localPtr1->next;//point headPtr to second node
            free(localPtr1);//remove the item node
            return headPtr;
        }
    //loop through nodes to look for target
    while(localPtr1)//not null
        {
            if( localPtr1->next->value == target )
                {
                    auto LNode *localPtr2 = localPtr1->next;//to point to the previous node
                    localPtr1->next = localPtr1->next->next;//to point to the next node
                    free(localPtr2);
                    return headPtr;
                }
        }
    
    puts("Target not found...");
    return headPtr;

}  // end of "RemoveItem"
