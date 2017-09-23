
default: example

example:
	g++ -W -Wall -Wextra -Werror driver.cc -o example

clean:
	rm -f example
