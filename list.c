#include "pixz.h"

#include <getopt.h>

#pragma mark FUNCTION DEFINITIONS

void pixz_list(bool tar) {
    decode_index();
    lzma_index_iter iter;
    lzma_index_iter_init(&iter, gIndex);
    while (!lzma_index_iter_next(&iter, LZMA_INDEX_ITER_BLOCK)) {
        printf("%9"PRIuMAX" / %9"PRIuMAX"\n",
            (uintmax_t)iter.block.unpadded_size,
            (uintmax_t)iter.block.uncompressed_size);
    }
    
    if (tar && read_file_index(0)) {
        printf("\n");
        dump_file_index(stdout);
        free_file_index();
    }
    
    lzma_index_end(gIndex, NULL);
    lzma_end(&gStream);
}
