doll-dev: doll.c
	gcc $^ -Wall -Wextra -Wconversion -o $@

# Make stripped binary to make it hard to reverse
doll: doll-dev
	strip $^ -o $@

clean:
	rm -f doll doll-*
