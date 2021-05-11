#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// SEE UPDATE COMMENTS AT END OF FILE
// 2006-01.29 fixed memory leaks

// eliminate need to qualify standard library with std::
using namespace std;

// ===============================================================
// C++ NEEDS SOME DECLARATIONS BEFORE THE MAIN RedBlackTree class.
// skip down a little to line this up with the other side
// ===============================================================
// requires forward declaration to resolve cycle between NodeVisitor and RedBlackTree
template<class T> class RedBlackTree;

// use an abstract class for the node visitor. it is templatized to match the templated RedBlackTree declaration
template<class T> class NodeVisitor {
public:
	// need a virtual destructor for the concrete classes
	virtual ~NodeVisitor() {}

	// ise a pure virtual function so a concrete class must implement
	// the proper signature
    virtual void visit(const RedBlackTree<T> *node,int depth) = 0;
};

// =============================================
// >>>>>>>>>>>>>>>>> RED BLACK TREE STARTS HERE
// =============================================
// in line with the STL conventions, this template uses 'by-value' semantics for the contained
// object. This means that the 'T' object will need to have the correct constructor and copy assignment
// semantics or it won't work. primitive types are OK but object instances would have to be
// put together correctly. 
template<class T> class RedBlackTree {
    
private:    
    /*
    Red/Black tree implementation based on 
    Algorithms in C++, Sedgewick
    Introduction To Algorithms Cormen, Thomas H. / Leiserson, Charl es E . / Rivest, Ronald L . The MIT Press 07/1990
    NOTE : LOOK AT END OF FILE TO SEE DIFFERENCES IN TRAVERSAL IDIOMS    
    */
    
	// yes, i could use an enum but since i want to print the values, using an enum is more
	// trouble than it is worth.
    static const int red   = 0;
    static const int black = 1;

	// use a common instance variable naming convention 'm_'. others use a single leading '_'
    int               m_color;
    T                 m_val;
    RedBlackTree      *m_left;
    RedBlackTree     *m_right;

    RedBlackTree(RedBlackTree *b) {
        m_val      = b->m_val;
        m_left     = b->m_left;
        m_right    = b->m_right;
        m_color    = red;
    }

    void copy(RedBlackTree *x) {
        m_val     = x->m_val;
        m_left    = x->m_left;
        m_right   = x->m_right;
		m_color   = x->m_color;

		// UPDATE 2006-01-28
		// node pointed to by 'x' is no longer needed, delete it. 
		// first make sure the delete won't descend into other nodes
		x->m_left  = 0;
		x->m_right = 0;
		delete x;
	}
    
    RedBlackTree *RBinsertLeft(T k,int sw) {
        RedBlackTree *l;
        RedBlackTree *b;
        
        l = m_left;
        if (l == 0) {
            m_left = b = new RedBlackTree(k);
        }
        else {
            b = l->RBinsert(k,sw);
        }
        return b;
    }
        
    RedBlackTree *RBinsertRight(T k,int sw) {
        RedBlackTree *r;
        RedBlackTree *b;
        
        r = m_right;
        if (r == 0) {
            m_right = b = new RedBlackTree(k);
        }
        else {
            b = r->RBinsert(k,sw);
        }
        return b;
    }
    
    RedBlackTree *rotLeft()
    {
       RedBlackTree *x;
       RedBlackTree *me;

	   if (m_right == 0) return 0;
      // make the changes in a copy of current node __self
      // on return, the caller will copy in 'me' to current node
	   me          = new RedBlackTree(this);
       x           = me->m_right;
       me->m_right = x->m_left;
       x->m_left   = me;
       return   x;
    }

    RedBlackTree *rotRight()
    {
       RedBlackTree *x;
       RedBlackTree *me;

	   if (m_left == 0) return 0;

      // make the changes in a copy of current node __self
      // on return, the caller will copy in 'me' to current node
	   me          = new RedBlackTree(this);
       x           = me->m_left;
       me->m_left  = x->m_right;
       x->m_right  = me;
       return x;
    }

    RedBlackTree *RBinsert(T k,int sw) {
        RedBlackTree *b = 0;
        RedBlackTree *x;
        RedBlackTree *l;
        RedBlackTree *ll;
        RedBlackTree *r;
        RedBlackTree *rr;
        
        // if current node is a 4 node, split it by flipping its colors
        // if both children of this node are red, change this one to red
        // and the children to black
        l = m_left;
        r = m_right;
        if ((l != 0)&&(l->m_color==red)&&(r != 0)&&(r->m_color==red)) {
            m_color = red;
            l->m_color = black;
            r->m_color = black;
        }
        
        // go left or right depending on key relationship
        if (k < m_val) {
            // recursively insert
            b = RBinsertLeft(k,0);
            
            // on the way back up check if a rotation is needed
            // if search path has two red links with same orientation
            // do a single rotation and flip the color bits
            l = m_left;
            if ((m_color == red)&&(l != 0)&&(l->m_color == red)&&(sw == 1)) {
                x = rotRight();
        		if (x != 0) {
        		    // copy returned node to 'this'
        		    copy(x);
            	}
            }
            
            // flip the color bits
            l = m_left;
            if (l != 0) {
                ll = l->m_left;
                if (ll != 0) {
                    if ((l->m_color == red)&&(ll->m_color == red)) {
                        x = rotRight();
                		if (x != 0) {
                		    copy(x);
                    	}
                        m_color = black;
                        r = m_right;
                        if (r != 0) {
                           r->m_color = red;
                        }
                    }
                }
            }
        }
        else {
            b = RBinsertRight(k,1);
            
            // on the way back up check if a rotation is needed
            // if search path has two red links with same orientation
            // do a single rotation and flip the color bits
            r = m_right;
            if ((m_color == red)&&(r != 0)&&(r->m_color == red)&&(sw == 0)) {
                x = rotLeft();
        		if (x != 0) {
        		    // copy returned node to 'this'
        		    copy(x);
            	}
            }
            
            // flip the color bits
            r = m_right;
            if (r != 0) {
                rr = r->m_right;
                if (rr != 0) {
                    if ((r->m_color == red)&&(rr->m_color == red)) {
                        x = rotLeft();
                		if (x != 0) {
                		    // copy returned node to 'this'
                		    copy(x);
                    	}
                        m_color = black;
                        l = m_left;
                        if (l != 0) {
                           l->m_color = red;
                        }
                    }
                }
            }
        }            
        
        return b;
    }
	
// ==================================================
// PUBLIC METHODS
// ==================================================
public:
	// construct with an initial value
    RedBlackTree(T x) {
        m_val      = x;
        m_left     = 0;
        m_right    = 0;
        m_color    = red;
    }

	~RedBlackTree() {

		if (m_left != 0) {
			delete m_left;
		}
		if (m_right != 0) {
			delete m_right;
		}
	}

	// return a string representation 
	string str() const {
		stringstream s(stringstream::out);
        // m_val (type T) must have the proper ostream insertion operator
		// or this implementation won't work
        s << "[" << m_val << "," << m_color << "]";
        return s.str();
    }
    
	// 'const' means this method doesn't change the object state
    T val() const {
        return m_val;
    }
    
	// 'const' means this method doesn't change the object state
    int color() const {
        return m_color;
    }

	// 'const' means this method doesn't change the object state
	// and it returns a pointer to a const node that the caller
	// cannot change, only inspect
	const RedBlackTree *find(const T &key) const {
        const RedBlackTree *result = 0;
        if (key == m_val) {
            result = this;
        }
        else if (key < m_val) {
            if (m_left != 0) {
                result = m_left->find(key);
            }
        }
        else {
            if (m_right != 0) {
                result = m_right->find(key);
            }
        }
        return result;
	}
    
	// 'const' means this method doesn't change the object state
	// and the visitor is not allowed to change the object state.
	// that may not be what is desired but is used here to 
	// illustrate something you can do in C++ that you can't do
	// in the other languages and that illustrates the bias towards
	// extensive static type checking
    void inorder(NodeVisitor<T> *visitor,int depth) const {
        if (m_left != 0) {
            m_left->inorder(visitor,depth+1);
        }
        visitor->visit(this,depth);
        if (m_right != 0) {
            m_right->inorder(visitor,depth+1);
        }
    }
    
    RedBlackTree *insert(T k) {
        RedBlackTree *b;
        b = RBinsert(k,0);
        m_color = black;
        return b;
    }
};

// define a concrete class for the node visitor
class IntNodeVisitor : public NodeVisitor<int> {
public:
	virtual ~IntNodeVisitor() {}

	// the node is 'const' so the visitor can't change it, only look at it
    virtual void visit(const RedBlackTree<int> *node,int depth) {
        if (node->val() != 0) {
            cout << "(" << node->val() << ":" << node->color() << ":" << depth << "), ";
        }
    }
};

// ==================================
// test program
// ==================================
int main(int argc,char *argv[]) {
    int nodelist[] = {11,4,8,14,17,6,9,7,16,15,13,5,19,18,12,10,3,20,1};
    NodeVisitor<int> *v;
    
    // insert all the data into the tree
    RedBlackTree<int> *root = new RedBlackTree<int>(2);

	// need to do an ugly calculation to figure out length of the nodelist array
	// if i used a collection object instead of an array, then I couldn't have
	// done static initialization. so its a tradeoff
    for(int i=0;i<(sizeof(nodelist)/sizeof(nodelist[0]));i++) {
        root->insert(nodelist[i]);
    }
    
    // anonymous class implementing the NodeVisitor interface
    v = new IntNodeVisitor;
    
	// print the header
    cout << "C++      = ";    
	// visit all the nodes in order
    root->inorder(v,0);
	// print a newline
    cout << endl;
    
	// find the specified element and print its value
    const RedBlackTree<int> *x = root->find(16);
    cout << x->str() << endl;
    
    // no garbage collection, need to explicitly delete
    delete root; // will recursively delete all the nodes
    delete v;
}
 

// ===================================================================
// UPDATE 2006-01-29
// there are memory leaks that need to be fixed. 
// 1. the algorithm leaks nodes after a rotate
//	two possible fixes : 
//	find where the leaks occur and do the needed deletes 
//		in this case the 'copy' method handles  
//              deleting unused nodes
//      use an appropriate smart pointer to handle deleteing
// 2. the tree is not properly disposed of when the program completes
//     In the STL tradition a delete of the tree should
//     delete all tree resources but not the contained data. the application
//     should handle deleting the contained data elements, if needed, prior
//     to deleting the tree. In this case a recursive delete of the 
//     nodes works gets rid of the tree resources
//
// these issue show that one of the big difficulties in C++ is to 
// handle disposing of data after you are done with it. that is indeed a
// source of many C++ program errors of the type that are related more to
// dealing with the complexity of the language rather than the solving 
// the problem. In this code the leaks are probably fixed but there is always
// a lingering doubt "Did I get all the leaks?"
// Thats a problem with C++, its hard to be certain.
//
// a modern approach is to use smart pointers to simulate garbage 
// collection. the Boost library referenced counted smart pointers
// will be included in the next standard revision of the C++ library
// so they are used here to handle all the cases.
// ===================================================================


