#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

// Doll integer size
typedef unsigned long long dint;
// 63-bit safe prime
#define P (0x7fffffffffffee27)
// Generator of multiplicative group mod p
#define C (11)
// A 64-bit marker value to facilitate binary searching
#define MARKER (6456472665565383409ULL)
#define DINT "%llu"
#define FN_PREFIX "doll-"
// length of 18446744073709551615
#define MAX_DINT_LENGTH 20

struct doll
{
    dint marker;
    dint x;
    dint r;
    dint generation;
};

// Parameters generated from python3 genchal.py
#define FLAG_ENC (614950695975220210ULL)
// generation count to print flag
#define GENERATION_COUNT (8338671502332819874)
volatile struct doll data = {
    MARKER, 1, 1, 0
};

dint get_random_dint(void) {
    dint num;
    if (getrandom((void *) &num, sizeof(num), 0) != (ssize_t) sizeof(num)) {
        printf("Some error occurred\n");
        exit(EXIT_FAILURE);
    }
    return num;
}

dint mul_modp(dint a, dint b) {
    dint product = 0;
    // assume p has 63 bits at most
    for (int i = 0; i < (int) (sizeof(dint) * 8); i++) {
        product = (product * 2) % P;
        if (b & (1ULL << (sizeof(dint) * 8 - 1))) {
            product = (product + a) % P;
        }
        b <<= 1;
    }
    return product;
}

dint inv_modp(dint a) {
    dint t = 0, r = P, nt = 1, nr = a;
    while (nr) {
        dint q = r / nr, rem = r % nr;
        dint t_new = nt;
        nt = (t + mul_modp(q, P - nt)) % P;
        t = t_new;
        r = nr;
        nr = rem;
    }
    return t;
}

off_t get_filesize(int fd) {
    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == (off_t) -1) {
        perror("Cannot determine file size");
        exit(1);
    }
    if (lseek(fd, 0, SEEK_SET) == (off_t) -1) {
        perror("Cannot rewind");
        exit(1);
    }
    return file_size;
}

void mutate(void *content, size_t length, struct doll *newdata) {
    void *current = content;
    void *max = content + length - sizeof(dint);
    int found = 0;
    while (current <= max) {
        if ((*(dint *)current) == newdata->marker) {
            found = 1;
            break;
        }
        current += sizeof(dint);
    }
    if (!found) {
        exit(2); // Marker not found, should not happen
    }
    memcpy(current, newdata, sizeof(*newdata));
}

void copy(struct doll *newdata) {
    int self_fd = open("/proc/self/exe", O_RDONLY);
    if (self_fd == -1) {
        perror("Unable to open myself");
        exit(1);
    }
    size_t file_size = (size_t) get_filesize(self_fd);
    char fn_buf[sizeof(FN_PREFIX) + MAX_DINT_LENGTH] = FN_PREFIX;
    snprintf(fn_buf + sizeof(FN_PREFIX) - 1, MAX_DINT_LENGTH + 1, DINT, newdata->generation);
    // puts(fn_buf); // DEBUG
    int copy_fd = open(fn_buf, O_WRONLY | O_EXCL | O_CREAT, S_IRWXU);
    if (copy_fd == -1) {
        perror("Unable to create new doll");
        exit(1);
    }
    // write(copy_fd, "abcd", 4); // DEBUG
    // printf("File size: %zd\n", file_size);
    void *file_content = malloc(file_size);
    if (file_content == NULL) {
        printf("malloc() failed!\n");
        exit(1);
    }
    ssize_t nread = read(self_fd, file_content, file_size);
    if (!(nread > 0 && ((size_t) nread) == file_size)) {
        printf("Something went wrong while reading myself!\n");
        exit(1);
    }
    mutate(file_content, file_size, newdata);
    if (write(copy_fd, file_content, file_size) == -1) {
        perror("Error copying doll");
        exit(1);
    }

    free(file_content);
    close(copy_fd);
    close(self_fd);
}

void print_flag(void) {
    dint x = mul_modp(data.x, inv_modp(data.r));
    dint str = mul_modp(FLAG_ENC, x);
    char strbuf[sizeof(dint) + 1];
    memcpy(strbuf, &str, sizeof(dint));
    strbuf[sizeof(dint)] = '\0';
    printf("Congrats! You found the flag:\n");
    printf("sdctf{%s_" DINT "}\n", strbuf, x);
}

int main(void) {
    if (data.generation == GENERATION_COUNT) {
        print_flag();
        return 0;
    }
    printf("Unwrapping the " DINT "-th doll\n", data.generation + 1);
    struct doll data_copy = data;
    dint r = get_random_dint();
    data_copy.r = mul_modp(data.r, r);
    data_copy.x = mul_modp(mul_modp(data_copy.x, C), r);
    data_copy.generation += 1;
    copy(&data_copy);
    return 0;
}
