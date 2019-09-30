#define _GNU_SOURCE
#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include "syscall.h"
#include "libc.h"

#define GET_ARG_MACRO(type) ({ \
		va_list ap; \
		va_start(ap, cmd); \
		type __arg = va_arg(ap, type); \
		va_end(ap); \
		__arg; \
		})

int fcntl(int fd, int cmd, ...)
{
	switch (cmd) {
	case F_GETFD:
	case F_GETFL:
	case F_GETSIG:
	case F_GETLEASE:
	case F_GET_SEALS:
	case F_GETPIPE_SZ:
		return syscall(SYS_fcntl, fd, cmd);
	case F_GETOWN: {
		struct f_owner_ex ex;
		int ret = __syscall(SYS_fcntl, fd, F_GETOWN_EX, &ex);
		if (ret == -EINVAL) return __syscall(SYS_fcntl, fd, cmd);
		if (ret) return __syscall_ret(ret);
		return ex.type == F_OWNER_PGRP ? -ex.pid : ex.pid;
	}
	case F_SETFL: {
		int arg = GET_ARG_MACRO(int);
		arg |= O_LARGEFILE;
		return syscall(SYS_fcntl, fd, cmd, arg);
	}
	case F_DUPFD_CLOEXEC: {
		int ret;
		int arg = GET_ARG_MACRO(int);
		ret = __syscall(SYS_fcntl, fd, F_DUPFD_CLOEXEC, arg);
		if (ret != -EINVAL) {
			if (ret >= 0)
				__syscall(SYS_fcntl, ret, F_SETFD, FD_CLOEXEC);
			return __syscall_ret(ret);
		}
		ret = __syscall(SYS_fcntl, fd, F_DUPFD_CLOEXEC, 0);
		if (ret != -EINVAL) {
			if (ret >= 0) __syscall(SYS_close, ret);
			return __syscall_ret(-EINVAL);
		}
		ret = __syscall(SYS_fcntl, fd, F_DUPFD, arg);
		if (ret >= 0) __syscall(SYS_fcntl, ret, F_SETFD, FD_CLOEXEC);
		return __syscall_ret(ret);
	}
	case F_DUPFD:
	case F_SETFD:
	case F_SETSIG:
	case F_SETLEASE:
	case F_ADD_SEALS:
	case F_SETOWN:
	case F_SETPIPE_SZ:
	case F_NOTIFY: {
		int arg = GET_ARG_MACRO(int);
		return syscall(SYS_fcntl, fd, cmd, arg);
	}
	case F_GETLK:
	case F_SETLK:
	case F_OFD_SETLK:
	case F_OFD_GETLK: {
		struct flock * arg = GET_ARG_MACRO(struct flock *);
		return syscall(SYS_fcntl, fd, cmd, arg);
	}
	case F_OFD_SETLKW:
	case F_SETLKW: {
		struct flock * arg = GET_ARG_MACRO(struct flock *);
		return syscall_cp(SYS_fcntl, fd, cmd, arg);
	}
	case F_GETOWN_EX:
	case F_SETOWN_EX: {
		struct f_owner_ex * arg = GET_ARG_MACRO(struct f_owner_ex *);
		return syscall(SYS_fcntl, fd, cmd, arg);
	}
	default: {
		unsigned long arg = GET_ARG_MACRO(unsigned long);
		return syscall(SYS_fcntl, fd, cmd, arg);
	}
	}
}
