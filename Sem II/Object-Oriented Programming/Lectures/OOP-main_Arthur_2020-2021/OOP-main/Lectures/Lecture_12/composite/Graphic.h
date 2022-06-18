#pragma once
#include <QPainter>

class Graphic
{
private:
	std::string name;
public:
	Graphic(std::string n) : name{ n } {}
	std::string getName() const { return this->name; }
	virtual void draw(QPainter* p) const = 0;
	virtual void add(Graphic* g) = 0;
	virtual ~Graphic() {}
};

class Line : public Graphic
{
private:
	int x1, y1, x2, y2;

public:
	Line(std::string name, int a1, int b1, int a2, int b2) : Graphic{ name }, x1 { a1 }, y1{ b1 }, x2{ a2 }, y2{ b2 } {}
	void draw(QPainter* p) const override;
	void add(Graphic* g) override {}
};

class Text : public Graphic
{
private:
	int x, y;
	std::string text;

public:
	Text(std::string name, int a, int b, std::string _text) : Graphic{ name }, x{ a }, y{ b }, text{ _text } {}
	void draw(QPainter* p) const override;
	void add(Graphic* g) override {}
};

class Circle : public Graphic
{
private:
	int x, y;
	double radius;

public:
	Circle(std::string name, int a, int b, double r) : Graphic{ name }, x{ a }, y{ b }, radius{ r } {}
	void draw(QPainter* p) const override;
	void add(Graphic* g) override {}
};

class Picture : public Graphic
{
private:
	std::vector<Graphic*> components;
public:
	Picture(std::string name) : Graphic{ name } {}
	void draw(QPainter* p) const override;
	void add(Graphic* g) override;
};