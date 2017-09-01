
import java.util.Iterator;



/**
 *
 * @author andersbo
 */
public class Edge<T>// implements Iterable<T>// implements MyIterator<Integer>  
{  
    private MyVertex target;
  private int weight;

  public Edge(MyVertex target, int weight) {
    this.target = target;
    this.weight = weight;
  }

  public MyVertex getTarget() {
    return target;
  }

  public int getWeight() {
    return weight;
  }

  @Override
  public int hashCode() {
    int result = 17;
    result = 31 * result + weight;
    return result;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj) {
      return true;
    } else if (obj == null) {
      return false;
    } else if (!(obj instanceof Edge)) {
      return false;
    } else {
      Edge edge = (Edge) obj;

      if (weight != edge.getWeight()) {
        return false;
      }
    }
    return true;
  }
    ArrayList<Edge> arr;
  @Override
  public String toString() {
    return "(target:" + target.getValue() + "; weight:" + weight + ")";
  }
  private int i = arr.length;
  //@Override
  public boolean hasNext()
  {
      return i > 0;
  }
  
  /*@Override
  public MyIterator iterator()
  {
      return new Edge<T>(target,weight);
  }*/
  /*
  //@Override
  public int next()
  {
      return arr.length-1;
  }
  
  //@Override
  public void remove()
  {
      throw new UnsupportedOperationException("Ikke implementert.\n");
  }

    @Override
    public Iterator<T> iterator() {
        return (Iterator<T>) new Edge(target,weight);
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }*/
} 
