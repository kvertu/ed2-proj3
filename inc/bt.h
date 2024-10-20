/* bt.h
header file for btree programs
*/

#include <stdio.h>
#include "base.h"
#include "hist.h"

struct pkey_withoffset
{
    pkey primary;
    int offset;
};

#define MAXKEYS 4
#define MINKEYS MAXKEYS/2
#define NOKEY {{"@@@", "@@@"}, -1}
#define NO 0
#define YES 1

typedef struct {
    short keycount; // number of keys in page
    struct pkey_withoffset key[MAXKEYS]; // the actual keys
    short child[MAXKEYS+1]; // ptrs to rrns of descendants
} BTPAGE;

#define PAGESIZE sizeof(BTPAGE)
extern short root; // rrn of root page
extern FILE* btfd; // file descriptor of btree file
extern FILE* infd; // file descriptor of input file

/* prototypes */
void btclose(FILE* index);
int btopen(FILE** index);
long btread(FILE* index, short rrn, BTPAGE *page_ptr);
long btwrite(FILE* index, short rrn, BTPAGE *page_ptr);
short create_root(char key, short left, short right);
short create_tree(FILE** index);
short getpage(FILE* index);
short getroot(FILE* index);
int insert(short rrn, char key, short *promo_r_child, char *promo_key);
void ins_in_page(char key,short r_child, BTPAGE *p_page);
void pageinit(BTPAGE *p_page);
void putroot(FILE* index, short root);
int search_node(char key, BTPAGE *p_page, short *pos);
void split(char key, short r_child, BTPAGE *p_oldpage, char *promo_key, short *promo_r_child, BTPAGE *p_newpage);