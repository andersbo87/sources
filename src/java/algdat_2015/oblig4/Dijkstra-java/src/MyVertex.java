
import java.util.Iterator;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author andersbo
 */
public class MyVertex//<T> implements Iterable<T>{
{  private int value;

  private ArrayList<Edge> adjacentVertices;
  private ArrayList<MyVertex> heap;
  //int adjLen = adjacentVertices.length;

  private MyVertex predecessor;

  private int distance;

  public MyVertex(int value) {
    this.value = value;
    adjacentVertices = new ArrayList<>();
  }

  public int getValue() {
    return value;
  }

  public ArrayList<Edge> getAdjacentVertices() {
    return adjacentVertices;
  }

  public void addAdjacentVertex(Edge adjacentVertex) {
    adjacentVertices.add(adjacentVertex);
  }

  public void setPredecessor(MyVertex vertex) {
    predecessor = vertex;
  }

  public MyVertex getPredecessor() {
    return predecessor;
  }

  public void setDistance(int distance) {
    this.distance = distance;
  }

  public int getDistance() {
    return distance;
  }

  @Override
  public int hashCode() {
    int result = 17;
    result = 31 * result + value;
    return result;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj) {
      return true;
    } else if (obj == null) {
      return false;
    } else if (!(obj instanceof MyVertex)) {
      return false;
    } else {
      MyVertex other = (MyVertex) obj;

      if (value != other.value) {
        return false;
      }
    }
    return true;
  }

  @Override
  public String toString() {
    return "(value:" + value + "; distance:" + distance + ")";
  }
  
  
  //@Override
  public boolean hasNext()
  {
      int i = heap.length;
      return i > 0;
  }
  
  /*@Override
  public MyIterator iterator()
  {
      //return new Edge<T>(target,weight);
      return new MyVertex<T>(value);
  }*/
  
  //@Override
  public int next()
  {
      return heap.length-1;
  }
  
  //@Override
  public void remove()
  {
      throw new UnsupportedOperationException("Ikke implementert.\n");
  }

    /*@Override
    public Iterator<T> iterator() {
        return (Iterator<T>) new MyVertex(value);
        //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }*/
} 
