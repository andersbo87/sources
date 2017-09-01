#include <cstdlib>
#include <iostream>

using namespace std;

template <typename Comparable>
class AVLTree
{
public:
    
    AVLTree() : root(NULL){}
    AVLTree(const AVLTree & rhs) : root(NULL)
    {
        *this = rhs;
    }
    ~AVLTree()
    {
        makeEmpty();
    }
    
    /**
     * Find the smallest item in the tree.
     */
    const Comparable & findMin() const
    {
        if(!isEmpty())
        {
            return findMin(root)->element;
        }
    }
    
    /**
     * Find the largest item in the tree.
     */
    const Comparable & findMax() const
    {
        if(!isEmpty())
        {
            return findMax(root)->element;
        }
    }
    
    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable & x) const
    {
        return contains(x, root);
    }
    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == NULL;
    }
    
    /**
     * Print the tree contents in sorted order.
     */
    void printTree() const
    {
        if(isEmpty())
        {
            cout << "Empty tree" << endl;
        }
        else
        {
            printTree(root);
        }
    }
    
    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }
    
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable & x )
    {
        insert(x,root);
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const Comparable & x)
    {
        remove(x,root);
    }
    
    /**
     * Deep copy.
     */
    const AVLTree & operator=(const AVLTree & rhs)
    {
        if( this != &rhs )
        {
            makeEmpty( );
            root = clone(rhs.root);
        }
        return *this;
    }
    
private:
    struct AVLNode
    {
        Comparable element;
        AVLNode* left;
        AVLNode* right;
        int height;
        
        AVLNode(const Comparable & theElement, AVLNode *lt,
                AVLNode *rt, int h = 0)
        : element(theElement), left(lt), right(rt), height(h) {}
    };
    
    AVLNode *root;
    
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable & x, AVLNode * & t)
    {
        if(t == NULL)
        {
            t = new AVLNode(x, NULL, NULL);
        }
        else if(x < t->element)
        {
            insert(x, t->left);
            if(height(t->left) - height(t->right) == 2)
                leftBalance(t);
            //	                if(x < t->left->element)
            //	                    rotateWithLeftChild(t);//LL rotate
            //	                else
            //	                    doubleWithLeftChild(t);//LR rotate
        }
        else if(t->element < x)
        {
            insert(x, t->right);
            if( height(t->right) - height(t->left) == 2)
                rightBalance(t);
            //	                if(t->right->element < x)
            //	                    rotateWithRightChild(t);//RR rotate
            //	                else
            //	                    doubleWithRightChild(t);//RL rotate
        }
        else
            ;  // Duplicate; do nothing
        t->height = max(height(t->left), height(t->right)) + 1;
    }
    
    /**
     * Internal method to remove in a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const Comparable & x, AVLNode * & t)
    {
        if(t == NULL)				//no such element
        {
            return;
        }
        else if(x < t->element)		//find in left subtree
        {
            remove(x, t->left);
            if(height(t->right) - height(t->left) == 2)
                rightBalance(t);
        }
        else if(t->element < x)		//find in right subtree
        {
            remove(x, t->right);
            if( height(t->left) - height(t->right) == 2)
                leftBalance(t);
        }
        else						//delete node *t?
        {
            if(t->left == NULL)
            {
                AVLNode* q = t;
                t = t->right;
                delete q;
            }
            else if(t->right == NULL)
            {
                AVLNode* q = t;
                t = t->left;
                delete q;
            }
            else
            {
                t->element = findMax(t->left)->element;
                remove(t->element,t->left);
                //t->element = findMin(t->right)->element;
                //remove(t->element,t->right);
            }
        }
        if(t)
            t->height = max(height(t->left), height(t->right)) + 1;
    }
	
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AVLNode * findMin(AVLNode *t) const
    {
        if(t == NULL)
            return NULL;
        if(t->left == NULL)
            return t;
        return findMin(t->left);
    }
	
    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AVLNode * findMax(AVLNode *t) const
    {
        if(t != NULL)
            while(t->right != NULL)
                t = t->right;
        return t;
    }
	
	
    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains(const Comparable & x, AVLNode *t) const
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
    /****** NONRECURSIVE VERSION*************************
     bool contains( const Comparable & x, AVLNode *t ) const
     {
     while( t != NULL )
     if( x < t->element )
     t = t->left;
     else if( t->element < x )
     t = t->right;
     else
     return true;    // Match
     
     return false;   // No match
     }
     *****************************************************/
	
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AVLNode * & t)
    {
        if(t != NULL)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = NULL;
    }
	
    void preOrder(AVLNode *t)const
    {
        if(t)
        {
            cout<<t->element<<" ";
            preOrder(t->left);
            preOrder(t->right);
        }
    }
    
    void inOrder(AVLNode *t)const
    {
        if(t)
        {
            inOrder(t->left);
            cout<<t->element<<" ";
            inOrder(t->right);
        }
    }
    
    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree(AVLNode *t) const
    {
        if(t)
        {
            cout<<"preOrder: "<<endl;
            preOrder(t);
            cout<<endl;
            cout<<"inOrder: "<<endl;
            inOrder(t);
            cout<<endl;
        }
    }
	
    /**
     * Internal method to clone subtree.
     */
    AVLNode * clone(AVLNode *t) const
    {
        if( t == NULL )
            return NULL;
        else
            return new AVLNode(t->element, clone(t->left), clone(t->right), t->height );
    }
    // Avl manipulations
    /**
     * Return the height of node t or -1 if NULL.
     * since the height of a tree with single node is 0
     */
    int height(AVLNode *t) const
    {
        return t == NULL ? -1 : t->height;
    }
	
    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }
	
    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1-LL.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AVLNode * & k2)
    {
        AVLNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max( height(k1->left), k2->height) + 1;
        k2 = k1;
    }
	
    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4-RR.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AVLNode * & k1)
    {
        AVLNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }
	
    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2-LR.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AVLNode * & k3)
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }
	void print(AVLNode *root)
	{
		structure(root, 0);
	}
    void padding(char ch, int n)
	{
		int i;
		for(i = 0; i<n; i++)
		{
			putchar(ch);
		}
	}
	void structure(AVLNode *root, int level)
	{
		if(root == 0x0)
		{
			padding('\t', level);
			puts("~");
		}
		else
		{
			structure(root->right, level+1);
			padding('\t', level);
			fprintf(stdout,"%c\n", (char)root->val);
			structure(root->left,level+1);
		}
	}
    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3-RL.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AVLNode * & k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
    
    /**
     * left balance the subtree with root t
     * this method can use for both insert and delete
     */
    void leftBalance(AVLNode *& t)
    {
        AVLNode* lc = t->left;
        if(height(lc->left) - height(lc->right) == -1)
        {
            doubleWithLeftChild(t);			//LR rotate
        }
        else
        {
            rotateWithLeftChild(t);			//LL rotate
        }
    }
    
    /**
     * right balance the subtree with root t
     * this method can use for both insert and delete
     */
    void rightBalance(AVLNode *& t)
    {
        AVLNode* rc = t->right;
        if(height(rc->left) - height(rc->right) == 1)
        {
            doubleWithRightChild(t);		//RL rotate
        }
        else
        {
            rotateWithRightChild(t);		//RR rotate
        }
    }
};

int main(int argc, char *argv[])
{
	const int N = 20;
	AVLTree<int> t;
	
	//insert
	for(int i=0; i<N; i++)
	{
		t.insert(i);
	}
	cout<<"after insert:"<<endl;
	
	cout<<endl<<endl;
	t.print();
	//remove
	for(int i=1; i<N; i += 2)
	{
		t.remove(i);	
	}
	cout<<"after remove:"<<endl;
	t.printTree();
	cout<<endl<<endl;
	
	t.makeEmpty();
	
    system("PAUSE");
    return EXIT_SUCCESS;
}
