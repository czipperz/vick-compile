CFLAGS=-std=c++11 -I../../src -I../../test -Isrc
LDFLAGS=`find ../../out -type f -not \( -name main.o -o -name configuration.o \)` \
        ../../testout/test_main.o

LDLIBS=`find ../vick-shell-command/out -type f`

O=out
S=src
T=test
TO=testout
CXX=clang++

files=$O/compile.o

testfiles=

all: ${files}

begin:
	git pull
	[ -d ../vick-shell-command ] || git clone "https://github.com/czipperz/vick-shell-command" ../vick-shell-command
	cd ../vick-shell-command && make begin

$O/%.o: $S/%.cc $S/%.hh
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}

$O/%.o: $S/%.cc
	@mkdir -p $O
	${CXX} -o $@ -c $< ${CFLAGS}

${TO}/%.o: $T/%.cc
	@mkdir -p ${TO}
	${CXX} -o $@ -c $< ${CFLAGS}

clean:
	[ ! -d $O ] || rm -R $O
	[ -z "`find -name '*~'`" ] || rm `find -name '*~'`
	[ ! -d ${TO} ] || rm -R ${TO}

test: ${files} ${testfiles}
	@mkdir -p ${TO}
	${CXX} -o ${TO}/out $^ ${CFLAGS} ${LDFLAGS} ${LDLIBS}
	./${TO}/out

.PHONY: all begin clean test
