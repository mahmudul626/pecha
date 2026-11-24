#include "../include/main.h"
#define MAX_DEV 32

static int get_dev_name(char **dev_name, size_t *size)
{
	struct dirent *a;
	DIR *dir = opendir("/sys/class/net");
	if(!dir)
		return -1;

	size_t count = 0;

	while((a = readdir(dir)) != NULL && count < MAX_DEV) {
		if(strcmp(a->d_name, ".") == 0 || strcmp(a->d_name, "..") == 0) {
			continue;
		}

		if(strcmp(a->d_name, "lo") == 0) {
			continue;
		}

		dev_name[count] = strdup(a->d_name);
		if(!dev_name[count])
			break;
		count++;
	}

	closedir(dir);
	*size = count;
	return 0;
}

void get_net(int *d_mb, int *u_mb)
{
	if(!d_mb || !u_mb)
		return;
	*d_mb = 0;
	*u_mb = 0;

	FILE *file = fopen("/proc/net/dev", "r");
        if(!file)
                return;
	
	char *dev_name[MAX_DEV];
	size_t count = 0;
	int ret = get_dev_name(dev_name, &count);
	if(ret != 0) {
		fclose(file);
		return;
	}

	char buffer[2048];

	while(fgets(buffer, sizeof(buffer), file) != NULL) {
		char *p = buffer;
		while(*p && isspace((unsigned char)*p)) {
			*p++;
		}

		for(int i = 0; i < count; i++) {
			size_t len = strlen(dev_name[i]);

			if(strncmp(p, dev_name[i], len) == 0) {
				unsigned long long d = 0, u = 0;

				if(sscanf(p+len+1, "%llu %*u %*u %*u %*u %*u %*u %*u %llu", &d, &u) == 2) {
					*d_mb += d / (1024ULL * 1024ULL);
					*u_mb += u / (1024ULL * 1024ULL);
				}
			}
		}
	}
	for(int i = 0; i < count; i++) {
		free(dev_name[i]);
	}
	fclose(file);
}
