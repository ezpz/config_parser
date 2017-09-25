
default: example

example:
	g++ -W -Wall -Wextra -Werror -std=c++11 driver.cc -o example

clean:
	rm -f example
