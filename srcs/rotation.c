#include "../includes/cluster.h"

void	rotation(int num_rotations, t_axial *tmp)
{
	while (num_rotations >= 0)
	{
		int s = - tmp->q - tmp->r;
		tmp->q = - tmp->r;
		tmp->r = - s;
		num_rotations--;
	}
}

int	reinsert_hash_table(t_hash_item **rotated_hash_array[HASH_SIZE])
{
	int n = 0;
	t_hash_item** tmp_hash_array = (t_hash_item**)malloc(sizeof(t_hash_item*) * HASH_SIZE);
	t_axial	axial_tmp;
	for (size_t i = 0; i < HASH_SIZE; i++)
	{
		if (*rotated_hash_array[i] != NULL)
		{
			t_hash_item *tmp = *rotated_hash_array[i];
			while (tmp != NULL)
			{
				if (!insert(axial_tmp, tmp->hex->color, &tmp_hash_array))
					return 0;
				if (!delete(axial_tmp, rotated_hash_array))
					return 0;
				tmp = tmp->next;
				n++;
			}
		}
	}
	for (size_t i = 0; i < HASH_SIZE; i++)
		hash_array[i] = tmp_hash_array[i];
	return 1;
}

int	rotate_cluster(int num_rotations)
{
	t_hash_item** rotated_hash_array = (t_hash_item**)malloc(sizeof(t_hash_item*) * HASH_SIZE);
	int n = 0;
	t_axial	axial_tmp;
	for (size_t i = 0; i < HASH_SIZE; i++)
	{
		if (hash_array[i] != NULL)
		{
			t_hash_item *tmp = hash_array[i];
			while (tmp != NULL)
			{
				rotation(num_rotations, &axial_tmp);
				if (!insert(axial_tmp, tmp->hex->color, &rotated_hash_array))
					return 0;
				if (!delete(axial_tmp, &hash_array))
					return 0;
				tmp = tmp->next;
				n++;
			}
		}
	}
	if (!reinsert_hash_table(&rotated_hash_array))
		return 0;
	return 1;
}
