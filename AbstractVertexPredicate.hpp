
#ifndef ABSTRACT_VERTEX_PREDICATE_HPP
#define ABSTRACT_VERTEX_PREDICATE_HPP


/**
 * This is the abstract base class for any predicate which operates on 
 * vertices of a graph.
 */
class AbstractVertexPredicate
{
public:
	/// Returns value of this predicate, for graph vertex 'u'.
	virtual double operator()( int u ) const = 0;
};


#endif // ABSTRACT_VERTEX_PREDICATE_HPP
