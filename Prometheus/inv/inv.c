#include <stdio.h>
#include <stdlib.h>

struct Data;

struct Data *init_data(FILE *in);
void clean_data(struct Data *data);

int get_inv(struct Data *data, int uid1, int uid2);

int main(int argc, char **argv)
{
	if (argc != 4) {
		return -1;
	}
	
	FILE *in = fopen(argv[1], "r");
	
	if (in == NULL) {
		return -1;
	}
	
	int uid1, uid2;
	
	if (sscanf(argv[2], "%d", &uid1) != 1 
	 || sscanf(argv[3], "%d", &uid2) != 1) {
		
		return -1;
	}

	struct Data *data = init_data(in);	

	printf("Inversions number: %d\n", get_inv(data, uid1, uid2));

	clean_data(data);
	fclose(in);
	return 0;
}

// hidden impl details

struct Data {
	int  n_users;
	int  n_movies;
	int *data;
};

int inv(int *arr, int *hlp, int l, int h);
int split_inv(int *arr, int *hlp, int l, int m, int h);

int get_inv(struct Data *data, int uid1, int uid2)
{
	int *arr = (int *) malloc(sizeof(int) * data->n_movies);
	int *hlp = (int *) malloc(sizeof(int) * data->n_movies);
	
	for (int i = 0; i < data->n_movies; i++) {
		int id = data->data[uid1 * data->n_movies + i];
		int vl = data->data[uid2 * data->n_movies + i];
		arr[id] = vl;
	}
	
	int inv_cnt = inv(arr, hlp, 0, data->n_movies);
	
	free(arr);
	free(hlp);
	return inv_cnt;
}

int inv(int *arr, int *hlp, int l, int h)
{
	if (h - l <= 1) {
		return 0;
	}
	
	int m = l + (h - l) / 2;
	
	int l_inv = inv(arr, hlp, l, m);
	int r_inv = inv(arr, hlp, m, h);
	int s_inv = split_inv(arr, hlp, l, m, h);
	
	return l_inv + r_inv + s_inv;
}

int split_inv(int *arr, int *hlp, int l, int m, int h)
{
	int inv = 0;
	int idl = l;
	int idr = m;
	
	for (int k = l; k < h; k++) {
		if (idl >= m) {
			hlp[k] = arr[idr++];
			continue;	
		}
		if (idr >= h) {
			hlp[k] = arr[idl++];
			continue;
		}
		if (arr[idr] < arr[idl]) {
			hlp[k] = arr[idr++];
			inv += m - idl;
		} else {
			hlp[k] = arr[idl++];
		}
	}
	for (int k = l; k < h; k++) {
		arr[k] = hlp[k];
	}
	return inv;
}

struct Data *init_data(FILE *in)
{
	struct Data *data = (struct Data *) malloc(sizeof(struct Data));
	
	fscanf(in, "%d %d", &data->n_users, &data->n_movies);
	
	data->data = (int *) malloc(sizeof(int) * data->n_users * data->n_movies);
	
	for (int i = 0; i < data->n_users; i++) {
		int user_id;
		fscanf(in, "%d", &user_id);
		user_id--; // make zero indexed user
		
		for (int j = 0; j < data->n_movies; j++) {
			int movie_pos;
			fscanf(in, "%d", &movie_pos);
			movie_pos--; // make zero indexed rating
			
			data->data[data->n_movies * user_id + j] = movie_pos;		
		}
	}
	return data;
}

void clean_data(struct Data *data)
{
	free(data->data);
	free(data);	
}
