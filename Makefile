SUBDIRS = release debug

format:
	clang-format -i ./*/*.cpp ./*/*.hpp


init:
	mkdir -p release && cd release && cmake -DCMAKE_BUILD_TYPE=Release .. && cd ..
	mkdir -p debug && cd debug && cmake -DCMAKE_BUILD_TYPE=Debug .. && cd ..


run:
	./test.sh


run_win:
	./test.ps1


.PHONY: release debug


all: release debug


release:
	$(MAKE) -C release -j 4;


debug:
	$(MAKE) -C debug -j 4;


clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done