#include "generator.hpp"

Generator::Generator(size_t n, const mt19937& rnd): n_(n), rnd_(rnd)  {
	pdata_ = new Point[n_];
	generate();
}

Generator::~Generator() {
	delete pdata_;
}

void Generator::generate(){
	
}

void Generator::write(iostream stream) {
	stream << n_ << "\n";
	for (size_t i = 0; i < n_; ++i){
		stream << pdata_[i].x << " " << pdata_[i].y << " " << pdata_[i].z << "\n";
	}
}
