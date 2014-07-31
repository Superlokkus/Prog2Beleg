#ifndef MK_string
#define MK_string

#include <iterator>

namespace MKay /* Markus Klemm */
{
    class string
    {
    public:
        using iterator = char*;
        using const_iterator = const char*;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        using size_type = std::size_t;
    private:
        std::size_t len;
        char *str; // len+1 elements (\0)
    public:
        string() : len(0), str(new char[1]) { str[0] = '\0'; }
        
        string( const string &s )
        : len(s.len), str(new char[len+1])
        { std::memcpy( str, s.str, len+1 ); }
        
        string( const string &s, size_t pos, size_t length )
        : len(length), str(new char[len])
        {
            std::memcpy( str, s.str + pos, length );
            str[len] = '\0';
        }
        
        string( const char *s )
        : len(strlen(s)), str(new char[len+1])
        { std::memcpy( str, s, len+1 ); }
        
        string( const char *s, size_t n )
        : len(n), str(new char[n+1])
        {
            std::memcpy( str, s, n );
            str[len] = '\0';
        }
        
        string( size_t n, char c )
        : len(n), str(new char[len+1])
        {
            std::memset( str, c, n );
            str[len] = '\0';
        }
        
        template<class RandomAccessIterator>
        string( RandomAccessIterator first, RandomAccessIterator last )
        : len(last-first+1), str(new char[len+1])
        {
            char *t = str;
            while( first != last )
            {
                *t = *first;
                ++t;
            }
            
            str[len] = '\0';
        }
        
        // The usual construct()/swap() for moves
        string( string&& str ) : string() { this->swap( str ); }
        
        ~string() { delete [] str; } // Free the memory
        
        void swap( string &s ) // Swapping two strings is easy
        {
            std::swap( len, s.len );
            std::swap( str, s.str );
        }
        
        // Return references to characters at given positions
        char &operator[]( size_t pos ) { return str[pos]; }
        const char &operator[](size_t pos) const { return str[pos]; }
        
        
        iterator begin() { return iterator( str ); }
        const_iterator begin() const { return const_iterator( str ); }
        const_iterator cbegin() const { return const_iterator( str ); }
        
        reverse_iterator rbegin() { return reverse_iterator( this->end() ); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator( this->end() ); }
        const_reverse_iterator crbegin() const { return const_reverse_iterator( this->end() ); }
        
        iterator end() { return iterator( str+len ); }
        const_iterator end() const { return const_iterator( str+len ); }
        const_iterator cend() const { return const_iterator( str+len ); }
        
        reverse_iterator rend() { return reverse_iterator( this->begin() ); }
        const_reverse_iterator rend() const { return const_reverse_iterator( this->begin() ); }
        const_reverse_iterator crend() const { return const_reverse_iterator( this->begin() ); }
        
        // Stream operator for easy output
        friend std::ostream &operator<<( std::ostream &out, string &str );
    };
    
    // Let std::swap() work with argument-dependent lookup
    void swap( string &s1, string &s2 ) { s1.swap( s2 ); }
    
    // Now cout knows about us too...
    std::ostream &operator<<( std::ostream &out, string &str )
    { return out << str.str; }
}

#endif
