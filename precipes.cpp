//********************************************************************************
// Copyright (c) 2013-2015 Yves Vandriessche and Frank Schlimbach.              **
//                                                                              **
// Redistribution and use in source and binary forms, with or without           **
// modification, are permitted provided that the following conditions are met:  **
//   * Redistributions of source code must retain the above copyright notice,   **
//     this list of conditions and the following disclaimer.                    **
//   * Redistributions in binary form must reproduce the above copyright        **
//     notice, this list of conditions and the following disclaimer in the      **
//     documentation and/or other materials provided with the distribution.     **
//   * Neither the name of Intel Corporation nor the names of its contributors  **
//     may be used to endorse or promote products derived from this software    **
//     without specific prior written permission.                               **
//                                                                              **
// This software is provided by the copyright holders and contributors "as is"  **
// and any express or implied warranties, including, but not limited to, the    **
// implied warranties of merchantability and fitness for a particular purpose   **
// are disclaimed. In no event shall the copyright owner or contributors be     **
// liable for any direct, indirect, incidental, special, exemplary, or          **
// consequential damages (including, but not limited to, procurement of         **
// substitute goods or services; loss of use, data, or profits; or business     **
// interruption) however caused and on any theory of liability, whether in      **
// contract, strict liability, or tort (including negligence or otherwise)      **
// arising in any way out of the use of this software, even if advised of       **
// the possibility of such damage.                                              **
//********************************************************************************

#include <iostream>
#include <string>

#include "precipes.hpp"
#include "parse_json.hpp"

typedef pipeline< json_init_pipeline > SeqPipeLine;

int main( int argc, char * argv [] )
{
#ifdef _DIST_
    CnC::dist_cnc_init< SeqPipeLine > _di;
#endif

    if( argc < 2 ) {
        std::cout << "No config file specified.\n";
        exit(1);
    }
    if( argc < 3 ) {
        std::cout << "No data files specified.\n";
        exit(1);
    }

    system( ("mkdir -p " + _local_path_).c_str() );

    std::ifstream f(argv[1]);
    std::string json_str( (std::istreambuf_iterator<char>(f)),
                          std::istreambuf_iterator<char>() );
    f.close();
    SeqPipeLine pl( json_str );
	//    CnC::debug::collect_scheduler_statistics( pl );
    

    for( int i = 2; i < argc; ++i ) {
      pl.run( argv[i], "fastq.gz", i-2 );
    }

    pl.wait();

    return 0;
}
