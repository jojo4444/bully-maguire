#include "generator.hpp"

Generator::Generator(size_t n, size_t seed): rnd(seed){
	this->n = n;
	pdata = new SpherePoint[n];
	generate();
}

Generator::~Generator() {
	if (pdata != nullptr){
		delete[] pdata;
	}
}

void Generator::generate(){
	uniform_real_distribution<> furd(-PI/2, PI/2);
	uniform_real_distribution<> surd(0., 2 * PI);
	for (size_t i = 0; i < n; ++i){
		pdata[i].first = furd(rnd);
		pdata[i].second = surd(rnd);
	}
	p.first = furd(rnd);
	p.second = surd(rnd);
}

Point Generator::convert(const SpherePoint &p){
    return Point(p.first, p.second);
}

void Generator::write(ostream& stream) {
	Point pd = convert(p);
	stream << n << "\n";
	for (size_t i = 0; i < n; ++i){
		double dist = distOnSphere(1, convert(pdata[i]), pd);
		stream << std::setprecision(9) << std::fixed << pdata[i].first << " " << pdata[i].second << " " <<  dist << "\n";
	}
}
