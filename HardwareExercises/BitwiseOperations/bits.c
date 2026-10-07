#include <stdio.h>
#include <stdint.h>

// Code below demonstrates different ways of byte order manipulation within a uint32_t
// Input:  0x12345678
// Expected: 0x78563412


// Method 1: Bitwise shifts
// Most portable. Does not depend on architecture or how the compiler stores variables in memory.
// Teaches: operators <<, >>, |, & and masks.

uint32_t swap_shifts(uint32_t value) {
    return ((value & 0x000000FF) << 24) |   // byte 0 -> position 3
           ((value & 0x0000FF00) <<  8) |   // byte 1 -> position 2
           ((value & 0x00FF0000) >>  8) |   // byte 2 -> position 1
           ((value & 0xFF000000) >> 24);    // byte 3 -> position 0
}

// Method 2: Access via pointer to bytes
// We create a pointer to uint8_t and copy bytes one by one.
// WARNING: This method DEPENDS on the endianness of the machine!
// On a little-endian machine, it will work "in reverse" compared to a big-endian machine.
// Teaches: memory aliasing and what endianness really means.
uint32_t swap_via_pointer(uint32_t value) {
    uint8_t *bytes = (uint8_t *)&value;
    uint8_t tmp;

    tmp = bytes[0]; bytes[0] = bytes[3]; bytes[3] = tmp;
    tmp = bytes[1]; bytes[1] = bytes[2]; bytes[2] = tmp;

    return value;
}

// Method 3: Union - two views of the same memory
// The same memory area is viewed as a uint32_t OR as an array of bytes.
// This is a common pattern in hardware drivers (parsing frames).
// WARNING: Similar to the previous method - depends on endianness.
// Teaches: union, memory layout, working with network protocols.
typedef union {
    uint32_t word;
    uint8_t  bytes[4];
} endian_u;

uint32_t swap_via_union(uint32_t value) {
    endian_u u;
    u.word = value;

    uint8_t t0 = u.bytes[0]; u.bytes[0] = u.bytes[3]; u.bytes[3] = t0;
    uint8_t t1 = u.bytes[1]; u.bytes[1] = u.bytes[2]; u.bytes[2] = t1;

    return u.word;
}


// Method 4: Loop + write "from the end"
// Readable, easy to extend to any width (16/64 bits).
// Teaches: generalizing algorithms and avoiding code duplication.
uint32_t swap_loop(uint32_t value) {
    const uint8_t *src = (const uint8_t *)&value;
    uint32_t result = 0;

    for (int i = 0; i < 4; i++) {
        result <<= 8;          // shift the result left by 8 bits
        result |= src[i];      // add the next byte to the result
    }
    return result;
}


// Method 5: Built-in function (GCC/Clang)
// The compiler generates a single processor instruction (BSWAP on x86).
// Fastest - but not portable outside GCC/Clang.
// Teaches: the existence of intrinsics and that "hand-crafted" code can be slower.
uint32_t swap_builtin(uint32_t value) {
#if defined(__GNUC__) || defined(__clang__)
    return __builtin_bswap32(value);
#else
    #error "No builtin bswap function for this compiler"
#endif
}

// Helper: detect endianness of the current machine
// (similar to how we detected stack direction earlier!)
int is_little_endian(void) {
    uint32_t probe = 0x00000001;
    uint8_t *p = (uint8_t *)&probe;
    return p[0] == 0x01;   // if the first byte is 1 -> little-endian
}

int main(void) {
    const uint32_t input = 0x12345678;
    const uint32_t expected = 0x78563412;

    printf("That machine usues : %s\n",
           is_little_endian() ? "little-endian" : "big-endian");
    printf("Input                : 0x%08X\n", input);
    printf("Expected            : 0x%08X\n\n", expected);

    struct { const char *name; uint32_t (*fn)(uint32_t); } methods[] = {
        { "1. Bitwise shifts     ", swap_shifts },
        { "2. Pointer to bytes   ", swap_via_pointer },
        { "3. Union              ", swap_via_union },
        { "4. Loop              ", swap_loop },
        { "5. __builtin_bswap32  ", swap_builtin },
    };

    size_t n = sizeof(methods) / sizeof(methods[0]);
    for (size_t i = 0; i < n; i++) {
        uint32_t out = methods[i].fn(input);
        printf("%s : 0x%08X  [%s]\n",
               methods[i].name, out,
               out == expected ? "OK" : "That's wrong!");
    }

    return 0;
}