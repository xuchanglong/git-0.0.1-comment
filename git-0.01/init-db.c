/*
 * GIT - The information manager from hell
 *
 * Copyright (C) Linus Torvalds, 2005
 */

/**
 * 该指令的作用：检查数据库存在，若不存在则创建。
*/
#include "cache.h"

int main(int argc, char **argv)
{
	// 从系统环境变量中获取 DB_ENVIRONMENT 对应的路径。
	char *sha1_dir = getenv(DB_ENVIRONMENT), *path;
	int len, i, fd;
	// 创建目录 .dircache 。
	if (mkdir(".dircache", 0700) < 0)
	{
		perror("unable to create .dircache");
		exit(1);
	}

	/*
	 * If you want to, you can share the DB area with any number of branches.
	 * That has advantages: you can save space by sharing all the SHA1 objects.
	 * On the other hand, it might just make lookup slower and messier. You
	 * be the judge.
	 */
	// 用户可以将该对象数据库与其他仓库进行共享，优点是可以共享所有的 SHA1 对象，
	// 缺点是操作更慢。
	sha1_dir = getenv(DB_ENVIRONMENT);
	if (sha1_dir)
	{
		struct stat st;
		if (!(stat(sha1_dir, &st) < 0) && S_ISDIR(st.st_mode))
			return;
		fprintf(stderr, "DB_ENVIRONMENT set to bad directory %s: ", sha1_dir);
	}

	/*
	 * The default case is to have a DB per managed directory. 
	 */
	// 默认的方式是每个仓库中都有一个 DB 。
	sha1_dir = DEFAULT_DB_ENVIRONMENT;
	fprintf(stderr, "defaulting to private storage area\n");
	len = strlen(sha1_dir);
	// 创建目录 DEFAULT_DB_ENVIRONMENT 。
	if (mkdir(sha1_dir, 0700) < 0)
	{
		if (errno != EEXIST)
		{
			perror(sha1_dir);
			exit(1);
		}
	}
	path = malloc(len + 40);
	memcpy(path, sha1_dir, len);
	// 创建子目录。
	for (i = 0; i < 256; i++)
	{
		sprintf(path + len, "/%02x", i);
		if (mkdir(path, 0700) < 0)
		{
			if (errno != EEXIST)
			{
				perror(path);
				exit(1);
			}
		}
	}
	return 0;
}
