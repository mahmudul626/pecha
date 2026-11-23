#include "../include/main.h"

static int get_dev_name(char dev_name[50])
{
	struct dirent *a;
	DIR *dir = opendir("/sys/class/net");
	if(dir == NULL)
		return 1;

	char path[1024] = "/sys/class/net/";

	while((a = readdir(dir)) != NULL) {
		char buffer[50];
		snprintf(path, sizeof(path), "/sys/class/net/%s/operstate", a->d_name);
		FILE *file = fopen(path, "r");
		if(file) {
			fgets(buffer, sizeof(buffer), file);
			buffer[strcspn(buffer, "\n")] = '\0';

			if(strcmp(buffer, "up") == 0) {
				strcpy(dev_name, a->d_name);
			}
			fclose(file);
		}
	}

	closedir(dir);
	return 0;
}

void get_net(int *d_mb, int *u_mb)
{
	char buffer[2024];
	char dev_name[50];

	int ret = get_dev_name(dev_name);
	if(ret == 1) {
		printf("Internet not connected\n");
		return;
	}

	int len = strlen(dev_name);

	FILE *file = fopen("/proc/net/dev", "r");
        if(!file)
                return;

	while(fgets(buffer, sizeof(buffer), file) != NULL) {
		if(strncmp(buffer+2, dev_name, len) == 0) {
			int d = 0, u = 0;
			if(sscanf(buffer+8, "%d %*d %*d %*d %*d %*d %*d %*d %d", &d, &u) == 2) {
				*d_mb = d / (1024 * 1024);
				*u_mb = u / (1024 * 1024);
			}
		}
	}

	fclose(file);
}
