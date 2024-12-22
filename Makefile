CC=g++ -Wall -Wextra -Werror -std=c++17
FUNC_FILES_CPP=s21_matrix_oop.cpp
FUNC_FILES_O=s21_matrix_oop.o
LIBNAME=s21_matrix_oop.a
GLFLAGS=--coverage

# Путь к заголовкам и библиотекам Google Test
GTEST_DIR=/usr/src/googletest/googletest

# Путь к заголовочным файлам
INCLUDES=-I/opt/homebrew/Cellar/googletest/1.14.0/include

# Путь к библиотекам
LIBS=-L/opt/homebrew/Cellar/googletest/1.14.0/lib -lgtest -lgtest_main -pthread

all: $(LIBNAME) test

build_object_files:
	$(CC) $(GLFLAGS) -c $(FUNC_FILES_CPP)

build_library: $(FUNC_FILES_O)
	ar rcs $(LIBNAME) $(FUNC_FILES_O)

$(LIBNAME): build_object_files build_library
	rm -rf *.o

test: $(LIBNAME)
	$(CC) $(GLFLAGS) $(INCLUDES) tests.cpp -L. $(LIBNAME) $(LIBS) -o test
	./test

clean:
	rm -rf *.o *.gcno *.gcda *.a test

rebuild: clean all
