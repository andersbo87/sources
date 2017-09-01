
import java.util.Iterator;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author anders
 */
//public class ArrayList<T> implements MyIterator<T> 
public class ArrayList<T> implements Iterable<T>
{
    ArrayList list;//t = new ArrayList();
    Object[] elementData;
    public int length;
    public int indexOf(Object o)
    {
      if (o == null) {
                 for (int i = 0; i < size(); i++)
                     if (elementData[i]==null)
                         return i;
             } else {
                 for (int i = 0; i < size(); i++)
                     if (o.equals(elementData[i]))
                         return i;
             }
             return -1;
    }
    public void add(Object a, int i)
    {
        if(list == null)
            list = new ArrayList();
        list.add(null,i);
        list.add(a,i);
    }
    public void add(Object a)
    {
        if(list == null)
            list = new ArrayList();
        list.add(null);
        list.add(a);
    }
    @SuppressWarnings("unchecked")
    T elementData(int index) {
        return (T) elementData[index];
    }
    public T set(int i, T o)
    {
        T oldVal = elementData(i);
        elementData[i] = o;
        return oldVal;
    }
    public void insert(Object b, int index)
    {
        list.add(b);
    }

    public Object remove(int index)
    {
        Object c = get(index);
        list.remove(index);
        return c;
    }

    public MyVertex get(int index)
    {
        return (list.get(index));
    }

    public int size()
    {
        length = list.size();
        return length;
    }
    //private int i = list.length;
    
   
    
    //@Override
    /*public boolean hasNext()
    {
        return i > 0;
    }
  
    //@Override
    public int next()
    {
        return list.length-1;
    }*/
    
    @Override
    public Iterator<T> iterator() {
        return (Iterator<T>) new ArrayList();
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
  
}
class arrListIter<T> implements Iterator<T>
{
    
    ArrayList<T> list;
    private int i = list.length;
    @Override
    public boolean hasNext()
    {
        return i > 0;
    }
    public static <T> T convertInstanceOfObject(Object o, Class<T> clazz) {
    try {
        return clazz.cast(o);
    } catch(ClassCastException e) {
        return null;
    }
}
    @Override
    public T next()
    {
        return convertInstanceOfObject(list.length-1, (Class<T>) Integer.class);
        //return list.length-1;
    }
}
