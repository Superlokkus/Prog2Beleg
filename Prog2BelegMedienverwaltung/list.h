#ifndef MK_list
#define MK_list

#include "misc.h"

#include <utility>
#include <iterator>
#include <cstdlib>

namespace MKay /* Markus Klemm */
{
    // Forward declare our list class to make it available
    // to our helper templates
    template<typename Element> class list;
    
    namespace impl /* implementation details */
    {
        struct listNodeBase /* contains the basic stuff of a list node */
        {
            // The usual stuff...
            struct listNodeBase *previous;
            struct listNodeBase *next;
        };
        
        template<typename Element>
        struct listNode : public listNodeBase
        /* This will be used as the real list node.
         Note that 'previous'/'next' only point to listNodeBases
         and not listNode<...> objects!
         This is used to properly implement the iterators.
         We will however have to use a few casts becuase of this... */
        {
            Element element; // The 'real' content of the node
            
            // Copy/Move versions...
            listNode( const Element &e, listNodeBase *p, listNodeBase *n )
            : listNodeBase{ p, n }, element(e) {}
            listNode( Element &&e, listNodeBase *p, listNodeBase *n )
             : listNodeBase{ p, n }, element(std::move(e)) {}
        };
        
        // To reduce typing the awfully long type below twice,
        // we stuff it into a templated typedef
        // We always need a 'const' and a 'non-const' iterator type,
        // But since they are almost equal, we use template magic to
        // distinguish them - the 'constIteratorFlag', true for const,
        // false for non-const.
        template<typename Element, bool constIteratorFlag>
        struct listIteratorBase
        {
            // The base iterator type! We are going to inherit from this thing!
            // The advantage is that we don't have to specialize
            // std::iterator_traits on our own, by using std::iterator!
            // It takes care of tat for us.
            using type = std::iterator<
                std::bidirectional_iterator_tag, /* iterator type */
                Element, /* value_type */
                std::ptrdiff_t, /* difference type */
                typename choose<constIteratorFlag, const Element, Element>::type *, /* pointer type */
                typename choose<constIteratorFlag, const Element, Element>::type & /* reference type */
            >;
        };
        
        // Now its time to implement the real iterator class(es)
        template<typename Element, bool constIteratorFlag>
        class listIterator :
        public listIteratorBase<Element, constIteratorFlag>::type
        /* Inheriting from listIteratorBase<...> takes care of the
         std::iterator_traits stuff (indirectly, details above).
         Note the saved code space! One line instead of 5 for the base class! */
        {
            // Friends are nice to have :)
            /* to allow conversions iterator -> const_iterator */
            friend listIterator<Element, true>;
            /* Make the list being able to actually use the iterators.
             Note that the only non-copying constructor below is private!
             This way no other class can use our iterators!
             (Paranoia... reduces number of possible error sources) */
            friend MKay::list<Element>;
            
        private:
            /* Again save us from typing that messy base type again... */
            using Base = typename listIteratorBase<Element, constIteratorFlag>::type;
        public:
            /* Inherit the typedefs from std::iterator<...> and make
             them public (!) so that everybody can use our beautiful
             iterator - every iterator should declare these... */
            using value_type = typename Base::value_type;
            using difference_type = typename Base::difference_type;
            using pointer = typename Base::pointer;
            using reference = typename Base::reference;
            using iterator_category = typename Base::iterator_category;
        private:
            /* typedef used for abbreviation in the casts... */
            using Node = listNode<value_type>;
            /* This is the 'real' list node type by the way */
            
            /* The actual content of our iterator */
            listNodeBase *current;
            /* The node that it points to */
            
            // The (meaningful) constructor!
            // The list class uses this method to create iterators
            // to its elements.
            listIterator( const listNodeBase *node )
            : current(const_cast<listNodeBase*>( node )) {}
            /* Note the const-cast! In order to reduce the amount of
             template magic, we accept 'const listNodebase*'
             but always store them as non-consts.
             The user interface below still makes sure that the
             appropriate const-ness is reapplied when necessary. */
        public:
            /* Biderectional iterators should be default constructible */
            listIterator( void ) = default;
            
            /* Allow the conversion 'iterator' -> 'const_iterator' */
            listIterator( const listIterator<value_type, false> &i )
            { current = i.current; }
        
            listIterator &operator++( void ) /* Preincrement */
            { current = current->next; return *this; }
            listIterator operator++( int ) /* Postincrement */
            { listIterator copy( *this ); ++(*this); return copy; }
            
            listIterator &operator--( void ) /* Predecrement */
            { current = current->previous; return *this; }
            listIterator operator--( int ) /* Postdecrement */
            { listIterator copy( *this ); --(*this); return copy; }
            
            // The dereferencing operators! With these the acutal content
            // is accessed (only the element).
            // The templated return types make sure that the appropriate
            // ocnst-ness is applied.
            typename choose<constIteratorFlag, const value_type, value_type>::type &
            operator*( void ) const
            { return static_cast<Node*>( current )->element; }
            
            typename choose<constIteratorFlag, const value_type, value_type>::type *
            operator->( void ) const
            { return &(static_cast<Node*>( current )->element); }
            
            // Comparison operators... Allow comparisons between
            // const and non-const versions.
            bool operator==( const listIterator<value_type, true> &i ) const { return current == i.current; }
            bool operator==( const listIterator<value_type, false> &i ) const { return current == i.current; }
            
            bool operator!=( const listIterator<value_type, true> &i ) const { return current != i.current; }
            bool operator!=( const listIterator<value_type, false> &i ) const { return current != i.current; }
        };
    }
    
    // Finally the list class!
    template<typename Element>
    class list
    {
    public:
        // Inherit the typedefs from our iterators
        using iterator = impl::listIterator<Element, false>;
        using const_iterator = impl::listIterator<Element, true>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        
        using value_type = typename iterator::value_type;
        using reference = typename iterator::reference;
        using const_reference = typename const_iterator::reference;
        using pointer = typename iterator::pointer;
        using const_pointer = typename const_iterator::pointer;
        using difference_type = typename iterator::difference_type;
        using size_type = typename std::make_unsigned<difference_type>::type;
    private:
        // Again abbreviate the Node class
        using Node = impl::listNode<value_type>;
        
        size_type sz; // The size of the list
        impl::listNodeBase implBase; // The "root" pseudo-node object
        /* The list is implemented like this:
         - There is a "root" node (implBase)
         - The root node does not contain any value_type object
         (listNodeBase, not listNode<...>
         - All other nodes (the real ones) are listNode<...> objects
         - But we only refer to them as listNodeBase objects
         (listNodeBase is a base class of listNode<...>)
         - The 'previous'/'next' entries are as usual, but
            the begin (implBase - the root node) and the last
            real node are also connected
         - This way it is enough to know the root node and not also
            the last node. (implBase->previous will point to the last node)
         - With this we can implement iterators properly!
         - We let the past-the-end iterator (list::end()) point to the
            root node. Dereferencing it yields the last element in the
            list (as it should be). The begin() iterator simply points
            to the first element in the list (implBase->next)
            (If the list is empty impleBase->next points to itself
            and begin() == end() as is required) */
    public:
        /* An empty list has size zero and
         implBase->next and implBase->previous simply point to implBase
         itself. We need this circular structure for the iterators! */
        list( void ) : sz(0), implBase{&implBase, &implBase} {}
        
        // Construct a list with 'num' entris each with value 'val'
        list( size_type num, const value_type &val ) : list()
        { this->insert( this->end(), num, val ); }
        
        // Copy a list
        list( const list &l ) : list( l.begin(), l.end() ) {}
        
        // Move a list, requires the result in 'l' - the parameter
        // from which we steal the data to be in a destructible state!
        // The simplest destructible state is an empty list, so we
        // default-initialize ourselves and simply swap the lists.
        // If we didn't remove the data from the other list, it would
        // be deleted twice - once upon this lists destruction and when
        // the other list gets destructed - which would be undefined
        // behaviour. This way we don't have that problem...
        list( list &&l ) : list() { this->swap( l ); }
        
        // Construct a list from an input sequence
        template<class InputIterator>
        list( InputIterator begin, InputIterator end ): list()
        { this->insert( this->end(), begin, end ); }
        
        // Destroying a list requies to free all memory!
        // clear() takes care of that.
        ~list( void ) { this->clear(); }
        
        // The usual stuff...
        size_type size( void ) const { return sz; }
        bool empty( void ) const { return sz == 0; }
        
        // Swapping two lists!
        void swap( list &l )
        {
            if( sz == 0 )
            {
                // Two empty lists are identical and hence need not
                // be swapped
                if( l.sz == 0 )
                    return;
                
                // Steal everything from the other list
                implBase.next = l.implBase.next;
                implBase.previous = l.implBase.previous;
                
                // implBase has a different address for each list
                // instance! Thus everything that points to it needs to
                // be updated. (Remember the circular structure)
                implBase.next->previous = &implBase;
                implBase.previous->next = &implBase;
                
                // Make the other list an emty list (see default initializer)
                l.implBase = { &(l.implBase), &(l.implBase) };
            } else if( l.sz == 0 )
                // We don't want to rewrite the logic above for the reverse
                // case, so simply reversing the parameters will do...
                return l.swap( *this );
            else
            {
                // If both lists contain real nodes, swapping is pretty easy
                std::swap( implBase, l.implBase );
                
                /* We still need to update the pointers to the implBases
                 though! The addresses of implBases are inherit to the
                 corresponding lists. */
                std::swap( implBase.previous->next, l.implBase.previous->next );
                std::swap( implBase.next->previous, l.implBase.next->previous );
            }
            
            // Finally swap the sizes
            std::swap( sz, l.sz );
        }
        
        // The usual iterator stuff... Simply creating the iterators...
        iterator begin( void ) { return iterator( implBase.next ); }
        const_iterator begin( void ) const { return const_iterator( implBase.next ); }
        const_iterator cbegin( void ) const { return const_iterator( implBase.next ); }
        
        reverse_iterator rbegin( void ) { return reverse_iterator( this->end() ); }
        const_reverse_iterator rbegin( void ) const { return const_reverse_iterator( this->end() ); }
        const_reverse_iterator crbegin( void ) const { return const_reverse_iterator( this->end() ); }
        
        iterator end( void ) { return iterator( &implBase ); }
        const_iterator end( void ) const { return const_iterator( &implBase ); }
        const_iterator cend( void ) const { return const_iterator( &implBase ); }
        
        reverse_iterator rend( void ) { return reverse_iterator( this->begin() ); }
        const_reverse_iterator rend( void ) const { return const_reverse_iterator( this->begin() ); }
        const_reverse_iterator crend( void ) const { return const_reverse_iterator( this->begin() ); }
        
        // Return references to the first/last elements...
        reference front( void ) { return *(this->begin()); }
        const_reference front( void ) const { return *(this->begin()); }
        
        reference back( void ) { return *(--(this->end())); }
        const_reference back( void ) const { return *(--(this->end())); }
        
        // Remove the last/first element
        void pop_back( void )
        {
            // t will get removed
            Node *t = static_cast<Node*>( implBase.previous );
            
            // Update the previous/next stuff accordingly...
            implBase.previous = t->previous;
            t->previous->next = &implBase;
            delete t; // free the memory
            sz--;
        }
        void pop_front( void )
        { // Almost identical to above
            Node *t = static_cast<Node*>( implBase.next );
            implBase.next = t->next;
            t->next->previous = &implBase;
            delete t;
            sz--;
        }
        
        // Insert single elements at the beginning/end of the list
        // Update the previous/next pointers accordingly...
        void push_back( const value_type &val )
        {
            implBase.previous->next = new Node( val, implBase.previous, implBase );
            implBase.previous = implBase.previous->next;
            sz++;
        }
        void push_back( value_type &&val )
        {
            implBase.previous->next = new Node( std::move( val ), implBase.previous, &implBase );
            implBase.previous = implBase.previous->next;
            sz++;
        }
        
        void push_front( const value_type &val )
        {
            implBase.next->previous = new Node( val, implBase, implBase.next );
            implBase.next = implBase.next->previous;
            sz++;
        }
        void push_front( value_type &&val )
        {
            implBase.next->previous = new Node( std::move( val ), &implBase, implBase.next );
            implBase.next = implBase.next->previous;
            sz++;
        }
        
        // Assignment operators for lists
        list &operator=( const list &l ) { this->assign( l ); return *this; }
        list &operator=( list &&l ) { this->assign( std::move( l ) ); return *this; }
        
        void assign( const list &l ) { this->assign( l.begin(), l.end() ); }
        
        // Probably the fastest way to handle a move
        void assign( list &&l ) { this->swap( l ); };
        
        // Assign a sequence to a list
        template<class InputIterator>
        void assign( InputIterator begin, InputIterator end )
        {
            // Fill the space that is already allocated in the list
            auto rest = MKay::copy_until_full( begin, end,
                                            this->begin(), this->end() );
            InputIterator restBegin = rest.first;
            
            // If there is more to add to the list, insert() it at the end
            if( restBegin != end )
                this->insert( this->end(), rest.first, end );
            else
            {
                // If we did not use all the space erase() the excess elements
                iterator excessBegin = rest.second;
                this->erase( excessBegin, this->end() );
            }
        }
        
        // Assign 'num' elements 'val' to the list
        // Essentially the same as the previous method
        template<class InputIterator>
        void assign( size_type num, const value_type &val )
        {
            auto rest = MKay::copy_n_until_full( val, num,
                                            this->begin(), this->end() );
            size_type numRest = rest.first;
            
            if( numRest != 0 )
                this->insert( this->end(), numRest, val );
            else
            {
                iterator excessBegin = rest.second;
                this->erase( excessBegin, this->end() );
            }
        }
        
        // Insert an element just before 'position'
        iterator insert( const_iterator position, const value_type &val )
        {
            impl::listNodeBase *pos = position.current;
            pos->previous->next = new Node( val, pos->previous, pos );
            pos->previous = pos->previous->next;
            sz++;
            
            // Return an iterator to the inserted element
            // Note that since we const_casted away the constness of
            // the listNodeBase pointer in the iterator class, we don't
            // need to care about const_iterator to iterator
            // (pos-1 to return value) issues here. Neat! (Lucky)
            return iterator( pos->previous );
        }
        
        // The same with a move...
        iterator insert( const_iterator position, value_type &&val )
        {
            impl::listNodeBase *pos = position.current;
            pos->previous->next = new Node( std::move( val ), pos->previous, pos );
            pos->previous = pos->previous->next;
            sz++;
            
            return iterator( pos->previous );
        }
        
        // Insert a number of elements just before 'position'
        iterator insert( const_iterator position, size_type n, const value_type &val )
        {
            sz += n; // Increase the size of our list
            impl::listNodeBase *prev = std::prev( position ).current;
            // Store the position of the preceeding element
            // (Needed for return value)
            
            // Populate the list...
            impl::listNodeBase *pos = position.current;
            impl::listNodeBase **nextToPopulate = &(pos->previous->next);
            impl::listNodeBase *last = pos->previous;
            
            while( n-- != 0 )
            {
                *nextToPopulate = new Node( val, last, pos );
                last = *nextToPopulate;
                nextToPopulate = &(last->next);
            };
            
            last->next->previous = last;
            
            // Return an iterator to the first element that was inserted
            // (or 'position' if n was 0)
            return iterator( prev->next );
        }
        
        // The same as above with a sequence...
        template<class InputIterator>
        iterator insert( const_iterator position, InputIterator begin, InputIterator end )
        {
            impl::listNodeBase *prev = std::prev( position ).current;
            
            impl::listNodeBase *pos = position.current;
            impl::listNodeBase **nextToPopulate = &(pos->previous->next);
            impl::listNodeBase *last = pos->previous;
            
            while( begin != end )
            {
                *nextToPopulate = new Node( *begin, last, pos );
                last = *nextToPopulate;
                nextToPopulate = &(last->next);
                
                ++begin;
                sz++;
            }
            
            last->next->previous = last;
            return iterator( prev->next );
        }
        
        // Erase the element at 'position'
        iterator erase( const_iterator position )
        {
            Node *t = static_cast<Node*>( position.current );
            t->previous->next = t->next;
            t->next->previous = t->previous;
            
            iterator it( t->next );
            delete t;
            
            sz--; // Decrease the size of the list
            // Return an iterator to the element
            // that comes after the deleted one
            return it;
        }
        
        // Erase a range and return an iterator to the element
        // that comes after the last deleted one (last as non-const iterator)
        iterator erase( const_iterator first, const_iterator last )
        {
            while( first != last )
                first = this->erase( first );
            
            return iterator( last.current );
        }
        
        // Resize the list
        void resize( size_type nsize )
        {
            if( sz == nsize ) // Nothing to do
                return;
            
            if( sz < nsize )
            {
                // Append a few elements to the list
                this->insert( this->end(), nsize-sz, value_type() );
                return;
            }
            
            // Remove a few elements from the list
            impl::listNodeBase *last = (--(this->end())).current;
            do
            {
                Node *t = static_cast<Node*>( last );
                last = last->previous;
                delete t;
                sz--;
            } while( sz > nsize );
            
            last->next = &implBase;
            implBase.previous = last;
        }
        
        // The same as above with a default value if the list needs
        // be enlarged
        void resize( size_type nsize, const value_type &val )
        {
            if( sz < nsize )
                this->insert( this->end(), nsize-sz, val );
            else
                // We don't need to append elements
                // The previous method knows what to do
                this->resize( nsize );
        }
        
        // Clearing is resisizng to 0...
        void clear( void ) { this->resize( 0 ); }
    };
    
    // Allow std::swap() to find our list through argument-dependent lookup
    template<typename Element>
    void swap( MKay::list<Element> &list1, MKay::list<Element> &list2 )
    { list1.swap( list2 ); }
}

#endif
