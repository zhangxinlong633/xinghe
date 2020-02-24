#include "../include/public.h"

#define PHONE_LIST_BLOCK_NAME 64

struct phone_list {
	uint32_t node_cap;
	khash_t(PHONE_LIST_BLOCK_NAME) *header;
};

struct phone_entry {
	uint64_t block_id;
	uint32_t node_len;
	khiter_t entry;
	uint32_t node[0];
};

struct phone_list *phone_list_create(uint32_t node_cap)
{
	struct phone_list *list = NULL;
	list = malloc(sizeof(struct phone_list));
	if (list == NULL) {
		goto exit;
	}

	list->node_cap = node_cap;
	list->header = kh_init(PHONE_LIST_BLOCK_NAME);

exit:
	return ret;
}

void phone_list_destroy(struct phone_list *phone_list)
{
	free(phone_list);
}

int phone_list_put(struct phone_list *phone_list, uint64_t block_id, uint32_t *node, uint32_t node_len)
{
	int ret = EINVAL;
	uint8_t free_flag = 0;
	uint32_t node_count = 0; 
	struct phone_entry *entry = NULL;

	if (node_len > 0) {
		node_count = min(phone_list->node_cap, node_len);
	} else {
		node_count = phone_list->node_cap;
	}

	entry = malloc(sizeof(struct phone_entry) + sizeof(uint32_t) * node_count);
	if (entry == NULL) {
		goto exit;
	}

	entry->block_id = block_id;
	entry->node_len = node_count;
	memcpy(entry->node, node, sizeof(uint32_t) * node_count);
	entry->entry = kh_put(PHONE_LIST_BLOCK_NAME, list->header, block_id, &ret);
	if (ret != 0) {
		free_flag = 1;
		goto exit;
	}

    kh_value(list->header, entry->entry) = entry;
		
	ret = 0;


exit:

	if (free_flag) {
		free(entry);
	}

	return ret;
}

int phone_list_get(struct phone_list *phone_list, uint64_t block_id, uint32_t *node, uint32_t node_len, uint32_t *ret_node_len)
{
	int ret = EINVAL;
	uint32_t node_count = 0;
	khiter_t k = kh_get(PHONE_LIST_BLOCK_NAME, list->header, block_id);

	if (node_len == 0) {
		ret = ENOENT;
		goto exit;
	}

	struct phone_entry *entry = kh_value(list->header, k);
	if (entry == NULL) {
		goto exit;
	}

	node_count = min(phone_list->node_cap, node_len);
	
	memcpy(node, entry->node, node_count);
	*ret_node_len = node_count;
	ret = 0;

exit:
	return ret;
}

int phone_list_save(char *path, int path_len)
{
	return 0;
}

int phone_list_load(char *path, int path_len)
{
	return 0;
}


int phone_list_init()
{
	return 0;
}

int phone_list_fini()
{

}

