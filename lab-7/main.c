#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define resource_count 3 //no of resources
#define process_count 5 //no of processoses
int i = 0;
int j = 0;
pthread_mutex_t mutex;
int init[resource_count];
int avail [resource_count];
int allocmatrix [process_count][resource_count];
int MaxMatrix [process_count][resource_count];
int NeedMatrix [process_count][resource_count];

void *procs(void* procsID) {
	int pID = *(int*)procsID;
	int c=0;
	while(c<3) {
		sleep(1);
		int request[resource_count];
		pthread_mutex_lock(&mutex);

		for(i = 0; i < resource_count; i++) {
			if(NeedMatrix[pID][i] != 0) {
				request[i] = rand() % NeedMatrix[pID][i];
			} else {
				request[i] = 0;
			}
		}

		printReqOrRelVector(request);

		getRes(pID,request);

		pthread_mutex_unlock(&mutex);

		sleep(1);
		int releaseVector[resource_count];
		pthread_mutex_lock(&mutex);

		for(i = 0; i < resource_count; i++) {
			if(allocmatrix[pID][i] != 0) {
				releaseVector[i] = rand() % allocmatrix[pID][i];
			} else {
				releaseVector[i] = 0;
			}
		}



		printReqOrRelVector(releaseVector);
		relRes(pID,releaseVector);
		pthread_mutex_unlock(&mutex);

		c++;
	}
}

int getRes(int pID,int request[]) {
	if (casegreaterthanneed(pID,request) == -1) {
		printf("Number of requested Resources is more than Needed.\n");
		return -1;
	}
	printf("Resources are being allocated...\n");

	if(enoughtoalloccase(request) == -1) {
		printf("Not enough Resources.\n");
		return -1;
	}


	for (i = 0; i < resource_count; ++i) {
		NeedMatrix[pID][i] -= request[i];
		allocmatrix[pID][i] += request[i];
		avail[i] -= request[i];
	}
	printf("Checking is the state is safe...\n");


	if (safemodecase() == 0) {
		printf("\nx========================x|Safe Mode. Resources Allocated|x=========================x\n");
		

		exit(1);
		return 0;
	} else {
		printf("\nx=====================x|State is not safe.|x=====================x\n");
		exit(1);

		return -1;
	}
}

int relRes(int pID,int releaseVector[]) {

	if(caseengoughtorel(pID,releaseVector) == -1) {
		printf("Not enought Resources.\n");
		return -1;
	}
	for(i = 0; i < resource_count; i++) {
		allocmatrix[pID][i] -= releaseVector[i];
		NeedMatrix[pID][i] += releaseVector[i];
		avail[i] += releaseVector[i];
	}
	printf("Released.\nMetrix Available:\n");
	showavail();
	printf("Metrix Allocated:\n");
	Showalloc();
	printf("Metrix Need:\n");
	ShowNeed();
	return 0;
}


int caseengoughtorel(int pID,int releaseVector[]) {
	for (i = 0; i < resource_count; ++i) {
		if (releaseVector[i] <= allocmatrix[pID][i]) {
			continue;
		} else {
			return -1;
		}
	}
	return 0;
}

int casegreaterthanneed(int pID,int request[]) {

	for (i = 0; i < resource_count; ++i) {
		if (request[i] <= NeedMatrix[pID][i]) {
			continue;
		} else {
			return -1;
		}
	}
	return 0;
}

int enoughtoalloccase(int request[]) {

	for (i = 0; i < resource_count; ++i) {
		if (request[i] <= avail[i]) {
			continue;
		} else {
			return -1;
		}
	}
	return 0;
}

void ShowNeed() {
	for (i = 0; i < process_count; ++i) {
		printf("{ ");
		for (j = 0; j < resource_count; ++j) {
			printf("%d, ", NeedMatrix[i][j]);
		}
		printf("}\n");
	}
	return;
}

void Showalloc() {
	for (i = 0; i < process_count; ++i) {
		printf("{ ");
		for (j = 0; j < resource_count; ++j) {
			printf("%d, ", allocmatrix[i][j]);
		}
		printf("}\n");
	}
	return;
}

void showavail() {
	for (i = 0; i < resource_count; ++i) {
		printf("%d, ",avail[i]);
	}
	printf("\n");
	return;
}


void printReqOrRelVector(int vec[]) {
	for (i = 0; i < resource_count; ++i) {
		printf("%d, ",vec[i]);
	}
	printf("\n");
	return;
}


int safemodecase() {
	int finish[process_count] = {0};
	int work[resource_count];

	for(i = 0; i < resource_count; i++) {
		work[i] = avail[i];
	}

	int k;
	for(i = 0; i < process_count; i++) {
		if (finish[i] == 0) {
			for(j = 0; j < resource_count; j++) {
				if(NeedMatrix[i][j] <= work[j]) {

					if(j==resource_count-1){
						finish[i] = 1;
						for (k = 0; k < resource_count; ++k) {
							work[k] += allocmatrix[i][k];

						}
						i = -1;
						break;
					} else {
						continue;
					}
				} else {
					break;
				}
			}
		} else {
			continue;
		}
	}

	for(i = 0; i < process_count; i++) {
		if (finish[i] == 0) {

			return -1;
		} else {
			continue;
		}
	}

	return 0;
}

int main() {
	printf("Enter available VECTOR\n");

	for(i = 0; i < resource_count; i++) {

		scanf("%d",&init[i]);
		avail[i] = init[i];
	}
	printf("Enter Allocation Matrix\n");
	for(i = 0; i < process_count; i++) {

		for(j = 0; j< resource_count; j++) {

			scanf("%d",&allocmatrix [i][j]);

		}
	}
	printf("Enter MAX Matrix\n");
	for(i = 0; i < process_count; i++) {

		for(j = 0; j< resource_count; j++) {

			scanf("%d",&MaxMatrix [i][j]);

		}
	}

	for (i = 0; i < process_count; ++i) {
		for (j = 0; j < resource_count; ++j) {
			NeedMatrix[i][j] = MaxMatrix[i][j] - allocmatrix[i][j];
		}
	}

	printf("Available Vector:\n");
	showavail();

	printf("Allocation Matrix:\n");
	Showalloc();

	printf("Need Matrix:\n");
	ShowNeed();

	pthread_mutex_init(&mutex,NULL);
	pthread_attr_t attrDefault;
	pthread_attr_init(&attrDefault);
	pthread_t *tid = malloc(sizeof(pthread_t) * process_count);

	int *pid = malloc(sizeof(int) * process_count); 

	for(i = 0; i < process_count; i++) {
		*(pid + i) = i;
		pthread_create((tid+i), &attrDefault, procs, (pid+i));
	}

	for(i = 0; i < process_count; i++) {
		pthread_join(*(tid+i),NULL);
	}
	return 0;
}