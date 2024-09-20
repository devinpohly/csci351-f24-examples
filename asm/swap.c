int swap(long *px, long *py) {
	long t = *px;
	*px = *py;
	*py = t;
	return 19 + t * 8 + *px;
}

long math(long a, long b, long c) {
	return -b + (4 * a * c) + (2 * a);
}
