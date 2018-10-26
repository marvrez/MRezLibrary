#ifndef UUID_H
#define UUID_H

#include <cstdio>
#include <cstdlib>

// Need this helper function because RAND_MAX isn't guaranteed to be > 0x7FFFFFFF
inline uint32_t rand32() {
	const uint32_t r1 = rand() & 0xff;
	const uint32_t r2 = rand() & 0xfff;
	const uint32_t r3 = rand() & 0xfff;
	return (r3 << 20) | (r2 << 8) | r1;
}

//  implements uuid v4
class UUID {
public:
    static UUID generate() {
        static const uint16_t c[] = { 0x8000, 0x9000, 0xa000, 0xb000 };
        uint32_t rand_vals[4] =  {
            (rand32() & 0xffffffff),
            (rand32() & 0xffff0fff) | 0x4000,
            (rand32() & 0xffff0fff) | c[rand32() & 0x03],
            (rand32() & 0xffffffff)
        };
        uint32_t rand_val, i;

        UUID uuid;
        for(i = 0; i < 16; i += 4) {
            rand_val = rand_vals[i >> 2];
            uuid.bytes_[i]   = (rand_val >> 24) & 0xff;
            uuid.bytes_[i+1] = (rand_val >> 16) & 0xff;
            uuid.bytes_[i+2] = (rand_val >>  8) & 0xff;
            uuid.bytes_[i+3] = rand_val & 0xff;
        }

        return uuid;
    }

    const char* toString() {
        char* buffer  = new char[2*16];
        for (unsigned int i = 0; i < 16; ++i) {
            sprintf(&buffer[2*i],"%02x", bytes_[i]);
        }
        return buffer;
    }

private:
    uint8_t bytes_[16];
};

#endif
