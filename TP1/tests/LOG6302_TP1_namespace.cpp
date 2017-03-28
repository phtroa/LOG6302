
namespace first
{
	int var = 5;
	namespace test
	{
		class foo {
			public:
				int x;
		};
	}
}

class foo {
	public :
		int y;
};

namespace second
{
	double var = 3.1416;
}

int main () {
	first::var++;
	second::var++;
	return 0;
}
