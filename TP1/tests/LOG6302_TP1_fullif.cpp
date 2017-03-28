class test 
{
	int foo()
	{
		if (0) {
			if (0) {
				return 1;
			}
			if (0) {
				return 1;
			}
		} 
		else if (1) {
			return 2;
		} 
		else {
			return 3;
		}
	}
};

int main() {
	if (0) {
		if (0) {
			return 1;
		}
	} 
	else if (1) {
		return 2;
	} 
	else {
		return 3;
	}
}
