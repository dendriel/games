/*
 * brief: main program used to develop and test the linked_list library
 * author: vitor.rozsa
 * date: 14/02/2013
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"


typedef struct {
	char name[32];
	int counter;
} myStruct;

st_list *test(void);
static void feed_list(int qnt, st_list *list);
static void list_dump_item(st_list_item *listItem);
static void list_dump(st_list *mlist);


int main(int argc, char *argv[])
{
	st_list *myList = NULL;
	st_list_item *item = NULL;

	myList = test();

	if (!myList) {
		fprintf(stderr, "Failed to operate with linke_list!\n");
		return -1;
	}

	// prints all elements from the list
	list_dump(myList);

	// prints the first item from the list
	item = list_get_first(myList);
	if (!item) {
		fprintf(stderr, "Failed to retrieve an item from the list");
		list_destroy(&myList);
		return -1;
	}
	list_dump_item(item);

	// prints the last item from the list
	item = list_get_last(myList);
	if (!item) {
		fprintf(stderr, "Failed to retrieve an item from the list");
		list_destroy(&myList);
		return -1;
	}
	list_dump_item(item);

	// get an item at the middle of the list
	item = list_get_item(myList, 4);
	if (!item) {
		fprintf(stderr, "Failed to retrieve an item from the list");
		list_destroy(&myList);
		return -1;
	}
	list_dump_item(item);

	// free the list elements and erase the reference
	list_destroy(&myList);

	return 0;
}

/**
 *	\b Allocate memory for the visual list.
 *	\p visual_list Reference to the visual list.
 *	\r GAME_RET_SUCCESS for correctly list creation;
 *	GAME_RET_ERROR if could not create the list.
 */
int videoSystem_visual_list_create(st_list *visual_list)
{
	visual_list = (st_list *)malloc(sizeof(st_list));
	if (!visual_list) {
		//debug("Failed to allocate memory for st_list.");
		return -1;
	}

	return 0;
}

/**
 *	\d Insert the first item in the visual list.
 *	\p visual_list Reference to the visual list that will receive the element.
 *	\p visual_elem The element to be inserted.
 */
int videoSystem_visual_list_add_first_elem(st_list *visual_list, st_visual *visual_elem)
{
	st_list_item *list_item = NULL;

	if (!visual_list || !visual_elem) {
		//debug("Null parameter received.");
		return -1;
	}

	list_item = (st_list_item *)malloc(sizeof(st_list_item));
	if (!list_item) {
		//debug("Failed to allocate memory for st_list_item.");
		return -1;
	}

	memset(list_item, 0, sizeof(st_list_item));
	list_item->data = visual_elem;

	// TODO: put in the list a verification for null values.
	list_add_first(visual_list, list_item);

	return 0;
}

/**
 *	\d Insert the first item in the visual list.
 *	\p visual_list Reference to the visual list that will receive the element.
 *	\p visual_elem The element to be inserted.
 */
int videoSystem_visual_list_add_elem(st_list *visual_list, st_visual *visual_elem)
{
	st_list_item *list_item = NULL;

	if (!visual_list || !visual_elem) {
		//debug("Null parameter received.");
		return -1;
	}

	list_item = (st_list_item *)malloc(sizeof(st_list_item));
	if (!list_item) {
		//debug("Failed to allocate memory for st_list_item.");
		return -1;
	}

	memset(list_item, 0, sizeof(st_list_item));
	list_item->data = visual_elem;

	// TODO: put in the list a verification for null values.
	list_add_next(visual_list, list_item);

	return 0;
}


/*
 * brief Initializes and fill up a new linked_list
 * return The created linked_list
 */
st_list *test(void)
{
	st_list *myList = NULL;
	st_list_item *myFirstItem = NULL;
	myStruct *data = NULL;

	myList = (st_list *)malloc(sizeof(st_list));
	if (!myList) {
		fprintf(stderr, "test() - malloc for myList failed!!\n");
		return NULL;
	}

	myFirstItem = (st_list_item *)malloc(sizeof(st_list_item));
	if (!myFirstItem) {
		list_destroy(&myList);
		fprintf(stderr, "test() - malloc for myFirstItem failed!!\n");
		return NULL;
	}

	data = (myStruct *)malloc(sizeof(myStruct));
	if (!data) {
		list_destroy(&myList);
		free(myFirstItem);
		fprintf(stderr, "test() - malloc for data failed!!\n");
		return NULL;
	}

	memset(myFirstItem, 0, sizeof(st_list_item));
	memset(data, 0 , sizeof(myStruct));

	strncpy(data->name, "first item!", sizeof(data->name));
	data->counter = 0;

	myFirstItem->data = data;

	list_add_first(myList, myFirstItem);

	// fill the list
	feed_list(10, myList);

	return myList;
}

/*
 * brief Fill up the list with default incremental values
 */
static void feed_list(int qnt, st_list *list)
{
	int i;
	char buf[32];
	st_list_item *listItem = NULL;
	myStruct *data = NULL;

	if (!list) {
		return;
	}

	for (i = 1; i < qnt; i++) {

		listItem = (st_list_item *) malloc(sizeof(st_list_item));
		if (!listItem) {
			fprintf(stderr, "feed_list - Failed to alloc memory for st_list_item!!\n");
			return;
		}

		data = (myStruct *) malloc(sizeof(myStruct));
		if (!data) {
			fprintf(stderr, "feed_list - Failed to alloc memory for data!!\n");
			free(listItem);
			return;
		}

		memset(listItem, 0, sizeof(st_list_item));
		memset(data, 0, sizeof(myStruct));

		snprintf(data->name, sizeof(data->name),"item number %d", i);
		data->counter = i*10;

		listItem->data = data;

		list_add_next(list, listItem);

		listItem = NULL;
	}
}

/*
 * brief Prints all members in the list
 */
static void list_dump(st_list *mlist)
{
	st_list_item *next = NULL;

	if ((mlist == NULL) || (mlist->first == NULL)) {
		return;
	}
	next = mlist->first->next;
	list_dump_item(mlist->first);


	while(next) {
		list_dump_item(next);
		next = next->next;
	}
}

/*
 * brief Prints the given item
 */
static void list_dump_item(st_list_item *listItem)
{
	myStruct *data = NULL;

	if (listItem->data != NULL) {
		data = (myStruct *)listItem->data;
		printf("counter: %d\nname: %s\n\n", data->counter, data->name);
	}
}

