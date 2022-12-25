#include "solution.hpp"

Solver::Solver() : sz(0), pdata(nullptr) {}

Solver::~Solver() {
	if (pdata != nullptr)  {
		delete[] pdata;
	}
}

void Solver::read(std::istream& stream) {
	stream >> sz;
	pdata = new std::pair<Point, double>[sz];

	double alpha, phi, d;
	for (int i = 0; i < sz; ++i) {
		stream >> alpha >> phi >> d;
		pdata[i].first = Point(alpha, phi);
		pdata[i].second = d;
	}
}

Point Solver::calc() const {
	Point O1 = pdata[0].first;
	double r1 = pdata[0].second;

	Point O2 = pdata[1].first;
	double r2 = pdata[1].second;

	// противоположные точки недопустимы
	if (O1 + O2 == Point(0, 0, 0)) {
		O2 = pdata[2].first;
		r2 = pdata[2].second;
	}

	double r1_sqr = std::max(static_cast<double>(0), 2 - 2*cos(r1));
	double r2_sqr = std::max(static_cast<double>(0), 2 - 2*cos(r2));

	double g1 = ((O1 % O1) - r1_sqr + 1) / 2; 
	double g2 = ((O2 % O2) - r2_sqr + 1) / 2;

	/*
		t - ответ

		скалярная система

		t % O1 = g1
		t % O2 = g2
	
		это система плоскостей

		x*O1.x + y*O1.y + z*O1.z = g1
		x*O2.x + y*O2.y + z*O2.z = g2
	
		ее решением будет прямая.
		
		Если 
		| O1.y   O1.z |
		|             | == 0
		| O2.y   O2.z |

		то прямая имеет вид (x = const, y = const, z - [-oo, +oo]) 

		иначе `x` принимает все значения [-oo, +oo], и можно найти две точки 
		при `x` = {0,1}, которые точно существуют. По этим точкам восстановим ответ

		Далее пересечем прямую с исходной сферой и найдем точки кандидаты (не более 2)
	*/

	Line L;

	double d = det(O1.y, O1.z, O2.y, O2.z);
	
	if (eq(d, 0)) {
		// метод Мрамера
		double dnew = det(O1.x, O1.y, O2.x, O2.y);
		double xd = det(g1, O1.y, g2, O2.y);
		double yd = det(O1.x, g1, O2.x, g2);
		double x = xd / dnew;
		double y = yd / dnew;
		L = Line(Point(x, y, 0), Point(0, 0, 1)); 	
	} else {
		Point p[2];
		for (int x = 0; x <= 1; ++x) {
			double ng1 = g1 - x*O1.x;
			double ng2 = g2 - x*O2.x;
			double yd = det(ng1, O1.z, ng2, O2.z);
			double zd = det(O1.y, ng1, O2.y, ng2);
			double y = yd / d;
			double z = zd / d;
			p[x] = Point(x, y, z);
		}
		L = Line(p[0], p[1] - p[0]);
	}

	vector<Point> cands = interSphereLine(1, L);

	if (cands.empty()) {
		// никогда не должно произойти
		return Point();
	}

	if (cands.size() == 1) {
		// касание прямой и сферы
		return cands[0];
	}

	/*
		обычный случай с двумя кандидатами на ответ:

		если точка A лежит в плоскости (O, O1, O2), то это не дает возможности 
		распознать, какой из кандидатов верный. Если все исходные точки в одной плоскости,
		то ответ неоднозначен, иначе мы рано или поздно найдем точку вне плоскости. 
	*/

	for (int i = 0; i < sz; ++i) {
		Point P = pdata[i].first;
		double realDist = pdata[i].second;

		double d1 = distOnSphere(1, P, cands[0]);
		double d2 = distOnSphere(1, P, cands[1]);

		if (eq(d1, d2)) {
			// в одной плоскости
			continue; 
		}

		return cands[eq(d2, realDist)];
	}

	/*
		только, если ответ не однозначный или отсутствует

		считаем, что данные корректны
	*/
	return Point();
}

bool Solver::validate(const Point& P) const {
	// точка на сфере
	if (!eq(1, P.len())) {
		return false;
	}

	// не противоречит исходным данным
	for (int i = 0; i < sz; ++i) {
		double realDist = pdata[i].second;
		double dist = distOnSphere(1, P, pdata[i].first);
		if (!eq(realDist, dist)) {
			return false;
		}
	}

	return true;
}