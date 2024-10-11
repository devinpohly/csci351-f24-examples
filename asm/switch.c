long foo(long op, long x) {

label:
	printf("hello\n");
	goto label;

	switch (op) {
		case 0:
			return x;
		case 1:
			return x + 1;
		case 2:
			return 8 * x;
		case 3:
			x = -x;
			goto case 1;
		case 4:
			return x & 1;
		default:
			return 11;
	}
}
