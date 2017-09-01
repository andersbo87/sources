/*
 * assignment08Main.cpp
 *
 *  Created on: Mar 13, 2012
 *      Author: andersbo
 */

#include <iostream>
#include <queue>
#include <stdlib.h>
#include <list>
using namespace std;
class TreeNode
{
public:
	int val;
	int h; //height
	int bf; //balansefaktor
    int level;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
    
	//r i setBalance er rota til treet.
    
	
	TreeNode(int v, TreeNode *left, TreeNode *right)
	{
		val = v;
		left = this->left;
		right = this->right;
		this->level = 0;
	}
	~TreeNode() //destrukt�r
	{
		if(left)
		{
			delete left;
		}
		if(right)
		{
			delete right;
		}
	}; //slutt destrukt�r
};
class Bst
{
public:
    int val;
	int h; //height
	int bf; //balansefaktor
    int level;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	TreeNode *root;
    int height(TreeNode *root)
	{
		if(root == 0x0)
		{
			return -1;
		}
		/*if(root->left == 0x0)
         {
         fprintf(stderr, "\nroot->left is null.\n");
         return -1;
         }
         if(root->right == 0x0)
         {
         fprintf(stderr, "\nroot->right is null.\n");
         return -1;
         }*/
		int leftSize = height(root->left);
		int rightSize = height(root->right);
		if(leftSize > rightSize)
		{
			return leftSize + 1;
		}
		else
		{
			return rightSize + 1;
		}
	}
    int setBalance(TreeNode *r)
	{
		if(r == 0x0)
		{
			return 0x0;
		}
		//r->bf = height(r->right) - height(r->left);
		int l = height(r->left);
		int h = height(r->right);
		if(l<h)
		{
			bf = l - h;
			return bf;// = l - h;
		}
		else
		{
			bf = h - l;
			return bf;// = h - l;
		}
	}
    int l;
    int r;
	//updates and then returns the balance factor of TreeNode *r
	int getBalance(TreeNode *root)
	{
        bf=0;
        l=0;
        r=0;
        if(root == 0x0)
        {
            fprintf(stderr, "This tree does not exist.\n");
            return -100;
        }
        char navn = (char)root->val;
        printf("%c\n", root->val);
        /*if(root->left == 0x0)
        {
            //printf("%c (%d) sitt venstrebarn er null.\n", navn, root->val);
        }
        else
        {
          //  printf("%c sitt venstrebarn er %c\n", root->val, root->left->val);
            l++;
            getBalance(root->left);
            
        }*/
        while(root->left != 0x0)
        {
            root = root->left;
            l++;
        }
        //printf("Left: %d\n", l);
        /*while(root->left != 0x0)
         {
         root = root->left;
         l++;
         fprintf(stdout, "Left: %d\n", l);
         }*/
        while(root->right != 0x0)
         {
         root = root->right;
         r++;
         //fprintf(stdout, "Right: %d\n", r);
         }
        //printf("Right: %d\n", r);
        printf("%d - %d\n",l,r);
        bf=l-r;
        fprintf(stdout, "Balansefaktoren for node %c er %d.\n", navn, bf);
        //return newBalance;
		//return setBalance(r);
        return bf;
	}
    
    /*If the balance factor of a given node is <= -2 or >= 2, the tree must be rebalanced.*/
    void rebalanceTree(TreeNode *root)
    {
        fprintf(stdout, "I ferd med å rebalansere treet...\n");
        int balance;
        if(root->right != 0x0)
        {
            balance = getBalance(root);
            if(balance == -1)
            {
                //rotateLeftRight(root);
                fprintf(stdout,"Going to execute a right-left rotation.\n");
                rotateRightLeft(root);
            }
            else
            {
                fprintf(stdout, "Going to execute a right rotation.\n");
                rotateRight(root);
            }
        }
        if(root->left != 0x0)
        {
            balance = getBalance(root);
            if(balance == 2 || balance == 1)
            {
                fprintf(stdout, "Going to execute a left-right rotation.\n");
                rotateLeftRight(root);
            }
            else
            {
                fprintf(stdout, "Going to execute a left rotation.\n");
                rotateLeft(root);
            }
        }
        //return root;
    }
    TreeNode *rotatedRoot;
    TreeNode *rotateRight(TreeNode *root)
    {
        fprintf(stdout, "Høyrerotering for %c.\n", (char)root->val);
        TreeNode *tmp;
        tmp = root->right;
        printf("tmp = root->right");
        root->right = tmp->left;
        tmp->left = root;
        root = tmp;
        rotatedRoot = tmp;
        print(root);
        fprintf(stdout, "Ferdig med høyrerotasjon.\n");
        return rotatedRoot;
    }
    void rotateRightLeft(TreeNode *root)
    {
        fprintf(stdout, "Høyre-høyre.\n");
        rotateRight(root);
        rotateLeft(root);
    }
    
    void rotateLeft(TreeNode *root)
    {
        fprintf(stdout, "Venstre.\n");
        TreeNode *tmp;
        fprintf(stdout, "So far so good...\n");
        tmp = root->left;
        fprintf(stdout, "tmp = root->left;\n");
        root->left = tmp->right;
        fprintf(stdout,"root->left = tmp->right;\n");
        tmp->right = root;
        fprintf(stdout, "tmp->right = root;\n");
        root = tmp;
        fprintf(stdout, "Ferdig.\n");
    }
    
    void rotateLeftRight(TreeNode *root)
    {
        fprintf(stdout, "Venstre-høyre.\n");
        rotateLeft(root);
        rotateRight(root);
    }
    void checkBalance(TreeNode *root)
    {
        fprintf(stdout, "OK.\n");
        int res = bf;
        fprintf(stdout, "Balansefaktor ved node %c (%d) er %d.\n", (char)root->val, root->val, res);
        if(res <= -2 || res >= 2)
        {
            fprintf(stdout, "Treet må rebalanseres.\n");
            rebalanceTree(root);
        }
    }
    
	int treeHeight(TreeNode *root)
    {
        int leftSize = 1, rightSize = 1;
        if(root == 0x0)
        {
            return 0x0;
        }
        while(root->left != 0x0)
        {
            leftSize++;
            root=root->left;
        }
        while(root->right != 0x0)
        {
            rightSize++;
            root=root->right;
        }
        if(leftSize > rightSize)
        {
            return leftSize +1;
        }
        else
        {
            return rightSize +1;
        }
    }
	void print(TreeNode *root)
	{
		structure(root, 0);
	}
    
	void printOut()
	{
		fprintf(stdout,"Preorder:\n");
		preOrder(root);
		fprintf(stdout,"Inorder:\n");
		inOrder(root);
		fprintf(stdout,"Postorder:\n");
		postOrder(root);
		fprintf(stdout, "Levelorder:\n");
		levelOrder(root);
	}
    
    
	//Drivermetoder.
	void preOrder()
	{
		preOrder(root);
	}
	void inOrder() //Drivermetoden til oppgave 1B
	{
		inOrder(root);
	}
    void postOrder() //Drivermetode til oppgave 1B
	{
		postOrder(root);
	}
	void levelOrder() //Drivermetode til oppgave 1C
	{
		levelOrder(root);
	}
    
	void levelOrderPrintLevel()
	{
		levelOrderPrintLevel(root); //Drivermetode til oppgave 1D
	}
    
	/*
	 * begynte p� oppgave 2c, men fant relativt fort ut at jeg ikke kom til � klare den.
	 * f�lgelig blir ikke denne metoden kalt i l�pet av programeksekveringa.
	 * dette er hva jeg har f�tt til.
	 */
	/*void remove(TreeNode *p, int val)
	{
        if(root == 0x0)
	    {
            return;
	    }
        fprintf(stdout, "Finito.\n");
	}*/
    /*void insert(TreeNode *n, TreeNode *root)
     {
     if(root == 0x0)
     {
     root = n;
     return;
     }
     TreeNode *curr = root;
     while(1)
     {
     if(n->val < curr->val)
     {
     fprintf(stdout, "n->val < curr->val\n");
     if(curr->left == 0x0)
     {
     curr->left = n;
     fprintf(stdout, "Oppdaterer balansefaktoren for subtreet med %c som rotnode (oppgave 2b)...\n", (char)curr->parent->val);
     root->setBalance(root);
     if(root->getBalance(root) == -2)
     {
     //ville her kalt funksjonen singleLeftRotation(TreeNode *root), men fikk den ikke helt til aa fungere som den skal.
     //singleRightRotation(curr->parent);
     }
     fprintf(stdout, "Balansefaktor etter innsettelse av %c: %d\n", char(n->val), curr->getBalance(root));
     return;
     }
     else
     {
     curr = curr->left;
     }
     }
     else
     {
     if(curr->right == 0x0)
     {
     curr->right = n;
     fprintf(stdout, "Oppdaterer balansefaktoren for subtreet med %c som rotnode (oppgave 2b)...\n", (char)curr->parent->val);
     root->setBalance(root);
     if(root->getBalance(root) == -2)
     {
     //Do something
     if(root->parent->val != 0x0)
     {
     //ville her kalt funksjonen singleRightRotation(TreeNode *root), men fikk den ikke helt til aa fungere som den skal.
     //singleLeftRotation(curr->parent);
     }
     }
     fprintf(stdout, "Balansefaktor etter innsettelse av %c: %d\n", char(n->val), curr->getBalance(root));
     return;
     }
     else
     {
     curr = curr->right;
     }
     }
     }
     fprintf(stdout, "Balansefaktor etter innsettelse av %c: %d\n", char(n->val), root->getBalance(n));
     }
     */
    void insert(TreeNode* element, TreeNode* root)
    {
        if(root == 0x0)
        {
            return;
        }
        if(element->val < root->val)
        {
            if(root->left == NULL)
            {
                root->left = element;
                root->level++;
            }
            else
            {
                insert(element,root->left);
                if(root->left->level != 0)
                {
                    root->level++;
                }
            }
        }
        else
        {
            if(root->right == NULL)
            {
                root->right = element;
                root->level--;
            }
            else
            {
                insert(element, root->right);
                if(root->right->level != 0)
                {
                    root->level--;
                }
            }
        }
    }
    
	void mirror(TreeNode *root)
    {
        if(root == 0x0)
        {
            return;
        }
        TreeNode *tmp;
        mirror(root->left);
        mirror(root->right);
        //bytte pekere
        tmp = root->right;
        root->right = root->left;
        root->left = tmp;
        
    }
    
private:
	void preOrder(TreeNode *n)
	{
		fprintf(stdout, "%c ", (char)n->val); //caster om til char for � skrive ut bokstaven istedenfor tallet bokstaven representerer. se "merknad" i main-metoden.
		if(n->left != 0x0)
		{
			preOrder(n->left);
		}
		if(n->right != 0x0)
		{
			preOrder(n->right);
		}
	}
    
	//oppgave 1B
	void inOrder(TreeNode *n)
	{
		if(n->left != 0x0)
		{
			inOrder(n->left);
		}
		fprintf(stdout, "%c ", (char)n->val); //caster om til char for � skrive ut bokstaven istedenfor tallet bokstaven representerer. se "merknad" i main-metoden.
		if(n->right != 0x0)
		{
			inOrder(n->right);
		}
	}
    
	//oppgave 1B
	void postOrder(TreeNode *n)
	{
		if(n->left != 0x0)
		{
			postOrder(n->left);
		}
		if(n->right != 0x0)
		{
			postOrder(n->right);
		}
		fprintf(stdout, "%c ", (char)n->val); //caster om til char for � skrive ut bokstaven istedenfor tallet bokstaven representerer. se "merknad" i main-metoden.
	}
    
	//oppgave 1C
	void levelOrder(TreeNode *root)
	{
		queue<TreeNode*> mq;
		mq.push(root);
		while(!mq.empty())
		{
			TreeNode *n = mq.front();
			if(n == 0x0)
			{
				fprintf(stderr, "n is null.\n");
			}
			fprintf(stdout, "%c ", (char)n->val); //caster om til char for � skrive ut bokstaven istedenfor tallet bokstaven representerer. se "merknad" i main-metoden.
			if(n->left != 0x0)
			{
				mq.push(n->left);
			}
			if(n->right != 0x0)
			{
				mq.push(n->right);
			}
			mq.pop();
		}
	}
    
	//oppgave 1D
	void levelOrderPrintLevel(TreeNode *root)
	{
		int level = 0;
		int prints = 0;
		if (!root)
			return;
		queue<TreeNode*> currentLevel, nextLevel;
		currentLevel.push(root);
		while (!currentLevel.empty())
		{
			TreeNode *currNode = currentLevel.front();
			currentLevel.pop();
			if (currNode)
			{
				if(prints == 0) //sjekker om prints (antall niv�utskrifter) er 0. dette for � hindre level x i � bli skrevet ut for hver gang while-l�kka kj�res.
				{
					fprintf(stdout, "\nLevel %d: ", level);
				}
				fprintf(stdout, "%c ", (char)currNode->val); //skriver ut bokstavverdien til gjeldende node.
				prints++; //�ker verdien til prints slik at "Level X" ikke skrives ut igjen f�r gjeldende k� er tom.
				nextLevel.push(currNode->left);
				nextLevel.push(currNode->right);
			}
			if (currentLevel.empty()) //hvis gjeldende k� er tom.
			{
				//fprintf(stdout, "\n"); //flytter mark�ren i konsollen til en ny linje. Tilsvarer System.out.println(); i Java.
				level++;
				prints = 0; //resetter prints, slik at level eventuelt kan skrives ut med ny verdi
				swap(currentLevel, nextLevel); //bytter k�en p� gjeldende niv� med k�en p� neste niv�.
			}
		}
	}
    
	//oppgave 2A
	void padding(char ch, int n)
	{
		int i;
		for(i = 0; i<n; i++)
		{
			putchar(ch);
		}
	}
	void structure(TreeNode *root, int level)
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
    
    
};
int main(void)
{
	Bst *bst = new Bst();
	/*
	 * caster om hvert enkelt element som settes inn i treet til et heltall.
	 * dette var for � pr�ve � l�se oppgave 2D, hvilket jeg ikke fikk til:
	 * void remove(TreeNode* p, int v)
	 * siden jeg f�rst hadde gjort disse endringene (byttet ut string v i klassen TreeNode med int v),
	 * valgte jeg � beholde klassene som de er n� og kaste frem og tilbake der det er "n�dvendig."
	 */
	TreeNode *rt = new TreeNode((int)'E', 0x0,0x0);
	TreeNode *l = new TreeNode((int)'C',0x0,0x0);
	TreeNode *r = new TreeNode((int)'F',0x0,0x0);
	TreeNode *ll = new TreeNode((int)'D', 0x0,0x0);
	TreeNode *lr = new TreeNode((int)'B', 0x0,0x0);
	TreeNode *rr = new TreeNode((int)'M', 0x0,0x0);
	TreeNode *i = new TreeNode((int)'T', 0x0,0x0);//brukes som argument til insert (oppgave 2c)
	bst->root = rt;
    fprintf(stdout, "Setter inn node i (oppgave 2C)\n");
    bst->insert(l, rt);
    bst->insert(r, rt);
    bst->insert(ll, l);
    bst->insert(lr, l);
    bst->insert(rr, r);
	bst->insert(i, rr);
	fprintf(stdout, "Pre-Order (fra timen):\n");
	bst->preOrder();
	fprintf(stdout, "\nIn-Order (Sett 7, oppgave 1b):\n");
	bst->inOrder();
	fprintf(stdout, "\nPost-Order (Sett 7, oppgave 1b)\n");
	bst->postOrder();
	fprintf(stdout, "\nLevel-Order (Sett 7, oppgave 1c):\n");
	bst->levelOrder();
	fprintf(stdout, "\nLevel-Order med nivaaer (Sett 7, oppgave 1d):");
	bst->levelOrderPrintLevel();
	fprintf(stdout, "\n");
    fprintf(stdout, "Treets høyde: %d\n", bst->treeHeight(rt));
    fprintf(stdout, "Sjekker balansefaktor ved node F (%d)...\n", r->val);
    bst->getBalance(rt);
	//fprintf(stdout, "\nLevels: %d\n", bst->height(rt));
	/*
	 * Ville her ha kalt p� metoden bst->remove(TreeNode *tn, int v)
	 * metoden lot seg kj�re som den skulle, men da jeg kalte p�
	 * enten preOrder, inOrder, postOrder eller levelOrder,
	 * etter � ha kj�rt remove, oppsto det en s�kalt
	 * "segmentation violation" - programmet pr�vde � aksessere
	 * minne det ikke hadde tilgang til. F�lgelig feilet programmet.
	 */
	//oppgave 2C
	//bst->insert(new TreeNode((int)'I', 0x0,0x0), bst->root);
	
	//fprintf(stdout, "Balansefaktor etter innsetting av alle noder: %d\n", r->getBalance(i));
	fprintf(stdout, "\nPrinter treet, rotert 90 grader (oppgave 2A)...\n");
	bst->print(rt);
    bst->mirror(rt);
	fprintf(stdout, "\nPrinter speilvendt utgave av treet, rotert 90 grader (oppgave 3)\n");
	bst->print(rt);
    return 0;
}


