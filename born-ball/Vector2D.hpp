#ifndef Vector2D_hpp
#define Vector2D_hpp

class Vector2D {
public:
	int x, y;

	Vector2D(int xval, int yval);
	~Vector2D();

	Vector2D* MUL(int n);
	int DOT(Vector2D* v);
	Vector2D* operator-(Vector2D* v);
	Vector2D* operator+(Vector2D* v);
};

#endif