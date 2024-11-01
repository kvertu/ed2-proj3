#ifndef BT_H
#define BT_H

/* bt.h
header file for btree programs
*/

#include <stdio.h>
#include "base.h"
#include "hist.h"

#define MAXKEYS 3
#define MINKEYS MAXKEYS/2
#define NOKEY pkeyInit("@@@", "@@@")
#define NO 0
#define YES 1

typedef struct {
    short keycount; // number of keys in page
    pkey keys[MAXKEYS]; // the actual keys
    int offsets[MAXKEYS]; // the offsets
    short child[MAXKEYS+1]; // ptrs to rrns of descendants
} BTPAGE;

#define PAGESIZE sizeof(BTPAGE)
// extern short root; // rrn of root page
// extern FILE* btfd; // file descriptor of btree file
// extern FILE* infd; // file descriptor of input file

/* prototypes */
pkey pkeyInit(char id[4], char sigla[4]);
void btclose(FILE* index);
int btopen(FILE** index, char * filename);
long btread(FILE* index, short rrn, BTPAGE *page_ptr);
long btwrite(FILE* index, short rrn, BTPAGE *page_ptr);
short create_root(FILE* index, pkey key, int offset, short left, short right);
void create_empty_tree(FILE** index, char * filename);
short create_tree(FILE** index, char * filename, pkey key, int offset);
short getpage(FILE* index);
short getroot(FILE* index);
int insert(FILE* index, short rrn, pkey key, int offset, short *promo_r_child, pkey *promo_key, int *promo_offset);
void ins_in_page(pkey key, int offset, short r_child, BTPAGE *p_page);
void pageinit(BTPAGE *p_page);
void putroot(FILE* index, short root);
int search_node(pkey key, BTPAGE *p_page, short *pos);
void split(FILE* index, pkey key, int offset, short r_child, BTPAGE *p_oldpage, pkey *promo_key, int *promo_offset, short *promo_r_child, BTPAGE *p_newpage);
void btprint(FILE* index, FILE* file, short rrn);
void btprint_aluno(FILE* index, FILE* file, short rrn, pkey key);
int btsearch_aluno(FILE* index, short rrn, pkey key);

#endif