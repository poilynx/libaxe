#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum state_en
{
	AVAIL,
	EMPTY,
	SUSPEND,
};

struct freenode_st
{
	uint32_t bufnode_idx;
	uint16_t offset;
};

struct bufnode_st
{
	size_t used_size;
	size_t free_size;
	void* buffer;
	struct bufnode_st *pre;
	struct bufnode_st *next;
	enum state_en state;
};

struct ax_block_pool_st {
	struct free_st** free_tab;
	struct bufnode_st** ptr_tab;
	struct bufnode_st* avai_lst;
	struct bufnode_st* susp_lst;
	size_t free_tab_siz;
	size_t ptr_tab_siz;
	size_t ptr_tab_use;
	size_t block_siz;
};

typedef struct ax_block_pool_st ax_block_pool;

static ax_block_pool* ax_block_pool_make()
{
	ax_block_pool* pool = malloc(sizeof(ax_block_pool));
	if(pool == NULL)
		return NULL;
	pool->ptr_tab = NULL;
	pool->ptr_tab_siz = 0;
	pool->ptr_tab_use = 0;

	pool->avai_lst = NULL;
	pool->susp_lst = NULL;

	pool->block_siz = 0;
	return pool;
}

static struct bufnode_st* prepare_bufnode(ax_block_pool* pool)
{
	return NULL;
}

static void adjuest_bufnode(ax_block_pool* pool)
{
	
}

void* ax_block_alloc(ax_block_pool* pool)
{
	void* block = NULL;
	return block;
}


void ax_block_free(ax_block_pool* pool, void* block)
{

}


int main()
{
	
}
