#ifndef BT_H
#define BT_H

/* bt.h
header file for btree programs
*/

#include <stdio.h>
#include "base.h"
#include "hist.h"

typedef struct 
{
    pkey primary;
    int offset;
} pkey_woffset;

#define MAXKEYS 3
#define MINKEYS MAXKEYS/2
#define NOKEY pkeyWOInit("@@@", "@@@", -1)
#define NO 0
#define YES 1

typedef struct {
    short keycount; // number of keys in page
    pkey_woffset key[MAXKEYS]; // the actual keys
    short child[MAXKEYS+1]; // ptrs to rrns of descendants
} BTPAGE;

#define PAGESIZE sizeof(BTPAGE)
extern short root; // rrn of root page
extern FILE* btfd; // file descriptor of btree file
extern FILE* infd; // file descriptor of input file

/* prototypes */
pkey_woffset pkeyWOInit(char id[4], char sigla[4], int offset);
void btclose(FILE* index);
int btopen(FILE** index, char * filename);
long btread(FILE* index, short rrn, BTPAGE *page_ptr);
long btwrite(FILE* index, short rrn, BTPAGE *page_ptr);
short create_root(FILE* index, pkey_woffset key, short left, short right);
short create_tree(FILE** index, char * filename, pkey_woffset key);
short getpage(FILE* index);
short getroot(FILE* index);
int insert(FILE* index, short rrn, pkey_woffset key, short *promo_r_child, pkey_woffset *promo_key);
void ins_in_page(pkey_woffset key,short r_child, BTPAGE *p_page);
void pageinit(BTPAGE *p_page);
void putroot(FILE* index, short root);
int search_node(pkey key, BTPAGE *p_page, short *pos);
void split(FILE* index, pkey_woffset key, short r_child, BTPAGE *p_oldpage, pkey_woffset *promo_key, short *promo_r_child, BTPAGE *p_newpage);

#endif