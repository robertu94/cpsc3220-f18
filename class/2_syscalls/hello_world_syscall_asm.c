int main()
{
	int ret;
	char msg[] = "hello world\n";
	asm volatile (
			"syscall"
			 : "=a"(ret)
			 : "a"(1), "D"(1), "S"(msg), "d"(14)
			 : "memory", "rcx"
	);
	return ret;
}

