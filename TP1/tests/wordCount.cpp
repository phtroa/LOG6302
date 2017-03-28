#define YES 1
#define NO 0

class Test {
	public:

int wordcount()
{
	int c, nl, nw, nc, inword;
	inword = NO;
	nl = 0;
	nw = 0;
	nc = 0;
	c = 0;
	while( c != 0) {
		nc = nc + 1;
		if ( c == '\n')
			nl = nl + 1;
		if ( c == ' ' || c == '\n' || c == '\t')
			inword = NO;
		else if (inword == NO) {
			inword = YES;
			nw = nw + 1;
		}
		c = 0;
	}
	return nw;
}

};

int main () {
	Test test;
}
