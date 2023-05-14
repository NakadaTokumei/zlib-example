#include <iostream>
#include <fstream>

#include <zlib.h>

int main(int argc, char** argv)
{
    char data[256] = {0,};
    char out[256] = {0,};
    z_stream zstream;

    std::ifstream filestream = std::ifstream(std::string(argv[1]));
    filestream.read(
        data,
        256
    );

    std::ofstream outFileStream = std::ofstream(std::string(argv[1]) + "_zip");

    zstream.zalloc = nullptr;
    zstream.zfree = nullptr;
    zstream.opaque = nullptr;

    zstream.next_in = reinterpret_cast<Bytef*>(data);
    zstream.avail_in = 256;

    zstream.next_out = reinterpret_cast<Bytef*>(out);
    zstream.avail_out = 256;


    deflateInit(&zstream, Z_BEST_COMPRESSION);
    deflate(&zstream, Z_FINISH);
    deflateEnd(&zstream);
    
    outFileStream.write(out, 256);
}