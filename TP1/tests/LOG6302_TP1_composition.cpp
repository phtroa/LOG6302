class Foo {

public:
    int x;
    
    int bar() {
        if (false)
            return 42;
        for (int i = 0; i < -1; i++);
        return -1;
    }

};

class baz {

public:
    int x;
    
    int bar() {
        if (false)
            return 42;
        for (int i = 0; i < -1; i++);
        return -1;
    }
private:
	Foo* f;
};

int main(void) {
    Foo foo;

    return 0;
}
