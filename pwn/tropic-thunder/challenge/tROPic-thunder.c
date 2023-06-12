#include <err.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <seccomp.h>
#include <sys/mman.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

void setup_seccomp()
{
	scmp_filter_ctx ctx;
	ctx = seccomp_init(SCMP_ACT_ALLOW);
	int ret = 0;
	ret |= seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(execve), 0);
	ret |= seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(execveat), 0);
	ret |= seccomp_load(ctx);
	if (ret)
	{
		exit(1);
	}

}
int main(void)
{
	  setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
	setup_seccomp();
	puts("you'll really be in the jungle with this one!");
	
	char thunder [100];
	fgets(thunder, 0x200, stdin);
}
