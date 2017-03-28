class Test 
{
	int foo()
	{
		while(1) {
			if (0) {
				return -1;
			}
		}
		return 0;
	}
};

int main() {
	Test test;
}
