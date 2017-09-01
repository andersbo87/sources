public class linkList<T>
{
    class NNode
    {
	private NNode next, prev;
	private Integer key;
	public NNode()
	{
	    next = null;
	    prev = null;
	    key = null;
	}
	public NNode(int newKey)
	{
	    key = newKey;
	    next = null;
	    prev = null;
	}
	public NNode(int newKey, NNode newNext, NNode newPrev)
	{
	    key = newKey;
	    next = newNext;
	    prev = newPrev;
	}
	public Integer getKey()
	{
	    return key;
	}
	public NNode getNext()
	{
	    return next;
	}
	public NNode getPrev()
	{
	    return prev;
	}
	public void setKey(int newKey)
	{
	    key = newKey;
	}
	public void setNext(NNode newNext)
	{
	    next = newNext;
	}
	public void setPrev(NNode newPrev)
	{
	    prev = newPrev;
	}
    }
    NNode root, tail;
    public linkList()
    {
        root = null;
	tail = null;
    }

    public void insert(int x)
    {
	NNode newNode = new NNode(x);
	if(root == null){
	    // første element
	    root = newNode;
	    tail = newNode;
	}
	if(root.next == null)
	{
	    tail.next = newNode;
	    newNode.prev = tail;
	    tail = newNode;
	}
    }

    public void delete(NNode n)
    {
	if(n.prev != null)
	    n.prev.next = n.next;
	else
	    root = n.next;
	if(n.next != null)
	    n.next.prev = n.prev;
	else
	    tail = n.prev;
    }

    public NNode search(Integer key)
    {
	NNode x = root; // mulig jeg tar feil, men tipper at head i dette tilfellet er det samme som root.
	while(key != null && x.getKey() != null)
	    x = x.next;
	return x;
    }
}
