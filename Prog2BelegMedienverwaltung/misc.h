#ifndef MK_algorithm_ext
#define MK_algorithm_ext

#include <utility>

namespace MKay
{
    // A little helper template...
    template<bool, typename T1, typename T2> struct choose {};
    
    template<typename T1, typename T2>
    struct choose<true, T1, T2> { using type = T1; };
    
    template<typename T1, typename T2>
    struct choose<false, T1, T2> { using type = T2; };
    
    /* Used like this:
     choose<true, T1, T2>::type yields T1
     choose<false, T1, T2>::type yields T2 */
    
    
    // Two almost identical helper algorithms...
    /* Copy a range of elements specified by 'inFirst'/'inLast'
     to the range given by 'outFirst'/'outLast'.
     If the input range is too large, stop when the output range is filled.
     If the output range is larger than the input range, stop when
     all elements have been copied.
     Return a pair<...> of iterators representing:
     - The last input element that was copied (inLast if all were)
     - The first output element not written to (outLast if all were)*/
    template<class InputIterator, class OutputIterator>
    std::pair<InputIterator, OutputIterator>
    copy_until_full( InputIterator inFirst, InputIterator inLast,
                    OutputIterator outFirst, OutputIterator outLast )
    {
        while( inFirst != inLast )
        {
            if( outFirst == outLast )
                break;
            
            *outFirst = *inFirst;
            ++inFirst;
            ++outFirst;
        }
        
        return std::make_pair( inFirst, outFirst );
    }
    
    // Pretty much the same, but n elements instead of an arbitrary range.
    template<typename T, typename size_type, class OutputIterator>
    std::pair<size_type, OutputIterator>
    copy_n_until_full( const T &val, size_type num,
                    OutputIterator outFirst, OutputIterator outLast )
    {
        while( num-- != 0 )
        {
            if( outFirst == outLast )
                break;
            
            *outFirst = val;
            ++outFirst;
        }
        
        return std::make_pair( num, outFirst );
    }
}

#endif
