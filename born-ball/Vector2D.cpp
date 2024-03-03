#include "Vector2D.hpp"

Vector2D::Vector2D(int xval, int yval) {
	x = xval;
	y = yval;
}

Vector2D::~Vector2D() {}

Vector2D* Vector2D::MUL(int n) {
	return new Vector2D(x * n, y * n);
}

int Vector2D::DOT(Vector2D* v) {
	return x * v->x + y * v->y;
}

Vector2D* Vector2D::operator-(Vector2D* v) {
	return new Vector2D(x - v->x, y - v->y);
}

Vector2D* Vector2D::operator+(Vector2D* v) {
	return new Vector2D(x + v->x, y + v->y);
}