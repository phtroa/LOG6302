
class Test
{
	public:
		Test(int x);
		Test& operator++(int);
	private:
		int counter;
};

int main() {
	Test t(0);
	t++;
}
